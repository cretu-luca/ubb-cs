import socket

s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(("0.0.0.0", 7777))
s.listen(5)

cs, addr = s.accept()

buff = cs.recv(100).decode()

X = buff.split(",")
X = [int(x) for x in X]

result = sum(X)

cs.send(str(result).encode())

s.close()
cs.close()