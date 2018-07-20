#pragma once
#include<iostream>
#include<cstdio>
using namespace std;

struct YeongSoo_Tree
{
	typedef long long Data;
	int size,max_size;
	Data* datas;
	long long * sums;
	YeongSoo_Tree **link;
	YeongSoo_Tree(int max_size);
	YeongSoo_Tree();
	void init(int max_size);
	~YeongSoo_Tree();
	void del();
	void insert(Data num,int height);
	long long getValue();
	int Search(Data value);
};
int YeongSoo_Tree::Search(Data value) 
{
	int left = 0; int right = max_size - 1; int mid = (left + right) / 2;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (datas[mid] > value)
		{
			right = mid-1;
		}
		else left = mid +1;
	}
	right = right < 0 ? 0 : right;
	return right;
}
void YeongSoo_Tree::insert(Data num, int height)
{
	int index = 0;
	if (height == 0)
	{
		if (size == max_size)
		{
			int max_index = max_size;
			max_size <<= 1;
			YeongSoo_Tree** new_Tree = new YeongSoo_Tree*[max_size];
			Data* new_data = new Data[max_size];
			long long *new_sum = new long long[max_size];
			for (int i = 0; i < max_index; i++)
			{
				new_Tree[i] = link[i];
				new_data[i] = datas[i];
				new_sum[i] = sums[i];
			}
			for (int i = max_index; i < max_size; i++)
			{
				new_Tree[i] = NULL;
				sums[i] = 0;
			}
			delete[] link;
			delete[] datas;
			delete[] sums;
			link = new_Tree;
			datas= new_data;
			sums = new_sum;
		}

		datas[size] = num;
		size++;
	}

	else
	{
		index = Search(num);
		if (!link[index]) link[index] = new YeongSoo_Tree(1);
		link[index]->insert(num, height - 1);
		sums[index]++;
	}
}
long long YeongSoo_Tree::getValue()
{
	long long result = 0;
	if (link)
	{
		for (int i = 0; i < size; i++)
		{
			if(link[i]) result += (link[i]->getValue())%1000000007;
		}
	}
	for (int i = 0; i < size; i++)
	{
		result+=((size - i)*sums[i])%1000000007;
	}
	result += size % 1000000007;
	return result % 1000000007;
}
void YeongSoo_Tree::del()
{
	delete(this);
}
YeongSoo_Tree::~YeongSoo_Tree()
{
	if(datas) delete[] datas;
	if (sums) delete[] sums;
	if (link)
	{
		for (int i = 0; i < max_size; i++) if(link[i]) delete(link[i]);
	}
}
void YeongSoo_Tree::init(int max_size)
{
	if (datas) delete[] datas;
	if (link) delete[] link;
	if (sums) delete[] sums;
	sums = new long long[max_size];
	datas = new Data[max_size];
	link = new YeongSoo_Tree*[max_size];
	this->max_size = max_size;
	for (int i = 0; i < max_size; i++)
	{
		link[i] = NULL;
		sums[i] = 0;
	}
	size = 0;
}
YeongSoo_Tree::YeongSoo_Tree()
{
	size = 0;
	max_size = 0;
	sums = NULL;
	datas = NULL; link = NULL;
}
YeongSoo_Tree::YeongSoo_Tree(int max_size) : max_size(max_size)
{
	size = 0;
	sums = new long long[max_size];
	datas = new Data[max_size ];
	link = new YeongSoo_Tree*[max_size];
	for (int i = 0; i < max_size; i++)
	{
		sums[i] = 0;
		link[i] = NULL;
	}
}

