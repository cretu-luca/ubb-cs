import socket

s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("0.0.0.0", 7777))
s.listen(5)

cs, addr = s.accept()

buff = cs.recv(100).decode()

x, y = buff.split(",")
x = int(x)
y = int(y)

cs.send(str(x + y).encode())

s.close()
cs.close()