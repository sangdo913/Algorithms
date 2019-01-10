//https://www.acmicpc.net/problem/16234
//BOJ 16234 인구이동
#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

int arr[50][50], n, l, r;
int check[50][50];
bool canmove[50][50][4];
int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

struct COD { 
	int r, c;
	COD() :r(0), c(0) {} 
	COD(int r, int c) :r(r), c(c) {}
};

bool isout(int r, int c) { return r < 0 || c < 0 || r >= n || c >= n; }
int ABS(int a){return a > 0 ? a : -a;}

int bfs(){
	int ret = 0;
	bool isend = false;
	queue<COD> que;
	queue<COD> uni;

	while(!isend){
		isend = true;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n ; j++){
				for(int d= 0; d <4 ;d++){
					int nr = i + dr[d];
					int nc = j + dc[d];

					if(isout(nr,nc)) continue;
					int diff= ABS(arr[i][j] - arr[nr][nc]);
					canmove[i][j][d] = (l<= diff && diff <= r);
					isend &= !canmove[i][j][d];
				}
			}
		}

		COD now, next;
		for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
			if(check[i][j] != ret){
				check[i][j] = ret; 
				int sum = 0;
				int num = 0;

				que.push({i,j});

				while(que.size()){
					now = que.front(); que.pop();
					uni.push(now);
					sum += arr[now.r][now.c];
					num++;

					for(int d = 0; d < 4 ;d++){
						if(canmove[now.r][now.c][d]){
							next.r = now.r + dr[d];
							next.c = now.c + dc[d];
							if(isout(next.r, next.c) || check[next.r][next.c] ==ret) continue;
							check[next.r][next.c] = ret;

							que.push(next);
						}
					}
				}

				while(uni.size()){
					now = uni.front(); uni.pop();
					arr[now.r][now.c] = sum/num;
				}
			}
		}

		ret++;
	}
	return ret-1;
}

int Do(){
	memset(check,-1,sizeof(check));

	cin >> n >> l >> r;
	for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) cin >> arr[i][j];

	cout << bfs();
	return 0;
}