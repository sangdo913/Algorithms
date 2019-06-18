#include<iostream>
#include<set>

using namespace std;

int map[50][50];
int dr[] = {0,-1,0,1};
int dc[] = {-1,0,1,0};
int n, m;
int visit[50][50];
int rnum = 1;

int rs[2501],que[5000][2] ;

int MAX(int i1, int i2){return i1 > i2 ? i1 : i2;}
#include<cstdlib>
#include<ctime>
void test() {
	srand(time(0));
	multiset<int> se;

	int t = 100;
	while (t--) {
		se.insert(1);
	}
	for (auto i = se.begin(); i != se.end(); ++i) {
		cout << *i <<' ';
	}
}

int bfs(int r, int c){
    int fr, re;
    fr = re= 0;

    que[re][0] = r;
    que[re++][1] = c;
    
    visit[r][c] = rnum;
    int res = 0;

    while(fr!=re){
        int now[2] = {que[fr][0], que[fr++][1]};
        res++;

        for(int d = 0; d < 4; d++){
            if((1<<d)& map[now[0]][now[1]]) continue;
            
            int next[2] = {now[0] + dr[d], now[1] + dc[d]};

            if(visit[next[0]][next[1]]) continue;
            visit[next[0]][next[1]] = rnum;

            que[re][0] = next[0];
            que[re++][1] = next[1];
        }
    }
    return res;
}

int main(){
    //cin >> n >> m;

    //for(int i = 0; i < m; i++){
    //    for(int j = 0; j < n ; j++){
    //        cin >> map[i][j];
    //    }
    //}

    //int res[3] = {};

    //for(int i = 0; i < m; i++){
    //    for(int j = 0; j < n ; j++){
    //        if(visit[i][j]) continue;
    //        
    //        res[0]++;
    //        rs[rnum] = bfs(i,j);
    //        res[1] = MAX(res[1], rs[rnum]);
    //        rnum++;
    //    }
    //}

    //for(int i =0; i < m; i++){
    //    for(int j =0; j < n;j ++){
    //        for(int d = 0; d < 4; d++){
    //            if(map[i][j] & (1<<d)){
    //                int next[2] = {i+dr[d], j + dc[d]};
    //                if(next[0] < 0 || next[1] < 0 || next[0] > m-1 ||next[1] > n-1 ) continue;
    //                int r1 = visit[i][j];
    //                int r2 = visit[next[0]][next[1]];
    //                
    //                if(r1 == r2) continue;

    //                res[2] = MAX(res[2], rs[visit[i][j]] + rs[visit[next[0]][next[1]]]);
    //            }
    //        }
    //    }
    //}

    //cout << res[0] << '\n' << res[1] << '\n' << res[2] << '\n';

	test();
    return 0;
}