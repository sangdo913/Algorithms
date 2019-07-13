#include<iostream>

using namespace std;

int dp[10][46][1024];
int n;
bool map[20][20];
int x[1000], y[1000], sum[1000];
int len[1000];
bool sero[1000];
int arr[20][20];
int m;
int dr[2] = { 0,1 };
int dc[2] = { 1,0 };
int info[1000][1000];
int mapinfo[20][20];
int tc;

int getNum(int bit){
	int res = 0;
	while(bit){
		res++;
		bit -= bit & -bit;
	}
	return res;
}
int getSum(int bit){
	int ret = 0;
	for(int i = 1; i < 10; ++i){
		if(bit & (1<<i)) ret += i;
	}
	return ret;
}
int avail[4000];
int used[4000];

int getAvail(int r, int c){
	int id1 = mapinfo[r][c] >> 10, id2= mapinfo[r][c] & 1023;
	return dp[len[id1]][sum[id1]][used[id1]] & dp[len[id2]][sum[id2]][used[id2]];
}
bool isfull(int idx){
	return getNum(used[idx]) == len[idx];
}
bool isok(int idx){
	return isfull(idx) || dp[len[idx]][sum[idx]][used[idx]];
}

bool make(int idx, int ilen){
	if(ilen == len[idx]){
		for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j){
			if(!arr[i][j]) continue;
			int id1 = mapinfo[i][j] >> 10;
			int id2 = mapinfo[i][j] &1023;
			int a1 = getNum(dp[len[id1]][sum[id1]][used[id1]]);
			int a2 = getNum(dp[len[id2]][sum[id2]][used[id2]]);
    
			if(isfull(id1) && isfull(id2)) continue;
			if(isfull(id1)){
				return make(id2,0);
			}
			if(isfull(id2)) 
				return make(id1,0);

			if(a1 == a2) {
				if(sum[id1] < sum[id2]) 
					if(isok(id1)) return make(id1, 0);
					else return make(id2,0);
			}
			else{
				if(len[id1] - a1 < len[id2] - a2) 
					if(isok(id1)) return make(id1, 0);
					else return make(id2, 0);
			}
		}
		return true;
	}
	if(!isok(idx)) return false;
	int r,c,tb; 
	r = info[idx][ilen] >> 10, c = info[idx][ilen] & 1023;
	if(arr[r][c]) return make(idx, ilen+1);
	int id2 = (mapinfo[r][c] >>(10*!sero[idx])) & 1023;
	tb = getAvail(r,c);

		for(int i = 1; i < 10; ++i){
			if((1<<i) & tb){
				used[idx] |= 1<<i;
				used[id2] |= 1<<i;
				arr[r][c] = i;

				if(make(idx, ilen+1)) return true;
				used[idx] ^= 1<<i;
				used[id2] ^= 1 <<i;
				arr[r][c] = 0;
			}
		}
	return false;
}

int Do() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> tc;
	++tc;

	for(int set = 2; set < 1024; set+=2){
		int l = getNum(set);
		int ssum = getSum(set);
		int subset = set;

		while(subset){
			dp[l][ssum][set&~subset]  |= set &~(set&~subset);
			subset--;
			subset = set& subset;
		}
	}

	while (--tc) {
		cin >> n;
		for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> map[i][j], mapinfo[i][j] = arr[i][j] = 0;
		cin >> m;

		int ii = 0;
		len[0] = 1000, sum[0] = 1000;
		for (int i = 1; i <= m; ++i) {
			used[i] = 0;
			len[i] = 0;
			cin >> y[i] >> x[i] >> sero[i] >> sum[i];
			y[i] -= !sero[i], x[i] -= sero[i];
			int r = y[i];
			int c = x[i];
			while (r < n && c < n && map[r][c]) {
				info[i][len[i]++] = (r << 10) + c;
				mapinfo[r][c] |= i << (10*(int)sero[i]);
				r += dr[sero[i]], c += dc[sero[i]];
			}
			if(len[i] == len[ii]) ii = sum[i] < sum[ii] ? i : ii;
			else ii = len[i] < len[ii] ? i : ii;
		}

		for(int ii = 1; ii <=m; ++ii)make(ii,0);

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) cout << arr[i][j] << ' ';
			cout << '\n';
		}
	}
	return 0;
}