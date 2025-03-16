// Copyright 2021 Justin Kiesskalt, All Rights Reserved.

#include "FlocksLookUpTable.h"

BoidLookUpTable::BoidLookUpTable()
{
	Boids.SetNum(MAX_BOIDS);
	BoidLookUpIndices.SetNum(MAX_BOIDS + 1);

	Reset();
}

BoidLookUpTable::~BoidLookUpTable()
{
}

uint16 BoidLookUpTable::AddBoid(BOID_HANDLE Boid)
{
	uint16 ObjectIndex = BoidHandleExtractIndex(Boid);
	if (ObjectIndex != INVALID_BOID_HANDLE_INDEX)
	{
		if (BoidLookUpIndices[ObjectIndex] != INVALID_BOID_HANDLE_INDEX)
		{
			//WARNING HERE
		}
		else
		{
			Boids[BoidTableSize] = Boid;
			BoidLookUpIndices[ObjectIndex] = BoidTableSize++;
		}

		return BoidLookUpIndices[ObjectIndex];
	}

	return INVALID_BOID_HANDLE_INDEX;
}

uint16 BoidLookUpTable::RemoveBoid(BOID_HANDLE Boid)
{
	uint16 ObjectIndex = BoidHandleExtractIndex(Boid);

	if (ObjectIndex != INVALID_BOID_HANDLE_INDEX)
	{
		auto SwapIndex = BoidLookUpIndices[ObjectIndex];

		if (SwapIndex != INVALID_BOID_HANDLE_INDEX)
		{
			auto LastObject = Boids[BoidTableSize - 1];
			auto LastObjectIndex = BoidHandleExtractIndex(LastObject);

			Boids[SwapIndex] = LastObject;
			BoidLookUpIndices[LastObjectIndex] = SwapIndex;

			BoidLookUpIndices[ObjectIndex] = INVALID_BOID_HANDLE_INDEX;
			BoidTableSize -= 1;

			return SwapIndex;
		}
	}

	return INVALID_BOID_HANDLE_INDEX;
}

void BoidLookUpTable::Reset()
{
	memset(BoidLookUpIndices.GetData(), UINT8_MAX, (MAX_BOIDS + 1) * sizeof(uint16));
	memset(Boids.GetData(), UINT8_MAX, MAX_BOIDS * sizeof(BOID_HANDLE));

	BoidTableSize = 0;
}

uint16 BoidLookUpTable::FindBoid(BOID_HANDLE Boid) const
{
	return BoidLookUpIndices[BoidHandleExtractIndex(Boid)];
}

bool BoidLookUpTable::ContainsBoid(BOID_HANDLE Boid) const
{
	return FindBoid(Boid) != INVALID_BOID_HANDLE_INDEX;
}

VolumeLookUpTable::VolumeLookUpTable()
{
	Volumes.SetNum(MAX_VOLUMES);
	VolumeLookUpIndices.SetNum(MAX_VOLUMES + 1);
	
	//Add an entry onto the end thats invalid volume index
	Reset();
}

VolumeLookUpTable::~VolumeLookUpTable()
{
}

uint16 VolumeLookUpTable::AddVolume(VOLUME_HANDLE Volume)
{
	uint16 ObjectIndex = VolumeHandleExtractIndex(Volume);
	if (ObjectIndex != INVALID_VOLUME_HANDLE_INDEX)
	{
		if (VolumeLookUpIndices[ObjectIndex] != INVALID_VOLUME_HANDLE_INDEX)
		{
			//WARNING HERE
		}
		else
		{
			Volumes[VolumeTableSize] = Volume;
			VolumeLookUpIndices[ObjectIndex] = VolumeTableSize++;
		}

		return VolumeLookUpIndices[ObjectIndex];
	}

	return INVALID_VOLUME_HANDLE_INDEX;
}

uint16 VolumeLookUpTable::RemoveVolume(VOLUME_HANDLE Volume)
{
	uint16 ObjectIndex = VolumeHandleExtractIndex(Volume);

	if (ObjectIndex != INVALID_VOLUME_HANDLE_INDEX)
	{
		auto SwapIndex = VolumeLookUpIndices[ObjectIndex];

		if (SwapIndex != INVALID_VOLUME_HANDLE_INDEX)
		{
			auto LastObject = Volumes[VolumeTableSize - 1];
			auto LastObjectIndex = VolumeHandleExtractIndex(LastObject);

			Volumes[SwapIndex] = LastObject;
			VolumeLookUpIndices[LastObjectIndex] = SwapIndex;

			VolumeLookUpIndices[ObjectIndex] = INVALID_VOLUME_HANDLE_INDEX;
			VolumeTableSize -= 1;

			return SwapIndex;
		}
	}

	return INVALID_VOLUME_HANDLE_INDEX;
}

void VolumeLookUpTable::Reset()
{
	memset(VolumeLookUpIndices.GetData(), UINT8_MAX, (MAX_VOLUMES + 1) * sizeof(uint16));
	memset(Volumes.GetData(), UINT8_MAX, MAX_VOLUMES * sizeof(VOLUME_HANDLE));

	VolumeTableSize = 0;
}

uint16 VolumeLookUpTable::FindVolume(VOLUME_HANDLE Volume) const
{
	return VolumeLookUpIndices[VolumeHandleExtractIndex(Volume)];
}

bool VolumeLookUpTable::ContainsVolume(VOLUME_HANDLE Volume) const
{
	return FindVolume(Volume) != INVALID_VOLUME_HANDLE_INDEX;
}