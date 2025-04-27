//
//  main.cpp
//  Assignment 3
//
//  Created by Kevin Chavez on 3/06/25.
//

#include <iostream>
#include <stdexcept> // For std::runtime_error

struct Stack {
    int data[100]; // Fixed-size array for simplicity
    int top = -1;  // Indicates an empty stack
};

int push(int T, Stack* stack) {
    if (stack->top >= 99) {
        return 0; // Stack overflow
    }
    stack->data[++stack->top] = T;
    return 1; // Success
}

int topandpop(Stack* stack) {
    if (stack->top == -1) {
        throw std::runtime_error("Stack underflow");
    }
    return stack->data[stack->top--];
}

int main() {
    Stack s;

    push(10, &s);
    push(20, &s);
    push(30, &s);

    std::cout << topandpop(&s) << std::endl; // 30
    std::cout << topandpop(&s) << std::endl; // 20
    std::cout << topandpop(&s) << std::endl; // 10

    return 0;
}
