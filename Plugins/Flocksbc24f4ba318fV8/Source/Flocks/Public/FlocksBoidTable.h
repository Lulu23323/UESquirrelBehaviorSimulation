// Copyright 2021 Justin Kiesskalt, All Rights Reserved.

#pragma once
#include "FlocksLookUpTable.h"
#include "FlocksTypes.h"
#include "FlocksTable.h"

struct FLOCKS_API FlocksBoidTable : public FlocksTable
{
public:
	FlocksBoidTable(AFlocksWorld* InWorld);
	virtual ~FlocksBoidTable();

	uint16 Find(BOID_HANDLE Boid) const;
	BOID_HANDLE Get(uint16 Index) const;
	virtual uint16 Size() const override;

protected:
	BoidLookUpTable* LookUpTable;
};
