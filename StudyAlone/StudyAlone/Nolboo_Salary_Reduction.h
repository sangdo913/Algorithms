#pragma once
#include<cstdio>

struct NolBoo_Node;
struct NolBoo_Data;
struct NolBoo_Data
{
	int num;
	int pay;
	int contribution;
	void set(int num, int contribution);
};
void NolBoo_Data::set(int n, int c)
{
	num = n; contribution = c; pay = -1;
}
struct NolBoo_Node
{
	typedef int Data;
	typedef NolBoo_Node Node;
	Data data;
	Node* next;
	Node* prev;
	NolBoo_Node();
};
NolBoo_Node::NolBoo_Node()
{
	next = prev = NULL;
	data=NULL;
}
struct NolBoo_List
{
	typedef NolBoo_Node Node;
	typedef Node::Data Data;
	typedef bool(*order)(Data d1, Data d2);
	bool empty();
	Node* head;
	Node* end;
	Node* cursor;
	Node* cursorEnd;
	NolBoo_List();
	~NolBoo_List();
	bool first();
	Node* getCursor()
	{
		return cursor;
	}
	void setCursor(Node* cursor);
	bool next(Data& data);
	void insert(Data data);
	void sort(order func);
	void partition(Node* left, Node* right,order func);
	int listCount(Node* left, Node* right);
	void delAll()
	{
		Node* rnode;
		Node* node;
		node = head->next;
		while (node != end)
		{
			rnode = node;
			node = node->next;
			delete(rnode);
		}
		head->next = end;
		end->prev = head;
	}
};
void NolBoo_List::setCursor(Node* cursor)
{
	if(cursor->prev)
		this->cursor = cursor->prev;
	else
	{
		cursor = head;
	}
}
void NolBoo_List::insert(Data data)
{
	Node* newNode = new Node();
	newNode->data = data;

	newNode->prev = head;
	newNode->next = head->next;
	newNode->next->prev = newNode;
	head->next = newNode;
}
bool NolBoo_List::next(Data& data)
{
	if (cursor->next == end)
	{
		return false;
	}
	cursor = cursor->next;
	data = cursor->data;
	return true;
}
bool NolBoo_List::first()
{
	cursor = head;
	if (empty())
	{
		return false;
	}
	return true;
}
int NolBoo_List::listCount(Node* left, Node* right)
{
	int result = 0;
	if (left == end) return -1;
	while (left != right)
	{
		result++;
		left = left->next;
	}
	return result;
}
void NolBoo_List::sort(order function)
{
	if (empty()) return;
	partition(head->next, end->prev, function);
}
void NolBoo_List::partition(Node* left, Node* right, order function)
{
	int size = listCount(left, right);
	Node* low = left; Node* high = right;
	int l = 1; int r = size;
	Data temp;
	low = left->next;
	while (l <= r)
	{
		while (l < size && function(low->data, left->data)) { l++; low = low->next; };
		while (r > 0 && function(left->data, high->data)) { r--; high = high->prev; };

		if (l <= r)
		{
			temp = low->data;
			low->data = high->data;
			high->data = temp;
			l++; low = low->next;
		}
	}
	temp = left->data;
	left->data = high->data;
	high->data = temp;
	if (r > 1) partition(left, high->prev, function);
	if (r < size) partition(high->next, right, function);
}

NolBoo_List::~NolBoo_List()
{
	Node* rnode = head;
	while (head)
	{
		rnode = head;
		head = head->next;
		delete(rnode);
	}
}
bool NolBoo_List::empty()
{
	return head->next == end;
}
NolBoo_List::NolBoo_List()
{
	head = new Node();
	end = new Node();
	head->next = end;
	end->prev = head;
}

NolBoo_List NolBoo_lists[100001];
bool NolBoo_isSelected[100001];
int NolBoo_parent[100001];
int NolBoo_order[100001];
int NolBoo_contributions[100001];
int NolBoo_pay[100001];

int NolBoo_Find(int index)
{
	if (NolBoo_parent[index] < 0) return index;
	NolBoo_parent[index] = NolBoo_Find(NolBoo_parent[index]);
}

void NolBoo_Union(int parent, int child)
{
	parent = NolBoo_Find(parent);
	child = NolBoo_Find(child);
	if (parent == child) return;
	int temp;
	if (NolBoo_parent[parent] > NolBoo_parent[child])
	{
		temp = parent;
		parent = child;
		child = parent;
	}
	NolBoo_parent[parent] += NolBoo_parent[child];
	NolBoo_parent[child] = parent;
}

bool NolBoo_SortByContribution(int index1, int index2)
{
	return NolBoo_contributions[index1] < NolBoo_contributions[index2];
}

void NolBoo_SetPay(int index1, int num)
{
	int parent = NolBoo_Find(index1);
	if (NolBoo_pay[parent] < num)
	{
		NolBoo_pay[parent] = num;
	}
}

int NolBoo_GetPay(int index)
{
	return NolBoo_pay[NolBoo_Find(index)];
}

