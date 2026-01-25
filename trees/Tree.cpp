#include <iostream>
#include "Queue.h"
using namespace std;

class Node
{
public:
    Node *lChird;
    Node *rChird;   
    int data;
};

class Queue
{
private:
    int front;
    int rear;
    int size;
    Node **Q; // one pointer point to another pointer of type Node

public:
    Queue()
    {
        front = rear = -1;
        size = 10;
        Q = new Node * [size];
    };

    Queue(int size)
    {
        size = size;
        front = rear = -1;
        this->size = size;
        Q = new Node * [this->size];
    };
    void enqueue(int x);
    int dequeue();
    int isEmpty();
    void Display();
    void create(int size);
};


void Queue::enqueue(Node *x)
{
   if(rear == size -1)
       cout<<"Queue is Full"<<endl;
   else
   {
       rear++;
       Q[rear] = x;
   }
   // struct Node *next;

}


Node* Queue::dequeue()
{
    Node *x = NULL;

    if(front == rear)
        cout<<"Queue is Empty"<<endl;
    else
    {
        front++; // circular increment to next index saving space
        x = Q[front];
    }
    return x;
};

