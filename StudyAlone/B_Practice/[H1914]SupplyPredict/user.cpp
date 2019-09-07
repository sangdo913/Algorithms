#define MAX_N    100
#define MAX_TOOL 50
#define MAX_LOT 100000

struct MACHINE {
	int id;
	int time;
	int lid;
	int pt;
}machine[MAX_TOOL*MAX_N];

struct LOTS {
	int id;
	int time;
}lots[MAX_LOT];

int used[MAX_N + 1][MAX_TOOL];
int usize[MAX_N + 1];

int readyMachine[MAX_N + 1][MAX_TOOL];
int rdmsize[MAX_N + 1];
int step;
int lid;

int waitting[MAX_N + 1][MAX_LOT+1];
int wlen[MAX_N + 1];

bool lcomp(int*arr, int i1, int i2) {
	return lots[arr[i1]].time < lots[arr[i2]].time;
}

void insert(int *arr,int *size, int lid, bool (*comp)(int *arr, int i1, int i2)) {
	arr[0] = lid;
	int c = ++*size, p = c >> 1;

	while (p && comp(arr, 0, p)) {
		arr[c] = arr[p];
		c = p;
		p = c >> 1;
	}
	arr[c] = lid;
}

int getChild(int *arr, int*size, int p, bool (*comp)(int * arr, int i1, int i2)) {
	int l = p << 1;
	int r = l + 1;
	if (l > *size) return 0;
	if (r > *size) return l;
	if (comp(arr,l,r)) return l;
	return r;
}

int pop(int *arr, int * size, bool (*comp)(int *arr, int i1, int i2)) {
	int ret = arr[1];
	arr[0] = arr[(*size)--];
	int p = 1, c = getChild(arr,size, 1,comp);

	while (c && comp(arr,c,0)) {
		arr[p] = arr[c];
		p = c;
		c = getChild(arr,size, p, comp);
	}
	arr[p] = arr[0];
	return ret;
}


void init(int N) {
	step = N;
	lid = 0;
	
	for (int i = 0; i <= N; ++i)wlen[i] = usize[i] = rdmsize[i] = 0;
}

void setupTool(int T, int stepNo[5000], int procTime[5000]) {
	for (int i = 0; i < T; ++i) {
		machine[i].id = i;
		machine[i].time = 0;
		machine[i].pt = procTime[i];
		readyMachine[stepNo[i]][rdmsize[stepNo[i]]++] = i;
	}
}


void addLot(int time, int number) {
	for (int i = 0; i < number; ++i) {
		LOTS& l = lots[lid];
		l.time = time;
		l.id = lid++;

		insert(waitting[0], &wlen[0],l.id, lcomp);
	}
}

int simulate(int time, int wip[MAX_N]) {
	for (int i = 0; i < step; ++i) {
		bool changed = true;
		int lid, mid;
		while (changed) {
			changed = false;
			//공정 완료
			for (int j = 0; j < usize[i]; ++j) {
				mid = used[i][j];
				lid = machine[mid].lid;

				if (machine[mid].time + machine[mid].pt <= time) {
					used[i][j--] = used[i][--usize[i]];
					lots[lid].time = machine[mid].time = machine[mid].time + machine[mid].pt;

					readyMachine[i][rdmsize[i]++] = mid;

					insert(waitting[i + 1],&wlen[i+1], lid, lcomp);
				}
			}

			//공정선택
			while (rdmsize[i] && wlen[i]) {
				lid = pop(waitting[i], wlen + i, lcomp);
				int sel = -1;
				int minPt = 0x3f3f3f3f;
				int ttime = 0x3f3f3f3f;
				
				for (int j = 0; j < rdmsize[i]; ++j) {
					mid = readyMachine[i][j];

					if (machine[mid].time <= lots[lid].time) {
						if (ttime > lots[lid].time) {
							sel = j;
							ttime = machine[mid].time;
							minPt = machine[mid].pt;
						}

						else if (machine[mid].pt < minPt) {
							ttime = machine[mid].time;
							minPt = machine[mid].pt;
							sel = j;
						}
					}

					else{
						if (machine[mid].time == ttime && machine[mid].pt < minPt) {
							sel = j;
							minPt = machine[mid].pt;
							ttime = machine[mid].time;
						}
						else if (machine[mid].time < ttime) {
							sel = j;
							minPt = machine[mid].pt;
							ttime = machine[mid].time;
						}
					}
				}

				mid = readyMachine[i][sel];

				machine[mid].time = lots[lid].time < machine[mid].time ? machine[mid].time : lots[lid].time;
				machine[mid].lid = lid;
					
				if (machine[mid].time + machine[mid].pt > time)
				{
					used[i][usize[i]++] = mid;
					readyMachine[i][sel] = readyMachine[i][--rdmsize[i]];
				}
				else {
					lots[lid].time = machine[mid].time += machine[mid].pt;
					insert(waitting[i + 1], wlen + i + 1, lid, lcomp);
				}
			}
		}
	}
	for (int i = 0; i < step; ++i) wip[i] = wlen[i] + usize[i];
	return wlen[step];
}