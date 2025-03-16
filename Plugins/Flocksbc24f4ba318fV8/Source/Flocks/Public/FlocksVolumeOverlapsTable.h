// Copyright 2021 Justin Kiesskalt, All Rights Reserved.

#pragma once
#include "FlocksTypes.h"
#include "FlocksVolumeOverlapsTable.h"
#include "FlocksVolumeTable.h"

class AFlocksWorld;

struct FLOCKS_API FlocksVolumeOverlapsTable : public FlocksVolumeTable
{
	struct FTableData
	{
		int32 NumBoidsInVolume;
		TArray<BOID_HANDLE> BoidsInVolume;
	};

	struct FAddVolumeData
	{
	};

public:
	FlocksVolumeOverlapsTable(AFlocksWorld* InWorld);
	virtual ~FlocksVolumeOverlapsTable();

	FTableData* Lock();
	void Unlock();

	virtual uint16 AddVolume(VOLUME_HANDLE Volume, const FAddVolumeData& AddVolumeData);
	virtual void RemoveVolume(VOLUME_HANDLE Volume);

	void RecalculateOverlaps();
	
private:
	FCriticalSection TableLock;
	TArray<FTableData> Data;
};