typedef struct YeongSoo_Heap
{
	typedef int Data;
	typedef bool(*Comp)(Data d1, Data d2);
	Data *datas;
	int size,max_size;
	Comp comp;
	int GetSize();
	int GetRight(int index);
	int GetLeft(int index);
	int GetChild(int index);
	int GetParent(int index);
	
	bool empty();
	bool push(Data data);
	bool pop(Data &data);
	void clear();
	YeongSoo_Heap(int max_size, Comp comp);
	YeongSoo_Heap()
	{
		size = 0;  max_size = 0; datas = NULL;
	}
	void set(int max_size, Comp comp);
	~YeongSoo_Heap();
} YeongSooHeap;
void YeongSoo_Heap:: set(int max_size, Comp comp)
{
	if (datas) delete[] datas;
	datas = NULL;
	this->max_size = max_size;
	size = 0;
	this->comp = comp;
	datas = new Data[max_size + 1];
}
bool YeongSoo_Heap::pop(Data &data)
{
	if (size == 0) return false;
	data = datas[1];
	int index = 1, child = GetChild(index);
	while (child)
	{
		if (comp(datas[child], datas[size]))
		{
			datas[index] = datas[child];
			index = child;
			child = GetChild(index);
		}
		else break;
	}

	datas[index] = datas[size--];
	return true;
}
bool YeongSoo_Heap::push(Data data)
{
	if (max_size == size)
	{
		int max_index = max_size;
		max_size <<= 1;
		Data* new_Data = new Data[max_size + 1];
		for (int i = 1; i <= max_index; i++)
		{
			new_Data[i] = datas[i];
		}
		delete[] datas;
		datas = new_Data;
	}
	int index = ++size, p = GetParent(index);
	while (p)
	{
		if (comp(data, datas[p]))
		{
			datas[index] = datas[p];
			index = p;
			p = GetParent(index);
		}
		else break;
	}
	datas[index] = data;
	return true;
}
bool YeongSoo_Heap::empty()
{
	return size == 0;
}
int YeongSoo_Heap::GetParent(int index)
{
	return index >> 1;
}

int YeongSoo_Heap::GetChild(int index)
{
	int l = GetLeft(index), r = GetRight(index);
	if (l > size) return 0;
	else if (r > size) return l;
	else
	{
		if (comp(datas[l], datas[r])) return l;
		else return r;
	}
}
int YeongSoo_Heap::GetRight(int index)
{
	return (index << 1) + 1;
}
int YeongSoo_Heap::GetLeft(int index)
{
	return index << 1;
}
int YeongSoo_Heap::GetSize()
{
	return size;
}
void YeongSoo_Heap::clear()
{
	size = 0;
}
YeongSoo_Heap::YeongSoo_Heap(int max_size, Comp comp) : max_size(max_size), size(0), comp(comp)
{
	datas = new Data[max_size+1];
}
YeongSoo_Heap::~YeongSoo_Heap()
{
	size = 0;
	delete[] datas;
	//cout << "\ndeleted" << endl;
}

YeongSoo_Heap p_queue[100000];
int YeongJoon_Get_Number()
{
	//ios::ios_base::sync_with_stdio(false);
	typedef YeongSooHeap::Data Data;
	typedef YeongSooHeap PQ;
	typedef YeongSoo_Tree Tree;
	int T,N,loop_Cnt;
	int store,prev_Store;
	long long store_Long;
	cin >> T;
	long long max_Num = 0;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N;

		long long YeongSoo_sums[100001] = { 0 };
		for (int i = 0; i < N;i++)
		{
			
			cin >> loop_Cnt;
			p_queue[i].set(loop_Cnt, [](Data d1, Data d2)->bool {return d1 > d2; });
			for (int c = 0; c< loop_Cnt; c++)
			{
				scanf("%d", &store);
				p_queue[i].push(store);
			}
		}
		int index,index_Temp;
		const long long  chd = 1000000007;
		for (int h = 0; h< N;h++)
		{
			prev_Store = -1;
			while (!p_queue[h].empty())
			{
				p_queue[h].pop(store);
				if (prev_Store != store)
				{
					max_Num = max_Num < store ? store : max_Num;
					prev_Store = index_Temp = index = store;

					store_Long = 0;
					//get
					while (index > 0)
					{
						store_Long += YeongSoo_sums[index];
						store_Long %= chd;
						index -= index&-index;
					}
					store_Long++; index = index_Temp;
					store_Long %= chd;
					//update
					while (index <= 100000)
					{
						YeongSoo_sums[index] += store_Long;
						YeongSoo_sums[index] %= chd;
						index += index & -index;
					}
				}
				else
				{
					index = index_Temp;
					//update
					while (index <= 100000)
					{
						YeongSoo_sums[index] += store_Long;
						YeongSoo_sums[index] %= chd;
						index += index & -index;
					}
				}
			}
		}

		long long result = 0;
		index = 100000;

		while (index > 0)
		{
			result += YeongSoo_sums[index];
			result %= chd;
			index -= index&-index;
		}
		cout << '#' << tc <<' ' << ++result << endl;
	}
	return 0;
}