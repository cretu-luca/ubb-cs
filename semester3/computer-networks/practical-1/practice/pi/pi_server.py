import socket
from threading import Thread
from struct import pack
import time

SOCK_ADDR = ('', 1234)
running = True
approx = 0.0
e = 0.009
points = []
clients = []

def get_pi_approx(inside, outside):
    return 4 * inside / outside if outside > 0 else 0  # Added safety check

def get_inside_points(points):
    return sum(1 for x, y in points if x ** 2 + y ** 2 < 1)

def handle_client(client_socket, client_addr):
    global running, approx, clients
    print(f"New client connected from {client_addr}")  
    try:
        while running:
            current_approx = pack("f", approx)
            client_socket.send(current_approx)
            time.sleep(0.1)
    except Exception as e:
        print(f"Client {client_addr} disconnected: {e}")
    finally:
        clients.remove(client_socket)
        client_socket.close()
def accept_clients(tcp_socket):
    global running
    while running:
        try:
            client_socket, client_addr = tcp_socket.accept()
            clients.append(client_socket)  # Add new client to list
            client_thread = Thread(target=handle_client, args=(client_socket, client_addr))
            client_thread.daemon = True  # Makes thread exit when main thread exits
            client_thread.start()
        except:
            break

def setup_udp_socket():
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    udp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    udp_socket.bind(SOCK_ADDR)
    print(f"UDP listening on {SOCK_ADDR}.")
    return udp_socket

def setup_tcp_socket():
    tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    tcp_socket.bind(SOCK_ADDR)
    tcp_socket.listen(7)
    print(f"TCP server listening on {SOCK_ADDR}")
    return tcp_socket

def convert_numb(numb):
    return (numb - 50) / 50

if __name__ == '__main__':
    udp_server = setup_udp_socket()
    tcp_socket = setup_tcp_socket()
   
    tcp_thread = Thread(target=accept_clients, args=(tcp_socket,))
    tcp_thread.daemon = True
    tcp_thread.start()
   
    while running:
        buff, addr = udp_server.recvfrom(7)
        numb_str = buff.decode('utf-8')
        try:
            numb1, numb2 = numb_str.split(';')
            numb1 = ''.join(c for c in numb1 if c.isdigit())
            numb2 = ''.join(c for c in numb2 if c.isdigit())
           
            if numb1 and numb2:
                numb1 = convert_numb(int(numb1))
                numb2 = convert_numb(int(numb2))
                points.append((numb1, numb2))
               
                inside = get_inside_points(points)
                oldapprox = approx
                approx = get_pi_approx(inside, len(points))
               
                print(f"Points: {len(points)}, Inside: {inside}, π ≈ {approx}")
               
                if abs(oldapprox - approx) < e and approx < 4:
                    running = False
                    print(f"Approximation is stable at {approx}")
        except Exception as e:
            print(f"Error processing data: {e}")
            continue
        
        time.sleep(0.001)  # Small delay to prevent CPU overload (1ms)
    
    # Clean shutdown
    for client in clients:
        try:
            client.close()
        except:
            pass
    udp_server.close()
    tcp_socket.close()