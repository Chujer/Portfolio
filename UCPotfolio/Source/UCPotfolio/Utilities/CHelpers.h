#pragma once

#include <algorithm>

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "Particles/ParticleSystem.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Skill/AddOns/CGhostTrail.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"

#define CheckTrue(x) { if(x == true) return; }
#define CheckFalse(x) {if(x == false) return;}

#define CheckTrueResult(x, y) { if(x == true) return y; }
#define CheckFalseResult(x, y) { if(x == false) return y;}

#define CheckNull(x) {if(x == nullptr) return;}
#define CheckNullResult(x, y) { if(x == nullptr) return y;}

class UCPOTFOLIO_API CHelpers
{
public:
	template<typename T>
	static void CreateComponent(AActor* InActor, T** OutComponent, FName InName, USceneComponent* InParent = nullptr, FName InSocketName = NAME_None)
	{
		*OutComponent = InActor->CreateDefaultSubobject <T>(InName);
		if(!!InParent)
		{
			(*OutComponent)->SetupAttachment(InParent, InSocketName);

			return;
		}

		InActor->SetRootComponent(*OutComponent);
	}

	template<typename T>
	static void CreateActorComponent(AActor* InActor, T** OutComponent, FName InName)
	{
		*OutComponent = InActor->CreateDefaultSubobject<T>(InName);
	}

	template<typename T>
	static void GetAsset(T** OutObject, FString InPath)
	{
		//파일 읽어다가 클래스만들기
		ConstructorHelpers::FObjectFinder<T> asset(*InPath);
		*OutObject = asset.Object;
	}

	template<typename T>
	static void GetAssetDynamic(T** OutObject, FString InPath)
	{
		*OutObject = Cast<T>(StaticLoadObject(T::StaticClass(), nullptr, *InPath));
	}

	template<typename T>
	static void GetClass(TSubclassOf<T>* OutObject, FString InPath)
	{
		ConstructorHelpers::FClassFinder<T> asset(*InPath);
		*OutObject = asset.Class;
	}

	template<typename T>
	static T* FindActor(UWorld* InWorld)
	{
		for(AActor* actor : InWorld->GetCurrentLevel()->Actors)
		{
			if (!!actor && actor.IsA<T>())
				return Cast<T>();
		}
		return nullptr;
	}

	template<typename T>
	static T* GetComponent(AActor* InActor)
	{
		return Cast<T>(InActor->GetComponentByClass(T::StaticClass()));
	}

	template<typename T>
	static T* GetComponent(TWeakObjectPtr<AActor> InActor)
	{
		return Cast<T>(InActor->GetComponentByClass(T::StaticClass()));
	}

	template<typename T>
	static  TArray<T*> GetComponents(AActor* InActor)
	{
		TArray<T*> temp;
		TArray<UActorComponent*> components;
		InActor->GetComponents(T::StaticClass(), components);
		for(UActorComponent* component : components)
		{
			temp.Add(Cast<T>(component));
		}

		return temp;
	}

	template<typename T>
	static T* GetComponent(AActor* InActor, const FString& InName)
	{
		TArray<T*> components;
		InActor->GetComponents<T>(components);

		for(T* component : components)
		{
			if (component->GetName() == InName)
				return component;
		}
		return nullptr;
	}

	static void AttachTo(AActor* InActor, USceneComponent* InParent, const FName& InSocketName)
	{
		InActor->AttachToComponent(InParent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
	}

	static UFXSystemComponent* PlayEffect(UWorld* InWorld, UFXSystemAsset* InEffect, const FTransform& InTransform, USkeletalMeshComponent* InMesh = nullptr, FName InSocketName = NAME_None)
	{
		UParticleSystem* particle = Cast<UParticleSystem>(InEffect);
		UNiagaraSystem* niagara = Cast<UNiagaraSystem>(InEffect);
		
		FVector location = InTransform.GetLocation();
		FRotator rotation = FRotator(InTransform.GetRotation());
		FVector scale = InTransform.GetScale3D();

		if(!!InMesh)
		{
			if(!!particle)
			{
				return UGameplayStatics::SpawnEmitterAttached(particle, InMesh, InSocketName, location, rotation, scale);;
			}
			if(!!niagara)
			{
				
				
				return UNiagaraFunctionLibrary::SpawnSystemAttached(niagara, InMesh, InSocketName, location, rotation, scale, EAttachLocation::KeepRelativeOffset, true, ENCPoolMethod::None);;
			}
		}
		else
		{
			if (!!particle)
			{
				

				return UGameplayStatics::SpawnEmitterAtLocation(InWorld, particle, InTransform);;
			}

			if (!!niagara)
			{
				

				return UNiagaraFunctionLibrary::SpawnSystemAtLocation(InWorld, niagara, location, rotation, scale);;
			}
		}
		return nullptr;
	}

	static ACGhostTrail* Play_GhostTrial(TSubclassOf<ACGhostTrail>& InClass, class ACharacter* InOwner)
	{
		CheckNullResult(InClass, nullptr);
		CheckNullResult(InOwner, nullptr);

		FActorSpawnParameters params;
		params.Owner = InOwner;
		params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FVector vector = InOwner->GetActorLocation();
		vector.Z = InOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

		FTransform transform;
		transform.SetTranslation(vector);

		return InOwner->GetWorld()->SpawnActor<ACGhostTrail>(InClass, transform, params);
	}

	//Character에 설정한 카메라와 타겟들중 가장 각도차가 적은것
	static ACharacter* NearyFromCameraFront(ACharacter* Character, TArray<ACharacter*> targets)
	{
		ACharacter* candidate = nullptr;
		float angle = 360;
		for(ACharacter* target : targets)
		{
			// 적 - (플레이어 - 적)벡터와 카메라 정면 백터의 각(내적)
			float tempAngle = UKismetMathLibrary::Dot_VectorVector(UKismetMathLibrary::GetForwardVector(Character->GetControlRotation()), 
				UKismetMathLibrary::Normal((target->GetActorLocation() - Character->GetActorLocation())));

			if(tempAngle <= angle)
			{
				angle = tempAngle;
				candidate = target;
			}
		}
		return candidate;
	}
};
