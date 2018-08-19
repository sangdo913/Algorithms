#pragma once
#include<iostream>

using namespace std;

typedef struct ToOneEdge
{
	long long from;
	long long to;
	long long double value;
} HData;

typedef struct _MyHeap
{
	typedef bool (*HeapFunc)(HData x1, HData x2);
	int size;
	int max_size;
	HData *data;
	HeapFunc func;

	void Init(int max_size, HeapFunc func);
	int GetRight(int index);
	int GetLeft(int index);
	int GetParent(int index);
	bool deque(HData &data);
	bool enque(HData data);

	void DelHeap();
	void Clear();
} Heap;
void _MyHeap::Clear()
{
	if (data) delete[] data;
	max_size = size = 0;
	func = NULL;
	data = NULL;
}
void _MyHeap::DelHeap()
{
	delete[] data;
	data = NULL;
	max_size = 0;
	size = 0;
}

void _MyHeap::Init(int max_size, HeapFunc func)
{
	this->max_size = max_size;
	this->func = func;
	data = new HData[max_size+1];
	size = 0;
}

int _MyHeap::GetRight(int index)
{
	return index * 2 + 1;
}

int _MyHeap::GetLeft(int index)
{
	return index * 2;
}

int _MyHeap::GetParent(int index)
{
	return index / 2;
}

bool _MyHeap::deque(HData &data)
{
	if (size == 0) return false;
	HData *datas = this->data;
	data = datas[1];
	HData end = datas[size];
	size--;
	int index = 1,
		cr = GetRight(index), cl = GetLeft(index);;
	bool is_cr = false, is_cl = false;
	while ((is_cr = cr <= size) || (is_cl = cl <= size))
	{
		if (!is_cr)
		{
			if (func(datas[cl], end))
			{
				datas[index] = datas[cl];
				index = cl;
			}
			else break;
		}
		else
		{
			if ((func( datas[cr], end)) && (func(datas[cl], end)))
			{
				if (func(datas[cl], datas[cr]))
				{
					datas[index] = datas[cl];
					index = cl;
				}
				else
				{
					datas[index] = datas[cr];
					index = cr;
				}
			}
			else
			{
				if (func(datas[cl], end))
				{
					datas[index] = datas[cl];
					index = cl;
				}
				else if (func(datas[cr], end))
				{
					datas[index] = datas[cr];
					index = cr;
				}
				else
				{
					break;
				}
			}
		}

		cr = GetRight(index); cl = GetLeft(index);
	}

	datas[index] = end;
	return true;
}

bool _MyHeap::enque(HData data)
{
	if (size == max_size)
	{	
		max_size *= 2;

		HData* new_data = new HData[max_size+1];
		for (int i = 0; i <= size; i++)
		{
			new_data[i] = this->data[i];
		}
		delete[] this->data;
		this->data = new_data;
	}
	HData *datas = this->data;
	int index = ++size;
	int p = GetParent(index);

	while (p != 0 && func(data,datas[p]))
	{
		datas[index] = datas[p];
		index = p;
		p = GetParent(index);
	}

	datas[index] = data;
	return true;
}