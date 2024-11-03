// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemableActor.h"


// Sets default values
AItemableActor::AItemableActor()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Info");
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetSimulatePhysics(true);
}
