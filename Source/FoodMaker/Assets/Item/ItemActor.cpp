#include "ItemActor.h"


AItemActor::AItemActor()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Item Mesh");
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetSimulatePhysics(true);
	
	// TODO: Compile 과정에서 csv 적용하기
}

void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	
}