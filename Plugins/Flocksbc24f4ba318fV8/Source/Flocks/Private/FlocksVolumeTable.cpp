// Copyright 2021 Justin Kiesskalt, All Rights Reserved.

#include "FlocksVolumeTable.h"
#include "FlocksWorld.h"
#include "FlocksDatabaseHeader.h"
#include "FlocksLookUpTable.h"
#include "Utils/IndexArray.h"

FlocksVolumeTable::FlocksVolumeTable(AFlocksWorld* InWorld) : FlocksTable(InWorld)
{
	LookUpTable = new VolumeLookUpTable();
}

FlocksVolumeTable::~FlocksVolumeTable()
{
	delete LookUpTable;
}

uint16 FlocksVolumeTable::Size() const
{
	return LookUpTable->VolumeTableSize;
}

uint16 FlocksVolumeTable::Find(VOLUME_HANDLE Volume) const
{
	return LookUpTable->FindVolume(Volume);
}