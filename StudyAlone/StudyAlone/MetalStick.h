#pragma once
#include<iostream>

using namespace std;

struct Metal_Stick
{
	int n;
	int m;
	int w;
};

template <typename T>
struct Metal_Node
{
	T value;
	Metal_Node<T>* next;
	Metal_Node<T>* prev;
	Metal_Node<T>()
	{
		next = prev = NULL;
	}
};

template<typename T>
struct Metal_List
{
	typedef Metal_Node<T> Node;
	Node* tail;
	Node* head;
	Node* cursor;
	int size;
	void clear()
	{
		Node* dNode;
		cursor = head->next;
		while (cursor!=tail)
		{
			dNode = cursor;
			cursor = cursor->next;
		}
		head->next = tail;
		tail->prev = head;
		cursor = head;
	}
	bool del()
	{
		if (size == 0) return false;
		Node* dNode = cursor;
		cursor = cursor->prev;
		cursor->next = cursor->next->next;
		cursor->next->prev = cursor;
		if (dNode != head && dNode != tail) delete(dNode);
		return true;
	}
	bool next(T& res)
	{
		if (cursor->next == tail) return false;
		cursor = cursor->next;
		res = cursor->value;
		return true;
	}
	void first()
	{
		cursor = head;
	}
	void insert(const T& value)
	{
		Node* newNode = new Node();
		newNode->value = value;
		newNode->prev = head;
		newNode->next = head->next;
		head->next->prev = newNode;
		head->next = newNode;
		size++;
	}
	Metal_List<T>()
	{
		tail = new Node();
		head = new Node();
		head->next = tail;
		tail->prev = head;
		size = 0;
	}
	~Metal_List<T>()
	{
		Node* dNode;
		while (head)
		{
			dNode = head;
			head = head->next;
		}
	}
};

bool Metal_visit[20] = { false };
int Metal_maxLength;
int Metal_length = 0;
Metal_Stick Metal_sticks[20];
Metal_List<int> Metal_res;
Metal_List<int> Metal_path;

void Metal_MaxLink(const int N, int w)
{
	
	for (int i = 0; i < N; i++)
	{
		if (w == Metal_sticks[i].m)
		{
			if (Metal_visit[i]) continue;
			Metal_visit[i] = true;
			Metal_length++;
			Metal_path.insert(i);
			Metal_MaxLink(N, Metal_sticks[i].w);
			Metal_visit[i] = false;
			Metal_path.cursor = Metal_path.tail->prev;
			Metal_path.del();
			Metal_length--;
		}
	}
	int metalNum;
	if (Metal_length > Metal_maxLength)
	{
		Metal_maxLength = Metal_length;

		Metal_res.clear();
		Metal_path.first();
		while (Metal_path.next(metalNum))
		{
			Metal_res.insert(metalNum);
		}
	}
}


int MetalStick()
{
	int T, N;
	cin >> T;
	for (int tc = 1; tc <= T;tc++)
	{
		cin >> N;
		Metal_length = 0;
		Metal_maxLength = 0;
		Metal_res.clear();
		//init
		for (int i = 0; i < N; i++)
		{
			cin >> Metal_sticks[i].m >> Metal_sticks[i].w;

			Metal_sticks[i].n = i;

			Metal_visit[i] = false;
		}
		for (int i = 0; i < N; i++)
		{
			Metal_visit[i] = true;
			Metal_path.insert(i);
			Metal_MaxLink(N, Metal_sticks[i].w);
			Metal_path.clear();
			Metal_visit[i] = false;
		}
		Metal_res.first();
		int metalNum;
		cout << '#' << tc;
		while (Metal_res.next(metalNum))
		{
			cout << ' ' << Metal_sticks[metalNum].m << ' ' << Metal_sticks[metalNum].w;
		}
		cout << endl;
	}
	return 0;
}