#include<iostream>

using namespace std;

int n;
bool map[20][20];
int x[1000], y[1000], sum[1000], check[1000];
int len[1000];
bool sero[1000];
int arr[20][20];
int m;
int dr[2] = { 0,1 };
int dc[2] = { 1,0 };
int info[1000][1000];
int mapinfo[20][20];
int infolen[1000];
int tc;
int maxSum[10];

int make(int idx, int ilen){
	if(!idx && !len[idx]) return 0;
	if(len[idx] && sum[idx] > maxSum[len[idx]]) return idx;
	if(ilen == infolen[idx]){
		if(sum[idx]) return -1;
		int nid = 0;
		for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j){
			if(!arr[i][j]) continue;
			int temp;
			int i1 = mapinfo[i][j] >>10;
			int i2 = mapinfo[i][j] & 1023;
			if(!len[i1] && !sum[i1]) i1 = 0;
			if(!len[i2]&& !sum[i2]) i2 = 0;

			if(len[i1] == len[i2]){
				temp = sum[i1] < sum[i2] ? i1 : i2;
			}
			else if(len[i1] < len[i2]) temp = i1;
			else temp = i2;
			if(!len[temp] && !sum[temp]) continue;
			if(len[nid] > len[temp]) nid = temp;
			else if(len[nid] == len[temp]){
				if(sum[nid] > sum[temp]) nid = temp;
			}
		}
		if(nid == 0) return 0;
		int res = make(nid, 0);
		return res == 0 ? 0 : -1;
	}
	int r = info[idx][ilen] >> 10, c = info[idx][ilen]&1023;
	if(arr[r][c]){
		return make(idx, ilen+1);
	}
	int idx2 = (mapinfo[r][c] >> (10 * !sero[idx])) & 1023;


	for(int num =1; num < 10; num++){
		if(check[idx] & (1<<num)) continue;
		if(check[idx2] & (1<<num)) continue;
		if(sum[idx2] - num < 0) return -1;
		if(sum[idx] - num < 0) return -1;
		check[idx] += 1<<num;
		check[idx2] += 1 << num;
		len[idx]--, len[idx2]--;
		arr[r][c] = num;
		sum[idx]-= num;
		sum[idx2] -= num;
		int res = make(idx, ilen+1);
		if(res == 0) return 0;
		
		arr[r][c] = 0;
		check[idx] ^= 1 << num;
		check[idx2] ^= 1<<num;
		sum[idx2] += num;
		sum[idx] += num;
		len[idx]++, len[idx2]++;
	}
	return -1;
}

int Do() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> tc;
	++tc;

	maxSum[0] = 1000;
	maxSum[1] = 9;
	int nnum = 8;
	for(int i = 2; i < 10; ++i){
		maxSum[i] = maxSum[i-1] + nnum--;
	}
	len[0] = 10000;

	while (--tc) {
		cin >> n;
		for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> map[i][j], mapinfo[i][j] = arr[i][j] = 0 ;
		cin >> m;

		for (int i = 1; i <= m; ++i) {
			check[i] = 0;
			infolen[i] = 0;
			len[i] = 0;
			cin >> y[i] >> x[i] >> sero[i] >> sum[i];
			y[i] -= !sero[i], x[i] -= sero[i];
			int r = y[i];
			int c = x[i];
			while (r < n && c < n && map[r][c]) {
				len[i]++;
				info[i][infolen[i]++] = (r << 10) + c;
				mapinfo[r][c] |= i << (10*(int)sero[i]);
				r += dr[sero[i]], c += dc[sero[i]];
			}
		}

		int cnt = m;
		while (cnt--) {
			int idx = 0;
			for (int i = 1; i <= m; ++i) {
				if (!len[i] && !sum[i]) continue;
				if (len[idx] > len[i]) {
					idx = i;
				}
				else if (len[idx] == len[i] && sum[idx] > sum[i]) {
					idx = i;
				}
			}
			if (idx) {
				make(idx, 0);
			}
		}

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) cout << arr[i][j] << ' ';
			cout << '\n';
		}
	}
	return 0;
}