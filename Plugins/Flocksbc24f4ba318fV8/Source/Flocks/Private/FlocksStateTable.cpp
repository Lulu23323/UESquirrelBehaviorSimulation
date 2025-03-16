// Copyright 2021 Justin Kiesskalt, All Rights Reserved.

#include "FlocksStateTable.h"
#include "FlocksWorld.h"
#include "FlocksBoidMap.h"
#include "FlocksDatabaseHeader.h"
#include "FlocksVolumeInfoTable.h"
#include "Utils/IndexArray.h"

#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"

FlocksStateTable::FlocksStateTable(AFlocksWorld* InWorld) : FlocksBoidTable(InWorld)
{
	Data.SetNum(MAX_BOIDS);
}

FlocksStateTable::~FlocksStateTable()
{
}


FlocksStateTable::FTableData* FlocksStateTable::Lock()
{
	TableLock.Lock();
	return Data.GetData();
}

void FlocksStateTable::Unlock()
{
	TableLock.Unlock();
}

TArray<uint16> FlocksStateTable::AddBoid(int32 Amount, BOID_HANDLE* Handles, const FAddBoidData* InData)
{
	TArray<uint16> AddedIndices;
	AddedIndices.SetNum(Amount);

	for (int32 i = 0; i < Amount; ++i)
	{
		AddedIndices[i] = LookUpTable->AddBoid(Handles[i]);
	}

	Lock();
	ParallelFor(Amount, [this, &AddedIndices, Handles, InData](int32 i) {
		int32 TableIndex = AddedIndices[i];

		if (TableIndex != INVALID_BOID_HANDLE_INDEX)
		{
			Data[TableIndex].Position = InData[i].Position;
			Data[TableIndex].Heading = InData[i].Heading;
			Data[TableIndex].Scale = InData[i].Scale;
			Data[TableIndex].Turning = InData[i].Turning;
			Data[TableIndex].Speed = InData[i].Speed;
			Data[TableIndex].Group = InData[i].Group;
			Data[TableIndex].MeshIndex = InData[i].MeshIndex;
			Data[TableIndex].MaxHealth = InData[i].MaxHealth;
			Data[TableIndex].bIsPendingDelete = false;
			Data[TableIndex].Action = 0;
			Data[TableIndex].Health = InData[i].MaxHealth;
		}
	});
	Unlock();

	return AddedIndices;
}

void FlocksStateTable::RemoveBoid(int32 Amount, BOID_HANDLE* Handles)
{
	Lock();
	for (int32 i = 0; i < Amount; ++i)
	{
		uint16 Index = Find(Handles[i]);

		if (Index != INVALID_BOID_HANDLE_INDEX)
		{
			LookUpTable->RemoveBoid(Handles[i]);
			Data[Index] = Data[Size()];
		}
	}
	Unlock();
}