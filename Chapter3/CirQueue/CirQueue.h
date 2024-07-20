#ifndef __CIRCULAR_QUEUE_H__
#define __CIRCULAR_QUEUE_H__
#include<stdlib.h>

#define MAXSIZE 50

template<class E>
class CirQueue { // 使用辅助变量的方法
private:
    E data[MAXSIZE];
    int front, rear;
    bool tag;

public:
    CirQueue() : front(0), rear(0), tag(false) {}

    bool isEmpty() const {
        return (front == rear) && !tag;
    }

    bool isFull() const {
        return (front == rear) && tag;
    }

    bool EnCirQueue(const E& e) {
        if (isFull()) return false;
        data[rear] = e;
        rear = (rear + 1) % MAXSIZE;
        if (rear == front) tag = 1;
        return true;
    }

    bool DeCirQueue(E& e) {
        if (isEmpty()) return false;
        e = data[front];
        front = (front + 1) % MAXSIZE;
        if (rear == front) tag = 0;
        return true;
    }

    bool getFront(E& e) const {
        if (isEmpty()) return false;
        e = data[front];
        return true;
    }
};

#endif