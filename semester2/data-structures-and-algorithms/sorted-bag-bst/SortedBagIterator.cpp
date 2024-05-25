#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>
#include <iostream>

using namespace std;


void SortedBagIterator::DFS(int current, int* array, int& index, const SortedBag& bag) {
	if (current != -1) {
		DFS(bag.left[current], array, index, bag);
		array[index++] = current;
		DFS(bag.right[current], array, index, bag);
	}
}

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	this->size = bag.size();
	this->array = new int[size];
	this->index = 0;

	int currentIndex = 0;
	DFS(bag.root, array, currentIndex, bag);
}

TComp SortedBagIterator::getCurrent() const {
	if (!valid()) {
		throw std::exception();
	}

	return bag.info[this->array[index]];
}

bool SortedBagIterator::valid() const {
	return index < size;
}

void SortedBagIterator::next() {
	if (!valid()) {
		throw std::exception();
	}

	this->index++;
}

void SortedBagIterator::first() {
	this->index = 0;
}