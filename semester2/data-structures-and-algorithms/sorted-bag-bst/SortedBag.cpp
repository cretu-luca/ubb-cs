#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

SortedBag::SortedBag(Relation r) {
    this->capacity = 20;
    this->sizeOfArray = 0;
    this->firstEmpty = 0;
    this->info = new int[this->capacity];
    this->left = new int[this->capacity];
    this->right = new int[this->capacity];
    this->nextEmpty = new int[this->capacity];
    this->parent = new int[this->capacity];

    for (int i = 0; i < this->capacity; ++i) {
        this->info[i] = NULL_TCOMP;
        this->left[i] = this->right[i] = -1;
        this->parent[i] = -1;
        this->nextEmpty[i] = i + 1;
    }

    this->nextEmpty[this->capacity - 1] = -1;
    this->root = -1;
    this->relation = r;
}

void SortedBag::add(TComp e) {
    if (this->sizeOfArray == capacity - 1) {
        resize();
    }

    int newNode = this->firstEmpty;
    this->firstEmpty = this->nextEmpty[this->firstEmpty];

    this->info[newNode] = e;
    this->left[newNode] = this->right[newNode] = -1;
    this->parent[newNode] = -1;

    if (this->root == -1) {
        this->root = newNode;
    } else {
        int current = this->root;
        int currentParent = -1;

        while (current != -1) {
            currentParent = current;
            if (this->relation(e, this->info[current])) {
                current = this->left[current];
            } else {
                current = this->right[current];
            }
        }

        if (this->relation(e, this->info[currentParent])) {
            this->left[currentParent] = newNode;
        } else {
            this->right[currentParent] = newNode;
        }

        this->parent[newNode] = currentParent;
    }

    this->sizeOfArray++;
}

void SortedBag::resize() {
    int newCapacity = 2 * this->capacity;

    int* newInfo = new int[newCapacity];
    int* newLeft = new int[newCapacity];
    int* newRight = new int[newCapacity];
    int* newNextEmpty = new int[newCapacity];
    int* newParent = new int[newCapacity];

    for (int i = 0; i < this->capacity; ++i) {
        newInfo[i] = this->info[i];
        newLeft[i] = this->left[i];
        newRight[i] = this->right[i];
        newNextEmpty[i] = this->nextEmpty[i];
        newParent[i] = this->parent[i];
    }

    for (int i = this->capacity; i < newCapacity; ++i) {
        newInfo[i] = NULL_TCOMP;
        newLeft[i] = newRight[i] = -1;
        newParent[i] = -1;
        newNextEmpty[i] = i + 1;
    }

    newNextEmpty[newCapacity - 1] = -1;

    delete[] info;
    delete[] left;
    delete[] right;
    delete[] nextEmpty;
    delete[] parent;

    this->info = newInfo;
    this->left = newLeft;
    this->right = newRight;
    this->nextEmpty = newNextEmpty;
    this->parent = newParent;
    this->firstEmpty = this->capacity;
    this->capacity = newCapacity;
}

bool SortedBag::remove(TComp e) {
    int current = this->root;
    int currentParent = -1;
    int side = 0;

    while (current != -1 && this->info[current] != e) {
        currentParent = current;
        if (this->relation(e, this->info[current])) {
            current = this->left[current];
            side = -1;
        } else {
            current = this->right[current];
            side = 1;
        }
    }

    if (current == -1) {
        return false;
    }

    if (this->left[current] == -1 && this->right[current] == -1) {
        if (current == this->root) {
            this->root = -1;
        } else {
            if (side == -1) {
                this->left[currentParent] = -1;
            } else {
                this->right[currentParent] = -1;
            }
        }
    } else if (this->left[current] == -1 || this->right[current] == -1) {

        int child;
        if(this->left[current] == -1) {
            child = this->right[current];
        } else {
            child = this->left[current];
        }

        if (current == root) {
            this->root = child;
        } else {
            if (side == -1) {
                this->left[currentParent] = child;
            } else {
                this->right[currentParent] = child;
            }
        }
        this->parent[child] = currentParent;

    } else {
        currentParent = current;
        int successor = this->right[current];
        side = 0;

        while (this->left[successor] != -1) {
            currentParent = successor;
            successor = this->left[successor];
            side = -1;
        }

        this->info[current] = this->info[successor];

        if (side == -1) {
            this->left[currentParent] = this->right[successor];
        } else {
            this->right[currentParent] = this->right[successor];
        }

        if (this->right[successor] != -1) {
            this->parent[right[successor]] = currentParent;
        }

        current = successor;
    }

    this->info[current] = NULL_TCOMP;
    this->nextEmpty[current] = this->firstEmpty;
    this->firstEmpty = current;

    this->sizeOfArray--;
    return true;
}

bool SortedBag::search(TComp e) const {
    int current = this->root;
    while (current != -1) {
        if (this->info[current] == e) {
            return true;
        }
        if (this->relation(e, this->info[current])) {
            current = this->left[current];
        } else {
            current = this->right[current];
        }
    }
    return false;
}

int SortedBag::nrOccurrences(TComp e) const {
    return nrOccurrencesRecursive(this->root, e);
}

int SortedBag::nrOccurrencesRecursive(int node, TComp e) const {
    if (node == -1) {
        return 0;
    }

    return (this->info[node] == e) + nrOccurrencesRecursive(this->left[node], e) +
        nrOccurrencesRecursive(this->right[node], e);
}

int SortedBag::size() const {
    return this->sizeOfArray;
}

bool SortedBag::isEmpty() const {
    return this->sizeOfArray == 0;
}

SortedBagIterator SortedBag::iterator() const {
    return SortedBagIterator(*this);
}

SortedBag::~SortedBag() {
    delete[] this->info;
    delete[] this->left;
    delete[] this->right;
    delete[] this->nextEmpty;
    delete[] this->parent;
}