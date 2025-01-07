import socket

def main():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
 
    host = '127.0.0.1'
    port = 12345
    server_socket.bind((host, port))
    
    server_socket.listen(1)
    print(f"Server listening on {host}:{port}")
    
    try:
        while True:
            client_socket, addr = server_socket.accept()
            print(f"Connection from {addr}")
            
            data = client_socket.recv(1024)
            if data:
                print(f"Received: {data.decode()}")
                response = "Hello from Python server!"
                client_socket.send(response.encode())
            
            client_socket.close()
            
    except KeyboardInterrupt:
        print("\nShutting down server...")
    finally:
        server_socket.close()

if __name__ == "__main__":
    main()