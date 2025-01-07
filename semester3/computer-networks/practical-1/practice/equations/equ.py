import select
import socket
import threading
import time
import random

UDP_PORT = 1234  # Matching C client's UDP_PORT
TCP_PORT = 5678  # Matching C client's TCP_PORT

def make_expression():
    return f"{random.randint(1, 10)}{random.choice(['+', '-', '*', '/'])}{random.randint(1, 10)}"

def handle_student(conn, addr, expressions, answers):
    try:
        print(f"Connection from {addr}")
        student_answers = []

        # Receive the answer from student
        data = conn.recv(1024).decode('utf-8').strip()
        if data:
            print(f"Received from {addr}: {data}")
            try:
                # Simple evaluation of answer
                mark = "Correct!" if float(data) == answers[-1] else f"Wrong! Expected: {answers[-1]}"
                conn.send(mark.encode('utf-8'))
            except ValueError:
                conn.send("Invalid answer format!".encode('utf-8'))

    except Exception as e:
        print(f"Error handling student {addr}: {e}")
    finally:
        conn.close()

def main():
    # Create UDP broadcast socket
    broadcast_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    broadcast_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    broadcast_sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

    # Create TCP socket for student connections
    tcp_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    tcp_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    tcp_sock.bind(('0.0.0.0', TCP_PORT))  # Listen on all interfaces
    tcp_sock.listen(5)

    print(f"Server started - TCP listening on port {TCP_PORT}, UDP broadcasting on port {UDP_PORT}")
    
    expressions = []
    answers = []
    student_threads = []

    try:
        while True:
            # Generate new expression
            expr = make_expression()
            expressions.append(expr)
            answers.append(eval(expr))

            # Broadcast the expression
            msg = f"{expr} = ?\n".encode('utf-8')
            broadcast_sock.sendto(msg, ('255.255.255.255', UDP_PORT))
            print(f"Broadcast: {expr} = ?")
            print(f"Answer: {answers[-1]}")

            # Accept TCP connections (non-blocking)
            try:
                tcp_sock.settimeout(0.1)  # Short timeout for non-blocking
                conn, addr = tcp_sock.accept()
                thread = threading.Thread(target=handle_student,
                                       args=(conn, addr, expressions, answers))
                thread.start()
                student_threads.append(thread)
            except socket.timeout:
                pass  # No connection waiting
            
            time.sleep(2)  # Wait before next equation

    except KeyboardInterrupt:
        print("\nShutting down...")
    finally:
        broadcast_sock.close()
        tcp_sock.close()
        for thread in student_threads:
            thread.join()
        print("Server closed")

if __name__ == "__main__":
    main()