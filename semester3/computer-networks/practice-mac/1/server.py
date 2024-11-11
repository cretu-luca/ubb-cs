import socket
import random
import time
import threading    

UDP_PORT = 1234
TCP_PORT = 5678
IP = '0.0.0.0'

def handle_tcp_client(client_socket, addr):
    print(f"New TCP connection from {addr}")
    try:
        while True:
            data = client_socket.recv(4)
            if not data:
                break

            sum_received = int.from_bytes(data, byteorder='little')
            print(f"Received {sum_received} from {addr}")
    except Exception as e:
        print(f"Error with client {addr}: {e}")
    finally:
        client_socket.close()
        print(f"Client {addr} disconnected")

def run_tcp_server():
    tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    tcp_socket.bind((IP, TCP_PORT))
    tcp_socket.listen(5)
    print(f"TCP Server listening on port {TCP_PORT}")
    
    while True:
        client_socket, addr = tcp_socket.accept()
        client_thread = threading.Thread(target=handle_tcp_client, args=(client_socket, addr))
        client_thread.start()

def run_udp_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

    try:
        while True:

            N = random.randint(1, 10)
            buffer = f"{N}"
            for i in range(N):
                val = random.randint(1, 10)
                buffer = buffer + f";{val}"

            server_socket.sendto(buffer.encode(), ('255.255.255.255', UDP_PORT))
            print(f"Broadcasting: {buffer}")

            time.sleep(1)
    except Exception as e:
        print(f"Server error: {e}")
    finally:
        server_socket.close()

if __name__ == "__main__":
    tcp_thread = threading.Thread(target=run_tcp_server)
    tcp_thread.daemon = True
    tcp_thread.start()

    run_udp_server()