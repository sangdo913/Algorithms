#include<cstdio>
bool buse[10][10];
bool remain[10][10];

int map[10][10][4];
int res[10][10];

void check(int x, int y,int n, bool flag){
	if(flag)res[x][y] = n; else(res[x][y] = 0);
	if(flag) map[x][y][0] |= (1<<10); else map[x][y][0] &=~(1<<10);

	for(int i = 1; i < 10; ++i) {
		if(flag)map[i][y][0] |= (1<<n), map[x][i][1] |= (1<<n);
		else map[i][y][0] &= ~(1<<n), map[x][i][1] &= ~(1<<n);
	}
	int gx = (x-1)/3;
	int gy = (y-1)/3;
	for(int i = 0; i < 3; ++i){
		for(int j = 0; j < 3; ++j){
			if(flag)map[gx*3+1+i][gy*3+1+j][3] |= (1<<n);
			else map[gx*3+1+i][gy*3+1+j][3] &= ~(1<<n);
		}
	}
}

int getCnt(int i){
	int ret = 0;
	while(i){
		++ret;
		i -= i & -i;
	}
	return 9-ret;
}

bool cantuse(int x1, int y1, int n1, int x2, int y2, int n2){
	bool cantuse = false;
	for(int d = 0; d < 4; ++d){
		cantuse |= map[x1][y1][d] & (1 << n1) || map[x2][y2][d] & ( 1<< n2);
	}

	int temp;
	if (n1 > n2)  temp = n1, n1 = n2, n2 = temp; 
	return cantuse ||  x1 < 1 || y1 < 1 || x2 < 1 || y2 < 1 || x1 > 9 || y1 > 9 || x2 > 9 || y2 > 9|| !remain[n1][n2];
}
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

int findnext(){
	int lowpos, temp;
	int low = 0x3f3f3f3f;
	for(int i = 1; i < 10; ++i)for(int j = 1; j < 10; ++j) {
		if(map[i][j][0] & (1<<10)) continue;
		if(low > (temp= getCnt(map[i][j][0] | map[i][j][1] | map[i][j][2] | map[i][j][3]))){
			low = temp;
			lowpos = (i << 10) + j;
		}
	}
	return lowpos;
}

bool make(int cnt, int x, int y){
	if(!cnt) return true;

	for(int i = 1; i < 10; ++i){
		for(int j  = 1; j < 10; ++j){
			for(int d = 0; d < 4; ++d) {
				int x2 = x + dx[d], y2 = y + dy[d];

				if(cantuse(x,y, i, x2, y2, j)) continue;
				if(map[x2][y2][0] & (1<<10)) continue;
				if(i < j) remain[i][j] = false; else remain[j][i] = false;
				check(x,y,i,1);
				check(x2,y2,j,1);
				
				int next = findnext();
				bool ret = make(cnt-1, next>>10, next&((1<<10)-1));
				if(ret) return true;
				if(i < j) remain[i][j] = true; else remain[j][i] = true;

				check(x,y,i,0);
				check(x2,y2,j,0);
			}
		}
	}
	return false;
} 
#include<cstring>

int ain(){
	int n;
	scanf("%d",&n);
	int tc = 1;

	while(n){
		memset(buse, false, sizeof(buse));
		memset(remain, 0 , sizeof(remain));
		memset(map, 0, sizeof(map));
		
		int cnt = 0;
		int a ;char a1; int a2; int b; char b1; int b2;
		while(n--){
			scanf("%d %c%d %d %c%d ", &a, &a1, &a2, &b, &b1, &b2);
			if(a < b) buse[a][b] = true;
			else buse[b][a] = true;
			check(a1-'A' + 1,a2,a, true);
			check(b1- 'A' + 1,b2,b, true);		
		}

		for(int i = 1; i < 10; ++i){
			scanf("%c%d ", &a1, &a2);
			check(a1-'A'+1,a2,i, true);
		}
		
		for(int i = 1; i < 10; ++i) for(int j = i+1; j< 10; ++j){
			if(!buse[i][j]){
				remain[i][j] = true;
				cnt++;
			}
		}

		int next = findnext();
		make(cnt, next >>10, next & ((1<<10)-1));
		printf("Puzzle %d\n", tc++);
		for(int i = 1; i < 10; ++i){
			for(int j= 1; j < 10; ++j) { printf("%d", res[i][j]); }
			printf("\n");
		} 
		
		scanf("%d",&n);
	}

	return 0;
}