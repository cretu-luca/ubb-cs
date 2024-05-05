#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

int multiplicationMethodFunction(int key, int capacity) {
    float A = 0.6180339887;
    return floor(capacity * (key * A - floor(key * A)));
}

SortedMultiMap::SortedMultiMap(Relation r) {
	this->elements = new Node*[this->capacity];
	for (int i = 0; i < this->capacity; i++) {
		this->elements[i] = nullptr;
	}
	this->relation = r;
	this->numberOfElements = 0;
}

void SortedMultiMap::add(TKey c, TValue v) {
	if(float(this->numberOfElements) / float(this->capacity) >= this->loadFactorThreshold)
		this->resize();

	int hashKey = this->hashFunction(c, this->capacity);

	Node* hashHead = this->elements[hashKey];
	Node* previous = nullptr;

	if(hashHead == nullptr) {
		Node* newHashHead = new Node;
		newHashHead->values = new TValue[newHashHead->valueArrayCapacity];
		newHashHead->numberOfValues = 0;
		newHashHead->key = c;
		newHashHead->values[newHashHead->numberOfValues++] = v;
		newHashHead->next = nullptr;

		this->elements[hashKey] = newHashHead;
	} else {
		while(hashHead != nullptr) {
			if(hashHead->key == c) {
				if(hashHead->numberOfValues == hashHead->valueArrayCapacity - 1) {
					auto newValues = new TValue[hashHead->valueArrayCapacity * 2];
					for(int i = 0; i < hashHead->numberOfValues; i++)
						newValues[i] = hashHead->values[i];

					delete[] hashHead->values;
					hashHead->values = newValues;
					hashHead->valueArrayCapacity = hashHead->valueArrayCapacity * 2;

					hashHead->values[hashHead->numberOfValues++] = v;
				} else {
					hashHead->values[hashHead->numberOfValues++] = v;
				}

				break;
			}

			if(relation(hashHead->key, c)) {
				Node* newHashHead = new Node;
				newHashHead->values = new TValue[newHashHead->valueArrayCapacity];
				newHashHead->numberOfValues = 0;
				newHashHead->key = c;
				newHashHead->values[newHashHead->numberOfValues++] = v;

				if(previous == nullptr) {
					elements[hashKey] = newHashHead;
					newHashHead->next = hashHead;
				} else {
					previous->next = newHashHead;
					newHashHead->next = hashHead;
				}

				break;
			}

			previous = hashHead;
			hashHead = hashHead->next;
		}

		if (hashHead == nullptr) {
			Node* newHashHead = new Node;
			newHashHead->key = c;
			newHashHead->values = new TValue[newHashHead->valueArrayCapacity];
			newHashHead->numberOfValues = 0;
			newHashHead->values[newHashHead->numberOfValues++] = v;
			newHashHead->next = nullptr;

			previous->next = newHashHead;
		}
	}

	this->numberOfElements++;
}

vector<TValue> SortedMultiMap::search(TKey c) const {
	int hashKey = this->hashFunction(c, this->capacity);
	vector<TValue> values;

	Node* hashHead = this->elements[hashKey];
	while(hashHead != nullptr) {
		if(hashHead->key == c) {
			for(int i = 0; i < hashHead->numberOfValues; i++) {
				values.push_back(hashHead->values[i]);
			}

			break;
		}

		hashHead = hashHead->next;
	}

	return values;
}

bool SortedMultiMap::remove(TKey c, TValue v) {
	int hashKey = this->hashFunction(c, this->capacity);
	Node* hashHead = this->elements[hashKey];
	Node* previous = nullptr;

	while(hashHead != nullptr) {
		if(hashHead->key == c) {
			for(int i = 0 ; i < hashHead->numberOfValues; i++) {
				if(hashHead->values[i] == v) {
					if(hashHead->numberOfValues == 1) {
						if(previous) {
							previous->next = hashHead->next;
						} else {
							elements[hashKey] = hashHead->next;
						}

						delete[] hashHead->values;
						delete hashHead;
					} else {
						hashHead->values[i] = hashHead->values[hashHead->numberOfValues - 1];
						hashHead->numberOfValues--;
					}

					this->numberOfElements--;
					return true;
				}
			}
		}

		previous = hashHead;
		hashHead = hashHead->next;
	}

	return false;
}

int SortedMultiMap::size() const {
	return this->numberOfElements;
}

bool SortedMultiMap::isEmpty() const {
	return this->numberOfElements == 0;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

void SortedMultiMap::resize() {
	int newCapacity = this->capacity * 2;
	auto newElements = new Node*[newCapacity];

	for (int i = 0; i < newCapacity; i++)
		newElements[i] = nullptr;

	for(int i = 0; i < this->capacity; i++) {
		Node* currentNode = this->elements[i];
		while(currentNode != nullptr) {
			Node* nextNode = currentNode->next;

			int newHashKey = this->hashFunction(currentNode->key, newCapacity);
			currentNode->next = newElements[newHashKey];
			newElements[newHashKey] = currentNode;

			currentNode = nextNode;
		}
	}

	delete[] this->elements;
	this->elements = newElements;
	this->capacity = newCapacity;
}

SortedMultiMap::~SortedMultiMap() {
	for(int i = 0; i < this->capacity; i++) {
		Node* current = this->elements[i];

		while(current != nullptr) {
			Node* next = current->next;

			delete[] current->values;
			delete current;

			current = next;
		}
	}

	delete[] this->elements;
}
