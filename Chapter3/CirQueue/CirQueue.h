#ifndef __CIRCULAR_QUEUE_H__
#define __CIRCULAR_QUEUE_H__


#define MAXSIZE 50

template<class E>
class CirQueue { // 使用辅助变量的方法
private:
    E data[MAXSIZE];
    int front, rear;
    bool tag;

public:
    CirQueue() {
        front = rear = 0;
        tag = 0;
    }

    bool isEmpty() const {
        if (tag) return false;
        if (front == rear) return true;
    }

    bool isFull() const {
        if (!tag) return false;
        if (front == rear) return true;
    }

    bool EnCirQueue(const E& e) {
        if (isFull()) return false;
        data[rear] = e;
        rear = (rear + 1) % MAXSIZE;
        tag = 1;
        return true;
    }

    bool DeCirQueue(E& e) {
        if (isEmpty()) return false;
        e = data[front];
        front = (front + 1) % MAXSIZE;
        tag = 0;
        return true;
    }

    bool getFront(E& e) const {
        if (isEmpty()) return false;
        e = data[front];
        return true;
    }
};

#endif