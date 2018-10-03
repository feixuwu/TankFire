/*
* uewebsocket - unreal engine 4 websocket plugin
*
* Copyright (C) 2017 feiwu <feixuwu@outlook.com>
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation:
*  version 2.1 of the License.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
*  MA  02110-1301  USA
*/

#include "WebSocket.h"
#include <iostream>
#include "WebSocketBase.h"

#if PLATFORM_UWP
#elif PLATFORM_HTML5
#elif PLATFORM_WINDOWS 
#include "PreWindowsApi.h"
#include "libwebsockets.h"
#include "PostWindowsApi.h" 
#else
#include "libwebsockets.h"
#endif

#define MAX_ECHO_PAYLOAD 64*1024

#if PLATFORM_UWP
using namespace concurrency;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Networking::Sockets;
using namespace Windows::Security::Cryptography::Certificates;
using namespace Windows::Storage::Streams;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Web;


FUWPSocketHelper::FUWPSocketHelper():Parent(0)
{

}

FUWPSocketHelper::~FUWPSocketHelper()
{
	Parent = 0;
}

void FUWPSocketHelper::SetParent(int64 p)
{
	Parent = p;
}

void FUWPSocketHelper::MessageReceived(Windows::Networking::Sockets::MessageWebSocket^ sender, Windows::Networking::Sockets::MessageWebSocketMessageReceivedEventArgs^ args)
{
	if (Parent != 0)
	{
		UWebSocketBase* p = (UWebSocketBase*)Parent;
		p->MessageReceived(sender, args);
	}
}

void FUWPSocketHelper::OnUWPClosed(Windows::Networking::Sockets::IWebSocket^ sender, Windows::Networking::Sockets::WebSocketClosedEventArgs^ args)
{
	if (Parent != 0)
	{
		UWebSocketBase* p = (UWebSocketBase*)Parent;
		p->OnUWPClosed(sender, args);
	}
}
#elif PLATFORM_HTML5

void FHtml5SocketHelper::Tick(float DeltaTime)
{
	if (mHostWebSocket == nullptr)
	{
		return;
	}

	if (mHostWebSocket->mIsError)
	{
		return;
	}

	if (mHostWebSocket->mWebSocketRef < 0)
	{
		return;
	}

	// check connect
	char szError[128] = { 0 };
	int checkError = SocketError(mHostWebSocket->mWebSocketRef, szError, (int)sizeof(szError) - 1);
	if ( (checkError == 0) && !mHostWebSocket->mConnectSuccess && SocketState(mHostWebSocket->mWebSocketRef) )
	{
		mHostWebSocket->mConnectSuccess = true;
		mHostWebSocket->OnConnectComplete.Broadcast();
	}
		
	if(checkError != 0)
	{
		mHostWebSocket->mIsError = true;

		if (!mHostWebSocket->mConnectSuccess)
		{
			FString strError = UTF8_TO_TCHAR(szError);
			mHostWebSocket->OnConnectError.Broadcast(strError);
		}
		else
		{
			mHostWebSocket->OnClosed.Broadcast();
		}

		return;
	}
	
	// check data receive
	int iRecvLen = SocketRecvLength(mHostWebSocket->mWebSocketRef);
	if (iRecvLen > 0)
	{
		char* pData = new char[iRecvLen + 1];
		SocketRecv(mHostWebSocket->mWebSocketRef, pData, iRecvLen);
		pData[iRecvLen] = (char)0;
		mHostWebSocket->ProcessRead((const char*)pData, (int)iRecvLen);
		delete[]pData;
	}
}

bool FHtml5SocketHelper::IsTickable() const
{
	return true;
}

TStatId FHtml5SocketHelper::GetStatId() const
{
	return TStatId();
}

#endif




UWebSocketBase::UWebSocketBase()
{
#if PLATFORM_UWP
	messageWebSocket = nullptr;
	uwpSocketHelper = ref new FUWPSocketHelper();
	uwpSocketHelper->SetParent( (int64)this);
#elif PLATFORM_HTML5
	mWebSocketRef = -1;
	mConnectSuccess = false;
	mIsError = false;
	
#else
	mlwsContext = nullptr;
	mlws = nullptr;
#endif
}


void UWebSocketBase::BeginDestroy()
{
	Super::BeginDestroy();

#if PLATFORM_UWP
	
	uwpSocketHelper->SetParent(0);
	uwpSocketHelper = nullptr;
	if (messageWebSocket != nullptr)
	{
		delete messageWebSocket;
		messageWebSocket = nullptr;
	}
#elif PLATFORM_HTML5
	mHtml5SocketHelper.UnBind();
#else
	if (mlws != nullptr)
	{
		lws_set_wsi_user(mlws, NULL);
		mlws = nullptr;
	}
#endif
}

#if PLATFORM_UWP

