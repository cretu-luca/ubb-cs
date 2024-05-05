#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d) {
    this->heap = new Heap(d.relation, d.capacity);
    for(int i = 0; i < d.capacity; i++)
        if(d.elements[i])
            heap->add(make_pair(d.elements[i]->key, d.elements[i]->values[0]));
}

void SMMIterator::first(){
    delete heap;
    this->heap = new Heap(map.relation, map.capacity);
    for(int i = 0; i < map.capacity; i++)
        if(map.elements[i])
            heap->add(make_pair(map.elements[i]->key, map.elements[i]->values[0]));
}

void SMMIterator::next() {
    if(!valid())
        throw std::exception();

    TElem currentMin = this->heap->getMinAndRemove();

    int key = currentMin.first;
    int hashKey = map.hashFunction(key, map.capacity);
    Node* currentNode = map.elements[hashKey];

    while (currentNode != nullptr && currentNode->key != key)
        currentNode = currentNode->next;

    if (currentNode != nullptr) {
        if (currentNode->next != nullptr) {
            heap->add(make_pair(currentNode->next->key, currentNode->next->values[0]));
        } else if (currentMin.second < currentNode->values[currentNode->numberOfValues - 1]) {
            for (int i = 0; i < currentNode->numberOfValues; i++) {
                if (currentNode->values[i] == currentMin.second && i < currentNode->numberOfValues - 1) {
                    heap->add(make_pair(currentNode->key, currentNode->values[i + 1]));
                    break;
                }
            }
        }
    }
}

bool SMMIterator::valid() const {
    return this->heap->length != 0;
}

TElem SMMIterator::getCurrent() const {
    if(!valid())
        throw std::exception();

    return this->heap->elements[1];
}

