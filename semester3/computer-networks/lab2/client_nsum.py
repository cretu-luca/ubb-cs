import socket
from random import randint

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.connect(("127.0.0.1", 7777))

X = [0] * 10
for i in range(10):
    X[i] = randint(0, 100)

message = ",".join(str(x) for x in X)
print(message)

s.send(message.encode())
result = s.recv(100).decode()

print("Sum is:", result)

s.close()