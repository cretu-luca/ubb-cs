import socket
import time
import threading

def handle_client():
    tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    sent = send()

def handle_connections(): # connects over UDP with clients; creates thread for each client
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    udp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    udp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)

    udp_socket.bind(('0.0.0.0', 1234))

    while True:

        data, addr = udp_socket.recvfrom(1024)
        client_ip = addr[0]
        client_port = addr[1]

        client_thread = threading.Thread(target=handle_client, args=(udp_socket,))
        client_thread.start()


if __name__ == "__main__":
    middle_thread = threading.Thread(target=handle_connections)
    middle_thread.daemon = True
    middle_thread.start()