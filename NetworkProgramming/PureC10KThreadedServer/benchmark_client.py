# benchmark_c_client.py
import socket
import threading
import time

HOST = "127.0.0.1"
PORT = 8080
NUM_CLIENTS = 10000
CONCURRENCY = 200
sema = threading.Semaphore(CONCURRENCY)

success, failed = 0, 0
lock = threading.Lock()

def worker(index):
    global success, failed
    with sema:
        try:
            s = socket.socket()
            s.connect((HOST, PORT))
            s.sendall(b"GET / HTTP/1.1\r\nHost: localhost\r\n\r\n")
            data = s.recv(1024)
            with lock:
                success += 1
            s.close()
        except Exception as e:
            with lock:
                failed += 1

start = time.time()
threads = [threading.Thread(target=worker, args=(i,)) for i in range(NUM_CLIENTS)]
for t in threads: t.start()
for t in threads: t.join()
end = time.time()

print(f"Success: {success}, Failed: {failed}")
print(f"QPS: {success / (end - start):.2f}")
