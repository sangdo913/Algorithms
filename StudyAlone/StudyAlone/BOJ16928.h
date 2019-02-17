#include<iostream>
#include<queue>
#include<cstring>

struct STATE{
    int n, cnt;
};

int visit[101], n, m;

using namespace std;
queue<STATE> que;

int sadari[101];
int snake[101];

int Do(){
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        sadari[x] = y;
    }
    for(int i = 0; i < m; i++){
        int x, y;
        cin >> x >> y;
        snake[x] = y;
    }

    memset(visit, 0x3f, sizeof(visit));

    que.push({1,0});        

    while(que.size()){
        STATE now, next;

        now = que.front(); que.pop();

        if(now.n == 100){
            cout << now.cnt; return 0;
        }

        for(int i = 1; i <= 6; i++){
            next.n = now.n + i;
            next.cnt = now.cnt + 1;
            if(next.n > 100) break;

            bool changed  = true;

            while(changed){
                changed = false;
                if(snake[next.n]) changed = true, next.n = snake[next.n];
                else if(sadari[next.n]) changed = true, next.n = sadari[next.n];
            }

            if(visit[next.n] <= next.cnt) continue;
            visit[next.n] = next.cnt;
            que.push(next);
        }
    }
    return 0;
}