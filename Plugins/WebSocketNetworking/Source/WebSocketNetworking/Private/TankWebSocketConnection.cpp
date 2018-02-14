// Fill out your copyright notice in the Description page of Project Settings.

#include "HTML5NetworkingPrivate.h"
#include "TankWebSocketConnection.h"

void UTankWebSocketConnection::CleanUp()
{
	OwningActor = nullptr;
	Super::CleanUp();
}


