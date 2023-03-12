#ifndef STACK_H
#define STACK_H

template <typename T>
class Stack{ 
    struct Node{
        T data;
        Node *next;
    };
    int lenth = 0;
    Node *top = NULL;
    Node *bottom = NULL;
public: 
    bool Empty();
    void Push(T val);
    T Pop();
    T GetTop();
};


#endif