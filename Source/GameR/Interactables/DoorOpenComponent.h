// DoorOpenComponent.h

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorOpenComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMER_API UDoorOpenComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDoorOpenComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 이 컴포넌트를 사용하는 액터(예: BP_Door)가 호출할 함수입니다.
	UFUNCTION(BlueprintCallable, Category = "Door")
	void ToggleDoor();

private:
	// 목표 회전 각도 (Yaw)
	float TargetYaw = 90.0f;
	
	// 초기 회전 각도 (Yaw)
	float InitialYaw;

	// 현재 문이 열리고 있는 중인지 상태를 저장하는 변수
	bool bIsOpening = false;
};