#pragma once
#include<iostream>
using namespace std;
typedef int _ListData;
typedef class _DBLinkedListNode
{
public:
	_DBLinkedListNode *next;
	_DBLinkedListNode *prev;
	_ListData data;
} DBLinkedListNode;


typedef class DBLinkedList
{
public:
	typedef DBLinkedListNode Node;
	typedef _ListData Data;
	int size;
	Node* front;
	Node *rear;
	Node *cur;

	void init();
	void delList();
	void Finsert(Data data);
	void Rinsert(Data data);
	Data Fget();
	Data Rget();
	Data Next();
	Data Prev();
	void FCursor();
	void Fdel();
	void Rdel();
};

void DBLinkedList::init()
{
	rear = new Node();
	front = new Node();
	front->prev = rear->next = NULL;
	front->next = rear;
	rear->prev = front;

	size = 0;
}
void DBLinkedList::delList()
{
	Node* rnode;
	while (front->next != rear)
	{
		rnode = front->next;
		front->next = front->next->next;
		delete(rnode);
	}
	size = 0;
	delete(front); delete(rear);
}

void DBLinkedList::Finsert(Data data)
{
	Node * new_node = new Node();
	new_node->data = data;

	new_node->next = front->next;
	new_node->prev = front;

	front->next->prev = new_node;
	front->next = new_node;
	size++;
}
void DBLinkedList::Rinsert(Data data)
{
	Node * new_node = new Node();
	new_node->data = data;
	new_node->next = rear;
	new_node->prev = rear->prev;

	rear->prev->next = new_node;
	rear->prev = new_node;
	size++;
}
_ListData DBLinkedList::Fget()
{
	if (front->next != rear) cur = front->next;
	else
	{
		cout << "empty\n" << endl;
		return -1;
	}

	return cur->data;
}
_ListData DBLinkedList::Rget()
{
	if (front ->next != rear) cur = rear->prev;
	else
	{
		cout << "empty\n" << endl;
		return -1;
	}
	return cur->data;
}
void DBLinkedList::FCursor()
{
	if (front->next != rear) cur = front->next;
	else
	{
		cout << "empty\n" << endl;
	}
}

void DBLinkedList::Fdel()
{
	if (front->next == rear)
	{
		cout << "empty\n" << endl;
		return;
	}

	Node* rnode = cur;
	cur = cur->prev;
	delete(cur);
	size--;
}

void DBLinkedList::Rdel()
{
	if (front->next == rear)
	{
		cout << "empty\n" << endl;
		return;
	}

	Node* rnode = cur;
	cur = cur->prev;
	delete(cur);
	size--;
}

_ListData DBLinkedList::Next()
{
	if (cur->next == rear)
	{
		cout << "Can't Go.." << endl;
		return -1;
	}
	cur = cur->next;
	return cur->data;
}
_ListData DBLinkedList::Prev()
{
	if (cur->prev == front)
	{
		cout << "Can't Go.." << endl;
		return -1;
	}
	cur = cur->prev;
	return cur->data;
}