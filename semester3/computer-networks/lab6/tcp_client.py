import socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("127.0.0.1", 7777))
while True:
    message = input("enter message: ")
    s.sendall(message.encode())
