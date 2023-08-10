#include "Weapons/SubActions/CSubAction_Aiming.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CStateComponent.h"
#include "Weapons/CAttachment_Bow.h"
#include "AIController.h"

UCSubAction_Aiming::UCSubAction_Aiming()
{
	CHelpers::GetAsset<UCurveVector>(&Curve, "CurveVector'/Game/Weapons/Bow/Curve_Aimming.Curve_Aimming'");
}

void UCSubAction_Aiming::BeginPlay(ACharacter* InOwner, ACAttachment* InAttachment, UCDoAction* InDoAction)
{
	Super::BeginPlay(InOwner, InAttachment, InDoAction);

	SpringArm = CHelpers::GetComponent<USpringArmComponent>(InOwner);
	Camera = CHelpers::GetComponent<UCameraComponent>(InOwner);

	FOnTimelineVector timeline;
	timeline.BindUFunction(this, "OnAiming");

	TimeLine.AddInterpVector(Curve, timeline);
	TimeLine.SetPlayRate(AimingSpeed);

	ACAttachment_Bow* bow = Cast<ACAttachment_Bow>(InAttachment);
	Bending = bow->GetBend();
}

void UCSubAction_Aiming::Tick_Implementation(float InDeltaTime)
{
	Super::Tick_Implementation(InDeltaTime);

	TimeLine.TickTimeline(InDeltaTime);
}

void UCSubAction_Aiming::OnAiming(FVector Output)
{
	Camera->FieldOfView = Output.X;		//기본 포브값이 90 줌 당겼을때 45 커브에도 설정해둠
	*Bending = Output.Y;		
}

void UCSubAction_Aiming::Pressed()
{	
	CheckTrue(State->IsSubActionMode());

	if (!!Owner->GetController<AAIController>())
	{
		Super::Pressed();

		State->OnSubActionMode();

		bAiming = true;
		return;
	}

	CheckNull(SpringArm);
	CheckNull(Camera);
	CheckTrue(bAiming);

	Super::Pressed();

	State->OnSubActionMode();

	bAiming = true;

	//기존 데이터
	OriginData.TargetArmLength = SpringArm->TargetArmLength;
	OriginData.SocketOffset = SpringArm->SocketOffset;
	OriginData.bEnableCameraLag = SpringArm->bEnableCameraLag;
	OriginData.CameraLocation = Camera->GetRelativeLocation();

	//AimData데이터로 현재 상태 변경
	SpringArm->TargetArmLength = AimData.TargetArmLength;
	SpringArm->SocketOffset = AimData.SocketOffset;
	SpringArm->bEnableCameraLag = AimData.bEnableCameraLag;
	Camera->SetRelativeLocation(AimData.CameraLocation);

	TimeLine.PlayFromStart();
}

void UCSubAction_Aiming::Released()
{

	CheckFalse(State->IsSubActionMode());

	
	if (!!Owner->GetController<AAIController>())
	{
		Super::Released();

		State->OffSubActionMode();

		bAiming = false;
		return;
	}
	CheckNull(SpringArm);
	CheckNull(Camera);
	CheckFalse(bAiming);


	State->OffSubActionMode();

	bAiming = false;
	
	SpringArm->TargetArmLength = OriginData.TargetArmLength;
	SpringArm->SocketOffset = OriginData.SocketOffset;
	SpringArm->bEnableCameraLag = OriginData.bEnableCameraLag;
	Camera->SetRelativeLocation(OriginData.CameraLocation);	

	TimeLine.ReverseFromEnd();
}
