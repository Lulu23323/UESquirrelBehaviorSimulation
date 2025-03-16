#pragma once
#include "FlocksBoidTable.h"
#include "FlocksTypes.h"
#include "UObject/StrongObjectPtr.h"

struct FlocksVisualsTable;

struct FLOCKS_API FlocksAnimationTable : public FlocksBoidTable
{
	struct FTableData
	{
		float AnimRateScale;
		float AnimTime;
		float AnimDuration;
		int32 ActiveAnimationIndex;
		FName ActiveAnimationName;
		FName LoopSingleAnimationName;
		float StartTime;
		float EndTime;
		float AnimationRateScale;
		int32 CurrentLoops;
		int32 TargetLoops;
		EFlocksAnimationMode AnimationMode;
	};

	struct FAddBoidData
	{
		float AnimRateScale;
	};

public:
	FlocksAnimationTable(AFlocksWorld* InWorld, FlocksVisualsTable* InVisualsTable);
	~FlocksAnimationTable();

	void SetAnimationData(class UFlocksAnimationData* InAnimationData);

	FTableData* Lock();
	void Unlock();

	virtual TArray<uint16> AddBoid(int32 Amount, BOID_HANDLE* Handles, const FAddBoidData* InData);
	virtual void RemoveBoid(int32 Amount, BOID_HANDLE* Handles);
	virtual void Update(float DeltaSeconds) override;

	void PlayOverrideAnimation(BOID_HANDLE Boid, const FName& Animation, float StartOffset, int32 NumLoops);
	void ClearAnimationOverride(BOID_HANDLE Boid);

	void SelectNewVariousAnimation(BOID_HANDLE Boid, float StartOffset);
	bool PlayAnimation(BOID_HANDLE Boid, const FName& Animation, float StartOffset, int32 NumLoops);

	FlocksVisualsTable* VisualsTable = nullptr;
	TWeakObjectPtr<class UFlocksAnimationData> AnimationData = nullptr;
	TMap<FName, int32> AnimationNameToIndex;

private:
	TArray<FTableData> Data;
	FCriticalSection TableLock;
};
