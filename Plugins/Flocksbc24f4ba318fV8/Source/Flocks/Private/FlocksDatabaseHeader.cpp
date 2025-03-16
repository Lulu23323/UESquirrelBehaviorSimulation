// Copyright 2021 Justin Kiesskalt, All Rights Reserved.

#include "FlocksDatabaseHeader.h"
#include "Flocks.h"

#include "Utils/IndexArray.h"

FlocksDatabaseHeader::FlocksDatabaseHeader()
{
	BoidGenerationNumbers.SetNum(MAX_BOIDS);
	VolumeGenerationNumbers.SetNum(MAX_VOLUMES);
	Boids.SetNum(MAX_BOIDS);
	Volumes.SetNum(MAX_VOLUMES);
	
	BoidInfo = new IndexArray(MAX_BOIDS);
	VolumeInfo = new IndexArray(MAX_VOLUMES);

	Reset();
}

FlocksDatabaseHeader::~FlocksDatabaseHeader()
{
	delete BoidInfo;
	delete VolumeInfo;
}

BOID_HANDLE FlocksDatabaseHeader::AddBoid()
{
	uint16 NextIndex = BoidInfo->Add();
	if (NextIndex != INVALID_BOID_HANDLE_INDEX)
	{
		check(Boids[NextIndex] == INVALID_BOID_HANDLE);

		Boids[NextIndex] = MakeBoidHandle(BoidGenerationNumbers[NextIndex]++, NextIndex);
		return Boids[NextIndex];
	}

	UE_LOG(FlocksLog, Warning, TEXT("Failure to add Boid: Most likely exceeded the max boid count of %i"), MAX_BOIDS);

	return INVALID_BOID_HANDLE;
}

bool FlocksDatabaseHeader::RemoveBoid(BOID_HANDLE Boid)
{
	if (!IsValidBoid(Boid))
		return false;

	uint16 ObjectIndex = BoidHandleExtractIndex(Boid);
	Boids[ObjectIndex] = INVALID_BOID_HANDLE;
	BoidInfo->Remove(ObjectIndex);
	return true;
}

bool FlocksDatabaseHeader::IsValidBoid(BOID_HANDLE Boid) const
{
	return Boid != INVALID_BOID_HANDLE && (Boids[BoidHandleExtractIndex(Boid)] == Boid);
}

VOLUME_HANDLE FlocksDatabaseHeader::AddVolume()
{
	uint16 NextIndex = VolumeInfo->Add();
	if (NextIndex != INVALID_VOLUME_HANDLE_INDEX)
	{
		check(Volumes[NextIndex] == INVALID_VOLUME_HANDLE);

		Volumes[NextIndex] = MakeVolumeHandle(VolumeGenerationNumbers[NextIndex]++, NextIndex);
		return Volumes[NextIndex];
	}

	UE_LOG(FlocksLog, Warning, TEXT("Failure to add Volume: Most likely exceeded the max volume count of %i"), MAX_VOLUMES);

	return INVALID_VOLUME_HANDLE;
}

bool FlocksDatabaseHeader::RemoveVolume(VOLUME_HANDLE Volume)
{
	if (!IsValidVolume(Volume))
		return false;

	uint16 ObjectIndex = VolumeHandleExtractIndex(Volume);
	Volumes[ObjectIndex] = INVALID_VOLUME_HANDLE;
	VolumeInfo->Remove(ObjectIndex);
	return true;
}

bool FlocksDatabaseHeader::IsValidVolume(VOLUME_HANDLE Volume) const
{
	return Volume != INVALID_VOLUME_HANDLE && (Volumes[VolumeHandleExtractIndex(Volume)] == Volume);
}

void FlocksDatabaseHeader::Reset()
{
	for(int32 i = 0; i < MAX_VOLUMES; i++)
	{
		Volumes[i] = INVALID_VOLUME_HANDLE;
		VolumeGenerationNumbers[i] = 0;
	}

	for(int32 i = 0; i < MAX_BOIDS; i++)
	{
		Boids[i] = INVALID_BOID_HANDLE;
		BoidGenerationNumbers[i] = 0;
	}
	
	BoidInfo->Reset();
	VolumeInfo->Reset();
}

BOID_HANDLE FlocksDatabaseHeader::GetBoid(uint16 Index) const
{
	return Boids[Index];
}

uint16 FlocksDatabaseHeader::NumBoids() const
{
	return BoidInfo->ArrayUsed;
}
