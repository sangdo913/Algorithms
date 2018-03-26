#pragma once
#include<iostream>

using namespace std;
typedef int DATA;
typedef class _NODE
{
public:
	DATA data;
	_NODE * next;
} _SNode;

typedef class _Stack
{
public:
	_SNode* head;
	int size;

	void init()
	{
		size = 0;
		head = NULL;
	}
	int GetSize() { return size; };

	void Push(DATA data);
	DATA Pop();
	void DelStack();
	bool isEmpty();
} MyStack;

DATA _Stack::Pop()
{
	if (isEmpty()) return -1;
	DATA result = head->data;
	_SNode* rnode = head;
	head = head->next;

	delete(rnode);
	size--;
	return result;
}

void _Stack::Push(DATA data)
{
	_SNode * new_node = new _SNode();
	new_node->data = data;
	if (head == NULL)
	{
		new_node->next = NULL;
	}

	else
	{
		new_node->next = head;
	}

	head = new_node;
	size++;
}

bool _Stack::isEmpty()
{
	return size == 0;
}

void _Stack::DelStack()
{
	_SNode *rnode;
	while (head != NULL)
	{
		rnode = head;
		head = head->next;
		delete(rnode);
		size--;
	}
}