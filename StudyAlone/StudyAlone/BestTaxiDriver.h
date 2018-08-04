#pragma once
#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct Taxi_Node
{
	typedef int Data;
	typedef Taxi_Node Node;
	Node* next;
	Node* prev;
	Data value;
	Taxi_Node()
	{
		next = prev = NULL;
		value = 0;
	}
};

struct Taxi_Path
{
	int path[150];
	int size;
	void push(int num);
	Taxi_Path();
};

Taxi_Path::Taxi_Path()
{
	size = 0;
}
void Taxi_Path::push(int num)
{
	path[size] = num;
	size++;
}

struct Taxi_List
{
	typedef Taxi_Node::Data Data;
	typedef Taxi_Node Node;

	Node* head;
	Node* tail;
	Node* cursor;

	void insert(Data data);
	void clear();

	void first();
	bool next(Data &data);

	Taxi_List();
	~Taxi_List();
};

void Taxi_List::insert(Data data)
{
	Node* newNode = new Node();
	newNode->value = data;
	newNode->prev = tail->prev;
	newNode->next = tail;

	tail->prev->next = newNode;
	tail->prev = newNode;
}

void Taxi_List::clear()
{
	Node* dNode;
	cursor = head->next;
	while (cursor != tail && cursor->next != tail)
	{
		dNode = cursor;
		cursor = cursor->next;
		delete(dNode);
	}
	head->next = tail;
	tail->prev = head;
	cursor = head;
}

bool Taxi_List::next(Data &data)
{
	if (cursor->next == tail) return false;
	cursor = cursor->next;
	data = cursor->value;
	return true;
}

void Taxi_List::first()
{
	cursor = head;
}
Taxi_List::~Taxi_List()
{
	Node* dNode;
	while (head)
	{
		dNode = head;
		head = head->next;
		delete(dNode);
	}
}
Taxi_List::Taxi_List()
{
	head = new Node();
	tail = new Node();
	cursor = head;
	head->next = tail;
	tail->prev = head;
}

struct Taxi_HeapData
{
	double time;
	double speed;
	int node;
	int *path;
	int size;
	void push(int num)
	{
		path[size++] = num;
	}
	Taxi_HeapData(Taxi_HeapData& data)
	{
		time = data.time;
		speed = data.speed;
		node = data.node;
		size = data.size;
		path = new int[150];
		for (int i = 0; i < size; i++) path[i] = data.path[i];
	}

	Taxi_HeapData(Taxi_HeapData&& data)
	{
		time = data.time;
		speed = data.speed;
		node = data.node;
		size = data.size;
		path = data.path;
		if (path == NULL) new int[150];
		data.path = NULL;
	}
	Taxi_HeapData(double time, int speed, int node) : time(time), speed(speed), node(node)
	{
		path = new int[150];
		size = 0;
	}
	Taxi_HeapData()
	{
		path = new int[150];
		size = 0;
	}
	~Taxi_HeapData()
	{
		if (path) delete(path);
	}
	Taxi_HeapData& operator=(Taxi_HeapData& data)
	{

		time = data.time;
		speed = data.speed;
		node = data.node;
		size = data.size;

		if (path == NULL) new int[150];

		for (int i = 0; i < size; i++) path[i] = data.path[i];
		return *this;
	}

	Taxi_HeapData& operator=(Taxi_HeapData&& data)
	{
		Taxi_HeapData res;
		res.time = data.time;
		res.speed = data.speed;
		res.node = data.node;
		res.path = data.path;
		data.path = NULL;

		res.size = data.size;
		if (res.path == NULL) res.path = new int[150];
		return res;
	}
};

struct Taxi_QueueNode
{
	typedef Taxi_QueueNode Node;
	typedef Taxi_HeapData Data;
	Node* prev;
	Node* next;
	Data value;
	Taxi_QueueNode()
	{
		prev = next = NULL;
		value = { 0,0,0 };
	}
};
struct Taxi_Queue
{
	typedef Taxi_QueueNode Node;
	typedef Node::Data Data;
	int size;
	Node* tail; Node* head;
	~Taxi_Queue()
	{
		Node* dNode;
		while (head)
		{
			dNode = head;
			head = head->next;
			delete dNode;
		}
	}

	Taxi_Queue()
	{
		size = 0;
		tail = new Node();
		head = new Node();
		tail->prev = head;
		head->next = tail;
	}
	
	Data&& pop()
	{
		if (size==0) return{ 0,0,0 };
		Node* dNode = tail->prev;
		Data res;
		res = (dNode->value);
		dNode->prev->next = tail;
		tail->prev = dNode->prev;
		size--;
		delete dNode;
		return (Data&&)res;
	}

	void push(Data data)
	{
		size++;
		Node* newNode = new Node();
		newNode->value = data;
		newNode->next = head->next;
		newNode->prev = head;
		head->next->prev = newNode;
		head->next = newNode;
	}
};

