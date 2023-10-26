#include "Skill/AddOns/CTraceSpear.h"
#include "Global.h"
#include "Characters/ICharacter.h"
#include "Skill/CSkill.h"
#include "Characters/CPlayer.h"
#include "Skill/CSkill.h"
#include "Weapon/CAttachment.h"

ACTraceSpear::ACTraceSpear()
{
	PrimaryActorTick.bCanEverTick = true;
	CHelpers::CreateActorComponent<USceneComponent>(this, &root, "RootComponent");
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &SM_Spear, "SM_Spear", root);

	SM_Spear->SetCollisionProfileName("OverlapAllDynamic");
}

void ACTraceSpear::BeginPlay()
{
	Super::BeginPlay();

	CLog::Print(targets.Num());

	Attachment = Cast<ACAttachment>(GetOwner());
	Character = Cast<ACPlayer>(Attachment->GetOwner());

	for (UFXSystemAsset* effect : SpearEffect)
	{
		if(effect->GetName() == "P_ky_stabShot")
			UGameplayStatics::SpawnEmitterAttached(Cast<UParticleSystem>(effect),SM_Spear,"None", FVector(0,0,200), 
				FRotator(90,0,0), FVector(0.5f, 1.0f,1.0f));
		else
			UNiagaraFunctionLibrary::SpawnSystemAttached(Cast<UNiagaraSystem>(effect), SM_Spear, "None", FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, false);
	}
	SetTargets();
	SetBezierPoint();


	FOnTimelineFloat timeline;
	timeline.BindUFunction(this, "Move");
	FOnTimelineEvent onEndMove;
	onEndMove.BindUFunction(this, "OnEndMove");

	Timeline.AddInterpFloat(Curve, timeline);
	Timeline.SetTimelineFinishedFunc(onEndMove);
}

void ACTraceSpear::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor != CurTarget || !!Hitted)
		return;

	Hitted = Cast<ACharacter>(OtherActor);

	IICharacter* iCharacter = Cast<IICharacter>(Hitted);
	iCharacter->ApplyDamage(Character, Attachment, EDamageType::NORMAL, Damage);
}


void ACTraceSpear::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetLookTarget();
	Timeline.TickTimeline(DeltaTime);
}

void ACTraceSpear::SetLookTarget()
{
	if (IsValid(CurTarget))
		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CurTarget->GetActorLocation()));
}

void ACTraceSpear::OnEndMove()
{
	if (targets.Num()-1 == curIndex)
	{
		Destroy();
		return;
	}

	SetBezierPoint();
}


void ACTraceSpear::SetBezierPoint()
{
	if (targets.Num() == 0 || targets.Num()-1 == curIndex)
		return;

	if (!IsValid(targets[curIndex]))	//���� Ÿ���� ������ �ٽ� �˻�
	{
		SetTargets();
	}
	CurTarget = targets[curIndex];
	UGameplayStatics::PlaySound2D(GetWorld(), MoveSound);

	SetLookTarget();

	//�������� �߰� ����Ʈ ����
	StartPos = GetActorLocation();
	BezierPointVector = StartPos + (GetActorForwardVector() * (UKismetMathLibrary::Vector_Distance(StartPos, CurTarget->GetActorLocation() / 2)));//�����Ÿ� ��
	BezierPointVector = BezierPointVector + (BezierPointVector.RightVector * UKismetMathLibrary::RandomFloatInRange(-600, 600));
	BezierPointVector = FVector(BezierPointVector.X, BezierPointVector.Y, BezierPointVector.Z + UKismetMathLibrary::RandomFloatInRange(0, 500));
	BezierMovePointVector = BezierPointVector;

	SelfMovePoint = GetActorLocation();

	Timeline.PlayFromStart();	//Ÿ�Ӷ��� ����

	curIndex++;	//���� ��� �غ�
	Hitted = nullptr;
}

void ACTraceSpear::Move(float time)
{
	if (!IsValid(CurTarget))
		return;

	EndPos = CurTarget->GetActorLocation();
	FVector pointToEnd = UKismetMathLibrary::VLerp(BezierMovePointVector, EndPos, time);
	FVector startToPoint = UKismetMathLibrary::VLerp(SelfMovePoint, BezierPointVector,time);
	SetActorLocation(UKismetMathLibrary::VLerp(startToPoint, pointToEnd, time));
}

void ACTraceSpear::SetTargets()	//Ÿ�� ����
{
	CLog::Print("SetTarget");
	StartPos = GetActorLocation();
	TArray<AActor*> ignores;
	TArray<FHitResult> hitResults;
	bool isLock = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), StartPos, StartPos, Range, 
		TraceType, false, ignores, DebugMode, hitResults, true);

	if (!isLock)	//�ֺ��� ���̾����� ����
	{
		Destroy();
		return;
	}

	for (FHitResult hitted : hitResults)
	{
		if(targets.Num() < 11)
			targets.Add(Cast<ACharacter>(hitted.Actor));
	}

	if (curIndex == 0)
	{
		int index = 0;
		while (targets.Num() < 11)	//�ֺ� ���� 10�� �̸��̶�� ���� ������ ����
		{
			targets.Add(Cast<ACharacter>(targets[index]));
			index++;
		}
	}
}

