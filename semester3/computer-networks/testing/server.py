import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

server_address = ('127.0.0.1', 12345)
sock.bind(server_address)
print(f'Starting UDP server on {server_address}')

while True:
    print('\nWaiting to receive message...')
    data, client_address = sock.recvfrom(1024)
    
    print(f'Received {len(data)} bytes from {client_address}')
    print(f'Data: {data.decode()}')
    
    if data:
        sent = sock.sendto(data, client_address)
        print(f'Sent {sent} bytes back to {client_address}')