import socket
import threading
import time
import struct

TCP_PORT = 8888
UDP_PORT = 8889
CLIENT_UDP_PORT = 8890
ARRAY_SIZE = 10

class Buffer:
    def __init__(self):
        self.array = ['u'] * ARRAY_SIZE

buffer = Buffer()
buffer_lock = threading.Lock()

def setup_tcp():
    tcp_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcp_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    tcp_sock.bind(('0.0.0.0', TCP_PORT))
    tcp_sock.listen(5)

    return tcp_sock

def setup_udp():
    udp_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    udp_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    udp_sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    udp_sock.bind(('0.0.0.0', UDP_PORT))
    
    return udp_sock

def broadcast_buffer(udp_sock):
    try:
        with buffer_lock:
            data = ''.join(buffer.array).encode()
        udp_sock.sendto(data, ('255.255.255.255', CLIENT_UDP_PORT))
        print(f"Buffer broadcast: {''.join(buffer.array)}")
    except Exception as e:
        print(f"Broadcast error: {e}")

def handle_client(client_sock, client_addr, udp_sock):
    print(f"New client connected from {client_addr}")
    
    try:
        while True:
            data = client_sock.recv(5)
            if not data or len(data) != 5:
                break
            
            # Unpack with native endianness
            index, char = struct.unpack('=ic', data)
            char = char.decode('ascii')
            print(f"Received: index={index}, char={char}")
            
            if 0 <= index < ARRAY_SIZE:
                with buffer_lock:
                    buffer.array[index] = char
                    print(f"Buffer updated: {''.join(buffer.array)}")
                broadcast_buffer(udp_sock)
                
    except Exception as e:
        print(f"Client error: {e}")
    finally:
        client_sock.close()
        print(f"Client {client_addr} disconnected")

if __name__ == "__main__":
    print("Starting server...")
    
    try:
        tcp_sock = setup_tcp()
        udp_sock = setup_udp()
        
        while True:
            client_sock, client_addr = tcp_sock.accept()
            thread = threading.Thread(
                target=handle_client,
                args=(client_sock, client_addr, udp_sock)
            )
            thread.daemon = True
            thread.start()
            
    except KeyboardInterrupt:
        print("\nShutting down...")
    finally:
        tcp_sock.close()
        udp_sock.close()