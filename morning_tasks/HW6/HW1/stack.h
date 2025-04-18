#ifndef STACK_H
#define STACK_H

class Stack {
    private:
        int top;
        int maxSize;
        int* stackArray;
    
    public:
        Stack(int size);
        ~Stack();

        bool isEmpty() const;
        bool isFull() const;

        void push();
        int pop();
        void clear();
        int getTop() const;
        void display() const;

        void initialize(int values[], int count);
        void handleChoice(int choice);
};

#endif