void NolBoo_SetMid(int* lists, int left, int right, bool (*order)( int Data, int Data2))
{
	int mid = (left + right) / 2;
	int temp;
	if (order(lists[mid], lists[left]))
	{
		temp = lists[mid];
		lists[mid] = lists[left];
		lists[left] = temp;
	}
	if (order(lists[right], lists[mid]))
	{
		temp = lists[right];
		lists[right] = lists[mid];
		lists[mid] = temp;
	}
	if (order(lists[left], lists[mid]))
	{
		temp = lists[left];
		lists[left] = lists[mid];
		lists[mid] = temp;
	}
}

void NolBoo_Quicksort(int* lists,int left, int right, bool(*order)(int i1, int i2))
{
	typedef int Data;
	NolBoo_SetMid(lists, left, right, order);
	int low = left + 1;
	int high = right;

	while (low <= high)
	{
		while (high > left && order(lists[left], lists[high])) high--;
		while (low < right && order(lists[low], lists[left]) )low++;
		if (low <= high)
		{
			Data temp = lists[low];
			lists[low] = lists[high];
			lists[high] = temp;
			low++;
		}
	}

	Data temp = lists[left];
	lists[left] = lists[high];
	lists[high] = temp;
	if (high > left) NolBoo_Quicksort(lists, left, high - 1, order);
	if(high < right)NolBoo_Quicksort(lists, high + 1, right, order);
}

struct NolBoo_Stack
{
	typedef NolBoo_Node Node;
	typedef Node::Data Data;

	Node* head;
	Node* end;
	NolBoo_Stack()
	{
		head = new Node();
		end = new Node();
		head->next = end;
		end->prev = head;
	}
	~NolBoo_Stack()
	{
		Node* rnode;
		while (head)
		{
			rnode = head;
			head = head->next;
			delete(rnode);
		}
	}
	void push(Data data)
	{
		Node* newNode = new Node();
		newNode->data = data;
		newNode->next = head->next;
		head->next = newNode;
	}
	bool pop(Data &data)
	{
		if (empty()) return false;
		data = head->next->data;
		Node* rnode = head->next;
		head->next = rnode->next;
		delete(rnode);
		return true;
	}
	bool empty() 
	{
		return head->next == end;
	}
};

int NolBoo_Salary_Reduction()
{
	int T, N, M;
	int friendly1, friendly2;
	int contribution; int temp;

	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		scanf("%d", &N);
		for (int i = 1; i<=N;i++)
		{
			scanf("%d", &NolBoo_contributions[i]);
			NolBoo_pay[i] = 0;
			NolBoo_parent[i] = -1;
			NolBoo_lists[i].delAll();
			NolBoo_order[i] = i;
			NolBoo_isSelected[i] = false;
		}
		scanf("%d", &M);
		for (int i = M; i--;)
		{
			scanf("%d %d", &friendly1, &friendly2);
			if(NolBoo_contributions[friendly1] <= NolBoo_contributions[friendly2])
				NolBoo_lists[friendly1].insert(friendly2);
			if(NolBoo_contributions[friendly2] <= NolBoo_contributions[friendly1])
				NolBoo_lists[friendly2].insert(friendly1);
		}
		int index, nextIndex,storeIndex;
		for (int i = 1; i <= N; i++)
		{
			NolBoo_lists[i].sort(NolBoo_SortByContribution);
		}
		//bind same contributions
		for (int i = 1; i <= N; i++)
		{
			NolBoo_lists[i].first();
			while (NolBoo_lists[i].next(index))
			{
				if (NolBoo_contributions[index] == NolBoo_contributions[i]) NolBoo_Union(i, index);
				while (NolBoo_lists[i].next(nextIndex))
				{
					if (NolBoo_contributions[nextIndex] == NolBoo_contributions[i]) NolBoo_Union(i, nextIndex);
					if (NolBoo_contributions[index] != NolBoo_contributions[nextIndex])
					{
						NolBoo_lists[i].cursor = NolBoo_lists[i].cursor->prev;
						break;
					}
					if (NolBoo_Find(index) != NolBoo_Find(nextIndex))
					{
						NolBoo_Union(index, nextIndex);
					}
				}
			}	
		}
		NolBoo_Quicksort(NolBoo_order, 1, N, NolBoo_SortByContribution);
		int prevContribution;
		int num = 1; int nowContribution;
		for (int i = 1; i <= N; i++)
		{
			index = NolBoo_order[i];
			num = 1 > NolBoo_GetPay(index) ? 1 : NolBoo_GetPay(index);
			NolBoo_SetPay(index, num);
			nowContribution = NolBoo_contributions[index];
			NolBoo_isSelected[i] = true; 
			NolBoo_lists[index].first();
			while (NolBoo_lists[index].cursor->next != NolBoo_lists[index].end) 
			{ 
				NolBoo_lists[index].next(prevContribution);

				if (nowContribution < NolBoo_contributions[prevContribution]) num++;
				NolBoo_SetPay(prevContribution, num);

				while (NolBoo_lists[index].next(contribution))
				{
					if (NolBoo_contributions[contribution] != NolBoo_contributions[prevContribution])
					{
						num++;
						NolBoo_SetPay(contribution, num);
						nowContribution = NolBoo_contributions[contribution];
						break;
					}
					NolBoo_SetPay(contribution, num);
				}
			}

		}
		int result = 0;
		for (int i = 1; i <= N; i++)result += NolBoo_GetPay(i);
		printf("#%d %d\n", tc, result);
	}
	return 0;
}