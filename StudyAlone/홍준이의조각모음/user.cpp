extern int getdiskSize();
extern int readDisk(int* buf, int addr, int size);
extern int move(int from, int to, int size);

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
int disksize;
int mydisk[20000];
int disknum[10];
int diskst[10];
int disked[10];
int dest[20000];
int maxnum;

int findmove() {
	int maxsize = 0;
	int maxsid, zerosid;
	int zeromax = 0;
	int num;
	for (register int i = 0; i < disksize;) {
		if (mydisk[i] && dest[i] == mydisk[i]) {
			++i;
			continue;
		}

		int st = i;
		int mynum = mydisk[i++];
		if (mynum) {
			while (mynum == mydisk[i] && dest[i] != mynum) ++i;
			if (i - st > maxsize) {
				num = mynum;
				maxsize = i - st;
				maxsid = st;
			}
		}
		else {
			while (i < disksize && !mydisk[i]) ++i;
			if (i - st > zeromax) {
				zeromax = i - st;
				zerosid = st;
			}
		}
	}
	maxsize = maxsize < zeromax ? maxsize : zeromax;
	maxsize = maxsize < 64 ? maxsize : 64;
	if (!maxsize) 
		return 0;
	while (mydisk[diskst[num]] == dest[diskst[num]]) diskst[num]++;
	int destto = diskst[num] + 1;
	while (destto <disked[num] &&  mydisk[destto] != num) destto++;
	maxsize = maxsize < destto - diskst[num] ? maxsize : destto - diskst[num];

	int zerosize = 0;
	while (zerosize < maxsize && !mydisk[diskst[num] + maxsize - 1 - zerosize]) zerosize++;
	int postzero = 0;
	while (postzero < maxsize && !mydisk[diskst[num] + postzero]) postzero++;
	if (maxsize == zerosize) zerosize = maxsize, postzero = 0;
	zerosid += zeromax - maxsize;

	int sz = maxsize - zerosize - postzero;
	int from = diskst[num] + postzero;
	int to = zerosid + maxsize - sz;
	if (diskst[num] <= to && to < diskst[num] + maxsize  ) {
		maxsize = to - diskst[num];
	}

	if (diskst[num] != zerosid && sz) {
		move(from, to, sz);
		for (register int i = 0; i < sz; ++i) {
			mydisk[to + i] = mydisk[from + i];
			mydisk[from + i] = 0;
		}
	}

	move(maxsid, diskst[num], maxsize);
	for (register int i = 0; i < maxsize; ++i) {
		mydisk[diskst[num]++] = mydisk[maxsid + i];
		mydisk[maxsid + i] = 0;
	}

	return maxsize;
}

void defragment()
{
	maxnum = 0;
	disksize = getdiskSize();
	readDisk(mydisk, 0, disksize);
	for (int i = 0; i < 10; ++i) disknum[i] = 0;

	for (int i = 0; i < disksize; ++i) {
		maxnum = maxnum < mydisk[i] ? mydisk[i] : maxnum;
		disknum[mydisk[i]]++;
	}

	int idx = 0;
	for (int i = 1; i <= maxnum; ++i) {
		diskst[i] = idx;
		disked[i] = diskst[i] + disknum[i];
		for (int j = 0; j < disknum[i]; ++j) dest[idx++] = i;
	}
	diskst[0] = idx;
	for (int j = 0; j < disknum[0]; ++j) dest[idx++] = 0;

	int cnt = 0;
	while (findmove()) cnt++;
}