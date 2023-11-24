#include "Skill/AddOns/CGhostTrail.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/PoseableMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Utilities/CLog.h"

ACGhostTrail::ACGhostTrail()
{
	CHelpers::CreateActorComponent(this, &scene, FName("meshs"));
}

void ACGhostTrail::EndTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void ACGhostTrail::SetOriginMaterial()
{
	TArray<UMaterialInterface*> materials = Owner->GetMesh()->GetMaterials();

	for (UPoseableMeshComponent* mesh : Meshs)
	{
		for (int i = 0; i < materials.Num(); i++)
		{
			UMaterialInstanceDynamic* instance = Cast<UMaterialInstanceDynamic>(materials[i]);
			mesh->SetMaterial(i, instance);
		}
	}

}

void ACGhostTrail::BeginPlay()
{
	Super::BeginPlay();

	UMaterialInstanceConstant* material;
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&material, "MaterialInstanceConstant'/Game/Materials/Custom/M_GhostMaterial_Inst.M_GhostMaterial_Inst'");

	Material = UMaterialInstanceDynamic::Create(material, nullptr);
	Material->SetVectorParameterValue("Color", Color);
	Material->SetScalarParameterValue("Exp", Exponent);

	Owner = Cast<ACharacter>(GetOwner());
	Skeletals = CHelpers::GetComponents<USkeletalMeshComponent>(Owner);


	for(int i = 0; i<Skeletals.Num();i++)
	{
		UPoseableMeshComponent* mesh = NewObject<UPoseableMeshComponent>(this, UPoseableMeshComponent::StaticClass(),FName(Skeletals[i]->GetName()));
		CheckNull(mesh);
		mesh->RegisterComponent();
		mesh->AttachToComponent(scene, FAttachmentTransformRules::KeepRelativeTransform);
		
		mesh->SetVisibility(false);
		mesh->SetSkeletalMesh(Skeletals[i]->SkeletalMesh);
		if (mesh->IsVisible() == false)
			mesh->ToggleVisibility();

		mesh->CopyPoseFromSkeletalComponent(Skeletals[i]);
		mesh->SetRelativeScale3D(Scale);
		
		for (int32 j = 0; j < Skeletals[i]->SkeletalMesh->Materials.Num(); j++)
			mesh->SetMaterial(j, Material);

		if (Meshs.Num() > 0)
			mesh->AttachToComponent(Meshs[0],FAttachmentTransformRules::KeepRelativeTransform ,Skeletals[i]->GetAttachSocketName());

		Meshs.Add(mesh);
	}
	
	FTimerDelegate timerDelegate = FTimerDelegate::CreateLambda([=]()	//타이머 설정
	{
		float height = Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		SetActorLocation(Owner->GetActorLocation() - FVector(ScaleAmount.X, ScaleAmount.Y, height - ScaleAmount.Z));
		SetActorRotation(Owner->GetActorRotation() - FRotator(0, 90, 0));

		for(UPoseableMeshComponent* mesh :Meshs)
		{
			//시간에 따른 동작 밑 위치,회전 설정
			if (mesh->IsVisible() == false)
				mesh->ToggleVisibility();

			mesh->CopyPoseFromSkeletalComponent(Owner->GetMesh());
		}
	});

	float height = Owner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	SetActorLocation(Owner->GetActorLocation() - FVector(ScaleAmount.X, ScaleAmount.Y, height - ScaleAmount.Z));
	SetActorRotation(Owner->GetActorRotation() - FRotator(0, 90, 0));

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, timerDelegate, Interval, true, StartDelay);
}

void ACGhostTrail::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}


