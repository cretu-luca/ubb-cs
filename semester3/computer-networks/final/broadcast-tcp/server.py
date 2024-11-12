# server broadcasts array of numbers
# client sends back the sum over TCP
# server sends back whether sum is prime or not 

import threading
import socket
import time
import random

BC_ADDR = "255.255.255.255"
UDP_PORT = 1234
TCP_PORT = 5678

def is_prime(n):
    if n < 2: return False
    for i in range(2, int(n ** 0.5) + 1):
        if n % i == 0: return False
    return True

# receive the sum + send back primality of number
def handle_client(client_socket, client_addr):
    try:
        while True:
            data = client_socket.recv(4)
            if not data:
                break
            
            num = int.from_bytes(data, 'little')
            print(f"Receiving {num}")
            
            result = 1 if is_prime(num) else 0
            client_socket.send(result.to_bytes(1, 'little'))
    except Exception as e:
        print(f"recv exception - {e}")
    finally:
        client_socket.close()

# connect over TCP with clients
def handle_connections():
    tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    tcp_socket.bind(('', TCP_PORT))
    tcp_socket.listen(5)

    while True:
        client_socket, addr = tcp_socket.accept()
        client_thread = threading.Thread(target=handle_client, args=(client_socket, addr,))
        client_thread.daemon = True
        client_thread.start()

# set up and run the broadcasting component 
def run_udp_server():
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    udp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    udp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
    udp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)   

    try:
        while True:
            N = random.randint(1, 10)
            message = f"{N}"
            for _ in range(N):
                message += f";{random.randint(1, 10)}"

            udp_socket.sendto(message.encode(), (BC_ADDR, UDP_PORT))

            print(f"Broadcasting {message}")

            time.sleep(1)
    except Exception as e:
        print(f"sendto exception - {e}")
    finally:
        udp_socket.close()


if __name__ == "__main__":
    middle_thread = threading.Thread(target=handle_connections)
    middle_thread.daemon = True
    middle_thread.start()

    run_udp_server()