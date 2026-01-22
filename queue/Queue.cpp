#include <iostream>
#include <stdlib.h>

using namespace std;

class Queue
{
private:
    int size;
    int front;
    int rear;
    int *Q;

public:
    Queue()
    {
        size = 10;
        front = rear = -1;
        Q = new int[size]; // default size 10 (dynamically allocated)
    }

    Queue(int size)
    {
        this->size = size;
        front = rear = -1;
        Q = new int[this->size];
    }

    void enqueue(int x);
    int dequeue();
    void display() const;
    bool isEmpty() const;
    bool isFull() const;
    int getFront() const;
    int getRear() const;
    int getSize() const;
    void clear();

    ~Queue()
    {
        delete[] Q;
    }
};

void Queue::enqueue(int x)
{

    if (rear == size - 1)
    {
        cout << "Queue is Full" << endl;
    }
    else
    {
        rear++;
        Q[rear] = x;
    }
}

int Queue::dequeue()
{
    int x = -1;
    if (front == rear)
    {
        cout << "Queue is Empty" << endl;
    }
    else
    {
        x = Q[front + 1];
        front++;
    }
    return x;
}

void Queue::display() const
{
    for (int i = front + 1; i <= rear; i++)
    {
        cout << Q[i] << " ";
    }
    cout << endl;
}

int main()
{

    Queue q(5);
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.display();
    q.dequeue();
    q.display();

    return 0;
}
/*
    benraiss@MacBookAir queue %  clang++ -std=c++17 -Wall -Wextra -o _cpp Queue.cpp
    benraiss@MacBookAir queue % ./_cpp
    10 20 30
    20 30
    benraiss@MacBookAir queue %
*/
