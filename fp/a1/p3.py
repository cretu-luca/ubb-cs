# third set, problem statement no 13

import math

def prime(x): # determines whether x is prime or not
    if x < 2:
        return 0
    if x == 2:
        return 1
    if x % 2 == 0:
        return 0
    for d in range(3, int(math.sqrt(x)) + 1, 2):
        if x % d == 0:
            return 0
    return 1


def solve(n):
    count = 0;
    num = 1

    while count < n:
        num = num + 1
        if prime(num):
            count += 1

        for d in range(2, num + 1):
            if num % d == 0:
                count += 1


def main():
    n = int(input())
    print(solve(n))


while 1:
    main()
