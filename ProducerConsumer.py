import threading
import time
import random

# Initialize variables and semaphores

buffer = []  # Shared buffer
buffer_size = 5  # Size of the buffer
mutex = threading.Semaphore()  # Mutex for mutual exclusion
full = threading.Semaphore()  # no. of full slots
empty = threading.Semaphore(buffer_size)  # no. of empty slots

MAX_ITERATIONS = 20  # Define the maximum number of iterations for each thread

# acquire means wait operation and release means signal operation

# for counting semaphores, acquire i.e. wait operation always decrement and the release semaphore
# for binary semaphore, both of the operations change the value of the lock from 1 to 0 or 0 to 1

def producer():
    while True:
        item = random.randint(1, 108)
        empty.acquire()
        mutex.acquire()
        while len(buffer) == buffer_size:
            print("Buffer is full. Producer is waiting.")
            mutex.release()  # Release the mutex to allow consumers to run
            time.sleep(1)  # Sleep briefly to avoid busy-waiting
            mutex.acquire()  # Reacquire the mutex before checking the buffer again
        buffer.append(item)
        print(f"Produced {item}. Buffer: {buffer}")
        mutex.release()
        full.release()

def consumer():
    for _ in range(MAX_ITERATIONS):
        mutex.acquire()
        if len(buffer) == 0:
            print("Buffer is empty. Consumer is waiting.")
            mutex.release()  # Release the mutex to allow producers to run
            time.sleep(1)  # Sleep briefly to avoid busy-waiting
        else:
            item = buffer.pop(0)
            print(f"Consumed {item}. Buffer: {buffer}")
            mutex.release()
            empty.release()

# Create producer and consumer threads

producer_thread = threading.Thread(target=producer)
consumer_thread = threading.Thread(target=consumer)

# Start the threads

producer_thread.start()
consumer_thread.start()

# Wait for the threads to finish (this will run indefinitely)

producer_thread.join()
consumer_thread.join()
