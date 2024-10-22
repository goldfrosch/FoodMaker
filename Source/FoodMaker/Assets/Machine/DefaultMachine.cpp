#include "DefaultMachine.h"


ADefaultMachine::ADefaultMachine()
{
	PrimaryActorTick.bCanEverTick = true;
	AssetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Machine Object"));
	AssetMesh->SetupAttachment(RootComponent);
}

void ADefaultMachine::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADefaultMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

