import math
from random import choice

from src.services import Services


class UserInterface:
    def __init__(self):
        self.__services = Services()
        self.__tournament_players = []
        while True:
            self.__read_user_input()

    def __read_user_input(self):
        display_sorted_option = 1
        qualifying_round_option = 2
        start_tournament_option = 3
        self.__main_menu()
        while True:
            try:
                option = int(input("> "))

                if option == display_sorted_option:
                    self.__display_sorted_ui()
                elif option == qualifying_round_option:
                    self.__start_qualifying_round()
                elif option == start_tournament_option:
                    self.__start_tournament()

            except ValueError as ve:
                print(ve)

    def __start_qualifying_round(self):
        '''
        get the two players with the lowest strengths
        :return:
        '''
        players_list = self.__services.retrieve_all_players()
        if type(math.log2(len(players_list))) == int:
            print("Power of two number of players already!")
        else:
            player_needed = self.__services.get_power_of_two(len(players_list))
            players_to_eliminate = len(players_list) - player_needed
            print("Qualifying round starts!")
            print(f"There are {len(players_list)} players, so we need to eliminate {players_to_eliminate}.")

            players_list = sorted(players_list, key=lambda x: x.strength)

            tournament_list = []
            while players_to_eliminate > 0:
                players_to_eliminate -= 1

                player1 = players_list[0]
                player2 = players_list[1]

                players_list.remove(player1)
                players_list.remove(player2)

                print(f"Player 1\n"
                      f"{player1.to_string}\n")

                print(f"Player 2\n"
                      f"{player2.to_string}\n")

                print("Choose the winner: \n"
                      "1. Player 1\n"
                      "2. Player 2\n")

                option = int(input("> "))
                if option == 1:
                    tournament_list.append(player1)
                    player1.strength += 1
                else:
                    tournament_list.append(player2)
                    player2.strength += 1

            tournament_list += players_list

            print("These are the players that qualified!")
            for player in tournament_list:
                print(player.to_string)

            self.__services.update_list(tournament_list)

    def __start_tournament(self):
        '''
        get the players randomly from the list
        :return:
        '''
        tournament_players = self.__services.retrieve_all_players()
        power_of_two = self.__services.get_power_of_two(len(tournament_players)) * 2

        while power_of_two != 1:
            print(f"Last {int(power_of_two)}")
            power_of_two /= 2
            players_to_eliminate = len(tournament_players) / 2

            new_tournament_players = []

            while players_to_eliminate > 0:
                players_to_eliminate -= 1

                #player1 = tournament_players[0]
                #player2 = tournament_players[1]

                player1 = choice(tournament_players)
                tournament_players.remove(player1)
                player2 = choice(tournament_players)
                tournament_players.remove(player2)

                print(f"Player 1\n"
                      f"{player1.to_string}\n")

                print(f"Player 2\n"
                      f"{player2.to_string}\n")

                print("Choose the winner: \n"
                      "1. Player 1\n"
                      "2. Player 2\n")

                option = int(input("> "))
                if option == 1:
                    new_tournament_players.append(player1)
                    player1.strength += 1
                else:
                    new_tournament_players.append(player2)
                    player2.strength += 1

            tournament_players = new_tournament_players

        print(f"{tournament_players[0].name} won!")
        exit(0)

    def __display_sorted_ui(self):
        players_list = self.__services.retrieve_all_players()
        players_list = sorted(players_list, key=lambda x: -x.strength)

        for player in players_list:
            print(player.to_string)

    @staticmethod
    def __main_menu():
        print("1. Display all players, sorted descending by player strength\n"
              "2. Play qualifying round\n"
              "3. Start tournament.\n")


UI = UserInterface()