struct Taxi_Heap
{
	typedef Taxi_HeapData Data;
	Data *datas;
	int size;
	int maxSize;
	int getChild(int node);
	int getLeft(int node);
	int getRight(int node);
	int getParent(int node);

	void push(Data data);
	bool pop(Data& data);

	Taxi_Heap(int maxSize);
	~Taxi_Heap();
};
int Taxi_Heap::getChild(int node)
{
	int r= getRight(node), l = getLeft(node);
	if (l > size)
	{
		return 0;
	}
	else if (r > size)
	{
		return l;
	}

	if (datas[l].time < datas[r].time)
	{
		return l;
	}
	else return r;
}
int Taxi_Heap::getLeft(int node)
{
	return node << 1;
}
int Taxi_Heap::getRight(int node)
{
	return (node << 1) + 1;
}
int Taxi_Heap::getParent(int node)
{
	return node >> 1;
}

void Taxi_Heap::push(Data data)
{
	if (size == maxSize)
	{
		maxSize <<= 1;
		Data* newData = new Data[maxSize + 1];
		for (int i = 1; i <= size; i++)
		{
			newData[i] = datas[i];
		}

		delete[] datas;
		datas = newData;
	}
	size++;
	int ind = size,parent = getParent(ind);
	while (parent && data.time < datas[parent].time)
	{
		datas[ind] = datas[parent];
		ind = parent;
		parent = getParent(ind);
	}
	datas[ind] = data;
}

bool Taxi_Heap::pop(Data& data)
{
	if (size == 0) return false;
	data = datas[1];
	Data store;
	store = datas[size];
	size--;
	int ind = 1, child = getChild(ind);
	while (child && store.time > datas[child].time)
	{
		datas[ind] = datas[child];
		ind = child;
		child = getChild(ind);
	}
	datas[ind] = store;
	return true;
}

Taxi_Heap::Taxi_Heap(int maxSize) : maxSize(maxSize)
{
	datas = new Data[maxSize+1];
	size = 0;
}

Taxi_Heap::~Taxi_Heap()
{
	delete [] datas;
}
struct Taxi_Edge
{
	double length;
	double speedLimit;
	Taxi_Edge()
	{
		length = 10000000000;
		speedLimit = 0.001f;
	}
};

Taxi_Edge Taxi_edges[150][150];
int Taxi_path[150];
int Taxi_resultSize;
double Taxi_time[150];
Taxi_List Taxi_adj[150];

void Taxi_GetMininuPathBFS(int N, int D)
{
	for (int i = 0; i < N; i++)
	{
		Taxi_time[i] = 100000000;
	}

	typedef Taxi_Heap queue;
	typedef Taxi_Heap::Data Data;
	typedef Taxi_List::Data adjNode;
	queue que(1000);
	Data nextNode, node;
	adjNode next;
	Taxi_Path path;

	double maxSpeed[150][150] = { 0 };


	nextNode.node = 0;
	nextNode.time = 0;
	nextNode.speed = 70;

	que.push(nextNode);
	int now;
	bool faster = false;
	bool moreSpeed = false;

	while (que.size)
	{
		que.pop(node);
		now = node.node;
		Taxi_adj[now].first();
		faster = node.time < Taxi_time[node.node];
		node.push(now);
		if (faster)
		{
			Taxi_time[node.node] = node.time;
			if (node.node == D)
			{
				for (int i = 0; i < node.size;i++) Taxi_path[i] = node.path[i];
				Taxi_resultSize = node.size;
				return;
			}
		}

		while (Taxi_adj[now].next(next))
		{
			nextNode.node = next;
			nextNode.speed = Taxi_edges[now][next].speedLimit == 0 ? node.speed : Taxi_edges[now][next].speedLimit;
			nextNode.time = node.time + Taxi_edges[now][next].length / nextNode.speed;
			for (int i = 0; i < node.size; i++)
			{
				nextNode.path[i] = node.path[i];
			}
			nextNode.size = node.size;

			if (Taxi_edges[now][next].speedLimit == 0)
			{
				if (maxSpeed[now][next] < nextNode.speed)
				{
					maxSpeed[now][next] = nextNode.speed;
					que.push(nextNode);
				}
			}
			else if (faster)	que.push(nextNode);
		}
	}

}
int BestTaxiDriver()
{
	ios::ios_base::sync_with_stdio(false);
	int T, N, M, D,from,to,limit,length;
	cin >> T;

	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N >> M >> D;
		for (int i = 0; i < N; i++)
		{
			Taxi_adj[i].clear();
		}

		for (int cnt = M; M--;)
		{
			cin >> from >> to >> limit >> length;
			Taxi_edges[from][to].speedLimit = limit;
			Taxi_edges[from][to].length = length;
			Taxi_adj[from].insert(to);			
		}

		Taxi_GetMininuPathBFS(N,D);
		cout << '#' << tc << ' ';
		int now = D;
		for (int i = 0; i < Taxi_resultSize; i++)
		{
			cout   << Taxi_path[i] << ' ';
		}
		cout << '\n';
		int stop = 0;
	}
	return 0;
}