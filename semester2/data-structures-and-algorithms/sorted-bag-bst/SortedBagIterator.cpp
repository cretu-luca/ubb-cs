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
	this->array = new int[this->size];
	this->index = 0;

	int currentIndex = 0;
	DFS(this->bag.root, this->array, currentIndex, this->bag);
}

TComp SortedBagIterator::getCurrent() const {
	if (!valid()) {
		throw std::exception();
	}

	return this->bag.info[this->array[this->index]];
}

bool SortedBagIterator::valid() const {
	return this->index < this->size;
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