#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>

template <typename T>
class CircularBuffer {
private:
    std::vector<T> buffer;
    int head;
    int tail;
    int size;
    bool full;

public:
    CircularBuffer(int capacity) : buffer(capacity), head(0), tail(0), size(capacity), full(false) {}

    bool isEmpty() const {
        return !full && head == tail;
    }

    bool isFull() const {
        return full;
    }

    void enqueue(const T& item) {
        buffer[tail] = item;
        tail = (tail + 1) % size;
        if (full) {
            head = (head + 1) % size;
        }
        full = (head == tail);
    }

    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Buffer is empty");
        }
        T item = buffer[head];
        head = (head + 1) % size;
        full = false;
        return item;
    }

    int getCount() const {
        if (full) return size;
        if (tail >= head) {
            return tail - head;
        } else {
            return size - head + tail;
        }
    }
};

// Test Fonksiyonları
void testEmptyBuffer() {
    CircularBuffer<int> buffer(5);
    try {
        if (buffer.isEmpty() == false) {
            std::cerr << "Test failed: Buffer should be empty initially." << std::endl;
        }
        buffer.dequeue();
        std::cerr << "Test failed: Should have thrown an exception on dequeue from empty buffer." << std::endl;
    } catch (const std::runtime_error& e) {
        if (std::string(e.what()) != "Buffer is empty") {
            std::cerr << "Test failed: Unexpected exception - " << e.what() << std::endl;
        } else {
            std::cout << "Test passed: Buffer correctly threw an exception for being empty." << std::endl;
        }
    }
}

void testFullBuffer() {
    CircularBuffer<int> buffer(5);
    for (int i = 0; i < 5; ++i) buffer.enqueue(i);
    if (!buffer.isFull()) {
        std::cerr << "Test failed: Buffer should be full." << std::endl;
    } else {
        std::cout << "Test passed: Buffer correctly identified as full." << std::endl;
    }
}

void testEnqueueDequeue() {
    CircularBuffer<int> buffer(5);
    for (int i = 0; i < 5; ++i) buffer.enqueue(i);
    for (int i = 0; i < 5; ++i) {
        if (buffer.dequeue() != i) {
            std::cerr << "Test failed: Dequeue returned wrong value - expected " << i << std::endl;
            return;
        }
    }
    if (buffer.isEmpty() == false) {
        std::cerr << "Test failed: Buffer should be empty after dequeuing all elements." << std::endl;
    } else {
        std::cout << "Test passed: Buffer correctly enqueued and dequeued elements." << std::endl;
    }
    for (int i = 0; i < 5; ++i) buffer.enqueue(i);
    buffer.enqueue(5);
    if (buffer.dequeue() != 1 || buffer.dequeue() != 2 || buffer.dequeue() != 3 || buffer.dequeue() != 4 || buffer.dequeue() != 5) {
        std::cerr << "Test failed: dequeue() did not return elements in FIFO order after overwrite." << std::endl;
    } else {
        std::cout << "Test passed: dequeue() correctly returned elements in FIFO order after overwrite." << std::endl;
    }
}

void testCount() {
    CircularBuffer<int> buffer(5);
    if (buffer.getCount() != 0) {
        std::cerr << "Test failed: Initial count should be 0." << std::endl;
    } else {
        std::cout << "Test passed: Initial count is correct." << std::endl;
    }
    
    for (int i = 0; i < 3; ++i) buffer.enqueue(i);
    if (buffer.getCount() != 3) {
        std::cerr << "Test failed: Count should be 3 after enqueuing 3 elements." << std::endl;
    } else {
        std::cout << "Test passed: Count is correct after enqueuing 3 elements." << std::endl;
    }
    
    for (int i = 3; i < 5; ++i) buffer.enqueue(i);
    if (buffer.getCount() != 5) {
        std::cerr << "Test failed: Count should be 5 after enqueuing 5 elements." << std::endl;
    } else {
        std::cout << "Test passed: Count is correct after enqueuing 5 elements." << std::endl;
    }
    
    for (int i = 0; i < 5; ++i) buffer.dequeue();
    if (buffer.getCount() != 0) {
        std::cerr << "Test failed: Count should be 0 after dequeuing all elements." << std::endl;
    } else {
        std::cout << "Test passed: Count is correct after dequeuing all elements." << std::endl;
    }
}

void testMultipleDataTypes() {
    CircularBuffer<int> intBuffer(5);
    CircularBuffer<std::string> strBuffer(5);
    
    for (int i = 0; i < 5; ++i) {
        intBuffer.enqueue(i);
        strBuffer.enqueue(std::to_string(i));
    }
    
    for (int i = 0; i < 5; ++i) {
        if (intBuffer.dequeue() != i) {
            std::cerr << "Test failed: Integer dequeue returned wrong value." << std::endl;
            return;
        }
        if (strBuffer.dequeue() != std::to_string(i)) {
            std::cerr << "Test failed: String dequeue returned wrong value." << std::endl;
            return;
        }
    }
    
    std::cout << "Test passed: CircularBuffer correctly handled multiple data types." << std::endl;
}

void testOverwrite() {
    CircularBuffer<int> buffer(5);
    for (int i = 0; i < 5; ++i) buffer.enqueue(i);
    
    // İlk elemanı tekrar yaz
    buffer.enqueue(100);
    if (buffer.dequeue() != 1) {
        std::cerr << "Test failed: Overwritten element dequeue returned wrong value." << std::endl;
    } else {
        std::cout << "Test passed: Buffer correctly overwrote the oldest element." << std::endl;
    }
}

int main() {
    std::cout << "Starting CircularBuffer unit tests:" << std::endl;
    testEmptyBuffer();
    testFullBuffer();
    testEnqueueDequeue();
    testCount();
    testMultipleDataTypes();
    testOverwrite();
    std::cout << "All tests completed." << std::endl;
    return 0;
}