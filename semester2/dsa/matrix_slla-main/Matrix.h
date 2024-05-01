#pragma once
#include <iostream>

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

struct triplet {
    int line;
    int column;
    TElem value;
};

class Matrix {
private:

    int numberOfLines, numberOfColumns;
    triplet* elements;
    int* next;
    int size, capacity, head, firstEmpty;
public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

    friend class MatrixIterator;

    void resize();
};

class MatrixIterator {
private:
    Matrix m;
    int index;
public:
    MatrixIterator(Matrix m);
    TElem getCurrent();
    void first();
    void getNext();
    bool isValid();
};
