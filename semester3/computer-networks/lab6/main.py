import socket
import random
import time

class PriceClient:
    def _init_(self):
        self.udp_port = 7777
        self.buffer_size = 1024
        self.host = '172.30.240.46'  # Listen on all available interfaces
        self.max_price = random.randint(400, 499)
        self.current_price = 0

    def run(self):
        print("MA-TA")
        # Create UDP socket
        udp_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        udp_sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        udp_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        
        # Bind socket to listen for incoming broadcasts
        udp_sock.bind(("172.30.240.46", 7777))
        
        print(f"Listening for broadcasts on port {self.udp_port}")
        print(f"Will make offers until price exceeds {self.max_price}")

        try:
            while self.current_price < self.max_price:
                print("Waiting for UDP message...")
                
                # Receive broadcast message
                udp_buffer, sender_addr = udp_sock.recvfrom(self.buffer_size)
                
                # Decode the message and convert it to an integer
                self.current_price = int(udp_buffer.decode().strip())
                
                
                my_offer = self.current_price + random.randint(1, 10)
                print(f"Received current price: {self.current_price}, My offer: {my_offer}")
                
        except Exception as e:
            print(f"Error: {e}")
        finally:
            udp_sock.close()

if __name__ == "__main__":
    random.seed(time.time())
    client = PriceClient()
    client.run()