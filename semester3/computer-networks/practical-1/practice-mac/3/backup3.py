import socket

def start_server():
    # Create a TCP/IP socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    # Use Windows VM's address - either localhost or VM's IP
    server_socket.bind(('0.0.0.0', 5000))
    
    # Listen for incoming connections
    server_socket.listen(1)
    print("Server listening on port 5000...")
    
    while True:
        # Wait for a connection
        connection, client_address = server_socket.accept()
        try:
            print(f"Connected to client: {client_address}")
            
            # Receive and echo data
            while True:
                data = connection.recv(1024)
                if data:
                    print(f"Received: {data.decode()}")
                    # Echo back the received data
                    connection.sendall(data)
                else:
                    break
                    
        finally:
            connection.close()

if __name__ == '__main__':
    start_server()