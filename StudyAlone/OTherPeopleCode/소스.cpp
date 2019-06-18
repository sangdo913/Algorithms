#include <stdio.h>
#define max_key 500007
#define max_data 500001

typedef struct _hash {
	char name[21];
}HASH;

typedef struct _heap {
	HASH hData[max_data];
	int numOfData;
}Heap;


HASH hb[max_key];
Heap h;

// 힙 관련 코드
int getChildPriority(Heap *h, int idx);

// 해싱
unsigned long Hash(char key[21]);
void add(char name[21]);
char *find(char name[21]);

void strCpy(char from[21], char to[21]);
int strCmp(char str1[21], char str2[21]);

void HInsert(Heap *h, char *str);
char *HDelete(Heap *h);
int main() {
	char buf[21] = { 0, };
	int N, M;

	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		scanf("%s", buf);
		add(buf);
	}

	h.numOfData = 0;
	for (int i = 0; i < M; i++) {
		scanf("%s", buf);
		char*ret = find(buf);
		if (ret == 0)
			continue;
		HInsert(&h, ret);
	}
	printf("%d\n", h.numOfData);
	while (h.numOfData > 0) {
		char *ret = HDelete(&h);
		//printf("%s\n", ret);
	}
	return 0;
}

// 힙 관련 코드
void HInsert(Heap *h, char *str) {
	int idx = h->numOfData + 1;

	while (idx != 0) {
		int pIdx = idx / 2;
		if (strCmp(h->hData[pIdx].name, str) > 0) { // 자식이 더 작은경우
			strCpy(h->hData[pIdx].name, h->hData[idx].name);
			idx = pIdx;
		}
		else
			break;
	}
	strCpy(str, h->hData[idx].name);
	h->numOfData += 1;
}
char* HDelete(Heap *h) {
	char retData[21];
	strCpy(h->hData[1].name, retData);
	HASH lastData = h->hData[h->numOfData];

	int parent = 1;
	int child = 0;

	while (child = getChildPriority(h, parent)) {
		if (strCmp(lastData.name, h->hData[child].name) <= 0) { // 자식이 작은경우
			break;
		} //position changed
			strCpy(h->hData[child].name, h->hData[parent].name);
			parent = child;
	}
	h->hData[parent] = lastData;
	h->numOfData -= 1;
	printf("%s\n", retData);
	return retData;
}
int getChildPriority(Heap *h, int idx) {
	if (idx * 2 > h->numOfData) // 인덱스 벗어난 경우
		return 0;
	else if (idx * 2 == h->numOfData) // 왼쪽 자식만 있는 경우
		return idx * 2;
	else {
		int LIdx = idx * 2;
		int RIdx = idx * 2 + 1;
		int num = strCmp(h->hData[LIdx].name, h->hData[RIdx].name);
		if (num > 0) {
			return RIdx;
		}
		else {
			return LIdx;
		}

	}
}

unsigned long Hash(char key[21]) {
	unsigned long hash = 5381;

	int c;

	while (c = *key++) {
		hash = (((hash << 5) + hash) + c) % max_key;
	}
	return hash % max_key;
}
void add(char name[21]) {

	unsigned long h = Hash(name);
	while (hb[h].name[0] != 0) {
		if (strCmp(name, hb[h].name) == 0)
			break;
		h = (h + 1) % max_key;
	}
	strCpy(name, hb[h].name);
}
char *find(char name[21]) {
	unsigned long h = Hash(name);

	int c = max_key;
	while (hb[h].name[0] != 0 && c--) {
		if (strCmp(hb[h].name, name) == 0) {
			return hb[h].name;
		}
		h = (h + 1) % max_key;
	}
	return 0;
}
void strCpy(char from[21], char to[21]) {
	while (*from != '\0') {
		*to = *from;
		*to++;
		*from++;
	}
	*to = '\0';
}
//changed
int strCmp(char str1[21], char str2[21]) {
	int i;
	for (i = 0; str1[i] != 0; i++) {
		if (str1[i] != str2[i]) {
			return str1[i] - str2[i];
		}
	}
	return str1[i] - str2[i];
}