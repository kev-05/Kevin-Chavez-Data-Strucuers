//
//  main.cpp
//  Assignment 5
//
//  Created by Kevin Chavez on 3/20/25.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

template <typename T>
class MaxHeap {
private:
    std::vector<T> heap;

    // Up-heap (bubble up) for insertion
    void upHeap(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] > heap[parent]) {
                std::swap(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    // Down-heap (bubble down) for removal
    void downHeap(int index) {
        int size = heap.size();
        while (true) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int largest = index;

            if (leftChild < size && heap[leftChild] > heap[largest]) {
                largest = leftChild;
            }
            if (rightChild < size && heap[rightChild] > heap[largest]) {
                largest = rightChild;
            }

            if (largest != index) {
                std::swap(heap[index], heap[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

public:
    MaxHeap() = default;

    // Insert element into heap
    void insert(const T& value) {
        heap.push_back(value);
        upHeap(heap.size() - 1);
    }

    // Remove and return max element
    T extractMax() {
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }

        T max = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        
        if (!heap.empty()) {
            downHeap(0);
        }

        return max;
    }

    // Get max element without removing
    const T& getMax() const {
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }
        return heap[0];
    }

    // Check if heap is empty
    bool isEmpty() const {
        return heap.empty();
    }

    // Get heap size
    size_t size() const {
        return heap.size();
    }

    // Print heap (for testing)
    void printHeap() const {
        for (const auto& elem : heap) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
};

// Test function
void testHeap() {
    MaxHeap<int> heap;

    // Test insertion and up-heap
    std::cout << "Inserting elements: 10, 20, 15, 30, 5" << std::endl;
    heap.insert(10);
    heap.insert(20);
    heap.insert(15);
    heap.insert(30);
    heap.insert(5);

    std::cout << "Heap after insertions: ";
    heap.printHeap();  // Should show heap structure with 30 at root

    // Test getMax
    std::cout << "Max element: " << heap.getMax() << std::endl;  // Should be 30

    // Test extraction and down-heap
    std::cout << "Extracting max elements one by one:" << std::endl;
    while (!heap.isEmpty()) {
        std::cout << "Extracted: " << heap.extractMax() << " | Heap: ";
        heap.printHeap();
    }

    // Test empty heap handling
    try {
        heap.getMax();
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

int main() {
    testHeap();
    return 0;
}
