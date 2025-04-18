#ifndef STACK_H
#define STACK_H

#include <string>

class Stack {
    private:
        int top;
        int maxSize;
        std::string* stackArray;

    public:
        Stack(int size);
        ~Stack();

        bool isEmpty() const;
        bool isFull() const;

        void push(const std::string& value);
        std::string pop();
        void clear();
        std::string getTop() const;
        void display() const;

        void initialize(std::string values[], int count);
        void shuffle();
};

#endif