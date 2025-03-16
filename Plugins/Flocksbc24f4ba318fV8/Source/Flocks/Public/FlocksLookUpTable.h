// Copyright 2021 Justin Kiesskalt, All Rights Reserved.

#pragma once
#include "FlocksTypes.h"

struct IndexArray;

struct FLOCKS_API BoidLookUpTable
{
public:
	BoidLookUpTable();
	~BoidLookUpTable();

	void Reset();

	uint16 AddBoid(BOID_HANDLE Boid);
	uint16 RemoveBoid(BOID_HANDLE Boid);

	//Converts sparse index into packed index. Use when indexing a table array instead of using the index.
	uint16 FindBoid(BOID_HANDLE Boid) const;
	bool ContainsBoid(BOID_HANDLE Boid) const;

public:
	TArray<BOID_HANDLE> Boids; //packed
	TArray<uint16> BoidLookUpIndices; //sparse
	uint32 BoidTableSize = 0;
};

struct FLOCKS_API VolumeLookUpTable
{
public:
	VolumeLookUpTable();
	~VolumeLookUpTable();

	void Reset();
	
	uint16 AddVolume(VOLUME_HANDLE Volume);
	uint16 RemoveVolume(VOLUME_HANDLE Volume);

	uint16 FindVolume(VOLUME_HANDLE Volume) const;
	bool ContainsVolume(VOLUME_HANDLE Volume) const;

public:
	TArray<VOLUME_HANDLE> Volumes; //packed
	TArray<uint16> VolumeLookUpIndices; //sparse
	uint32 VolumeTableSize = 0;
};