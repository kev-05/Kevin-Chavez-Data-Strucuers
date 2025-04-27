//
//  main.cpp
//  Assignment 2
//
//  Created by Kevin Chavez on 2/27/25.
//

#include <iostream>

struct Node {
    int data;
    Node* prev;
    Node* next;
};

int DoubleLinkedlistInsert(int data, int index, Node** Ptr) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->prev = nullptr;
    newNode->next = nullptr;

    if (index == 0) {
        newNode->next = *Ptr;
        if (*Ptr != nullptr) {
            (*Ptr)->prev = newNode;
        }
        *Ptr = newNode;
        return 1; // Success
    }

    Node* current = *Ptr;
    for (int i = 0; i < index - 1; i++) {
        if (current == nullptr) {
            delete newNode;
            return 0; // Index out of bounds
        }
        current = current->next;
    }

    if (current == nullptr) {
        delete newNode;
        return 0; // Index out of bounds
    }

    newNode->next = current->next;
    newNode->prev = current;
    if (current->next != nullptr) {
        current->next->prev = newNode;
    }
    current->next = newNode;
    return 1; // Success
}

int DoubleLinkedlistDelete(int index, Node** Ptr) {
    if (*Ptr == nullptr) {
        return 0; // List is empty
    }

    Node* temp = *Ptr;
    if (index == 0) {
        *Ptr = temp->next;
        if (*Ptr != nullptr) {
            (*Ptr)->prev = nullptr;
        }
        delete temp;
        return 1; // Success
    }

    Node* current = *Ptr;
    for (int i = 0; i < index; i++) {
        if (current == nullptr) {
            return 0; // Index out of bounds
        }
        current = current->next;
    }

    if (current == nullptr) {
        return 0; // Index out of bounds
    }

    if (current->prev != nullptr) {
        current->prev->next = current->next;
    }
    if (current->next != nullptr) {
        current->next->prev = current->prev;
    }
    delete current;
    return 1; // Success
}

// Helper function to print the linked list
void printList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

int main() {
    Node* head = nullptr;

    DoubleLinkedlistInsert(10, 0, &head); // List: 10
    DoubleLinkedlistInsert(20, 1, &head); // List: 10 -> 20
    DoubleLinkedlistInsert(30, 1, &head); // List: 10 -> 30 -> 20

    printList(head);

    DoubleLinkedlistDelete(1, &head); // List: 10 -> 20
    printList(head);

    return 0;
}
