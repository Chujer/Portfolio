#include "Skill/AddOns/CTraceSpear.h"
#include "Global.h"

ACTraceSpear::ACTraceSpear()
{
	PrimaryActorTick.bCanEverTick = true;
	CHelpers::CreateActorComponent<USceneComponent>(this, &root, "RootComponent");
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &SM_Spear, "SM_Spear", root);

	//TODO : 2023.10.24 - 생성시 에디터에서 설정한 스태틱매쉬의 설정이 초기화됨

	SM_Spear->SetCollisionProfileName("OverlapAllDynamic");
}

void ACTraceSpear::BeginPlay()
{
	Super::BeginPlay();

	for (UFXSystemAsset* effect : SpearEffect)
	{
		if(effect->GetName() == "P_ky_stabShot")
			UGameplayStatics::SpawnEmitterAttached(Cast<UParticleSystem>(effect),SM_Spear,NAME_None, FVector(0,0,200), 
				FRotator(0,90,0), FVector(0.5f, 1.0f,1.0f));
		else
			UNiagaraFunctionLibrary::SpawnSystemAttached(Cast<UNiagaraSystem>(effect), SM_Spear, "None", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, false);
	}
	
}

void ACTraceSpear::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

