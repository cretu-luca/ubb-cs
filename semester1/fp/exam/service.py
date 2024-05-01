class Service:
    def __init__(self, repository):
        self.repository = repository

    def attack_at_service(self, line, row):
        return self.repository.attack_at(line, row)

    def display_board_service(self, display_aliens):
        self.repository.display_board(display_aliens)

    def move_alien_ships_service(self):
        self.repository.move_alien_ships()

    def check_neighbors_of_earth(self):
        neighboring_cells = self.repository.get_neighbors_of_earth()
        for neighbor in neighboring_cells:
            if neighbor == 2:
                return 0

        return 1