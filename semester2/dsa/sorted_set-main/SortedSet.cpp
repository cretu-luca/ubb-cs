#include "SortedSet.h"
#include "SortedSetIterator.h"

/*
 * Complexity:
 * Theta(1)
 */
SortedSet::SortedSet(Relation r) {
    this->capacity = 10;
    this->sizeOfArray = 0;
    this->elements = new TElem[this->capacity];
    this->relation = r;
}

/*
 * Complexity:
 * Best case: Theta(1)
 * Worst case: Theta(sizeOfArray)
 * Total case: O(sizeOfArray)
 */
bool SortedSet::add(TComp elem) {
    if (!search(elem)) {
        if(this->size() == this->capacity)
            this->resize();

        int index = 0;
        while(index < this->sizeOfArray && this->relation(this->elements[index], elem))
            index++;

        for (int i = this->sizeOfArray; i > index; i--)
            this->elements[i] = this->elements[i - 1];

        this->elements[index] = elem;
        this->sizeOfArray++;

        return true;
    }
    else
        return false;
}

/*
 * Complexity:
 * Theta(sizeOfArray)
 */
void SortedSet::resize() {
    this->capacity *= 2;
    auto *newElements = new TComp[this->capacity];
    for(int i = 0; i < size(); i++)
        newElements[i] = this->elements[i];

    delete[] this->elements;
    this->elements = newElements;
}

/*
 * Complexity:
 * Best case: Theta(1)
 * Worst case: Theta(sizeOfArray)
 * Total case: O(sizeOfArray)
 */
bool SortedSet::remove(TComp elem) {
	if(search(elem)){
        int index = getIndex(elem);
        for(int i = index; i < size(); i++)
            this->elements[i] = this->elements[i+1];

        this->sizeOfArray--;

        return true;
    }
    else
	    return false;
}

/*
 * Complexity:
 * Best case: Theta(1)
 * Worst case: Theta(sizeOfArray)
 * Total case: O(sizeOfArray)
 */
int SortedSet::getIndex(TComp elem) const {
    if(search(elem)){
        for(int i = 0; i < this->sizeOfArray; i++)
            if (this->elements[i] == elem)
                return i;
    }
    else
        return -1;
}

/*
 * Complexity:
 * Best case: Theta(1)
 * Worst case: Theta(sizeOfArray)
 * Total case: O(sizeOfArray)
 */
bool SortedSet::search(TComp elem) const {
	for(int i = 0; i < this->size(); i++)
        if(this->elements[i] == elem)
            return true;

	return false;
}

/*
 * Complexity:
 * Theta(1)
 */
int SortedSet::size() const {
    return this->sizeOfArray;

}

/*
 * Complexity:
 * Theta(1)
 */
bool SortedSet::isEmpty() const {
	return this->sizeOfArray == 0;
}

/*
 * Complexity:
 * Theta(1)
 */
SortedSetIterator SortedSet::iterator() const {
	return *this;
}

/*
 * Complexity:
 * Theta(1)
 */
SortedSet::~SortedSet() {
	delete[] this->elements;
}


