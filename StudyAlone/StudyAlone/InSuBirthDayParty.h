#pragma once
#include<iostream>

using namespace std;
struct _InSu_Edge
{
	int from;
	int to;
	int value;
};
typedef class _InSu_Heap
{
public:
	typedef _InSu_Edge Data;
	typedef bool(*Order_Check)(Data d1, Data d2);
	int max_size;
	int size;
	Data* datas;
	_InSu_Heap(int size, Order_Check check);
	~_InSu_Heap();
	Order_Check func;
	int GetParent(int node);
	int GetChild(int node);
	int GetLeft(int node);
	int GetRight(int node);
	bool Push(Data data);
	bool Pop(Data &data);
	bool IsEmpty();
	void clear();
}InSu_Heap;
void _InSu_Heap::clear()
{
	size = 0;
}
_InSu_Heap::_InSu_Heap(int max_size, Order_Check check) : size(0), max_size(max_size), func(check)
{
	datas = new Data[max_size + 1];
}

int _InSu_Heap::GetParent(int node)
{
	return node >> 1;
}
int _InSu_Heap::GetLeft(int node)
{
	return node << 1;
}
int _InSu_Heap::GetRight(int node)
{
	return (node << 1) + 1;
}

int _InSu_Heap::GetChild(int node)
{
	int r = GetRight(node), l = GetLeft(node);
	if (l > size)
	{
		return 0;
	}
	else if (r > size)
	{
		return l;
	}
	else
	{
		if (func(datas[l], datas[r])) return l;
		else return r;
	}
}

_InSu_Heap::~_InSu_Heap()
{
	delete[] datas;
}
bool _InSu_Heap::IsEmpty()
{
	return size == 0;
}

bool _InSu_Heap::Push(Data data)
{
	if (size == max_size)
	{
		int max_ind = max_size;
		max_size = max_size<< 1;
		Data* new_datas = new Data[max_size + 1];
		Data* r_data = datas;
		for (int i = 1; i <= max_ind; i++)
		{
			new_datas[i] = datas[i];
		}
		delete[] r_data;
		datas = new_datas;
		cout << "delete\n";
		cout << "max : " << max_size << endl;
	}
	size++;

	int ind = size, p_ind = GetParent(ind);
	while (p_ind && func(data, datas[p_ind]))
	{
		datas[ind] = datas[p_ind];
		ind = p_ind;
		p_ind = GetParent(ind);
	}
	datas[ind] = data;
	return true;
}

bool _InSu_Heap::Pop(Data &data)
{
	if (IsEmpty()) return false;
	data = datas[1];
	int ind = 1, last = size--;
	int child_ind = GetChild(ind);
	while (child_ind && func(datas[child_ind], datas[last]))
	{
		datas[ind] = datas[child_ind];
		ind = child_ind;
		child_ind = GetChild(ind);
	}
	datas[ind] = datas[last];
}

struct InSu_List
{
	InSu_List* next;
	int to;
	int value;
	int size;
	void Init(int to, int value)
	{
		next = NULL;
		this->to = to;
		this->value = value;
		size = 0;
	}
	void del_nodes()
	{
		if (next != NULL) delete( next);
		next = NULL;
	}
	void Insert(InSu_List* list)
	{
		list->next = next;
		next = list;
		size++;
	}
	~InSu_List();
};

InSu_List *InSu_edges[1001];
InSu_List *InSu_dis[1001];
bool InSu_isvisit[1001][1001];
int InSu_distances[1001][1001];

bool order(_InSu_Heap::Data d1, _InSu_Heap::Data d2)
{
	return d1.value < d2.value;
}

#include<cstdio>


InSu_List::~InSu_List()
{
	if (next != NULL)delete(next);
	next = NULL;
	return;
}

int InSu_GetMin(int node,int des,int max, InSu_Heap &pq)
{
	if (InSu_distances[node][des] > 0) return InSu_distances[node][des];
	InSu_Heap::Data edge;
	int cnt = 1;
	InSu_isvisit[node][node] = true;

	InSu_List* dis, *e;
	dis = InSu_dis[node]->next;
	while (dis)
	{
		cnt++;
		int dt = dis->to,next;
		InSu_List* next_edge = InSu_edges[dt]->next;
		while (next_edge)
		{
			next = next_edge->to;
			if (!InSu_isvisit[node][next]) pq.Push({ dt,next_edge->to,next_edge->value + dis->value });
			next_edge = next_edge->next;
		}
		dis = dis->next;
	}
	e = InSu_edges[node]->next;
	while (e)
	{
		if (!InSu_isvisit[node][e->to]) pq.Push({ node,e->to,e->value });
		e = e->next;
	}

	int from, to,value;
	int path[1001];
	for (int i = 1; i <=max;i++) path[i] = -1;

	while (cnt != max)
	{
		pq.Pop(edge);
		if (InSu_isvisit[node][edge.to]) continue;
		from = edge.from; to = edge.to; value = edge.value;
		path[to] = from;
		cnt++;
		InSu_distances[node][to] = value;
		InSu_isvisit[node][to] = true;
		InSu_List * info = new InSu_List();
		info->Init(to, value);
		InSu_dis[node]->Insert(info);

		if (to == des) break;

		e = InSu_edges[to]->next;
		while (e)
		{
			if (InSu_isvisit[node][e->to])
			{
				e = e->next;
				continue;
			}
			pq.Push({ to,e->to,e->value + InSu_distances[node][to] });
			e = e->next;
		}
		
	}
	int start;
	for (int i = 1; i <= max; i++)
	{
		start = path[i];
		while (start != -1)
		{
			if (InSu_isvisit[start][i])
			{
				break;
			}
			InSu_isvisit[start][i] = true;
			InSu_distances[start][i] = InSu_distances[node][i] - InSu_distances[node][start];
			InSu_List* info = new InSu_List();
			info->Init(i, InSu_distances[start][i]);
			InSu_dis[start]->Insert(info);
			start = path[start];
		}
	}

	
	return InSu_distances[node][des];
}
int InSu_Birthday()
{
	ios::ios_base::sync_with_stdio(false);
	int max,T,M,N,x,y,c, X;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N >> M >> X;

		InSu_Heap pq(5000, order);
		for (int i = 1; i <= N; i++)
		{
			InSu_edges[i] = new InSu_List();
			InSu_edges[i]->Init(-1, -1);
			InSu_dis[i] = new InSu_List();
			InSu_dis[i]->Init(-1, -1);

			for (int j = 1; j <= N; j++)
			{
				//InSu_Edge[i][j] = -1;
				InSu_distances[i][j] = -1;
				InSu_isvisit[i][j] = false;
			}
		}

		for (int i = 0; i < M; i++)
		{
			scanf("%d %d %d", &x, &y, &c);
			InSu_List *info  = new InSu_List();
			info->Init(y, c);
			InSu_edges[x]->Insert(info);
		}
		for (int i = 1; i <= N; i++)
		{
			InSu_distances[i][i] = 0;
		}

		int max_time = -1;
		int store;
		InSu_GetMin(X, X, N,pq);
		pq.clear();
		for (int node = 1; node <= N; node++)
		{
			if (node == X) continue;
			store = InSu_GetMin(node, X, N,pq);
			pq.clear();
			max_time = max_time < store+ InSu_distances[X][node] ? store+InSu_distances[X][node] : max_time;
		}

		printf("#%d %d\n", tc, max_time);
		for (int i = 1; i <= N; i++)
		{
			delete(InSu_edges[i]);
			delete(InSu_dis[i]);
		}
	}
	return 0;
}