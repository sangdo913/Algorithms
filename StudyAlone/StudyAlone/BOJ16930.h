#include<iostream>
#include<queue>
#include<cstring>

using namespace std;

struct COD{
    int r,c,cnt;
};

queue<COD> que;
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};
char arr[1000][1001];
int n,m,k;
bool visit[1000][1000];

bool isout(int r, int c){
    return r< 0 || c < 0 || r >= n || c >= m;
}

int Do(){
    COD st,dt;
    cin >> n >> m>> k;

    for(int i = 0; i < n; i++)
        cin >> arr[i];

    cin >> st.r >> st.c;
    cin >> dt.r >> dt.c;
    st.cnt = 0;
    st.r--, st.c--, dt.r--, dt.c--;
    que.push(st);
    visit[st.r][st.c] = true;

    while(que.size()){
        COD now, next;
        now = que.front(); que.pop();

        if(now.r == dt.r && now.c == dt.c){
            cout << now.cnt; return 0;
        }

        for(int d = 0; d < 4 ;d++){
            for(int i = 1; i <= k; i++){
                next.r = now.r + dr[d]*i;
                next.c = now.c  +dc[d]*i;
                if(isout(next.r, next.c) || arr[next.r][next.c] =='#') break;
                if(visit[next.r][next.c]) continue;

                visit[next.r][next.c] = true;
                next.cnt = now.cnt+1;
                que.push(next);
            }
        }
    }

    cout << -1;
    return 0;
}