import socket

PORT = 1235
SOCK_ADDR = ('', PORT)

def udp_client():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    client_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    client_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    client_socket.bind(SOCK_ADDR)

    while True:
        data, server = client_socket.recvfrom(1024)
        print(f'server: {server}\nreceived: {data.decode()}\n\n')

if __name__ == '__main__':
    udp_client()