import socket
import time

PORT = 1235
SOCK_ADDR = ('255.255.255.255', PORT)

def udp_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_socket.bind(SOCK_ADDR)

    print('UDP broadcasting has started...')

    while True:
        data, client = server_socket.recvfrom(1024)
        print(f'Client: {client}\nReceieved: {data.decode()}\n')


if __name__ == '__main__':
    udp_server()