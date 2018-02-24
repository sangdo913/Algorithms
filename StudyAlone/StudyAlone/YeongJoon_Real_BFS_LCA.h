#pragma once
#include<iostream>
#include<cstdio>
using namespace std;

struct YeongJoonBFSNode
{
	typedef int Data;
	typedef YeongJoonBFSNode Node;
	Node* next;
	Node* prev;
	Data value;
	YeongJoonBFSNode();
};


YeongJoonBFSNode::YeongJoonBFSNode()
{
	next = prev = NULL;
}


struct YeongJoonBFSQueue
{
	typedef YeongJoonBFSNode Node;
	typedef Node::Data Data;

	Node* head;
	Node* tail;
	YeongJoonBFSQueue();
	~YeongJoonBFSQueue();
	int size;
	void push(Data data);
	Data pop();
};

YeongJoonBFSQueue::Data YeongJoonBFSQueue::pop()
{
	if (size == 0) return-1;
	size--;
	Node* rNode = tail->prev;
	Data ret = rNode->value;

	tail->prev = rNode->prev;
	rNode->prev->next = tail;

	return ret;
}
void YeongJoonBFSQueue::push(Data data)
{
	Node* newNode = new Node();
	newNode->value = data;

	newNode->prev = head;
	newNode->next = head->next;

	head->next->prev = newNode;
	head->next = newNode;
	size++;
}

YeongJoonBFSQueue::YeongJoonBFSQueue()
{
	head = new Node();
	tail = new Node();
	head->next = tail;
	tail->prev = head;
	size = 0;
}

YeongJoonBFSQueue::~YeongJoonBFSQueue()
{
	Node* rNode;
	while (head)
	{
		rNode = head;
		head = head->next;
		delete(rNode);
	}
}
struct YeongJoonListNode
{
	typedef int Data;
	typedef YeongJoonListNode Node;
	Node* prev;
	Node* next;
	Data value;
	YeongJoonListNode();
};

YeongJoonListNode::YeongJoonListNode()
{
	prev = next = NULL;
	value = 0;
}

struct YeongJoonList
{
	typedef YeongJoonListNode Node;
	typedef Node::Data Data;
	typedef bool(*order)(Data d1, Data d2);
	int size;
	Node* cursor;
	Node* head;
	Node* tail;
	void first();
	Data next();
	Data prev();
	bool empty();
	void clear();
	void del();
	void insert(Data value);
	int listCount(Node* first, Node* end);
	void sort(order func);
	void partition(Node* first, Node* end, order func);
	YeongJoonList();
	~YeongJoonList();
};
void YeongJoonList::clear()
{
	Node* rNode;
	cursor = head->next;
	while (cursor != tail)
	{
		rNode = cursor;
		cursor = cursor->next;
		delete(rNode);
	}
	size = 0;
	head->next = tail;
	tail->prev = head;
	cursor = tail;
}
void YeongJoonList::sort(order func)
{
	if (size == 0) return;
	partition(head->next, tail->prev, func);
}
int YeongJoonList::listCount(Node* first, Node* end)
{
	int count = 0;
	while (first != end)
	{
		first = first->next;
		count++;
	}
	return count;
}

void YeongJoonList::partition(Node* first, Node* end, order func)
{
	Node* lowNode = first->next; Node*highNode = end;
	int right = listCount(first, end);
	int left = 0;
	int low = 1; int high = right;
	Data temp;
	while (low <= high)
	{
		while (low < right && func(lowNode->value, first->value))
		{
			low++; lowNode = lowNode->next;
		}
		while (high > 0 && func(first->value, highNode->value))
		{
			high--; highNode = highNode->prev;
		}
		if (low <= high)
		{
			temp = lowNode->value;
			lowNode->value = highNode->value;
			highNode->value = temp;
			lowNode = lowNode->next;
			low++;
		}
	}

	temp = highNode->value;
	highNode->value = first->value;
	first->value = temp;

	if (high > 0) partition(first, highNode->prev, func);
	if (high < right) partition(highNode->next, end, func);
}

void YeongJoonList::first()
{
	cursor = tail;
}
YeongJoonList::Data YeongJoonList::next()
{
	if (cursor->prev == head || cursor == head) return -1;
	cursor = cursor->prev;
	return cursor->value;
}

YeongJoonList::Data YeongJoonList::prev()
{
	if (cursor->prev == head || cursor == head) return -1;
	cursor = cursor->prev;
	return cursor->value;
}

bool YeongJoonList::empty()
{
	return size == 0;
}

void YeongJoonList::del()
{
	if (size == 0) return;
	Node* rNode = cursor;
	cursor->prev->next = cursor->next;
	cursor->next->prev = rNode->prev;
	cursor = cursor->prev;
	delete(rNode);
	size--;
}

void YeongJoonList::insert(Data value)
{
	size++;
	Node* newNode = new Node();
	newNode->value = value;

	newNode->next = head->next;
	newNode->prev = head;

	newNode->next->prev = newNode;
	head->next = newNode;
}
YeongJoonList::YeongJoonList()
{
	head = new Node();
	tail = new Node();
	cursor = tail;
	head->next = tail;
	tail->prev = head;
}

