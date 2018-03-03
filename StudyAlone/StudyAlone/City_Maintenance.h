#pragma once
#include<iostream>
#include<algorithm>
using namespace std;
struct City_Edge;

struct City_Edge
{
	int from;
	int to;
	long long distance;
	void set(int f, int t, long long d)
	{
		from = f;
		to = t;
		distance = d;
	}
};

struct City_QueueData
{
	int from;
	long long untilDistance;
};
struct City_Node
{
	typedef City_Edge Data;
	typedef City_Node Node;
	Node* prev;
	Node* next;
	Data value;
	City_Node();
};

City_Node::City_Node()
{
	prev = next = NULL;
	value = { 0,0 };
}
struct City_List
{
	typedef City_Node Node;
	typedef Node::Data Data;

	int size;
	Node* head;
	Node* tail;
	Node* cursor;

	void clear();
	void first();
	void del();
	Data next();

	void insert(Data value);
	City_List();
	~City_List();
};
void City_List::del()
{
	if (cursor == head) return;
	Node* dNode = cursor;
	cursor = cursor->prev;
	dNode->next->prev = dNode->prev;
	dNode->prev->next = dNode->next;
	delete dNode;
}
void City_List::clear()
{
	Node* dNode;
	cursor = head->next;
	while (cursor != tail)
	{
		dNode = cursor;
		cursor = cursor->next;
		delete dNode;
	}
	head->next = tail;
	tail->prev = head;
	cursor = head;
}

void City_List::insert(Data value)
{
	size++;
	Node* newNode = new Node();
	newNode->value = value;
	
	newNode->prev = head;
	newNode->next = head->next;

	head->next->prev = newNode;
	head->next = newNode;
}

City_List::Data City_List::next()
{
	if (cursor->next == tail) return{ 0,0 };
	cursor = cursor->next;
	return cursor->value;
}

void City_List::first()
{
	cursor = head;
}
City_List::~City_List()
{
	Node* dNode;
	while (head)
	{
		dNode = head;
		head = head->next;
		delete dNode;
	}
}
City_List::City_List()
{
	size = 0; head = new Node();
	tail = new Node;
	head->next = tail;
	tail->prev = head;
	cursor = head;
}
struct City_Heap
{
	typedef City_Edge Data;
	typedef bool(*order)(Data d1, Data d2);
	Data *datas;
	int size;
	int maxSize;
	int getParent(int node);
	int getChild(int node);
	int getLeft(int node);
	int getRight(int node);
	void insert(Data value);
	order func;
	Data pop();

	City_Heap(int size, order func);
	~City_Heap()
	{
		delete datas;
	}
};
City_Heap::Data City_Heap::pop()
{
	Data rValue = datas[1];
	int index = 1;
	int child = getChild(1);
	while (child && func(datas[child], datas[size]))
	{
		datas[index]= datas[child];
		index = child;
		child = getChild(index);
	}
	datas[index] = datas[size];
	size--;
	return rValue;
}

void City_Heap::insert(Data value)
{
	if (maxSize == size)
	{
		Data* newData = new Data[maxSize<<1+1];
		for (int i = 1; i <= maxSize; i++)
		{
			newData[i]=datas[i];
		}
		maxSize <<= 1;
		delete datas;
		datas = newData;
	}

	size++;
	int index = size,parent = getParent(index);
	while (parent && func(value, datas[parent]))
	{
		datas[index] = datas[parent];
		index = parent;
		parent = getParent(index);
	}
	datas[index] = value;
}
int City_Heap::getRight(int node)
{
	return (node << 1) + 1;
}
int City_Heap::getLeft(int node)
{
	return node << 1;
}
int City_Heap::getChild(int node)
{
	int r = getRight(node), l = getLeft(node);
	if (l > size)
	{
		return 0;
	}
	else if (r > size)
	{
		return l;
	}

	if (func(datas[l], datas[r]))
	{
		return l;
	}
	else return r;
}

int City_Heap::getParent(int node)
{
	return node >> 1;
}
City_Heap::City_Heap(int size, order func) :maxSize(size), func(func)
{
	datas = new Data[maxSize + 1];
	this->size = 0;
}

inline void City_Swap(int*arr, int left, int right)
{
	int temp;
	temp = arr[left];
	arr[left] = arr[right];
	arr[right] = temp;
}
inline void City_SetMin(int*arr, int left, int right,bool(*order)(int i1, int i2))
{
	int mid = (left + right) >> 1;
	if (order(arr[mid], arr[left]))
	{
		City_Swap(arr, left, mid);
	}
	if (order( arr[right], arr[mid]))
	{
		City_Swap(arr, mid, right);
	}

	if (order(arr[left], arr[mid]))
	{
		City_Swap(arr, left, mid);
	}

	int x = 0;
}
void City_QuickSort(int* arr, int left, int right, bool (*order)(int i1, int i2))
{
	City_SetMin(arr, left, right,order);

	int low = left + 1,high = right;
	
	while (low <= high)
	{
		while (low < right && order(arr[low],arr[left])) low++;
		while (high > left && order(arr[left],arr[high])) high--;

		if (low <= high)
		{
			City_Swap(arr, low, high); low++;
		}
	}
	City_Swap(arr, left, high);
	if (high-1 > left) City_QuickSort(arr, left, high-1,order);
	if (high+1 < right) City_QuickSort(arr, high+1, right,order);
}

