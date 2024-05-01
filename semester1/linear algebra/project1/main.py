import sys


def generate_bell_number(n):
    # this function calculates the number of ways
    # in which you can partition a set with n elements using the bell triangle
    bell_matrix = [[0 for _ in range(n+1)] for _ in range(n+1)]  # matrix full of 0's
    bell_matrix[0][0] = 1

    for i in range(1, n + 1):
        bell_matrix[i][0] = bell_matrix[i-1][i-1]
        # first element in row is the last element of the last row

        for j in range(1, i + 1):
            bell_matrix[i][j] = bell_matrix[i-1][j-1] + bell_matrix[i][j-1]
            # current element is the sum of the element up and left and the element to the left

    return bell_matrix[n][0]  # first element of the last row represents the result


def print_partitions(x, n):
    partitions = []
    pair_elements = []

    for group in set(x[1:n + 1]):  # picks indexes representing the partitions each element belongs to
        partition = []
        for element in range(1, n + 1):
            if x[element] == group:
                partition.append("a" + str(element))
        # each number gets added to its partition based on the corresponding value in x[]
        if len(partition) > 1:  # true for partitions with more than one element -> we need to create "pairs"
            # the following for's generate pairs of elements within the same partition to represent relations
            for i in range(len(partition)):
                for j in range(len(partition)):
                    if i != j:
                        pair_elements.append("(" + partition[i] + ", " + partition[j] + ")")
        partitions.append("{" + ", ".join(partition) + "}")  # adds the brackets, separates by commas

    if len(partitions) == 1:  # there is only one partition in which all elements are grouped together
        print(partitions[0], "-> A × A")
    elif pair_elements:  # pairs of elements in relation to each other
        print("{", ", ".join(partitions), "}", "-> dA U {" + ", ".join(pair_elements) + "}")
    else:  # each element is in its own separate partition
        print("{", ", ".join(partitions), "}", "-> dA")


def partitions_using_backtracking(k, x, n):
    m = max(x[:k])  # the maximum represents the number of partitions that contain at least an element so far
    for i in range(1, m + 2):
        # for (1, m), the element belongs to an existing partition
        # for m + 1, the elements becomes the new partition's first element
        x[k] = i
        # x[] contains what partition every element belongs to
        # for example, x[i] = y means the i-th element belongs to the y-th partition
        if k == n:
            print_partitions(x, n)
        else:
            partitions_using_backtracking(k + 1, x, n)


def main():
    # n = int(input())
    if len(sys.argv) < 3:
        print("Usage: python script_name.py input_filename output_filename")
        sys.exit(1)

    input_file = sys.argv[1]
    output_file = sys.argv[2]

    with open(input_file, 'r') as f:
        n = int(f.readline().strip())

    x = [0] * (n + 1)

    with open(output_file, 'w') as out_file:
        sys.stdout = out_file
        print("1. There are", generate_bell_number(n), "ways in which the set can be partitioned.\n")
        print("2. The partitions are the following: \n")
        partitions_using_backtracking(1, x, n)

    sys.stdout = sys.__stdout__


if __name__ == "__main__":
    main()
