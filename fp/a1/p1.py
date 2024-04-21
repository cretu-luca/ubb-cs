# first set, problem statement no 1

import math

def prime(x):  # determines whether a number is prime or not
    if x == 0 or x == 1:
        return 0
    if x == 2:
        return 1
    if x % 2 == 0:
        return 0
    for d in range(3, int(math.sqrt(x)) + 1, 2):
        if x % d == 0:
            return 0
    return 1


def main():
    x = int(input()) + 1

    while prime(x) == 0:
        x += 1

    print(x)


while 1:
    main()

