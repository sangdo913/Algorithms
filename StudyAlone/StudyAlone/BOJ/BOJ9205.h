#include<iostream>

using namespace std;

int pos[102][2];
int visit[102];
int Q[102];
#define ABS(x) ((x) > 0 ? (x) : -(x))

int main(){
    freopen("0Text.txt", "r", stdin);
    int T;
    cin >> T;
    for(int tc = 1; tc <= T; ++tc){
        int fr, re;
        fr = re = 0;
        int n;
        cin >> n;
        int x, y;
        for(int i = 0; i < n+2; ++i){
            cin >> pos[i][0] >> pos[i][1];
        }
        Q[re++] = 0;
        visit[0] = tc;
        while(fr != re){
            int now = Q[fr++];
            if(now == n+1){
                cout << "happy\n";
                goto END;
            }
            for(int i = 1; i <= n+1; ++i){
                if(visit[i] == tc) continue;
                if(ABS(pos[i][0]-pos[now][0]) + ABS(pos[i][1]-pos[now][1]) > 1000) continue;
                visit[i] = tc;
                Q[re++] = i;
            }
        }
        cout << "sad\n";
        END:
        int d =1;
    }

    return 0;
}
