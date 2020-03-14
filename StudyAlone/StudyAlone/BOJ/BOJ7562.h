#include<iostream>
#include<queue>

using namespace std;

struct INFO{
    int r,c;
};

int visit[300][300];

int dr[8] = {-1,-2,-2,-1,1,2,2,1};
int dc[8] = {-2,-1,1,2,2,1,-1,-2};

int main(){
    freopen("0Text.txt", "r", stdin);
    int T;
    cin >>T;
    
    for(int tc = 1; tc <= T; ++tc){
        queue<INFO> Q;
        int n, sr,sc,er,ec;
        cin >> n;
        cin >> sr >>sc >> er >> ec;
        Q.push({sr,sc});
        visit[sr][sc] = tc;
        int len = 0;

        while(Q.size()){
            int cnt = Q.size();
            while(cnt--){
                INFO now = Q.front(); Q.pop();
                INFO next;
                if(now.r == er && now.c == ec) goto END;

                for(int d = 0;  d < 8; ++d){
                    next.r = now.r + dr[d];
                    next.c = now.c + dc[d];
                    if(next.r < 0 || next.c < 0 || next.r >= n || next.c >= n) continue;
                    if(visit[next.r][next.c] == tc)continue;
                    visit[next.r][next.c] = tc;
                    Q.push(next);
                }
            }
            len++;
        }
        END:
        cout << len << '\n';
    }

    return 0;
}