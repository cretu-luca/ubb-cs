# second set, problem statement no 6

def main():
    y, d = map(int, input().split())  # year and day number
    m = 0  # month

    days = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]  # number of days in each month

    if y % 4 == 0:  # leap years
        days[1] += 1

    while d > days[m]:
        d -= days[m]
        m += 1

    print(y, m + 1, d)

while 1:
    main()
