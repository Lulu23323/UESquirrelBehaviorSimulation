// Copyright 2021 Justin Kiesskalt, All Rights Reserved.

#include "Utils/IndexArray.h"

IndexArray::IndexArray(uint32 MaxSize) :
	ArrayMax(MaxSize)
{
	NextFree = new uint16[MaxSize];
	Reset();
}

IndexArray::~IndexArray()
{
	delete[] NextFree;
}

uint16 IndexArray::Add()
{
	if (ArrayUsed < ArrayMax)
	{
		auto result = ArrayNext;
		ArrayNext = NextFree[result];
		ArrayUsed += 1;
		
		return result;
	}
	
	return 0xffff;
}

void IndexArray::Remove(uint16 Index)
{
	if (Index < ArrayMax)
	{
		NextFree[Index] = ArrayNext;
		ArrayNext = Index;
		ArrayUsed -= 1;
	}
}

bool IndexArray::IsFull() const
{
	return ArrayUsed >= ArrayMax;
}


void IndexArray::Reset()
{
	for (uint32 i = 0; i < ArrayMax; ++i)
		NextFree[i] = i + 1;
	
	ArrayNext = 0;
	ArrayUsed = 0;
}
