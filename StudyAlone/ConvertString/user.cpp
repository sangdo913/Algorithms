int pqid[50000];
int key[50000];
int isout[50000];
int nidx;
const int asize = (26 << 10) + (26 << 5) + 27;
int myheap[asize][2000];
int hsize[asize];
int conv[256];
char *str;
int nn;
#define MAX_WORD_LIST 50000

void push(int key, int v) {
	int size = ++hsize[key];
	int* nowheap = myheap[key];

	register int c = size;
	register int p = c >> 1;
	while (p && v <nowheap[p]) {
		nowheap[c] = nowheap[p];
		pqid[nowheap[c]] = c;
		c = p;
		p = c >> 1;
	}
	nowheap[c] = v;
	pqid[v] = c;
}

inline int getchild(int*arr, int p, int size) {
	int l = p << 1;
	int r = l + 1;
	if (l > size) return 0;
	if (r > size) return l;
	if (arr[l] < arr[r]) return l;
	return r;
}

int pop(int key) {
	int *nowheap = myheap[key];
	int size = hsize[key]--;
	int ret = nowheap[1];

	int data = nowheap[size--];
	register int p = 1;
	register int c = getchild(nowheap, p, size);
	while (c && nowheap[c] < data) {
		nowheap[p] = nowheap[c];
		pqid[nowheap[p]] = p;
		p = c;
		c = getchild(nowheap, p, size);
	}
	nowheap[p] = data;
	pqid[data] = p;
	return ret;
}

void update(int key, int pos) {
	register int c = pos;
	register int p = c >> 1;
	int *nowheap = myheap[key];
	register int size = hsize[key]--;
	int v = nowheap[size--];

	while (p && nowheap[p] > v) {
		nowheap[c] = nowheap[p];
		pqid[nowheap[c]] = c;
		c = p;
		p = c >> 1;
	}
	nowheap[c] = v;
    pqid[v] = c;

	p = c;
	c = getchild(nowheap, p, size);

	while (c && nowheap[c] < v) {
		nowheap[p] = nowheap[c];
		pqid[nowheap[p]] = p;
		p = c;
		c = getchild(nowheap, p, size);
	}
	nowheap[p] = v;
	pqid[v] = p;
}

void init(int n, char Word[])
{
	nn = n;
	str = Word;
	nidx = 0;
	int cnt = 0;
	for (int i = 'a'; i <= 'z'; ++i) conv[i] = cnt++;

	for (register int i = 0; i < asize; ++i) hsize[i] = 0;

	for (register int i = 0; i <= n - 3; ++i) {
		key[i] = (conv[Word[i]]<<10)+ (conv[Word[i+1]]<<5)+ conv[Word[i + 2]];
		push(key[i],i);
	}
}

int st[50000];
int query;

int Replace(char str1[], char str2[])
{
	query++;
	int mini = -1;
	register int stsize = 0;
	int rkey = (conv[str1[0]] << 10) + (conv[str1[1]] << 5) + conv[str1[2]];
	int id;
	register int ret = 0;

	while (hsize[rkey]) {
		id = pop(rkey);

		if (mini > id) {
			if (isout[id] != query) {
				st[stsize++] = id;
				isout[id] = query;
			}
			
			continue;
		}

		if (isout[id] != query) {
			st[stsize++] = id;
			isout[id] = query;
		}
		ret++;

		str[id] = str2[0], str[id + 1] = str2[1], str[id + 2] = str2[2];

		int end = id + 4 >= nn ? nn-2 : id + 3;
		for (register int l = id - 2 < 0 ? 0 : id - 2; l < end ; ++l) {
			if (isout[l] == query) continue;
			isout[l] = query;
			st[stsize++] = l;
		}
		mini = id + 3;
	}

	while (stsize) {
		id = st[--stsize];
		if(key[id] != rkey) update(key[id], pqid[id]);
		key[id] = (conv[str[id]] << 10) + (conv[str[id+1]] << 5) + conv[str[id+2]];
		push(key[id], id);
	}

	return ret;
}
void GetStr(char Result[])
{
	for (register int i = 0; i < nn; ++i) {
		Result[i] = str[i];
	}
}
