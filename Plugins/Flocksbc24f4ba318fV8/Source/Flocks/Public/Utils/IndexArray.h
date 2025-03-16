// Copyright 2021 Justin Kiesskalt, All Rights Reserved.

#pragma once
#include "CoreMinimal.h"

struct IndexArray
{
	IndexArray(uint32 MaxSize);
	virtual ~IndexArray();

	uint16 Add();
	void Remove(uint16 Index);

	void Reset();
	bool IsFull() const;
	
public:
	uint32 ArrayMax = 0;
	uint32 ArrayUsed = 0;
	uint16 ArrayNext = 0;
	uint16* NextFree = nullptr;
};
