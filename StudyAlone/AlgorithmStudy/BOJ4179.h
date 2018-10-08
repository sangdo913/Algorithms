#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>

using namespace std;

int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};

bool visit[1002][1002];
char map[1002][1002] ;
int r,c ;
queue<pair<int, int> > que;
queue<pair<int, int> > fires;

void spread(){
    int cnt = fires.size();

    while(cnt--){
        pair<int, int> now = fires.front();
        fires.pop();

        for(int d = 0; d < 4; d++){
            pair<int, int> next;
            next.first = now.first  + dr[d];
            next.second = now.second + dc[d];

            if(map[next.first][next.second] == '.'){
                map[next.first][next.second] = 'F';
                que.push(next);
            }
        }
    }
}

int bfs(){
    int t = 0;

    bool escape =false;
    
    while(que.size() && !escape){
        int cnt = que.size();
        t++;

        while(cnt--){
            pair<int, int> now = que.front();
            if(map[now.first][now.second] == 0){
                escape = true;
                break;
            }
            que.pop();

            if(map[now.first][now.second] == 'F') continue;

            for(int d = 0; d < 4; d++){
                pair<int, int> next;
                next.first = now.first + dr[d];
                next.second = now.second + dc[d];

                if(visit[next.first][next.second]){
                    continue;
                }

                if(map[next.first][next.second] == 'F') continue;
                if(map[next.first][next.second] == '#') continue;
                visit[next.first][next.second] = true;

                que.push(next); 
            }
        }
        spread();
    }

    return escape ? --t : -1;
}


int BOJ4179() {
    cin >> r >> c;

    for(int i = 1; i <= r; i++){
        for(int j = 1; j <= c; j++){
            cin >>map[i][j];
            if(map[i][j] == 'J')
            {
                que.push(make_pair(i,j));
                visit[i][j] = true;
                map[i][j] = '.';
            }
            else if(map[i][j] == 'F'){
                fires.push(make_pair(i,j));
            }
        }
    }
    
    int t = bfs();

    if(t == -1) cout << "IMPOSSIBLE\n";
    else cout << t ;


    return 0;
}