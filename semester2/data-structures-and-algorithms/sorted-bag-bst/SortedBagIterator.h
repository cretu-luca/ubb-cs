#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

public:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

	int index;
	int* array;
	int size;

public:
	TComp getCurrent() const;
	bool valid() const;
	void next();
	void first();

	static void DFS(int current, int* array, int& index, const SortedBag& bag);
};

