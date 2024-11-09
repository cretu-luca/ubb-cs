from os import fork
import socket

def handle_client(client_socket, client_address):
    print("new connection from f{}".format(client_address))

    while True:
        message = client_socket.recv(1024).decode()

        if not message:
            break

        print(message)


    client_socket.close()


def run_server(sock):
    while True:
        client_sock, client_addr = sock.accept()
        pid = fork()

        if pid == 0: # child
            handle_client(client_sock, client_addr)
            exit()


tcp_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
tcp_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
tcp_sock.bind(("0.0.0.0", 7777))
tcp_sock.listen(5)

run_server(tcp_sock)