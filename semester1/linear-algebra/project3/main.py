import itertools
import numpy as np
import sys


def number_of_bases_of_zn2(n):
    # prod = (2^n - 2^0) * (2^n - 2^1) * (2^n - 2^2) * (2^n - 2^4) * ...
    prod = 1
    two_to_n = 2 ** n

    for p in range(0, n):
        two_to_p = 2 ** p
        val = two_to_n - two_to_p
        prod = prod * val

    return prod


def generate_vectors(n):
    for vectors in itertools.product(range(2), repeat=n * n):
        matrix = np.array(vectors).reshape(n, n)  # create matrix with the n x n values in the cartesian product
        det = int(round(np.linalg.det(matrix))) % 2  # we work in Z2, so we have (0, 1)
        # a determinant of 1 (not 0) means the matrix's rows give a valid basis
        if det == 1:  # determinant is either 0 or 1
            matrix_tuple = tuple(tuple(row) for row in matrix)
            print(matrix_tuple)


def main():
    if len(sys.argv) != 3:
        sys.exit(1)

    n = int(sys.argv[1])
    filename = sys.argv[2]

    with open(filename, 'w') as f:
        sys.stdout = f
        print(f"n is {n}")
        print(f"1. There are {number_of_bases_of_zn2(n)} bases")
        if n < 5:
            print("2. The vectors of each such basis are: ")
            generate_vectors(n)

        sys.stdout = sys.__stdout__


if __name__ == "__main__":
    main()
