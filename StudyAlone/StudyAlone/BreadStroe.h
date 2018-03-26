#pragma once
#include<iostream>

using namespace std;

template<typename T>
struct BreadStore_Vector
{
	T *values;
	int maxSize;
	int size;
	void resize(int size)
	{
		maxSize = size;
		this->size = 0;
		delete[] values;
		values = new T[maxSize];
	}

	void clear()
	{
		delete[] values;
	}
	BreadStore_Vector<T>()
	{
		size = 0;
		maxSize = 100;
		values = new T[maxSize];
	}

	~BreadStore_Vector<T>()
	{
		delete[] values;
	}
	void push(const T& value)
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
struct BreadStore_Cod
{
	int x;
	int y;
};
template <typename T>
struct Bread_Node
{
	T value;
	typedef Bread_Node<T> Node;
	Node* prev;
	Node* next;

	Bread_Node<T>()
	{
		prev = next = NULL;
	}
};

template <typename T>
struct Bread_Queue
{
	typedef Bread_Node<T> Node;
	
	int size;
	Node* tail;
	Node* head;
	Bread_Queue<T>()
	{
		tail = new Node();
		head = new Node();
		tail->prev = head;
		head->next = tail;
		size = 0;
	}
	~Bread_Queue<T>()
	{
		Node* dNode;
		while (head)
		{
			dNode = head;
			head = head->next;
			delete dNode;
		}
	}
	void push(const T& value)
	{
		Node* newNode = new Node();
		newNode->value = value;
		newNode->next = head->next;
		newNode->prev = head;
		head->next->prev = newNode;
		head->next = newNode;
		size++;
	}
	T pop()
	{
		if (size) size--;
		Node* dNode = tail->prev;
		T res = dNode->value;

		tail->prev = dNode->prev;
		tail->prev->next = tail;
		if (dNode != head) delete dNode;
		return res;
	}
};
char BreadStore_map[10002][500];
bool BreadStore_MakePipe(int x,int y, const int &R, const int &C)
{
	int dy[3] = { -1,0,1 };
	int nextX;
	int nextY;
//	lowestR = lowestR < y ? y : lowestR;
	bool res = false;

	if (x == C - 1) return true;

	for (int d = 0; d < 3; d++)
	{
		nextX = x + 1;
		nextY = y + dy[d];
		if (BreadStore_map[nextY][nextX]!='.') continue;
		BreadStore_map[nextY][nextX] = 'y';
		res = BreadStore_MakePipe(nextX, nextY, R, C);
		if (res) return true;

		//BreadStore_map[nextY][nextX] = '.';
	}

	return res;
}

bool BreadStore_visit[10002][500] = { false };

BreadStore_Cod Bread_prev[10002][500];
int BreadStore()
{
	int R, C;
	cin >> R >> C;
	typedef BreadStore_Cod cod;
	int BreadStore_maxPipe = 0;
	for (int r = 1; r <= R; r++)
	{
		for (int c = 0; c < C; c++)
		{
			cin >> BreadStore_map[r][c];
		}
	}
	for (int c = 0; c < C; c++)
	{
		BreadStore_map[0][c] = 'x';
		BreadStore_map[R + 1][c] = 'x';
	}
	cod temp,next;
	int nextX, nextY;
	for (int r = 1; r <= R; r++)
	{
		BreadStore_maxPipe+= BreadStore_MakePipe(0, r, R, C);
	}
	/*
	while (true)
	{
		cod des;
		Bread_Queue<cod> que;
		for (int r = 1; r <= R; r++)
		{
			if (BreadStore_map[r][0] != '.') continue;
			temp.x = 0;
			temp.y = r;
			que.push(temp);

			for (int c = 0; c < C;c++) BreadStore_visit[r][c] = false;
		}

		des.x = -1; des.y = -1;
		while (que.size)
		{
			temp = que.pop();
			if (temp.x == C - 1)
			{
				BreadStore_maxPipe++;
				des = temp;
				break;
			}

			for (int d = 0; d < 3; d++)
			{
				nextX = temp.x + 1; nextY = temp.y + dy[d];
				if (BreadStore_map[nextY][nextX] == '.')
				{
					if (BreadStore_visit[nextY][nextX]) continue;
					BreadStore_visit[nextY][nextX] = true;
					next.x = nextX; next.y = nextY;
					Bread_prev[next.y][next.x] = temp;
					que.push(next);
					break;
				}
			}
		}

		if (des.x == -1) break;

		cod prev = Bread_prev[des.y][des.x];
		BreadStore_map[des.y][des.x] = 'y';
		while (prev.x != 0)
		{
			BreadStore_map[prev.y][prev.x] = 'y';
			prev = Bread_prev[prev.y][prev.x];
		}
		BreadStore_map[prev.y][prev.x] = 'y';
	}
	*/

	cout << BreadStore_maxPipe << endl;
	return 0;
}