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
        if(full) return size;
        if (tail >= head) {
            return tail - head;
        } else {
            return size - head + tail;
        }
    }
};

// Test işlevleri
void testEmptyBuffer() {
    CircularBuffer<int> buffer(5);
    std::cout << "Running testEmptyBuffer...\n";

    // Boş bir buffer isEmpty kontrolü
    if (buffer.isEmpty()) {
        std::cout << "PASS: isEmpty() returns true for a newly created buffer.\n";
    } else {
        std::cout << "FAIL: isEmpty() returns false for a newly created buffer.\n";
    }

    // Boş bir buffer dequeue çağrısı
    try {
        buffer.dequeue();
        std::cout << "FAIL: dequeue() did not throw an exception on an empty buffer.\n";
    } catch (const std::runtime_error&) {
        std::cout << "PASS: dequeue() throws an exception on an empty buffer.\n";
    }
}

void testFullBuffer() {
    CircularBuffer<int> buffer(3);
    std::cout << "Running testFullBuffer...\n";

    // Kuyruğa eleman ekleme
    buffer.enqueue(1);
    buffer.enqueue(2);
    buffer.enqueue(3);

    if (buffer.isFull()) {
        std::cout << "PASS: isFull() returns true when buffer is full.\n";
    } else {
        std::cout << "FAIL: isFull() returns false when buffer is full.\n";
    }
}

void testEnqueueDequeue() {
    CircularBuffer<int> buffer(3);
    std::cout << "Running testEnqueueDequeue...\n";

    buffer.enqueue(1);
    buffer.enqueue(2);
    buffer.enqueue(3);

    // FIFO sırasını kontrol etme
    if (buffer.dequeue() == 1 && buffer.dequeue() == 2 && buffer.dequeue() == 3) {
        std::cout << "PASS: enqueue and dequeue maintain FIFO order.\n";
    } else {
        std::cout << "FAIL: enqueue and dequeue do not maintain FIFO order.\n";
    }
}

void testGetCount() {
    CircularBuffer<int> buffer(4);
    std::cout << "Running testGetCount...\n";

    buffer.enqueue(1);
    buffer.enqueue(2);

    if (buffer.getCount() == 2) {
        std::cout << "PASS: getCount() returns correct count after enqueue operations.\n";
    } else {
        std::cout << "FAIL: getCount() returns incorrect count after enqueue operations.\n";
    }

    buffer.dequeue();

    if (buffer.getCount() == 1) {
        std::cout << "PASS: getCount() returns correct count after dequeue operations.\n";
    } else {
        std::cout << "FAIL: getCount() returns incorrect count after dequeue operations.\n";
    }
}

void testMultipleDataTypes() {
    std::cout << "Running testMultipleDataTypes...\n";

    CircularBuffer<int> intBuffer(3);
    CircularBuffer<std::string> stringBuffer(2);

    intBuffer.enqueue(42);
    stringBuffer.enqueue("hello");

    if (intBuffer.dequeue() == 42 && stringBuffer.dequeue() == "hello") {
        std::cout << "PASS: CircularBuffer works with multiple data types.\n";
    } else {
        std::cout << "FAIL: CircularBuffer does not work with multiple data types.\n";
    }
}

void testOverwriteAndPlacement() {
    CircularBuffer<int> buffer(3);
    std::cout << "Running testOverwriteAndPlacement...\n";

    buffer.enqueue(1);
    buffer.enqueue(2);
    buffer.enqueue(3);
    buffer.enqueue(4); // Overwrites oldest (1)

    if (buffer.dequeue() == 2 && buffer.dequeue() == 3 && buffer.dequeue() == 4) {
        std::cout << "PASS: Overwriting and placement work correctly.\n";
    } else {
        std::cout << "FAIL: Overwriting and placement do not work correctly.\n";
    }
}

int main() {
    std::cout << "Starting CircularBuffer tests...\n\n";

    testEmptyBuffer();
    testFullBuffer();
    testEnqueueDequeue();
    testGetCount();
    testMultipleDataTypes();
    testOverwriteAndPlacement();

    std::cout << "\nAll tests completed.\n";
    return 0;
}
