#pragma once
#include<iostream>
#include<queue>
template <typename T>
struct Queue_Node
{
	typedef Queue_Node Node;
	T values;
	Node* next;
	Node* prev;

	Queue_Node<T>()
	{
		next = prev = NULL;
	}
};

template <typename T>
struct Bridge_Queue
{
	typedef Queue_Node<T> Node;
	Node* head;
	Node* tail;

	int size;
	T front()
	{
		return tail->prev->values;
	}
	bool empty()
	{
		return size == 0;
	}
	void pop()
	{
		if (size == 0) return;
		size--;
		Node* dNode;
		dNode = tail->prev;
		tail->prev = dNode->prev;
		dNode->prev->next = tail;
		delete dNode;
	}
	void push(T value)
	{
		Node* newNode = new Node();
		newNode->prev = head;
		newNode->next = head->next;
		newNode->values = value;
		head->next->prev = newNode;
		head->next = newNode;
		size++;
	}
	Bridge_Queue<T>()
	{
		head = new Node();
		tail = new Node();
		head->next = tail;
		tail->prev = head;

		size = 0;
	}

	~Bridge_Queue<T>()
	{
		Node* dNode;
		while (head)
		{
			dNode = head;
			head = head->next;
			delete dNode;
		}
	}
};

using namespace std;
struct Bridge_Cod
{
	int x;
	int y;
	int size;
	int iNum;
};
int Bridge_map[102][102];
bool Bridge_visit[102][102] = { false };
int Bridge_iNum = 2;
Bridge_Cod Bridge_memoi[102][102];

void Bridge_MakeIslandNum(int n, Bridge_Cod pos)
{

	typedef Bridge_Cod cod;
	typedef Bridge_Queue<Bridge_Cod> queue;
	queue que;
	que.push(pos);
	int dx[4] = { 0,1,0,-1 };
	int dy[4] = { -1,0,1,0 };

	cod next, now;
	int &iNum = Bridge_iNum;
	while (!que.empty())
	{
		now = que.front();
		que.pop();

		if (Bridge_map[now.y][now.x] != 1) continue;
		Bridge_map[now.y][now.x] = iNum;
		for (int d = 0; d < 4; d++)
		{
			next.x = now.x + dx[d];
			next.y = now.y + dy[d];
			
			if (Bridge_map[next.y][next.x] == -1) continue;
			que.push(next);
		}

	}

	iNum++;
	return;
}

int Bridge_FindMinLength(int n)
{
	typedef Bridge_Cod cod;
	typedef Bridge_Queue<Bridge_Cod> queue;
	queue que;
	cod c;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			if (Bridge_map[i][j] != 0)
			{
				c.x = j; c.y = i; c.size = 0; c.iNum = Bridge_map[i][j];
				que.push(c);
			}
		}
	int res = n*n;

	int dx[4] = { 0,1,0,-1 };
	int dy[4] = { -1,0,1,0 };
	Bridge_Cod next;
	bool find = false;

	while (!que.empty())
	{
		c = que.front();
		que.pop();

		if (Bridge_visit[c.y][c.x] && Bridge_memoi[c.y][c.x].iNum != c.iNum)
		{
			res = res > Bridge_memoi[c.y][c.x].size + c.size - 1 ? Bridge_memoi[c.y][c.x].size + c.size - 1 : res;
		}

		if (Bridge_visit[c.y][c.x]) continue;

		Bridge_visit[c.y][c.x] = true;
		Bridge_memoi[c.y][c.x] = c;

		for (int d = 0; d < 4; d++)
		{
			next.x = c.x + dx[d]; next.y = c.y + dy[d];
			next.size = c.size + 1;
			next.iNum = c.iNum;

			if (Bridge_map[next.y][next.x] == -1) continue;
			if (Bridge_memoi[next.y][next.x].iNum == c.iNum) continue;
			if (find) continue;

			que.push(next);
		}
	}
	return res;
}

int MakeBridge()
{
	int N;
	for (int i = 0; i < 102; i++)
	{
		for (int j = 0; j < 102;j++)
			Bridge_map[i][j] = -1;
	}

	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++) cin >> Bridge_map[i][j];
	}


	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (Bridge_map[i][j] == 1)
			{
				Bridge_MakeIslandNum(N, { j,i });
			}
		}
	}

	int res = Bridge_FindMinLength(N);
	cout << res << '\n';


	return 0;
}