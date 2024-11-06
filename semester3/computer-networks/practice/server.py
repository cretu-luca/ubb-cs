import socket
import time

PORT = 1235
SOCK_ADDR = ('255.255.255.255', PORT)

def udp_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

    print('UDP broadcasting has started...')

    while True:
        server_socket.sendto('salut'.encode(), SOCK_ADDR)

        time.sleep(2)


if __name__ == '__main__':
    udp_server()