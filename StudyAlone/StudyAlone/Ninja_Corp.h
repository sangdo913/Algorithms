#pragma once
#include<iostream>
using namespace std;


template <typename T>
struct Ninja_Node
{
	typedef Ninja_Node<T> Node;
	T value;
	Node* prev;
	Node* next;
	Ninja_Node<T>()
	{
		prev = next = NULL;
	}
};

template <typename T>
struct Ninja_Queue
{
	typedef Ninja_Node<T> Node;
	typedef bool(*order)(T v1, T v2);
	T *values;
	int maxSize;
	int sz;
	order func;
	Node* head;
	Node* tail;
	Ninja_Queue<T>()
	{
		maxSize = 100;
		sz = 0;
		values = new T[maxSize + 1];
		func = [](T d1, T d2)->bool {return d1 > d2; };
	}
	Ninja_Queue<T>(int size, order func) : maxSize(size), func(func)
	{
		values = new T[maxSize+1];
		sz = 0;
	}
	~Ninja_Queue<T>()
	{
		delete[] values;
	}
	int getChild(int node);
	int getParent(int node);
	int getLeft(int node);
	int getRight(int node);

	T top();
	void pop();
	int size();

	void push(T Data);
};

template<typename T>
int Ninja_Queue<T>::getChild(int node)
{
	int l, r;
	l = getLeft(node); r = getRight(node);
	if (l > sz && r > sz)
	{
		return 0;
	}
	else if (r > sz)
	{
		return l;
	}
	else
	{
		if (func(values[l], values[r])) return l;
		else return r;
	}
}

template<typename T>
int Ninja_Queue<T>::getParent(int node)
{
	return node >> 1;
}

template<typename T>
int Ninja_Queue<T>::getLeft(int node)
{
	return node << 1;
}

template<typename T>
int Ninja_Queue<T>::getRight(int node)
{
	return (node << 1) + 1;
}

template<typename T>
int Ninja_Queue<T>::size()
{
	return sz;
}

template<typename T>
void Ninja_Queue<T>::pop()
{
	if (sz == 0) return;
	T v = values[sz--];
	int c;
	int index = 1;
	c = getChild(index);
	while (c && func(values[c], v))
	{
		values[index] = values[c];
		index = c;
		c = getChild(index);
	}
	values[index] = v;
}

template<typename T>
T Ninja_Queue<T>::top()
{
	return values[1];
}

template<typename T>
void Ninja_Queue<T>::push(T data)
{
	if (sz == maxSize)
	{
		maxSize <<= 1;
		T* newValues = new T[maxSize+1];

		for (int i = 1; i <= sz; i++)
		{
			newValues[i] = values[i];
		}

		delete[] values;
		values = newValues;
	}
	sz++;

	int index = sz;
	int p = getParent(index);
	while (p && func(data, values[p]))
	{
		values[index] = values[p];
		index = p;
		p = getParent(index);
	}

	values[index] = data;
	return;
}

long long Ninja_B[100001] = { 0 };
long long Ninja_C[100001] = { 0 };
long long Ninja_L[100001] = { 0 };
long long Ninja_sum[100001] = { 0 };
int Ninja_pointer[100001] = { 0 };
Ninja_Queue<long long> Ninja_que[100001];

inline long long Ninja_max(long long ll1, long long ll2)
{
	return ll1 > ll2 ? ll1 : ll2;
}

int Ninja_Corp()
{

	int T, N;
	long long M;
	scanf("%d", &T);
	long long result;
	long long temp;

	for (int tc = 1; tc <= T; tc++)
	{
		 result = 0;
		 scanf("%d %lld", &N, &M);

		 for (int i = 0; i <= N; i++)
		 {
			 while (Ninja_que[i].size())
			 {
				 Ninja_que[i].pop();
			 }
			 Ninja_sum[i] = 0; 
			 Ninja_pointer[i] = i;
		 }

		 for (int i = 1; i<= N;i++)
		 {
			 scanf("%lld %lld %lld", &Ninja_B[i], &Ninja_C[i], &Ninja_L[i]);
		 }

		 for (int i = N; i >0; i--)
		 {
			 int &now = Ninja_pointer[i];
			 int &p = Ninja_pointer[Ninja_B[i]];

			 Ninja_que[now].push(Ninja_C[i]);
			 Ninja_sum[now] += Ninja_C[i];

			 while (Ninja_sum[now] > M)
			 {
				 Ninja_sum[now] -= Ninja_que[now].top();
				 Ninja_que[now].pop();
			 }

			 result = Ninja_max(result, (long long)(Ninja_que[now].size()) * Ninja_L[i]);

			 //critical 큐에 있는 내용을 옮기는 대신에 부모가 가르키는 포인터를 옮긴다!
			 if (Ninja_que[now].size() > Ninja_que[p].size())
			 {
				 temp = Ninja_sum[now];
				 Ninja_sum[now] = Ninja_sum[p];
				 Ninja_sum[p] = temp;

				 temp = now;
				 now = p;
				 p = temp;
			 }

			 Ninja_sum[p] += Ninja_sum[now];

			 while (Ninja_que[now].size())
			 {
				 Ninja_que[p].push(Ninja_que[now].top());
				 Ninja_que[now].pop();
			 }
		 }

		 printf("#%d %lld\n", tc, result);
	}

	return 0;
}