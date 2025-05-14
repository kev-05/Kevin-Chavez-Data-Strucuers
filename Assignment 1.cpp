//
//  main.cpp
//  Assignment 1
//
//  Created by Kevin Chavez on 2/20/25.
//

#include <iostream>

struct Node {
    int data;
    Node* next;
};

int LinkedlistInsert(int data, int index, Node** Ptr) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;

    if (index == 0) {
        newNode->next = *Ptr;
        *Ptr = newNode;
        return 1; // Success
    }

    Node* current = *Ptr;
    for (int i = 0; i < index - 1; i++) {
        if (current == nullptr) {
            return 0; // Index out of bounds
        }
        current = current->next;
    }

    if (current == nullptr) {
        return 0; // Index out of bounds
    }

    newNode->next = current->next;
    current->next = newNode;
    return 1; // Success
}

int LinkedlistDelete(int index, Node** Ptr) {
    if (*Ptr == nullptr) {
        return 0; // List is empty
    }

    Node* temp = *Ptr;
    if (index == 0) {
        *Ptr = temp->next;
        delete temp;
        return 1; // Success
    }

    Node* current = *Ptr;
    for (int i = 0; i < index - 1; i++) {
        if (current->next == nullptr) {
            return 0; // Index out of bounds
        }
        current = current->next;
    }

    if (current->next == nullptr) {
        return 0; // Index out of bounds
    }

    Node* nodeToDelete = current->next;
    current->next = nodeToDelete->next;
    delete nodeToDelete;
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

    LinkedlistInsert(10, 0, &head); // List: 10
    LinkedlistInsert(20, 1, &head); // List: 10 -> 20
    LinkedlistInsert(30, 1, &head); // List: 10 -> 30 -> 20

    printList(head);

    LinkedlistDelete(1, &head); // List: 10 -> 20
    printList(head);

    return 0;
}
