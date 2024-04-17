import itertools
import numpy as np
import sys


def create_rref_form(matrix, n, k):
    # converts the matrix to its rref (reduced row echelon form) which will later be used to calculate the rank
    # of a matrix and compare the generated subspaces by each matrix
    i, j = 0, 0
    while i < k and j < n:
        max_row = i
        # first non-zero element in current column
        while max_row < k and matrix[max_row][j] == 0:
            max_row += 1

        # if no non-zero element is found, move to the next column
        if max_row == k:
            j += 1
            continue

        # swap rows to move the non-zero element to the current row
        matrix[i], matrix[max_row] = matrix[max_row], matrix[i]

        # zero out element from the same column, but from other rows
        for row in range(k):
            if row != i and matrix[row][j] != 0:
                for col in range(j, n):
                    matrix[row][col] = (matrix[row][col] - matrix[i][col]) % 2  # obtain Z2 values

        i += 1
        j += 1

    return matrix


def matrix_rank(matrix, n, k):
    # rank - number of non-zero rows in matrix's rref form
    rref_matrix = create_rref_form(matrix, n, k)
    rank = 0
    for row in rref_matrix:
        if any(row):  # checks whether there is any non-zero value on the current row
            rank += 1

    return rank


def check(basis1, basis2, n, k):
    # check if two basis span the same subspace using their RREF forms

    basis1 = create_rref_form(basis1, n, k)
    basis2 = create_rref_form(basis2, n, k)

    return np.array_equal(basis1, basis2)


def solve(n, k):
    counter = 0
    matrix_set = []
    # generates all possible k-dimensional subspaces
    k_dim_subspaces = itertools.product(range(2), repeat=k*n)

    for subset in k_dim_subspaces:
        matrix = np.array(subset)
        matrix = matrix.reshape(k, n)

        rank = matrix_rank(matrix, n, k)

        if rank == k:  # linear independence based on matrix rank (rank = number of linearly independent vectors)
            matrix_set.append(matrix)
            counter += 1

    return matrix_set


def main():
    if len(sys.argv) < 3:
        sys.exit(1)

    input_file = sys.argv[1]
    output_file = sys.argv[2]

    with open(input_file, 'r') as f:
        n, k = map(int, f.readline().split())

    matrix_set = solve(n, k)
    final_matrix_set = [matrix_set[0]]  # first matrix is valid, so we add it and compare the others with it
    counter = 1

    for basis in matrix_set:
        unique_subspace = 0
        for existing_basis in final_matrix_set:
            # we compare the current's basis generated subspace with other basis already in the final list
            # the comparison is done using rref's
            # identical rref's result in identical generated subspaces
            if check(basis, existing_basis, n, k):
                unique_subspace = 1

            if not unique_subspace:  # the basis generates a unique subspace, so add it to the final list
                final_matrix_set.append(basis)
                counter += 1

    with open(output_file, 'w') as out_file:
        sys.stdout = out_file
        print(f"k is {k}, n is {n}")
        print(f"1. The number of {k}-dimensional subspaces is {counter}")
        print(f"2. A basis of each such subspace is:\n")

        for matrix in final_matrix_set:
            current_basis = ",".join(str(tuple(row)) for row in matrix)
            print(f"({current_basis})")

        sys.stdout = sys.__stdout__


if __name__ == "__main__":
    main()
