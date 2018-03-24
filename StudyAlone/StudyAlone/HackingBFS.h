#pragma once
#include<iostream>
using namespace std;
template <typename T>
struct HackingBFS_Node
{
	T value;
	typedef HackingBFS_Node Node;
	Node* prev;
	Node* next;
	HackingBFS_Node<T>()
	{
		prev = next = NULL;
	}
};

template <typename T>
struct HackingBFS_Queue
{
	typedef HackingBFS_Node<T> Node;
	int size;
	Node* head;
	Node* tail;
	HackingBFS_Queue<T>()
	{
		head = new Node();
		tail = new Node();
		head->next = tail;
		tail->prev = head;
		size = 0;
	}
	void push(const T& data)
	{
		size++;
		Node* newNode = new Node();
		newNode->value = data;
		newNode->next = head->next;
		newNode->prev = head;
		head->next->prev = newNode;
		head->next = newNode;
	}
	bool pop(T& data)
	{
		if (size == 0) return false;
		size--;
		Node* dNode = tail->prev;
		data = dNode->value;
		tail->prev = dNode->prev;
		tail->prev->next = tail;
		delete dNode;
	}
};

template <typename T>
struct HackingBFS_Vector
{
	int size;
	int maxSize;
	T* values;
	HackingBFS_Vector<T>()
	{
		size = 0;
		maxSize = 100;
		values = new T[maxSize];
	}
	void push_back(const T& value)
	{
		if (size == maxSize)
		{
			maxSize <<= 1;
			T* newValues = new T[maxSize];
			for (int i = 0; i < size; i++)
			{
				newValues[i] = values[i];
			}
			delete[] values;
			values = newValues;
		}

		values[size++] = value;
	}


	T& operator[](int index)
	{
		return values[index];
	}
};

HackingBFS_Vector<int> HackingBFS_adj[10001];
int HackingBFS_hackedComputers[10001] = { 0 };
int HackingBFS_results[10001] = { 0 };
int HackingBFS()
{
	int N, M, from, to, resultSize = 0;
	cin >> N >> M;

	for (int i = M; i--;)
	{
		cin >> from >> to;
		HackingBFS_adj[to].push_back(from);
	}

	HackingBFS_Queue<int> que;
	int adjSize, now, next, max = 0, cnt = 0;
	for (int i = 1; i <= N; i++)
	{
		cnt = 1;
		bool visit[10001] = { false };
		que.push(i);
		visit[i] = true;
		while (que.size)
		{
			que.pop(now);

			adjSize = HackingBFS_adj[now].size;
			for (int i = 0; i < adjSize; i++)
			{
				next = HackingBFS_adj[now][i];
				if (visit[next]) continue;
				visit[next] = true;

				que.push(next);
				cnt++;
			}
		}
		if (max < cnt)
		{
			max = cnt;
			resultSize = 0;
			HackingBFS_results[resultSize++] = i;
		}
		else if(max == cnt)
		{ 
			HackingBFS_results[resultSize++] = i;
		}
	}

	for (int i = 0; i < resultSize; i++)
	{
		cout << HackingBFS_results[i] << ' ';
	}
	cout << '\n';
	return 0;
}