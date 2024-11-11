import socket
import threading

def handle_tcp_client(tcp_socket, client_addr, reversed_message):
    try:
        tcp_socket.send(reversed_message.encode())
    except Exception as e:
        print(f"TCP Error: {e}")
    finally:
        tcp_socket.close()

if __name__ == "__main__":
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)
    udp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    udp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    udp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)
    UDP_PORT = 1234
    udp_socket.bind(('', UDP_PORT))

    tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
    tcp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    TCP_PORT = 5678
    tcp_socket.bind(('', TCP_PORT))
    tcp_socket.listen(5)

    print(f"Server listening on UDP port {UDP_PORT} and TCP port {TCP_PORT}...")

    while True:
        try:
            data, addr = udp_socket.recvfrom(1024)
            message = data.decode()
            print(f"Received from {addr}: {message}")

            reversed_message = message[::-1]
            print(f"Reversed message: {reversed_message}")

            client_socket, client_addr = tcp_socket.accept()
            print(f"TCP connection from {client_addr}")
            
            thread = threading.Thread(
                target=handle_tcp_client,
                args=(client_socket, client_addr, reversed_message)
            )
            thread.start()

        except KeyboardInterrupt:
            print("\nServer shutting down...")
            break
        except Exception as e:
            print(f"Error: {e}")

    udp_socket.close()
    tcp_socket.close()