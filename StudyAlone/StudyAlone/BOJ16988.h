#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>

using namespace std;

struct COD{
    int r,c;
};

int arr[1000][1000];
const int dr[] = {-1,1,0,0};
const int dc[] = {0,0,-1,1};
int n,m;
int len[1000001];
int info[1000001][3][2];
int group[1000][1000];
int gsize[1000001];
int gnum = 1;
int holecheck[1000][1000];
int visit[1000001];
int ch = 1;
vector<int> idx[3];

struct cmp{
    bool operator()(int i, int j){
        return gsize[i] > gsize[j];
    }
};

void grouping(int i, int j){
    queue<COD> que;
    que.push({i,j});
    group[i][j] = gnum;
    int cnt = 0;

    COD next;
    while(que.size()){
        COD now = que.front(); que.pop();
        cnt++;
         
        for(int d = 0; d < 4; d++){
            next.r = now.r + dr[d]; next.c = now.c + dc[d];
            if(next.r < 0 || next.r == n || next.c < 0 || next.c == m) continue;
            if(arr[next.r][next.c] == 0){
                if(holecheck[next.r][next.c] != gnum) {
                    holecheck[next.r][next.c] = gnum;
                    len[gnum] = len[gnum] == 3? len[gnum] = 2 : len[gnum];
                    info[gnum][len[gnum]][0] = next.r;
                    info[gnum][len[gnum]++][1] = next.c;
                }
            }
            if(arr[next.r][next.c] != 2) continue;
            if(group[next.r][next.c]) continue;
            group[next.r][next.c] = gnum;;
            que.push(next);
        }
    }
    if(len[gnum] <= 2){ idx[len[gnum]].push_back(gnum); }
    gsize[gnum++] = cnt;
}

bool isok(int g){
    for(int i = 0; i < len[g]; i++){
        if(arr[info[g][i][0]][info[g][i][1]] != 1) return false;
    }
    return true;
}

int getnum(int i, int j){
    int res = 0;
    for(int d = 0; d < 4; d++){
        int nr = i+ dr[d], nc = j + dc[d];
        if(nr < 0 || nr == n || nc < 0 || nc == m) continue;
        int g = group[nr][nc];
        if(g && len[g] < 3 && visit[g] != ch){
            visit[g] = ch;
            res += (isok(g) ? gsize[g] : 0);
        }
    }
    return res;
}

int Do(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); 

    cin >> n >> m;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) cin >> arr[i][j];

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(arr[i][j] != 2 || group[i][j]) continue;
            grouping(i,j);
        }
    }

    int res = 0;
    int cnt;
    sort(idx[1].begin(),idx[1].end(), cmp());
    
    if(idx[1].size()){
        for(int i = 0; i < idx[1].size(); i++){
                cnt = 0;
                int g1 = idx[1][i];
                int g2 = idx[1][0];
                int i1 = info[g1][0][0], j1 = info[g1][0][1];
                int i2 = info[g2][0][0], j2 = info[g2][0][1];

                arr[i1][j1] = 1;
                arr[i2][j2] = 1;

                for(int d = 0; d < 4; d++){
                cnt += getnum(i1,j1);
                cnt += getnum(i2,j2);
                }
                arr[i1][j1] = 0;
                arr[i2][j2] = 0;
                res = cnt > res ? cnt : res;
                ch++;
            }
    }
    
    for(int i = 0; i < idx[2].size(); i++){
        cnt = 0;
        int g = idx[2][i];
        int i1 = info[g][0][0], j1 = info[g][0][1];
        int i2 = info[g][1][0], j2 = info[g][1][1];
        arr[i1][j1] = arr[i2][j2] = 1;

        for(int d= 0; d < 4; d++){
            cnt+= getnum(i1,j1);
            cnt+= getnum(i2,j2);
        }
        arr[i1][j1] = arr[i2][j2] = 0;
        res = cnt > res ? cnt :res;
        ch++;
    }
    cout << res;
    return 0;
}