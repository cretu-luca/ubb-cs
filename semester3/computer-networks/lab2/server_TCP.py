import socket
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.bind(("0.0.0.0",7777))
s.listen(5)
cs, addr=s.accept()
b = cs.recv(100)
print(b.decode())
cs.send(str.encode("Hello World"))
cs.close()