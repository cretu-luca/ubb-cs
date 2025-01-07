import socket
import threading
import time
import os
import sys

# Constants
BOARD_SIZE = 10

# Initialize client
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('172.30.240.46', 6969))

# Initial position of the snake
snake_positions = [[0, 0]]
apple_position = [0, 0]  # Initialize apple_position

direction = 'd'  # Default direction

def get_input():
    global direction
    while True:
        new_direction = sys.stdin.readline().strip().lower()
        if new_direction in ['w', 'a', 's', 'd']:
            direction = new_direction

def move_snake():
    global snake_positions
    head = snake_positions[0][:]  # Copy the head position

    if direction == "w":
        head[1] = max(0, head[1] - 1)
    elif direction == "s":
        head[1] = min(BOARD_SIZE - 1, head[1] + 1)
    elif direction == "a":
        head[0] = max(0, head[0] - 1)
    elif direction == "d":
        head[0] = min(BOARD_SIZE - 1, head[0] + 1)

    # Check if the snake eats the apple
    if head == apple_position:
        snake_positions.insert(0, head)  # Grow the snake
    else:
        snake_positions.insert(0, head)
        snake_positions.pop()  # Move the snake

def print_board():
    os.system('cls' if os.name == 'nt' else 'clear')
    for y in range(BOARD_SIZE):
        for x in range(BOARD_SIZE):
            if [x, y] == apple_position:
                print('A', end=' ')
            elif [x, y] in snake_positions:
                print('S', end=' ')
            else:
                print('.', end=' ')
        print()
    print()
    print("Enter direction (w/a/s/d): ", end='', flush=True)

# Start the input thread
input_thread = threading.Thread(target=get_input)
input_thread.daemon = True  # Daemonize thread to exit when main program exits
input_thread.start()

try:
    while True:
        # Receive apple position from server
        data = s.recv(1024).decode()
        if data:
            apple_position = list(map(int, data.strip().split(',')))

        # Move the snake
        move_snake()

        # Print the board
        print_board()

        # Send snake positions to server
        snake_positions_str = ';'.join([f"{pos[0]},{pos[1]}" for pos in snake_positions])
        s.sendall(snake_positions_str.encode())

        time.sleep(0.2)  # Adjust delay as needed for game speed

except KeyboardInterrupt:
    print("\nGame terminated by user.")

s.close()
