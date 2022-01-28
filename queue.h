#include <iostream>
using namespace std;

template <typename T> class Node
{
public:
    T data;
    Node *next;
    Node()
    {
        next = NULL;
    }
};
template <typename T> class queue
{
public:
    Node<T> *fro;
    Node<T> *rear;
    int count;
    queue()
    {
        count = 0;
        rear = NULL;
        fro = NULL;
    }
    int size(){
        return count;
    }
    bool isEmpty()
    {
        return count == 0;
    }
    void enqueue(T x)
    {
        Node<T> *temp = new Node<T>;

        temp->data = x;
        if (isEmpty())
        {
            fro = temp;
            rear = temp;
        }
        else
        {
            rear->next = temp;
            rear = temp;
        }
        count++;
    }
    void dequeue()
    {
        if (!isEmpty())
        {
            T temp = fro->data;
            count--;
            fro = fro->next;
        }
    }
    T front()
    {
        if (!isEmpty())
        {
            return fro->data;
        }
        else
        {
            return NULL;
        }
    }
};