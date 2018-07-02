#pragma once
#include<cstdio>

struct NODE
{
	int value;
	NODE *next, *prev;

	NODE()
	{
		prev = next = 0;
	}
};

static struct MYMAL
{
	int idx;
	NODE nodes[5002];

	MYMAL()
	{
		idx = 0;
	}

	NODE* malloc()
	{
		return &nodes[idx++];
	}
} mymal;

struct LIST
{
	NODE *tail, *cursor;
	LIST()
	{
		tail = 0;
	}

	void insert(int i)
	{
		NODE* nn = mymal.malloc();
		nn->value = i;

		if (tail) {
			nn->next = tail->next;
			nn->next->prev = nn;
			nn->prev = tail;

			tail->next = nn;
		}
		else {
			nn->next = nn;
			nn->prev = nn;
			tail = nn;
		}
	}

	void clear()
	{
		cursor = tail;
	}

	int next()
	{
		if (cursor == 0) return -1;
		cursor = cursor->next;
		return cursor->value;
	}

	void del()
	{
		if (cursor == tail)
		{
			if (tail->prev == tail) tail = 0;
			else {
				tail = tail->prev;
			}
		}

		cursor->next->prev = cursor->prev;
		cursor->prev->next = cursor->next;

		cursor = cursor->prev == cursor ? 0 : cursor->prev;
	}
};

int JOCEPERS()
{
	int n, m;
	scanf("%d %d\n", &n, &m);
	LIST li;
	for (int i = n; i >= 1; i--)
	{
		li.insert(i);
	}

	li.clear();
	printf("<");
	for (int i = 1; i < n; i++)
	{
		int out;
		for (int j = 0; j < m; j++) {
			out = li.next();
		}
		printf("%d, ", out);
		li.del();
	}

	printf("%d>\n", li.next());

	return 0;
}