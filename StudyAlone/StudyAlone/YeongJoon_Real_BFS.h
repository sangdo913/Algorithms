#pragma once
#include<iostream>

using namespace std;

struct YeongJoonBFSNode;
struct YongJoonBFSStack;
struct YeongJoonList;
struct YeongJoonListNode;
struct YeongJoonStackData;
struct YeongJoonStackData
{
	int node;
	int height;
};
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
	cursor = head;
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
	cursor = head;
}
YeongJoonList::Data YeongJoonList::next()
{
	if (cursor->next == tail || cursor == tail) return -1;
	cursor = cursor->next;
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
	cursor = head;
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

struct YeongJoonBFSNode
{
	typedef YeongJoonStackData Data;
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

struct YeongJoonBFSStack
{
	typedef YeongJoonBFSNode Node;
	typedef Node::Data Data;
	Node* head;
	Node* tail;
	int size;
	void push(Data value);
	Data pop();
	bool empty();
	YeongJoonBFSStack();
	~YeongJoonBFSStack();
};

bool YeongJoonBFSStack::empty()
{
	return size == 0;
}

void YeongJoonBFSStack::push(Data value)
{
	size++;
	Node* newNode = new Node();
	newNode->value = value;

	newNode->next = head->next;
	newNode->prev = head;
	head->next->prev = newNode;
	head->next = newNode;
}

YeongJoonBFSStack::Data YeongJoonBFSStack::pop()
{
	if (size == 0) return{ -1,-1 };
	Node* rNode = head->next;

	rNode = head->next;
	head->next = rNode->next;
	rNode->next->prev = head;

	Data result = rNode->value;
	delete(rNode);
	size--;
	return result;
}


YeongJoonBFSStack::YeongJoonBFSStack()
{
	head = new Node();
	tail = new Node();
	head->next = tail;
	tail->prev = head;
	size = 0;
}

YeongJoonBFSStack::~YeongJoonBFSStack()
{
	Node* rNode;
	while (head)
	{
		rNode = head;
		head = head->next;
	}
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
	if (size == 0) return{ -1,-1 };
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
YeongJoonList YeongJoon_edges[100001];
YeongJoonList YeongJoon_height[100001];
int YeongJoon_parent[100001];
int YeongJoon_size[100001];
int YeongJoon_height_BIT[100001];

void YeongJoon_Init();

bool YeongJoon_Height_Order(int index1, int index2)
{
	return YeongJoon_size[index1] < YeongJoon_size[index2];
}

int YeongJoonBFS_Set_Height(int N)
{
	typedef YeongJoonBFSQueue queue;
	queue que;
	typedef queue::Data Data;
	Data node,next; int nextNode;
	int maxHeight = 0;
	node.height = 0; node.node = 1;
	que.push(node);
	while (que.size)
	{
		node = que.pop();
		YeongJoon_height[node.height].insert(node.node);
		maxHeight = maxHeight > node.height ? maxHeight : node.height;
		YeongJoon_edges[node.node].first();
		int index = node.height;
		while (index && index <= N)
		{
			YeongJoon_height_BIT[index] += 1;
			index += index & -index;
		}

		while ((nextNode = YeongJoon_edges[node.node].next()) != -1)
		{
			next.node = nextNode;
			next.height = node.height + 1;
			que.push(next);
		}
		YeongJoon_edges[node.node].first();
	}
	for (int i = 1; i <= maxHeight; i++)
	{
		YeongJoon_height[i].sort(YeongJoon_Height_Order);
	}
	return maxHeight;
}

int YeongJoon_Get_Num()
{
	typedef YeongJoonBFSStack stack;
	typedef YeongJoonBFSStack::Data Data;

	Data pathRecord, now,tempNode;
	int result = 0;
	now.node = 1;
	now.height = 0;
	int nowHeight= 0;
	int untilHeight= 0;
	stack path;
	int nowNode;

	while (YeongJoon_size[now.node] > 0)
	{
		untilHeight++;
		path.push(now);
		YeongJoon_edges[now.node].first();
		result--;
		while (path.size != 0)
		{
			result++;
			bool isPush = false;
			if (now.height == untilHeight)
			{

				if (YeongJoon_size[now.node] == 0 && YeongJoon_parent[now.node] != -1)
				{
					YeongJoon_edges[YeongJoon_parent[now.node]].del();
					YeongJoon_size[YeongJoon_parent[now.node]]--;
				}

				tempNode = path.pop();
				while (path.size != 0 && tempNode.height < nowHeight) tempNode = path.pop();
				if (tempNode.height >= nowHeight) now = tempNode;
				continue;
			}
			while ((nowNode = YeongJoon_edges[now.node].next()) != -1)
			{
				if (YeongJoon_size[now.node] == 1 && YeongJoon_parent[now.node] == -1)
				{
					YeongJoon_size[now.node] = 0;
					YeongJoon_parent[nowNode] = -1;
					nowHeight++;
				}
				isPush = true;
				pathRecord = now;
				path.push(pathRecord);
				now.node = nowNode;
				now.height++;
				if (isPush) break;
			}
			if (isPush) continue;

			if (YeongJoon_size[now.node] == 0)
			{
				YeongJoon_edges[YeongJoon_parent[now.node]].del();
				YeongJoon_size[YeongJoon_parent[now.node]]--;
			}
			
			YeongJoon_edges[now.node].first();

			tempNode = path.pop();
			while (path.size != 0 && tempNode.height < nowHeight) tempNode = path.pop();
			if (tempNode.height >= nowHeight) now = tempNode;
		}
	}
	return result;
}




void YeongJoon_Init(int N)
{
	for (int num = 1; num <= N; num++)
	{
		YeongJoon_edges[num].clear();
		YeongJoon_height[num].clear();
		YeongJoon_height_BIT[num] = 0;
		YeongJoon_size[num] = 0;
	}
	for (int i = 2; i <= N; i++)
	{
		cin >> YeongJoon_parent[i];
		YeongJoon_edges[YeongJoon_parent[i]].insert(i);
		YeongJoon_size[YeongJoon_parent[i]]++;
	}

	for (int i = 1; i <= N; i++)
	{
		YeongJoon_edges[i].sort([](int i1, int i2)->bool {return i1 < i2; });
	}

	YeongJoon_parent[1] = -1;
}

int YeongJoon_ChangeParent(int node,int &gap)
{
	gap = 0;

	while (YeongJoon_size[node] == 1)
	{
		YeongJoon_edges[node].first();
		node = YeongJoon_edges[node].next();
		gap++;
	}
	return node;
}
int YeongJoon_Get_BIT(int height)
{
	int ret = 0;
	while (height > 0)
	{
		ret += YeongJoon_height_BIT[height];
		height -= height & -height;
	}
	return ret;
}

void YeongJoon_BIT_Update(int height, int maxHeight, int value)
{
	while (height <= maxHeight)
	{
		YeongJoon_height_BIT[height] += value;
		height += height & -height;
	}
}
int YeongJoon_Get_Min_BFS(int maxHeight)
{
	int nowHeight = 0;
	int nowParent = 1;
	int untilHeight = 1;
	int gap;
	int ret = 0;
	int sum = 0;
	int decreaseSizeIndex;
	while (nowHeight != maxHeight)
	{
		sum = YeongJoon_Get_BIT(untilHeight);
		sum = (sum << 1);
		YeongJoon_height[untilHeight].first();
		while ((decreaseSizeIndex = YeongJoon_height[untilHeight].next()) != -1)
		{
			if (YeongJoon_size[decreaseSizeIndex] != 0) break;
			decreaseSizeIndex = YeongJoon_parent[decreaseSizeIndex];
			YeongJoon_size[decreaseSizeIndex]--;
			YeongJoon_BIT_Update(decreaseSizeIndex, maxHeight, -1);
			while (YeongJoon_size[decreaseSizeIndex] == 0)
			{
				decreaseSizeIndex = YeongJoon_parent[decreaseSizeIndex];
				if (decreaseSizeIndex == -1) break;
				YeongJoon_size[decreaseSizeIndex]--; 
				YeongJoon_BIT_Update(decreaseSizeIndex, maxHeight, -1);
			}
		}

		nowParent = YeongJoon_ChangeParent(nowParent, gap);
		untilHeight++;
		nowHeight += gap;
		sum -= gap;
		ret += sum;
	}

	return ret;
}

int YeongJoon_Real_BFS()
{
	ios::ios_base::sync_with_stdio(false);
	typedef YeongJoonList list;
	typedef YeongJoonBFSStack stack;
	int T, N,height;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		int result = 0;
		cin >> N;
		YeongJoon_Init(N);
		height = YeongJoonBFS_Set_Height(N);
		//result = YeongJoon_Get_Num();
		result = YeongJoon_Get_Min_BFS(height);
		cout << '#' << tc << ' ' << result << endl;
	}
	return 0;
}