int City_nodesPrevs[100001];
City_List City_lists[1000001];

long long distances[100001];
bool isConnected[100001];
int orderedIndex[100001];

bool order(int i1, int i2)
{

	return distances[i1] < distances[i2];
}
struct Order
{
	bool operator()(int i1, int i2)
	{
		return distances[i1] < distances[i2];
	}
};

long long City_GetMinCost(long long total,int N, long long C)
{
	typedef City_Edge Edge;
	typedef City_List list;
	typedef City_Heap queue;
	typedef City_Heap::Data EdgeValue;
	for (int i = 1; i <= N; i++)
	{
		distances[i] = INT64_MAX;
		isConnected[i] = false;
		orderedIndex[i] = i;
	}
	isConnected[1] = true;
	distances[1] = 0;

	Edge edge;
	queue que(10000, [](queue::Data d1, queue::Data d2)->bool {return d1.distance < d2.distance; });
	int newNode;
	
	int cnt = 1; long long newDistance;
	Edge newEdge;
	Edge e,nextEdge;
	City_lists[1].first();
	while ((edge = City_lists[1].next()).from)
	{
		que.insert(edge);
	}
/*
	while (que.size)
	{
		edge = que.pop();
		if (edge.untilDistance > distances[edge.from]) continue;

		City_lists[edge.from].first();
		while ((e = City_lists[edge.from].next()).from)
		{
			newDistance = edge.untilDistance + e.distance;
			if (distances[e.to] < newDistance) continue;
			distances[e.to] = newDistance;
			newEdge = { e.to,newDistance };
			que.insert(newEdge);
		}
	}*/
	
	while (cnt < N)
	{
		edge = que.pop();

		if (!(isConnected[edge.from] ^ isConnected[edge.to])) continue;
		newNode = isConnected[edge.from] ? edge.to : edge.from;
		isConnected[newNode] = true;

		distances[newNode] = (long long)edge.distance;

		City_lists[newNode].first();
		while ((newEdge = City_lists[newNode].next()).from)
		{
			if (isConnected[newEdge.to]) continue;
			newEdge.distance += distances[newNode];
			que.insert(newEdge);
		}
		cnt++;
	}

	//City_QuickSort(orderedIndex, 2, N,order);

	for (int i = 1; i <= N; i++)
	{
		isConnected[i] = false;
	}
	isConnected[1] = true;
	sort(orderedIndex + 2, orderedIndex + N + 1, Order());
	long long minCost = total;
	long long JiHaDoCost;
	int selectedIndex;
	long long nowCost;
	int maxCnt = 1;
	int nowCnt = 0;
	for (int i = 2; i <= N; i++)
	{
		selectedIndex = orderedIndex[i];
		JiHaDoCost = C*distances[selectedIndex];
		if (JiHaDoCost >= minCost) return minCost;

		City_lists[selectedIndex].first();

		while ((e = City_lists[selectedIndex].next()).from)
		{
			if (isConnected[e.to])
			{
				total -= e.distance;
			}
		}
		isConnected[selectedIndex] = true;
		nowCost = total + JiHaDoCost;
		minCost = minCost > nowCost ? nowCost : minCost;
	}
	return minCost;
}

int City_Maintenance()
{
	typedef City_Edge Edge;
	ios::ios_base::sync_with_stdio(false);
	int T, N, M, C;
	//scanf("%d", &T);
	cin >> T;

	int from, to, distance;
	Edge temp;
	long long total;
	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	City_QuickSort(arr, 0, 9, [](int i1, int i2)->bool {return i1 < i2; });
	for (int tc = 1; tc <= T; tc++)
	{
		//scanf("%d %d %d", &N, &M, &C);
		cin >> N >> M >> C;
		total = 0;
		
		for (int i = 1; i <= N; i++)
		{
			City_lists[i].clear();
		}

		for (int cnt = M; cnt--;)
		{
			cin >> from >> to >> distance;
			temp.set(from, to, distance);
			City_lists[from].insert(temp);

			temp.set(to, from, distance);
			City_lists[to].insert(temp);
			total += (long long)distance;
		}

		total = City_GetMinCost(total, N, C);
		
		cout << '#' << tc << ' ' << total << '\n';
	}
	return 0;
}