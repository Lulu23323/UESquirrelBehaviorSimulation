// Copyright 2021 Justin Kiesskalt, All Rights Reserved.

#pragma once
#include "FlocksTable.h"

struct FLOCKS_API FlocksBoidMap
{
	struct FBoidMapData
	{
		TArray<uint32> SortedCellList;
		TArray<uint32> CellOffsetList;
		TArray<uint32> CellBoidCount;
	};

public:
	FlocksBoidMap(AFlocksWorld* InWorld);
	~FlocksBoidMap();

	FBoidMapData* Lock();
	void Unlock();

	void Update(float DeltaSeconds);
	uint32 GetFlatCellIndex(FIntVector CellIndex) const;

	float CellSize = 300.0f;
	class AFlocksWorld* World;

private:
	void Reset();
	
	FCriticalSection MapLock;
	FBoidMapData Data;
};