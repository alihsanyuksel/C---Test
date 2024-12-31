#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>

// CircularBuffer sınıfı
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

// Boş Buffer Testi
void testEmptyBuffer() {
    CircularBuffer<int> buffer(3);
    try {
        buffer.dequeue();
        std::cerr << "Test failed: dequeue() did not throw an exception on an empty buffer." << std::endl;
    } catch (const std::runtime_error&) {
        std::cout << "Test passed: dequeue() correctly threw an exception on an empty buffer." << std::endl;
    }
    if (buffer.isEmpty() == false) {
        std::cerr << "Test failed: isEmpty() did not return true on an empty buffer." << std::endl;
    } else {
        std::cout << "Test passed: isEmpty() correctly returned true on an empty buffer." << std::endl;
    }
}

// Dolu Buffer Testi
void testFullBuffer() {
    CircularBuffer<int> buffer(3);
    buffer.enqueue(1);
    buffer.enqueue(2);
    buffer.enqueue(3);
    if (buffer.isFull() == false) {
        std::cerr << "Test failed: isFull() did not return true on a full buffer." << std::endl;
    } else {
        std::cout << "Test passed: isFull() correctly returned true on a full buffer." << std::endl;
    }
}

// Kuyruğa Alma ve Sıradan Çıkarma Testi
void testEnqueueDequeue() {
    CircularBuffer<int> buffer(3);
    buffer.enqueue(1);
    buffer.enqueue(2);
    buffer.enqueue(3);

    if (buffer.dequeue() != 1 || buffer.dequeue() != 2 || buffer.dequeue() != 3) {
        std::cerr << "Test failed: dequeue() did not return elements in FIFO order." << std::endl;
    } else {
        std::cout << "Test passed: dequeue() correctly returned elements in FIFO order." << std::endl;
    }

    buffer.enqueue(1);
    buffer.enqueue(2);
    buffer.enqueue(3);
    buffer.enqueue(4); // üzerine yazma
    if (buffer.dequeue() != 1 || buffer.dequeue() != 2 || buffer.dequeue() != 3 || buffer.dequeue() != 4) {
        std::cerr << "Test failed: dequeue() did not return elements in FIFO order after overwrite." << std::endl;
    } else {
        std::cout << "Test passed: dequeue() correctly returned elements in FIFO order after overwrite." << std::endl;
    }
}

// Sayı Testi
void testGetCount() {
    CircularBuffer<int> buffer(3);
    if (buffer.getCount() != 0) {
        std::cerr << "Test failed: getCount() did not return 0 on an empty buffer." << std::endl;
    } else {
        std::cout << "Test passed: getCount() correctly returned 0 on an empty buffer." << std::endl;
    }

    buffer.enqueue(1);
    if (buffer.getCount() != 1) {
        std::cerr << "Test failed: getCount() did not return 1 after enqueue." << std::endl;
    } else {
        std::cout << "Test passed: getCount() correctly returned 1 after enqueue." << std::endl;
    }

    buffer.enqueue(2);
    buffer.enqueue(3);
    buffer.dequeue();
    if (buffer.getCount() != 2) {
        std::cerr << "Test failed: getCount() did not return 2 after dequeue." << std::endl;
    } else {
        std::cout << "Test passed: getCount() correctly returned 2 after dequeue." << std::endl;
    }
}

// Çoklu Veri Türleri Testi
void testMultipleDataTypes() {
    CircularBuffer<int> buffer(3);
    buffer.enqueue(1);
    buffer.enqueue(2);
    if (buffer.dequeue() != 1 || buffer.dequeue() != 2) {
        std::cerr << "Test failed: dequeue() did not return integers in FIFO order." << std::endl;
    } else {
        std::cout << "Test passed: dequeue() correctly returned integers in FIFO order." << std::endl;
    }

    CircularBuffer<std::string> bufferStr(3);
    bufferStr.enqueue("a");
    bufferStr.enqueue("b");
    if (bufferStr.dequeue() != "a" || bufferStr.dequeue() != "b") {
        std::cerr << "Test failed: dequeue() did not return strings in FIFO order." << std::endl;
    } else {
        std::cout << "Test passed: dequeue() correctly returned strings in FIFO order." << std::endl;
    }
}

// Ana Test İşlevi
int main() {
    std::cout << "Running CircularBuffer Unit Tests..." << std::endl;
    testEmptyBuffer();
    testFullBuffer();
    testEnqueueDequeue();
    testGetCount();
    testMultipleDataTypes();
    std::cout << "All tests completed." << std::endl;
    return 0;
}