void UWebSocketBase::MessageReceived(Windows::Networking::Sockets::MessageWebSocket^ sender, Windows::Networking::Sockets::MessageWebSocketMessageReceivedEventArgs^ args)
{
	Windows::ApplicationModel::Core::CoreApplication::MainView->Dispatcher->RunAsync(
		Windows::UI::Core::CoreDispatcherPriority::Normal,
		ref new Windows::UI::Core::DispatchedHandler([this, args]()
	{
		DataReader^ reader = args->GetDataReader();
		reader->UnicodeEncoding = UnicodeEncoding::Utf8;
		try
		{
			String^ read = reader->ReadString(reader->UnconsumedBufferLength);
			FString strData(read->Data(), read->Length());
			OnReceiveData.Broadcast(strData);
		}
		catch (Exception^ ex)
		{
		}
		delete reader;
	}));
}

void UWebSocketBase::OnUWPClosed(Windows::Networking::Sockets::IWebSocket^ sender, Windows::Networking::Sockets::WebSocketClosedEventArgs^ args)
{
	Windows::ApplicationModel::Core::CoreApplication::MainView->Dispatcher->RunAsync(
		Windows::UI::Core::CoreDispatcherPriority::Normal,
		ref new Windows::UI::Core::DispatchedHandler([this]()
	{
		OnClosed.Broadcast();
	}));
}

Concurrency::task<void> UWebSocketBase::ConnectAsync(Platform::String^ uriString)
{
	Uri^ server = nullptr;
	try
	{
		server = ref new Uri(uriString);
	}
	catch (NullReferenceException^)
	{
		return task_from_result();
	}
	catch (InvalidArgumentException^)
	{
		return task_from_result();
	}

	messageWebSocket = ref new MessageWebSocket();
	messageWebSocket->Control->MessageType = SocketMessageType::Utf8;
	messageWebSocket->MessageReceived +=
		ref new TypedEventHandler<
		MessageWebSocket^,
		MessageWebSocketMessageReceivedEventArgs^>(uwpSocketHelper, &FUWPSocketHelper::MessageReceived);
	messageWebSocket->Closed += ref new TypedEventHandler<IWebSocket^, WebSocketClosedEventArgs^>(uwpSocketHelper, &FUWPSocketHelper::OnUWPClosed);

	return create_task(messageWebSocket->ConnectAsync(server))
		.then([this](task<void> previousTask)
	{
		try
		{
			previousTask.get();
		}
		catch (Exception^ ex)
		{
			delete messageWebSocket;
			messageWebSocket = nullptr;
			return;
		}

		messageWriter = ref new DataWriter(messageWebSocket->OutputStream);
	});
}


Concurrency::task<void> UWebSocketBase::SendAsync(Platform::String^ message)
{
	if (message == "")
	{
		return task_from_result();
	}
	messageWriter->WriteString(message);

	return create_task(messageWriter->StoreAsync())
		.then([this](task<unsigned int> previousTask)
	{
		try
		{
			previousTask.get();
		}
		catch (Exception^ ex)
		{
			return;
		}
	});
}


#endif

void UWebSocketBase::Connect(const FString& uri, const TMap<FString, FString>& header)
{
	if (uri.IsEmpty())
	{
		return;
	}

#if PLATFORM_UWP
	ConnectAsync(ref new String(*uri) ).then([this]()
	{
		Windows::ApplicationModel::Core::CoreApplication::MainView->Dispatcher->RunAsync(
			Windows::UI::Core::CoreDispatcherPriority::Normal,
			ref new Windows::UI::Core::DispatchedHandler([this]()
		{
			if (messageWebSocket != nullptr)
			{
				OnConnectComplete.Broadcast();
			}
			else
			{
				OnConnectError.Broadcast(TEXT("connect error") );
			}
		}));
	});
#elif PLATFORM_HTML5
	mHtml5SocketHelper.Bind(this);
	std::string strUrl = TCHAR_TO_UTF8(*uri);
	mWebSocketRef = SocketCreate(strUrl.c_str() );
	
#else
	if (mlwsContext == nullptr)
	{
		return;
	}

	int iUseSSL = 0;
	int iPos = uri.Find(TEXT(":"));
	if (iPos == INDEX_NONE)
	{
		//UE_LOG(WebSocket, Error, TEXT("Invalid Websocket address:%s"), *uri);
		return;
	}

	FString strProtocol = uri.Left(iPos);
	if (strProtocol.ToUpper() != TEXT("WS") && strProtocol.ToUpper() != TEXT("WSS"))
	{
		//UE_LOG(WebSocket, Error, TEXT("Invalid Protol:%s"), *strProtocol);
		return;
	}

	if (strProtocol.ToUpper() == TEXT("WSS"))
	{
		iUseSSL = 2;
	}

	FString strHost;
	FString strPath = TEXT("/");
	FString strNextParse = uri.Mid(iPos + 3);
	iPos = strNextParse.Find("/");
	if (iPos != INDEX_NONE)
	{
		strHost = strNextParse.Left(iPos);
		strPath = strNextParse.Mid(iPos);
	}
	else
	{
		strHost = strNextParse;
	}

	FString strAddress = strHost;
	int iPort = 80;
	iPos = strAddress.Find(":");
	if (iPos != INDEX_NONE)
	{
		strAddress = strHost.Left(iPos);
		iPort = FCString::Atoi(*strHost.Mid(iPos + 1));
	}
	else
	{
		if (iUseSSL)
		{
			iPort = 443;
		}
	}

	struct lws_client_connect_info connectInfo;
	memset(&connectInfo, 0, sizeof(connectInfo));

	std::string stdAddress = TCHAR_TO_UTF8(*strAddress);
	std::string stdPath = TCHAR_TO_UTF8(*strPath);
	std::string stdHost = TCHAR_TO_UTF8(*strHost);;

	connectInfo.context = mlwsContext;
	connectInfo.address = stdAddress.c_str();
	connectInfo.port = iPort;
	connectInfo.ssl_connection = iUseSSL;
	connectInfo.path = stdPath.c_str();
	connectInfo.host = stdHost.c_str();
	connectInfo.origin = stdHost.c_str();
	connectInfo.ietf_version_or_minus_one = -1;
	connectInfo.userdata = this;

	mlws = lws_client_connect_via_info(&connectInfo);
	//mlws = lws_client_connect_extended(mlwsContext, TCHAR_TO_UTF8(*strAddress), iPort, iUseSSL, TCHAR_TO_UTF8(*strPath), TCHAR_TO_UTF8(*strHost), TCHAR_TO_UTF8(*strHost), NULL, -1, (void*)this);
	if (mlws == nullptr)
	{
		UE_LOG(WebSocket, Error, TEXT("create client connect fail"));
		return;
	}

	mHeaderMap = header;
#endif
}

