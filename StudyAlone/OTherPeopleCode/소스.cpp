#include <string>
#include<cstdio>

struct NODE {
	NODE* next, *prev;
	char value[4];
	NODE() {
		next = prev = NULL;
		value[0] = value[1] = value[2] = value[3] = 9;
	}
} nodes[10000];

struct MYAL {
	int i;
	MYAL() {
		i = 0;
	}
	void clear() {
		i = 0;
	}

	NODE* alloc() {
		if (i >= 10000) return NULL;

		return &nodes[i++];
	}
}myal;

struct List {
	int size;

	NODE *head, *tail, *cursor;
	List() {
		head = myal.alloc();
		tail = myal.alloc();
		head->next = tail;
		tail->prev = head;
	}

	void insert(const char num[4]) {
		NODE* nn = myal.alloc();
		memcpy(nn->value, num, sizeof(char) * 4);

		nn->prev = tail->prev;
		nn->next = tail;

		tail->prev->next = nn;
		tail->prev = nn;
		size++;
	}

	void clear() {
		size = 0;
		head = myal.alloc();
		tail = myal.alloc();

		head->next = tail;
		tail->prev = head;
	}
	void setCursor() {
		cursor = head;
	}

	bool next(char num[4]) {
		if (cursor->next == tail) {
			return false;
		}

		cursor = cursor->next;
		memcpy(num, cursor->value, sizeof(char) * 4);
		return true;
	}

	void del() {
		if (cursor == head) return;

		cursor->prev->next = cursor->next;
		cursor->next->prev = cursor->prev;
		cursor = cursor->prev;
		size--;
	}
}list;

int nums[10] = { 0,1,2,3,4,5,6,7,8,9 };

void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

void setFirst(int depth, char num[4]) {
	if (depth == 4) {
		for (int i = 0; i < depth; i++) {
			num[i] = nums[i] + '0';
		}
		list.insert(num);
	}

	for (int i = depth; i < 10; i++) {
		swap(nums[depth], nums[i]);
		setFirst(depth + 1, num);
		swap(nums[depth], nums[i]);
	}
}

void init() {
	myal.clear();
	list.clear();

	char num[4];
	for (int i = 1; i < 10; i++) {
		swap(nums[0], nums[i]);
		setFirst(1, num);
		swap(nums[0], nums[i]);
	}
}

typedef struct QUERTY {
	int str, ball;
} QUERTY;

QUERTY ballAndStrike(const char numA[4], const char numB[4]) {
	bool nums[10] = { false };
	int b = 0, s = 0;
	for (int i = 0; i < 4; i++) {
		s += numA[i] == numB[i];
		nums[numA[i] - '0'] = true;
	}

	for (int i = 0; i < 4; i++) {
		b += nums[numB[i] - '0'];
	}
	return { s, b - s };
}

int main() {
	init();

	list.setCursor();
	char num[4];

	list.next(num);
	int x = 5;
	return 0;
}