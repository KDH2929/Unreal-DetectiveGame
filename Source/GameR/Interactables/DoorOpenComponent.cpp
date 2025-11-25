// DoorOpenComponent.cpp

#include "Interactables/DoorOpenComponent.h"
#include "GameFramework/Actor.h" // GetOwner() 함수를 사용하기 위해 필요합니다.

UDoorOpenComponent::UDoorOpenComponent()
{
	// 이 컴포넌트가 매 프레임마다 Tick 함수를 호출하도록 설정합니다.
	PrimaryComponentTick.bCanEverTick = true;
}

void UDoorOpenComponent::BeginPlay()
{
	Super::BeginPlay();

	// 게임이 시작될 때, 이 컴포넌트를 가지고 있는 액터의 초기 회전 값을 저장합니다.
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	// 목표 회전 값은 초기 값에 90도를 더한 값으로 설정합니다.
	TargetYaw = InitialYaw + 90.0f;
}

void UDoorOpenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// bIsOpening 상태가 true일 때만 아래 코드를 실행합니다.
	if (bIsOpening)
	{
		// 현재 액터의 회전 값을 가져옵니다.
		FRotator CurrentRotation = GetOwner()->GetActorRotation();
		// 목표 회전 값을 만듭니다.
		FRotator TargetRotation = FRotator(0.f, TargetYaw, 0.f);

		// FMath::RInterpTo 함수를 사용해 현재 회전 값에서 목표 회전 값으로 부드럽게 보간합니다.
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, 2.0f);

		// 보간된 새로운 회전 값을 액터에 적용합니다.
		GetOwner()->SetActorRotation(NewRotation);
	}
}

// 이 함수가 바로 우리가 '함수처럼' 사용할 핵심 기능입니다.
void UDoorOpenComponent::ToggleDoor()
{
	// 현재 상태를 반전시킵니다. (true -> false, false -> true)
	bIsOpening = !bIsOpening;
}