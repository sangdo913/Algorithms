#pragma once
#include<iostream>
template<typename T>
struct Hacking_StackNode
{
	typedef Hacking_StackNode Node;
	Node* prev;
	Node* next;
	T value;
	Hacking_StackNode()
	{
		prev = next = NULL;
	}
};

template<typename T>
struct Hacking_Queue
{
	typedef Hacking_StackNode<T> Node;
	Node* head;
	Node* tail;
	int size;
	Hacking_Queue<T>()
	{
		head = new Node();
		tail = new Node();
		head->next = tail;
		tail->prev = head;
		size = 0;

	}
	void push(const T& value)
	{
		size++;
		Node* newNode = new Node();
		newNode->value = value;
		newNode->prev = head;
		newNode->next = head->next;

		newNode->next->prev = newNode;
		head->next = newNode;
	}

	~Hacking_Queue<T>()
	{
		Node* rNode;
		while (head)
		{
			rNode = head;
			head = head->next;
			delete rNode;
		}
	}

	T pop()
	{
		if (size == 0) return head->value;
		size--;
		T res = tail->prev->value;
		Node* dNode = tail->prev;
		tail->prev = dNode->prev;
		dNode->prev->next = tail;
		return res;
	}
};

template<typename T>
struct Hacking_Stack
{
	typedef Hacking_StackNode<T> Node;
	Node* head;
	Node* tail;
	Hacking_Stack<T>()
	{
		head = new Node();
		tail = new Node();
		head->next = tail;
		tail->prev = head;
	}
	void push(const T& value)
	{
		Node* newNode = new Node();
		newNode->value = value;
		newNode->next = head->next;
		newNode->prev = head;

		head->next->prev = newNode;
		head->next = newNode;
	}
	T pop()
	{
		Node* dNode = head->next;
		T res = dNode->value;
		dNode->next->prev = head;
		head->next = dNode->next;
		delete dNode;
		return res;
	}
	void clear()
	{
		Node* rNode;
		Node* cursor = head->next;
		while (cursor != tail)
		{
			rNode = cursor;
			delete(rNode);
		}
	}
};

template <typename T>
struct Hacking_Vector
{
	T * values;
	int size;
	int maxSize;
	T& operator [](int ind)
	{
		return values[ind];
	}
	Hacking_Vector<T>()
	{
		size = 0;
		maxSize = 100;
		values = new T[maxSize];
	}
	void push_back(const T& data)
	{
		if(size == maxSize)
		{
			maxSize <<= 1;
			T* newValue = new T[maxSize];
			for (int i = 0; i < size; i++)
			{
				newValue[i] = values[i];
			}

			delete[] values;
			values = newValue;
		}

		values[size++] = data;
	}

	Hacking_Vector<T>& operator=(const Hacking_Vector<T> &vec)
	{
		maxSize = vec.maxSize;
		size = vec.size;
		T* newValues = new T[maxSize];
		for (int i = 0; i < size; i++)
		{
			newValues[i] = vec.values[i];
		}

		if (values) delete[] values;
		values = newValues;
		return *this;
	}

	void clear()
	{
		delete[] values;
		size = 0;
		maxSize = 100;
		values = new T[maxSize];
	}

	~Hacking_Vector<T>()
	{
		delete[] values;
	}

	void resize(int n)
	{
		if (values) delete[] values;
		size = n;
		maxSize = n;
		values = new T[maxSize];
	}
};

using namespace std;

Hacking_Vector<Hacking_Vector<int> > Hacking_SCC;
Hacking_Vector<int> Hacking_adj[10001];
Hacking_Stack<int> Hacking_stack;
bool Hacking_SSCFinished[10001] = { false };
int Hacking_dist[10001] = { -1 };
int Hacking_outDegree[100001] = { 0 };
int Hacking_SCCind[10001]; 
int Hacking_hack[10001];
Hacking_Vector<int> Hacking_SCCAdj[10001];
int Hacking_MakeSSC(int nowNum, int dist)
{
	Hacking_stack.push(nowNum);
	int minimumDist = dist;
	Hacking_dist[nowNum] = dist;
	int next;
	int temp;
	for (int i = 0; i < Hacking_adj[nowNum].size; i++)
	{
		next = Hacking_adj[nowNum][i];
		if (Hacking_dist[next] == -1)
		{
			temp = Hacking_MakeSSC(next, dist + 1);
			minimumDist = minimumDist > temp ? temp : minimumDist;
		}

		else if (!Hacking_SSCFinished[next])minimumDist = minimumDist > Hacking_dist[next] ? Hacking_dist[next] : minimumDist;
	}
	if (minimumDist == Hacking_dist[nowNum])
	{
		int SSCNode;
		Hacking_Vector<int> SSC;
		while (true)
		{
			SSCNode = Hacking_stack.pop();
			SSC.push_back(SSCNode);
			Hacking_SSCFinished[SSCNode] = true;
			
			Hacking_SCCind[SSCNode] = Hacking_SCC.size;
			if (SSCNode == nowNum) break;
		}
		Hacking_SCC.push_back(SSC);
	}

	return minimumDist;
}

int Hacking()
{
	int M, N;
	cin >> N >> M;
	int from, to, size;

	Hacking_stack.clear();
	Hacking_SCC.clear();
	for (int i = 1; i <= N; i++)
	{
		Hacking_adj[i].clear();
		Hacking_dist[i] = -1;
	}
	for (int i = M; i--;)
	{
		cin >> from >> to;
		Hacking_adj[from].push_back(to);
	}

	for (int i = 1; i <= N; i++)
	{
		if (Hacking_dist[i] == -1)
			Hacking_MakeSSC(i, 0);
	}
	size = Hacking_SCC.size;
	int SSCSize;
	int node;
	int adjSize;
	int next;
	for (int i = 0; i < size; i++)
	{
		SSCSize = Hacking_SCC[i].size;
		bool visit[10001] = { false };

		for (int SSCI = 0;  SSCI< SSCSize; SSCI++)
		{
			node = Hacking_SCC[i][SSCI];
			adjSize = Hacking_adj[node].size;
			for (int adjI = 0; adjI < adjSize; adjI++)
			{
				next = Hacking_SCCind[Hacking_adj[node][adjI]];
				if (visit[next]) continue;
				if (next == i) continue;
				visit[next] = true;
				Hacking_SCCAdj[i].push_back(next);
				Hacking_outDegree[next]++;
			}
		}
	}
	Hacking_Queue<int> que;
	for (int i = 0; i < size; i++)
	{
		Hacking_hack[i] = Hacking_SCC[i].size;
		if (Hacking_outDegree[i] == 0)
			que.push(i);
	}
	int max =0 ;
	int now;
	int nextSize;
	while (que.size)
	{
		now = que.pop();
		max = max < Hacking_hack[now] ? Hacking_hack[now] : max;
		nextSize = Hacking_SCCAdj[now].size;
		for (int i = 0; i < nextSize; i++)
		{
			next = Hacking_SCCAdj[now][i];
			Hacking_hack[next] += Hacking_hack[now];

			max = max < Hacking_hack[next] ? Hacking_hack[next] : max;

			Hacking_outDegree[next]--;
			if (Hacking_outDegree[next] == 0) que.push(next);
		}
	}
	for (int i = 1; i <= N; i++)
	{
		if (Hacking_hack[Hacking_SCCind[i]] == max)
		{
			cout << i << ' ';
		}
	}
	cout << '\n';
	return 0;
}