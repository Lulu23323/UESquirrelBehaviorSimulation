// Copyright 2021 Justin Kiesskalt, All Rights Reserved.

#include "FlocksVolumeOverlapsTable.h"

#include "FlocksLookUpTable.h"
#include "FlocksWorld.h"

FlocksVolumeOverlapsTable::FlocksVolumeOverlapsTable(AFlocksWorld* InWorld) : FlocksVolumeTable(InWorld)
{
	Data.SetNum(MAX_VOLUMES);
}

FlocksVolumeOverlapsTable::~FlocksVolumeOverlapsTable()
{

}

FlocksVolumeOverlapsTable::FTableData* FlocksVolumeOverlapsTable::Lock()
{
	TableLock.Lock();
	return Data.GetData();
}

void FlocksVolumeOverlapsTable::Unlock()
{
	TableLock.Unlock();
}

uint16 FlocksVolumeOverlapsTable::AddVolume(VOLUME_HANDLE Volume, const FAddVolumeData& AddVolumeData)
{
	uint16 Index = LookUpTable->AddVolume(Volume);

	if (Index != INVALID_VOLUME_HANDLE_INDEX)
	{
		Lock();
		Data[Index].NumBoidsInVolume = 0;
		Data[Index].BoidsInVolume.SetNum(MAX_BOIDS);
		Unlock();
	}

	return Index;
}

void FlocksVolumeOverlapsTable::RemoveVolume(VOLUME_HANDLE Volume)
{
	uint16 Index = Find(Volume);
	LookUpTable->RemoveVolume(Volume);

	if (Index != INVALID_VOLUME_HANDLE_INDEX)
	{
		Lock();
		Data[Index] = Data[Size()];
		Unlock();
	}
}

void FlocksVolumeOverlapsTable::RecalculateOverlaps()
{
	TArray<FlocksStateTable::FTableData> StateTableDataCopy;
	StateTableDataCopy.SetNum(MAX_BOIDS);

	FlocksStateTable::FTableData* StateTableData = World->StateTable->Lock();
	memcpy(StateTableDataCopy.GetData(), StateTableData, sizeof(FlocksStateTable::FTableData) * MAX_BOIDS);
	World->StateTable->Unlock();

	FlocksVolumeOverlapsTable::FTableData* VolumeOverlapsData = Lock();

	TArray<FThreadSafeCounter> Counters;
	Counters.SetNum(MAX_VOLUMES);
	
	ParallelFor(World->StateTable->Size(), [this, &Counters, StateTableDataCopy, &VolumeOverlapsData](int32 Index)
		{
			BOID_HANDLE Boid = World->StateTable->Get(Index);
			int32 NumVolumes = StateTableDataCopy[Index].NumVolumesAffecting;

			for (int32 i = 0; i < NumVolumes; ++i)
			{
				int32 VolumeIndex = StateTableDataCopy[Index].VolumesAffectingIndices[i];
				VolumeOverlapsData[VolumeIndex].BoidsInVolume[Counters[VolumeIndex].GetValue()] = Boid;

				Counters[VolumeIndex].Increment();
			}
		});

	for (int32 i = 0; i < MAX_VOLUMES; ++i)
	{
		VolumeOverlapsData[i].NumBoidsInVolume = Counters[i].GetValue();
	}

	Unlock();
}
