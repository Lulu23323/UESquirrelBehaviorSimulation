// Copyright 2021 Justin Kiesskalt, All Rights Reserved.

#pragma once
#include "FlocksTypes.h"

struct IndexArray;

struct FLOCKS_API FlocksDatabaseHeader
{
	FlocksDatabaseHeader();
	~FlocksDatabaseHeader();

	BOID_HANDLE AddBoid();
	bool RemoveBoid(BOID_HANDLE Boid);
	bool IsValidBoid(BOID_HANDLE Boid) const;

	VOLUME_HANDLE AddVolume();
	bool RemoveVolume(VOLUME_HANDLE Volume);
	bool IsValidVolume(VOLUME_HANDLE Volume) const;

	void Reset();

	BOID_HANDLE GetBoid(uint16 Index) const;
	uint16 NumBoids() const;

public:
	TArray<uint8> BoidGenerationNumbers;
	TArray<uint8> VolumeGenerationNumbers;
	TArray<BOID_HANDLE> Boids; //packed
	TArray<VOLUME_HANDLE> Volumes; //packed

	IndexArray* BoidInfo;
	IndexArray* VolumeInfo;
};
