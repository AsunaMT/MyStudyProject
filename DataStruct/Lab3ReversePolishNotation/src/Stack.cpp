#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include "Stack.h"

template <typename T>
bool Stack<T>::Empty(){
    if(lenth == 0) return true;
    else return false;
}

template <typename T>
void Stack<T>::Push(T val){
    Node *p = new Node;
    p->data = val;
    if(Empty()){
        p->next = NULL;
        top = bottom = p;
        lenth ++;
        return;
    }
    top -> next = p;
    top = p;
    top -> next = NULL;
    lenth ++;
}

template <typename T>
T Stack<T>::Pop(){
    if(Empty()) abort();
    T temp = top -> data;
    lenth --;
    Node *p = bottom;
    for(int i = 1; i < lenth; i++){
        p = p -> next;
    }
    top = p;
    top -> next = NULL;
    if(lenth == 0) bottom = NULL; 
    return temp;
}

template <typename T>
T Stack<T>::GetTop(){
    if(Empty()) abort();
    return top -> data;
}