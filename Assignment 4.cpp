//
//  main.cpp
//  Assignment 4
//
//  Created by Kevin Chavez on 3/10/25.
//

#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class CircularQueue {
private:
    Node* rear; // Only rear pointer is needed (front is rear->next)
public:
    CircularQueue() : rear(nullptr) {}

    bool isEmpty() {
        return rear == nullptr;
    }

    void enqueue(int val) {
        Node* newNode = new Node(val);
        if (isEmpty()) {
            rear = newNode;
            rear->next = rear; // Points to itself
        } else {
            newNode->next = rear->next;
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return;
        }
        Node* front = rear->next;
        if (front == rear) { // Only one node
            rear = nullptr;
        } else {
            rear->next = front->next;
        }
        delete front;
    }

    int getFront() {
        if (isEmpty()) {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        return rear->next->data;
    }

    ~CircularQueue() {
        if (!isEmpty()) {
            Node* current = rear->next;
            while (current != rear) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
            delete rear;
        }
    }
};

int main() {
    CircularQueue q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    cout << "Front: " << q.getFront() << endl; // 10
    q.dequeue();
    cout << "Front after dequeue: " << q.getFront() << endl; // 20

    return 0;
}
