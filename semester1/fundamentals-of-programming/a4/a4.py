import random


def calculate_maximum_profit_naive(price_per_piece_length_list, price_list_length, price_indices_corresponding_to_maximum_profit):
    if price_list_length == 0:
        return 0, []

    maximum_profit = 0

    for i in range(1, price_list_length + 1):
        current_profit, current_price_indices_selected = (
            calculate_maximum_profit_naive(
            price_per_piece_length_list, price_list_length - i, price_indices_corresponding_to_maximum_profit))
        current_profit += price_per_piece_length_list[i-1]

        if current_profit > maximum_profit:
            maximum_profit = current_profit
            price_indices_corresponding_to_maximum_profit = [i] + current_price_indices_selected

    return maximum_profit, price_indices_corresponding_to_maximum_profit


def calculate_maximum_profit_for_randomly_generated_price_list_using_dynamic_programming(
        price_per_piece_length_list, price_list_length, price_indices_corresponding_to_maximum_profit):
    maximum_profit_per_length = [0 for _ in range(price_list_length + 1)]
    for i in range(1, price_list_length + 1):
        for j in range(i):
            if maximum_profit_per_length[i-j-1] + price_per_piece_length_list[j] > maximum_profit_per_length[i]:
                maximum_profit_per_length[i] = maximum_profit_per_length[i-j-1] + price_per_piece_length_list[j]
                price_indices_corresponding_to_maximum_profit[i] = j + 1

            print(maximum_profit_per_length, '\n')

    return maximum_profit_per_length[price_list_length]


def print_reconstructed_sequence_of_lengths_of_cut_pieces(price_list_length, price_indices):
    price_indices_corresponding_to_maximum_profit = []
    while price_list_length > 0:
        price_indices_corresponding_to_maximum_profit.append(price_indices[price_list_length])
        price_list_length -= price_indices[price_list_length]
    return price_indices_corresponding_to_maximum_profit


def main():
    price_list_length = int(input("Insert the length of the rod: \n> "))
    price_indices_corresponding_to_maximum_profit = [0] * (price_list_length + 1)
    price_per_piece_length_list = sorted([random.randint(1, 25) for _ in range(price_list_length)])

    for _ in range(2):
        implementation = int(input("\nChoose between dynamic programming and naive implementation:\n"
                                   "1. Dynamic Programming\n"
                                   "2. Naive Implementation\n> "))

        if implementation == 1:
            print("This is the price list for each length: \n", price_per_piece_length_list, '\n')
            print("This is the maximum profit:",
                  calculate_maximum_profit_for_randomly_generated_price_list_using_dynamic_programming(
                      price_per_piece_length_list, price_list_length, price_indices_corresponding_to_maximum_profit), '\n')
            print("These are the lengths of the cuts necessary for obtaining the maximum profit: \n",
                  print_reconstructed_sequence_of_lengths_of_cut_pieces(price_list_length, price_indices_corresponding_to_maximum_profit))

        else:
            print("This is the price list for each length: \n", price_per_piece_length_list, '\n')
            maximum_profit, price_indices_corresponding_to_maximum_profit = (
                calculate_maximum_profit_naive(
                    price_per_piece_length_list, price_list_length, price_indices_corresponding_to_maximum_profit))

            print("This is the maximum profit:", maximum_profit, '\n')
            print("These are the lengths of the cuts necessary for obtaining the maximum profit: \n", price_indices_corresponding_to_maximum_profit)


while True:
    main()