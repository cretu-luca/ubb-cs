#include "SortedSetIterator.h"
#include <exception>

using namespace std;

/*
 * Complexity:
 * Theta(1)
 */
SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
	this->currentIndex = 0;
}

/*
 * Complexity:
 * Theta(1)
 */
void SortedSetIterator::first() {
    this->currentIndex = 0;
}

/*
 * Complexity:
 * Theta(1)
 */
void SortedSetIterator::next() {
    if(!valid())
        throw std::exception();

    this->currentIndex++;
}

/*
 * Complexity:
 * Theta(1)
 */
TElem SortedSetIterator::getCurrent()
{
    if(!valid())
        throw std::exception();

	return this->multime.elements[this->currentIndex];
}

/*
 * Complexity:
 * Theta(1)
 */
bool SortedSetIterator::valid() const {
	return this->currentIndex < this->multime.size();
}

