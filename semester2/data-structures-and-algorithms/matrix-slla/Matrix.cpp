#include "Matrix.h"
#include <exception>
using namespace std;

// BC = WC = TC = theta(n)
Matrix::Matrix(int nrLines, int nrCols) {
    this->numberOfLines = nrLines;
    this->numberOfColumns = nrCols;
    this->capacity = 10;

    this->elements = new triplet[this->capacity];
    this->next = new int[this->capacity];

    for(int i = 0; i < this->capacity - 1; i++)
        this->next[i] = i + 1;

    this->next[this->capacity - 1] = -1;
    this->head = -1;
    this->firstEmpty = 1;
    this->size = 0;
}

// BC = WC = TC = theta(1)
int Matrix::nrLines() const {
    return this->numberOfLines;
}

// BC = WC = TC = theta(1)
int Matrix::nrColumns() const {
    return this->numberOfColumns;
}

// BC = theta(1), WC = theta(n), TC = O(n)
TElem Matrix::element(int i, int j) const {
    if(i < 0 || j < 0 || i >= this->nrLines() || j >= this->nrColumns())
        throw std::exception();

    int currentIndex = this->head;
    while(currentIndex != -1) {
        if(elements[currentIndex].line == i && elements[currentIndex].column == j)
            return elements[currentIndex].value;

        currentIndex = next[currentIndex];
    }

    return NULL_TELEM;
}

// BC = theta(1), WC = theta(n), TC = O(n)
TElem Matrix::modify(int i, int j, TElem e) {
    if(i < 0 || j < 0 || i >= this->nrLines() || j >= this->nrColumns())
        throw exception();

    int currentIndex = this->head, previous = -1;
    while (currentIndex != -1 && (elements[currentIndex].line < i || (elements[currentIndex].line == i && elements[currentIndex].column < j))) {
        previous = currentIndex;
        currentIndex = next[currentIndex];
    }

    if(currentIndex != -1 && elements[currentIndex].line == i && elements[currentIndex].column == j) {
        TElem oldValue = elements[currentIndex].value;

        if(e == NULL_TELEM) {
            if(previous == -1)
                this->head = next[currentIndex];
            else
                next[previous] = next[currentIndex];

            next[currentIndex] = this->firstEmpty;
            this->firstEmpty = currentIndex;
            this->size--;
        }
        else
            elements[currentIndex].value = e;

        return oldValue;

    } else {
        if(firstEmpty == -1)
            this->resize();

        int newIndex = this->firstEmpty;
        this->firstEmpty = next[newIndex];
        this->elements[newIndex] = {i, j, e};
        this->next[newIndex] = currentIndex;

        if(previous == -1)
            this->head = newIndex;
        else
            next[previous]  = newIndex;

        this->size++;

        return 0;
    }
}

void Matrix::resize() {
    int newCapacity = this->capacity * 2;

    auto newElements = new triplet[newCapacity];
    auto newNext = new int[newCapacity];

    for(int i = 0; i < this->capacity; i++) {
        newElements[i] = this->elements[i];
        newNext[i] = this->next[i];
    }

    for(int i = this->capacity; i < newCapacity - 1; i++) {
        newNext[i] = i + 1;
    }

    newNext[newCapacity - 1] = -1;

    delete[] this->elements;
    delete[] this->next;

    this->elements = newElements;
    this->next = newNext;
    this->firstEmpty = this->capacity;
    this->capacity = newCapacity;
}

MatrixIterator::MatrixIterator(Matrix m) : m(m) {
    this->index = m.head;
}

int MatrixIterator::getCurrent() {
    if(!isValid())
        throw exception();

    return m.elements[index].value;
}

void MatrixIterator::getNext() {
    if(!isValid())
        throw exception();

    index = m.next[index];
}

void MatrixIterator::first() {
    this->index = m.head;
}

bool MatrixIterator::isValid() {
    return this->index != -1;
}