YeongJoonList:: ~YeongJoonList()
{
	Node* rNode;
	while (head)
	{
		rNode = head;
		head = head->next;
	}
}

YeongJoonList YeongJoon_edges[100001];
int YeongJoon_depth[100001];
int YeongJoon_ancestors[100001][18];
inline int YeongJoon_Get_Log(int num)
{
	int cmp = 1;
	int ret = 0;
	while (num >= cmp)
	{
		cmp <<= 1;
		ret++;
	}
	return ret;
}

int YeongJoon_Get_LCA(int node1,int node2 , int maxHeight)
{
	int temp, parentMemory, lca;
	if (YeongJoon_depth[node1] < YeongJoon_depth[node2])
	{
		temp = node1;
		node1 = node2;
		node2 = temp;
	}

	//for (int i = maxHeight; i>= 0; i--)
	//{
	//	if (YeongJoon_depth[YeongJoon_ancestors[node1][i]] >= YeongJoon_depth[node2])
	//	{
	//		node1 = YeongJoon_ancestors[node1][i];
	//	}
	//}

	int diff = YeongJoon_depth[node1] - YeongJoon_depth[node2];
	for (int i = 0; diff != 0; i++)
	{
		node1 = diff % 2 == 1 ? YeongJoon_ancestors[node1][i] : node1;
		diff >>=1;
	}

	lca = node1;
	if (node1 != node2)
	{
		for (int i = maxHeight; i >= 0; i--)
		{
			if (YeongJoon_ancestors[node2][i] != YeongJoon_ancestors[node1][i])
			{
				node1 = YeongJoon_ancestors[node1][i];
				node2 = YeongJoon_ancestors[node2][i];
			}
		}
		lca = YeongJoon_ancestors[node1][0];
	}
	return lca;
}
//
//void YeongJoon_Make_LCA_Tree(int parent, int child,int maxHeight)
//{
//	int parentMemory,nextChild;
//	YeongJoon_depth[child] = YeongJoon_depth[parent] + 1;
//
//	YeongJoon_ancestors[child][0] = parent;
//
//	for (int i = 1; i <= maxHeight; i++)
//	{
//		parentMemory = YeongJoon_ancestors[child][i - 1];
//		YeongJoon_ancestors[child][i] = YeongJoon_ancestors[parentMemory][i - 1];
//	}
//
//	YeongJoon_edges[child].first();
//	while ((nextChild = YeongJoon_edges[child].next()) != -1)
//	{
//		YeongJoon_Make_LCA_Tree(child, nextChild, maxHeight);
//	}
//}

int YeongJoon_Init(int N)
{
	int maxHeight = YeongJoon_Get_Log(N);
	int input;

	for (int i = 0; i <= N; i++)
	{
		YeongJoon_edges[i].clear();
		YeongJoon_depth[i] = 0;
		for (int i2 = 1; i2 <= maxHeight;i2++)
			YeongJoon_ancestors[i][i2] = 0;
	}


	YeongJoon_depth[0] = -1;
	for (int i = 2; i <= N; i++)
	{
		scanf("%d", &input);
		YeongJoon_edges[input].insert(i);

		YeongJoon_depth[i] = YeongJoon_depth[input] + 1;
		YeongJoon_ancestors[i][0] = input;
	}
	int memoryAc;
	for (int node = 2; node <= N;node++)
	{
		for (int acOrder = 1; acOrder <= maxHeight;acOrder++)
		{
			memoryAc = YeongJoon_ancestors[node][acOrder-1];
			YeongJoon_ancestors[node][acOrder] = YeongJoon_ancestors[memoryAc][acOrder - 1];
		}
	}

	return maxHeight;
}

long long YeongJoon_Get_Number_Of_BFS(int N, int maxHeight)
{
	typedef YeongJoonBFSQueue queue;
	queue que;
	int BFS_Order[100001];
	int cursor = 0, r = 1;
	long long ret = 0;
	int node, nextNode, lca;
	que.push(1);
	BFS_Order[0] = 1;
	while (r<N)
	{
		node = BFS_Order[cursor++];


		YeongJoon_edges[node].first();

		nextNode = YeongJoon_edges[node].next();
		while (nextNode != -1)
		{
			BFS_Order[r++] = (nextNode);
			nextNode = YeongJoon_edges[node].next();
		}
	}

	for (int cursor = 0; cursor < N-1; cursor++)
	{
		node = BFS_Order[cursor];
		nextNode = BFS_Order[cursor + 1];
		lca = YeongJoon_Get_LCA(node, nextNode, maxHeight);

		ret += (long long)(YeongJoon_depth[node] + YeongJoon_depth[nextNode]- (YeongJoon_depth[lca] << 1));
	}
	return ret;
}

int YeongJoon_Real_BFS_LCA()
{
	setbuf(stdout, NULL);
	int T, N,maxHeight;
	long long result;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		scanf("%d", &N);
		result = 0;
		maxHeight = YeongJoon_Init(N);
		result = YeongJoon_Get_Number_Of_BFS(N, maxHeight);
		printf("#%d %lld\n", tc, result);
	}

	return 0;
}