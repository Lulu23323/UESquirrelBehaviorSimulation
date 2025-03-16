// Copyright 2021 Justin Kiesskalt, All Rights Reserved.

#pragma once
#include "FlocksTypes.h"
#include "FlocksTable.h"

struct VolumeLookUpTable;

struct FLOCKS_API FlocksVolumeTable : public FlocksTable
{
public:
	FlocksVolumeTable(AFlocksWorld* InWorld);
	virtual ~FlocksVolumeTable();

	uint16 Find(VOLUME_HANDLE Volume) const;
	virtual uint16 Size() const override;

protected:
	VolumeLookUpTable* LookUpTable;
};
