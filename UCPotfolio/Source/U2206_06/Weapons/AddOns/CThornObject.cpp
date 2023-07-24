#include "Weapons/AddOns/CThornObject.h"
#include "Global.h"
#include "NiagaraComponent.h"
#include "GameFramework/Character.h"

ACThornObject::ACThornObject()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UNiagaraComponent>(this, &Niagara, "Niagara", Root);
}

void ACThornObject::BeginPlay()
{
	Super::BeginPlay();

	Niagara->SetNiagaraVariableObject("Collision",this);		//나이아가라에 오브젝트로 설정한 이름의 값을 수저할 수 있도록 설정 
	Niagara->OnSystemFinished.AddDynamic(this, &ACThornObject::OnSystemFinished);		//파티클재생이 끝났을때 실행

	if(!!NiagaraMesh)
	{
		FBox box = NiagaraMesh->GetBoundingBox();	//매쉬의 충돌체 크기 가져오기
		BoxExtent = (box.Max - box.Min).GetAbs() * 0.5f;
	}
}

void ACThornObject::ReceiveParticleData_Implementation(const TArray<FBasicParticleData>& Data,	//Data가 배열인이유 : 스폰시킨 모든 파티클의 배열
	UNiagaraSystem* NiagaraSystem)
{
	CheckFalse(Data.Num() > 0);

	static TArray<AActor*> ignores;
	ignores.AddUnique(GetOwner());

	static FHitResult hitResult;
	for(int32 i = Data.Num() - 1; i >=0; i--)
	{
		FVector position = Data[i].Position + GetActorLocation();
		FVector scale = Data[i].Velocity * BoxExtent;	//ExportParticleData의 scale을 velocity로 받아왔기 때문에

		UKismetSystemLibrary::BoxTraceSingleByProfile(GetWorld(), position, position, scale, NiagaraMeshRotation, "Pawn", false, ignores, EDrawDebugTrace::None, hitResult, true);

		if(hitResult.bBlockingHit)
		{
			if (!!CollisionEffect)
			{
				FTransform transform = CollisionEffectTransform;
				transform.AddToTranslation(hitResult.Location);

				CHelpers::PlayEffect(GetWorld(), CollisionEffect, transform);
			}

			ACharacter* character = Cast<ACharacter>(hitResult.GetActor());
			if (!!character && character != GetOwner())
				HitData.SendDamage(Cast<ACharacter>(GetOwner()), this, character);
		}
	}
}

void ACThornObject::OnSystemFinished(UNiagaraComponent* PSystem)
{
	Destroy();
}

