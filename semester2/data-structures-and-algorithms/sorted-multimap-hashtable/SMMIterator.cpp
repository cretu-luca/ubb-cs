#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d) {
    this->heap = new Heap(d.relation, d.capacity);
    for(int i = 0; i < map.capacity; i++) {
        if(map.elements[i]) {
            heap->add(make_pair(map.elements[i]->key, map.elements[i]->values[0]));
            this->heap->valueIndices[i] = 1;
        }
    }
}

void SMMIterator::first() {
    delete heap;
    this->heap = new Heap(map.relation, map.capacity);
    for(int i = 0; i < map.capacity; i++) {
        if(map.elements[i]) {
            heap->add(make_pair(map.elements[i]->key, map.elements[i]->values[0]));
            this->heap->valueIndices[i] = 1;
        }
    }
}

void SMMIterator::next() const {
    if (!valid())
        throw std::exception();

    TElem currentMin = this->heap->getMinAndRemove();
    int key = currentMin.first;
    int hashKey = map.hashFunction(key, map.capacity);
    Node* currentNode = map.elements[hashKey];

    while (currentNode != nullptr && currentNode->key != key)
        currentNode = currentNode->next;

    if (currentNode != nullptr) {
        int valueIndex = this->heap->valueIndices[hashKey];
        if (valueIndex < currentNode->numberOfValues) {
            heap->add(make_pair(currentNode->key, currentNode->values[valueIndex]));
            this->heap->valueIndices[hashKey]++;
        } else {
            if (currentNode->next != nullptr) {
                currentNode = currentNode->next;
                this->heap->valueIndices[map.hashFunction(currentNode->key, map.capacity)] = 0;
                heap->add(make_pair(currentNode->key, currentNode->values[0]));
                this->heap->valueIndices[map.hashFunction(currentNode->key, map.capacity)]++;
            }
        }
    }
}


bool SMMIterator::valid() const {
    return this->heap->length > 0;
}

TElem SMMIterator::getCurrent() const {
    if(!valid())
        throw std::exception();

    return this->heap->elements[1];
}

