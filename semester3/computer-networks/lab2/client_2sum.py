import socket
from random import randint

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.connect(("127.0.0.1", 7777))

x = randint(0, 10)
y = randint(0, 10)

print(f"Generated {x} and {y} inside client.")

message = f"{x},{y}".encode()

s.send(message)
result = s.recv(100).decode()

print("Sum is:", result)

s.close()