void UWebSocketBase::SendText(const FString& data)
{
#if PLATFORM_UWP
	SendAsync(ref new String(*data)).then([this]()
	{
	});

#elif PLATFORM_HTML5
	std::string strData = TCHAR_TO_UTF8(*data);
	SocketSend(mWebSocketRef, strData.c_str(), (int)strData.size() );
#else
	if (data.Len() > MAX_ECHO_PAYLOAD)
	{
		UE_LOG(WebSocket, Error, TEXT("too large package to send > MAX_ECHO_PAYLOAD:%d > %d"), data.Len(), MAX_ECHO_PAYLOAD);
		return;
	}

	if (mlws != nullptr)
	{
		mSendQueue.Add(data);
	}
	else
	{
		UE_LOG(WebSocket, Error, TEXT("the socket is closed, SendText fail"));
	}
#endif
}

void UWebSocketBase::ProcessWriteable()
{
#if PLATFORM_UWP
#elif PLATFORM_HTML5
#else
	while (mSendQueue.Num() > 0)
	{
		std::string strData = TCHAR_TO_UTF8(*mSendQueue[0]);

		unsigned char buf[LWS_PRE + MAX_ECHO_PAYLOAD];
		memcpy(&buf[LWS_PRE], strData.c_str(), strData.size() );
		lws_write(mlws, &buf[LWS_PRE], strData.size(), LWS_WRITE_TEXT);

		mSendQueue.RemoveAt(0);
	}
#endif
}

void UWebSocketBase::ProcessRead(const char* in, int len)
{
	FString strData = UTF8_TO_TCHAR(in);
	OnReceiveData.Broadcast(strData);
}


bool UWebSocketBase::ProcessHeader(unsigned char** p, unsigned char* end)
{
#if PLATFORM_UWP
#elif PLATFORM_HTML5
#else
	if (mHeaderMap.Num() == 0)
	{
		return true;
	}
	
	for (auto& it : mHeaderMap)
	{
		std::string strKey = TCHAR_TO_UTF8(*(it.Key) );
		std::string strValue = TCHAR_TO_UTF8(*(it.Value));

		strKey += ":";
		if (lws_add_http_header_by_name(mlws, (const unsigned char*)strKey.c_str(), (const unsigned char*)strValue.c_str(), (int)strValue.size(), p, end))
		{
			return false;
		}
	}
#endif

	return true;
}

void UWebSocketBase::Close()
{
#if PLATFORM_UWP
	if (messageWriter != nullptr)
	{
		messageWriter->DetachStream();
		delete messageWriter;
		messageWriter = nullptr;
	}
#elif PLATFORM_HTML5
	SocketClose(mWebSocketRef);
	mWebSocketRef = -1;
	OnClosed.Broadcast();
#else
	if (mlws != nullptr)
	{
		lws_set_wsi_user(mlws, NULL);
		mlws = nullptr;
	}

	OnClosed.Broadcast();
#endif
}

void UWebSocketBase::Cleanlws()
{
#if PLATFORM_UWP
#elif PLATFORM_HTML5
#else
	if (mlws != nullptr)
	{
		lws_set_wsi_user(mlws, NULL);
	}
#endif
}




