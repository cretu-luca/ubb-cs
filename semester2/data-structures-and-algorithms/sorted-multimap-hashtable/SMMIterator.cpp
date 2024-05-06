#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d) {
    this->heap = new Heap(d.relation, d.capacity);
    for(int i = 0; i < map.capacity; i++) {
        if(map.elements[i]) {
            heap->add(make_pair(map.elements[i]->key, map.elements[i]->values[0]));
            this->heap->valueIndices[i] = 1;
            heap->currentNodes[map.hashFunction(map.elements[i]->key, map.capacity)] = map.elements[i];
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
            heap->currentNodes[map.hashFunction(map.elements[i]->key, map.capacity)] = map.elements[i];
        }
    }
}

void SMMIterator::next() const {
    if (!valid())
        throw std::exception();

    TElem currentMin = this->heap->getMinAndRemove();
    int key = currentMin.first;
    int hashKey = map.hashFunction(key, map.capacity);

    if (heap->currentNodes[hashKey] != nullptr) {
        int valueIndex = this->heap->valueIndices[hashKey];
        if (valueIndex < heap->currentNodes[hashKey]->numberOfValues) {
            heap->add(make_pair(heap->currentNodes[hashKey]->key, heap->currentNodes[hashKey]->values[valueIndex]));
            this->heap->valueIndices[hashKey]++;
        } else {
            if (heap->currentNodes[hashKey]->next != nullptr) {
                heap->currentNodes[hashKey] = heap->currentNodes[hashKey]->next;
                this->heap->valueIndices[map.hashFunction(heap->currentNodes[hashKey]->key, map.capacity)] = 0;
                heap->add(make_pair(heap->currentNodes[hashKey]->key, heap->currentNodes[hashKey]->values[0]));
                this->heap->valueIndices[map.hashFunction(heap->currentNodes[hashKey]->key, map.capacity)]++;
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

