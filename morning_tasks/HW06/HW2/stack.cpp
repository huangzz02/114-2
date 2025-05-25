#include "stack.h"
#include <iostream>
#include <algorithm>
#include <random>

Stack::Stack(int size) {
    maxSize = size;
    top = -1;
    stackArray = new std::string[maxSize];
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

void Stack::push(const std::string& value) {
    if (isFull()) {
        std::cout << "The stack is full!" << std::endl;
        return;
    }
    stackArray[++top] = value;
}

std::string Stack::pop() {
    if (isEmpty()) {
        return "";
    }
    std::string value = stackArray[top--];
    return value;
}

void Stack::clear() {
    top = -1;
    std::cout << "Empty the stack." << std::endl;
}

std::string Stack::getTop() const {
    if (isEmpty()) {
        return "";
    }
    return stackArray[top];
}

void Stack::display() const {
    std::cout << "Stack: " << std::endl;
    if (isEmpty()) {
        std::cout << "The stack is empty." << std::endl;
        return;
    }
    for (int i = top; i >= 0; i--) {
        std::cout << stackArray[i] << std::endl;
    }
}

void Stack::initialize(std::string values[], int count) {
    if (count > maxSize) {
        count = maxSize;
    }
    for (int i = 0; i < count; i++) {
        stackArray[i] = values[i];
    }
    top = count - 1;
}

void Stack::shuffle() {
    if (top < 0) {
        std::cout << "The stack is empty, nothing to shuffle." << std::endl;
        return;
    }
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::shuffle(stackArray, stackArray + top + 1, engine);
    display();
}