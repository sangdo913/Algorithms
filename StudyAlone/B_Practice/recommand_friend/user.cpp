//julysky 님 코드 참고
//bitpos : 1ull << i 의 위치를 쉽게 찾을 수 있음(1ull이 2^n이기 때문에 어떤 수로 모듈라연산을 해도 충돌이 적음)

//차이
//5만개의 쿼리로는 친구의 목록이 크지 않기 때문에 1~10000의 아이디를 찾는 방식보다 
//실제 친구인 비트들의 위치를 비교해가면서 친구의 친구를 확인하는 방식이 훨씬 빠르다(이전 코드와 속도차이 약 2배)

#define MAXL	5
#define MAXF	10
#define MAXN 10000
#define rint register int
#define ull unsigned long long

unsigned long long isfriend[MAXN+1][MAXN / 64 + 1];
int n;
#define HASH 201
int bitpos[HASH];
int fvisit[MAXN + 1];
int tc;

void init(int N)
{
	n = N;
	rint len = N / 64 + 1;
	if (!bitpos[2]) {
		for (rint i = 0; i < 64; ++i) {
			bitpos[(1ULL << i) % HASH] = i;
		}
	}
	for (rint i = 1; i <= N; ++i) {
		for (rint j = 0; j < len; ++j) {
			isfriend[i][j] = 0;
		}
	}
}

void add(int id, int F, int ids[MAXF])
{
	for (rint i = 0; i < F; ++i) {
		isfriend[id][ids[i] / 64] |= (1ULL << (ids[i] % 64));
		isfriend[ids[i]][id/64] |= (1ULL << (id % 64));
	}
}

void del(int id1, int id2)
{
	isfriend[id1][id2 / 64] &= ~(1ULL << (id2 % 64));
	isfriend[id2][id1/64] &= ~(1ULL << (id1 % 64));
}

int nums[MAXN+1];

int recommend(int id, int list[MAXL])
{
	tc++;
	rint l = 0;
	rint len = n / 64 + 1;
	for (rint i = 1; i <= n; ++i) nums[i] = 0;

	for (rint i = 0; i < len; ++i) {
    	register long long ibit = isfriend[id][i];

		while (ibit) {
			register ull f = ibit & -ibit;
			rint p = bitpos[f%HASH];
			register int fid = i*64 + p;

			for (rint j = 0; j < len; ++j) {
				register long long jbit = isfriend[fid][j];
				while (jbit) {
					register ull fof = jbit & -jbit;
					rint fofp = bitpos[fof%HASH];
					rint fofid = 64*j + fofp;

					if (!(isfriend[id][j] & fof) && (fofid != id)) {
						if (fvisit[fofid] != tc) {
							fvisit[fofid] = tc;
							++l;
						}
						nums[fofid]++;
					}
					jbit -= fof;
				}
			}
			ibit -= f;
		}
	}
	if (l > 5) l = 5;
	for (rint i = 0; i < l; ++i) {
		rint max = 0, ii;
		for (rint id = 1; id <= n; ++id) {
			if (nums[id] > max) {
				max = nums[id];
				ii = id;
			}
		}
		list[i] = ii;
		nums[ii] = 0;
	}

	return l;
}