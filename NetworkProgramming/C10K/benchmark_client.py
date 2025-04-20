import socket
import threading
import time

HOST = "127.0.0.1"
PORT = 8080
NUM_CLIENTS = 10000
MAX_CONCURRENCY = 200

sema = threading.Semaphore(MAX_CONCURRENCY)
success_count = 0
fail_count = 0
lock = threading.Lock()
sample_print_limit = 5  # 只打印前 N 个成功响应
sample_print_index = 0

def client_worker(index):
    global success_count, fail_count, sample_print_index
    with sema:
        try:
            s = socket.socket()
            s.connect((HOST, PORT))

            http_request = (
                "GET /big HTTP/1.1\r\n"
                "Host: localhost\r\n"
                "Connection: close\r\n"
                "\r\n"
            )
            s.sendall(http_request.encode())

            chunks = []
            while True:
                chunk = s.recv(4096)
                if not chunk:
                    break
                chunks.append(chunk)
            total = b''.join(chunks)

            with lock:
                success_count += 1
                if sample_print_index < sample_print_limit:
                    print(f"[{index}] Received {len(total)} bytes")
                    sample_print_index += 1

            s.close()

        except Exception as e:
            with lock:
                fail_count += 1
            print(f"Client {index} failed: {e}")

def main():
    threads = []
    start_time = time.time()

    for i in range(NUM_CLIENTS):
        t = threading.Thread(target=client_worker, args=(i,))
        threads.append(t)
        t.start()

    for t in threads:
        t.join()

    end_time = time.time()
    duration = end_time - start_time

    print(f"\nTotal clients: {NUM_CLIENTS}")
    print(f"Success: {success_count}, Failed: {fail_count}")
    print(f"Total Time: {duration:.3f} sec")
    print(f"QPS: {success_count / duration:.2f}")

if __name__ == "__main__":
    main()
