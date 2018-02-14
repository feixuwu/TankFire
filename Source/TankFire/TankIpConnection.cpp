// Fill out your copyright notice in the Description page of Project Settings.

#include "TankIpConnection.h"
#include "SocketSubsystem.h"

#include "IPAddress.h"
#include "Sockets.h"
#include "Net/NetworkProfiler.h"
#include "Net/DataChannel.h"
#include "PacketAudit.h"

// Size of a UDP header.
#define IP_HEADER_SIZE     (20)
#define UDP_HEADER_SIZE    (IP_HEADER_SIZE+8)

void UTankIpConnection::CleanUp()
{
	OwningActor = nullptr;
	Super::CleanUp();
}


void UTankIpConnection::InitLocalConnection(UNetDriver* InDriver, class FSocket* InSocket, const FURL& InURL, EConnectionState InState, int32 InMaxPacket, int32 InPacketOverhead)
{
	InitBase(InDriver, InSocket, InURL, InState,
		// Use the default packet size/overhead unless overridden by a child class
		(InMaxPacket == 0 || InMaxPacket > MAX_PACKET_SIZE) ? MAX_PACKET_SIZE : InMaxPacket,
		InPacketOverhead == 0 ? UDP_HEADER_SIZE : InPacketOverhead);

	// Figure out IP address from the host URL
	bool bIsValid = false;
	// Get numerical address directly.
	RemoteAddr = InDriver->GetSocketSubsystem()->CreateInternetAddr();
	RemoteAddr->SetIp(*InURL.Host, bIsValid);
	RemoteAddr->SetPort(InURL.Port);

	// save the origin host
	ConnectUrl = InURL;

	bIsValid = false;
	// Try to resolve it if it failed
	if (bIsValid == false)
	{
		// Create thread to resolve the address.
		ResolveInfo = InDriver->GetSocketSubsystem()->GetHostByName(TCHAR_TO_ANSI(*InURL.Host));
		if (ResolveInfo == NULL)
		{
			Close();
			UE_LOG(LogNet, Verbose, TEXT("IpConnection::InitConnection: Unable to resolve %s"), *InURL.Host);
		}
	}

	// Initialize our send bunch
	InitSendBuffer();
}

void UTankIpConnection::LowLevelSend(void* Data, int32 CountBytes, int32 CountBits)
{
	const uint8* DataToSend = reinterpret_cast<uint8*>(Data);

	if (ResolveInfo)
	{
		// If destination address isn't resolved yet, send nowhere.
		if (!ResolveInfo->IsComplete())
		{
			// Host name still resolving.
			return;
		}
		else if (ResolveInfo->GetErrorCode() != SE_NO_ERROR)
		{
			// Host name resolution just now failed.
			UE_LOG(LogNet, Log, TEXT("Host name resolution failed with %d"), ResolveInfo->GetErrorCode());
			Driver->ServerConnection->State = USOCK_Closed;
			delete ResolveInfo;
			ResolveInfo = NULL;
			return;
		}
		else
		{
			//uint32 Addr;
			// Host name resolution just now succeeded.
			
			//ResolveInfo->GetResolvedAddress().GetIp(Addr);
			//RemoteAddr->SetIp(Addr);
			
			GetDriver()->GetSocketSubsystem()->GetHostByNameFromCache(TCHAR_TO_ANSI(*ConnectUrl.Host), RemoteAddr);// ResolveInfo->GetResolvedAddress();
			RemoteAddr->SetPort(ConnectUrl.Port);
			
			UE_LOG(LogNet, Log, TEXT("Host name resolution completed"));
			delete ResolveInfo;
			ResolveInfo = NULL;
		}
	}


	// Process any packet modifiers
	if (Handler.IsValid() && !Handler->GetRawSend())
	{
		const ProcessedPacket ProcessedData = Handler->Outgoing(reinterpret_cast<uint8*>(Data), CountBits);

		if (!ProcessedData.bError)
		{
			DataToSend = ProcessedData.Data;
			CountBytes = FMath::DivideAndRoundUp(ProcessedData.CountBits, 8);
			CountBits = ProcessedData.CountBits;
		}
		else
		{
			CountBytes = 0;
			CountBits = 0;
		}
	}

	bool bBlockSend = false;

#if !UE_BUILD_SHIPPING
	LowLevelSendDel.ExecuteIfBound((void*)DataToSend, CountBytes, bBlockSend);
#endif

	if (!bBlockSend)
	{
		// Send to remote.
		int32 BytesSent = 0;
		CLOCK_CYCLES(Driver->SendCycles);

		if (CountBytes > MaxPacket)
		{
			UE_LOG(LogNet, Warning, TEXT("UIpConnection::LowLevelSend: CountBytes > MaxPacketSize! Count: %i, MaxPacket: %i %s"), CountBytes, MaxPacket, *Describe());
		}

		FPacketAudit::NotifyLowLevelSend((uint8*)DataToSend, CountBytes, CountBits);

		if (CountBytes > 0)
		{
			Socket->SendTo(DataToSend, CountBytes, BytesSent, *RemoteAddr);
		}

		UNCLOCK_CYCLES(Driver->SendCycles);
		NETWORK_PROFILER(GNetworkProfiler.FlushOutgoingBunches(this));
		NETWORK_PROFILER(GNetworkProfiler.TrackSocketSendTo(Socket->GetDescription(), DataToSend, BytesSent, NumPacketIdBits, NumBunchBits, NumAckBits, NumPaddingBits, this));
	}
}
