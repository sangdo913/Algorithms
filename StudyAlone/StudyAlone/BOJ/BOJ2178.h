#include<iostream>
#include<queue>

using namespace std;

struct INFO{
    int r,c;
};
char mymap[100][101];
bool visit[100][100];
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};

int main(){
    freopen("0Text.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; ++i) cin >> mymap[i];
    visit[0][0] = true;
    
    queue<INFO> Q;
    Q.push({0,0});
    int len = 0;
    while(!Q.empty()){
        int cnt = Q.size();
        len++;

        while(cnt--){
            INFO now = Q.front(); Q.pop();
            INFO next;
            if(now.r == n-1 && now.c == m-1) return !(cout << len);

            for(int d = 0; d < 4; ++d){
                next.r = now.r + dr[d];
                next.c = now.c + dc[d];

                if(next.r <0 || next.c < 0 || next.r ==n || next.c == m) continue;
                if(mymap[next.r][next.c] == '0') continue;
                if(visit[next.r][next.c]) continue;
                visit[next.r][next.c] = true;
                Q.push(next);
            }
        }
    }

    return 0;
}