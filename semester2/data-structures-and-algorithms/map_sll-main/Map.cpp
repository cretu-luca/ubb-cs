#include "Map.h"
#include "MapIterator.h"

// BC = WC = TC = theta(1)
Map::Map() {
    this->head = nullptr;
}

// BC = WC = TC = theta(1)
Map::~Map() {
	Node* currentNode = head;
    while(currentNode != nullptr){
        Node* nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
    }
}

// BC = theta(1), WC = theta(n), TC = O(n)
TValue Map::add(TKey c, TValue v){
    Node* currentNode = this->head;
    while(currentNode != nullptr) {
        if(currentNode->info.first == c) {
            TValue oldValue = currentNode->info.second;
            currentNode->info.second = v;

            return oldValue;
        }
        currentNode = currentNode->next;
    }

    Node* newTElem = new Node{std::make_pair(c, v), head};
    this->head = newTElem;

    return NULL_TVALUE;
}

// BC = theta(1), WC = theta(n), TC = O(n)
TValue Map::search(TKey c) const{
    Node* currentNode = this->head;
    while(currentNode != nullptr) {
        if(currentNode->info.first == c)
            return currentNode->info.second;

        currentNode = currentNode->next;
    }

	return NULL_TVALUE;
}

// BC = theta(1), WC = theta(n), TC = O(n)
TValue Map::remove(TKey c){
    Node* currentNode = this->head;
    Node* previousNode = nullptr;

    while(currentNode != nullptr) {
        if(currentNode->info.first == c) {
            TValue tValue = currentNode->info.second;

            if(previousNode == nullptr)
                this->head = currentNode->next;
            else
                previousNode->next = currentNode->next;

            delete currentNode;
            return tValue;
        }

        previousNode = currentNode;
        currentNode = currentNode->next;
    }

	return NULL_TVALUE;
}

// BC = WC = TC = theta(n)
int Map::size() const {
	int size = 0;
    Node* currentNode = this->head;
    while(currentNode != nullptr){
        size++;
        currentNode = currentNode->next;
    }

	return size;
}

// BC = WC = TC = theta(1)
bool Map::isEmpty() const{
    return this->head == nullptr;
}

// BC = WC = TC = theta(1)
MapIterator Map::iterator() const {
	return MapIterator(*this);
}



