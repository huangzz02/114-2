#include "stack.h"
#include <iostream>

Stack::Stack(int size) {
    maxSize = size;
    top = -1;
    stackArray = new int[maxSize];
}

Stack::~Stack() {
    delete[] stackArray;
}

bool Stack::isEmpty() const {
    return top == -1;
}

bool Stack::isFull() const {
    return top == maxSize - 1;
}

void Stack::push() {
    if (isFull()) {
        std::cout << "The stack is full!" << std::endl;
        return;
    }
    std::cout << "Push number: ";
    int value;
    std::cin >> value;
    stackArray[++top] = value;
    display();
}

int Stack::pop() {
    if (isEmpty()) {
        std::cout << "The stack is empty!" << std::endl;
        return -1; // Error value
    }
    int value = stackArray[top--];
    std::cout << "Pop number: " << value << std::endl;
    display();
    return value;
}

void Stack::clear() {
    top = -1;
    std::cout << "Empty the stack." << std::endl;
}

int Stack::getTop() const {
    if (isEmpty()) {
        std::cout << "The stack is empty!" << std::endl;
        return -1; // Error value
    }
    std::cout << "Top number is: " << stackArray[top] << std::endl;
    return stackArray[top];
}

void Stack::display() const {
    std::cout << "Stack: " << std::endl;
    if (isEmpty()) {
        return;
    }
    for (int i = top; i >= 0; i--) {
        std::cout << stackArray[i] << std::endl;
    }
}

void Stack::initialize(int values[], int count) {
    if (count > maxSize) {
        count = maxSize;
    }
    for (int i = 0; i < count; i++) {
        stackArray[i] = values[i];
    }
    top = count - 1;
}

void Stack::handleChoice(int choice) {
    int num;
    switch (choice) {
        case 1: // Push
            push();
            break;
        case 2: // Pop
            pop();
            break;
        case 3: // Empty
            clear();
            break;
        case 4: // Top
            getTop();
            break;
        default:
            std::cout << "Invalid choice!" << std::endl;
    }
    std::cout << std::endl;
}