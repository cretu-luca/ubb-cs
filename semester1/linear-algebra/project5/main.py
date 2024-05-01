import itertools
import numpy
import sys


def pivot_position_in_row_i(matrix, m, i):  # find the leading 1
    for j in range(m):
        if matrix[i][j] == 1:
            return j

    return -1


def check_column(matrix, n, row, j):  # checks whether there are more 1's in a column
    for i in range(n):
        if matrix[i][j] == 1 and i != row:
            return False

    return True


def check_next_rows(matrix, n, m, row):  # checks if the bottom lines only have 0's
    for i in range(row + 1, n):
        if pivot_position_in_row_i(matrix, m, i) != -1:
            return False

    return True


def valid(matrix, n, m):
    pivot_positions = list()
    for i in range(n):
        pivot_position = pivot_position_in_row_i(matrix, m, i)

        if pivot_position == -1:  # all zero row
            if not check_next_rows(matrix, n, m, i):
                return 0
        else:
            if not check_column(matrix, n, i, pivot_position):
                return 0
            pivot_positions.append(pivot_position)

    if pivot_positions != sorted(pivot_positions):
        return 0

    return 1


def solve(n, m):
    counter = 0
    matrix_set = []

    matrices = itertools.product(range(2), repeat=m*n)

    for matrix in matrices:
        matrix = numpy.array(matrix).reshape(n, m)

        if valid(matrix, n, m):
            counter += 1
            matrix_set.append(matrix)

    return matrix_set, counter


def main():
    if len(sys.argv) < 3:
        sys.exit(1)

    input_file = sys.argv[1]
    output_file = sys.argv[2]

    with open(input_file, 'r') as f:
        n, m = map(int, f.readline().split())

    matrices, counter = solve(n, m)

    with open(output_file, 'w') as output_file_:
        sys.stdout = output_file_
        print(f"n = {n}, m = {m}")
        print(f"\nThe number of {n} x {m} matrices in reduced echelon form is {counter}\n")
        print(f"The n x m  matrices in reduced echelon form are: \n")
        for matrix in matrices:
            print(matrix, '\n')

        sys.stdout = sys.__stdout__


if __name__ == "__main__":
    main()


