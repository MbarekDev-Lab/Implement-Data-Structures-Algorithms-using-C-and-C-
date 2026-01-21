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
        Q = new int[size];
    }

    Queue(int size)
    {
        this->size = size;
        front = rear = -1;
        Q = new int[this->size];
    }

    voiid enqueue(int x);
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
}

int main()
{

    return 0;
}