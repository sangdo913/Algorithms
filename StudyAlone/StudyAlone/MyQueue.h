#pragma once
#include<iostream>

using namespace std;
typedef int __MyData;

typedef class _QNode
{
public:
	_QNode* next;
	__MyData data;
} _QNode;

typedef class MyQueue
{
public:
	typedef __MyData Data;
	typedef _QNode Node;
	_QNode* front;
	_QNode* rear;
	int size;
	bool IsEmpty();
	void enqueue(Data data);
	Data dequeue();
	void init();
	void DelQueue();
};
bool MyQueue::IsEmpty()
{
	return size == 0;
}
void MyQueue::enqueue(Data data)
{
	Node *newNode = new Node();
	newNode->data = data;
	newNode->next = NULL;
	if (IsEmpty())
	{
		front = newNode;
	}
	else
	{
		rear->next = newNode;
	}
	rear = newNode;

	size++;
}
__MyData MyQueue::dequeue()
{
	if (IsEmpty()) return -1;
	__MyData result = front->data;
	Node* rnode = front;
	front = front->next;
	delete(rnode);
	size--;
	return result;
}
void MyQueue::init()
{
	rear = front = NULL;
	size = 0;
}
void MyQueue::DelQueue()
{
	Node* rnode;
	while (front!=NULL)
	{
		rnode = front;
		front = front->next;
		delete(rnode);
	}
	size = 0;
}