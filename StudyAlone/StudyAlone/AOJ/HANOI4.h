#include<iostream>
#include<queue>

using namespace std;
struct info{
    unsigned long long bit;
    int cnt;
};
int visit[20000000] = {};
char tcvisit[20000000] = {};
int stateToBit(int state[4][12], int num[4]){
    int ret = 0;
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < num[i]; ++j){
            ret |= i << ((state[i][j]-1)*2);
        }
    }
    return ret;
}

void BitToState(int n, int state[4][12], int num[4], int bit){
    num[0] = num[1] = num[2] = num[3] = 0;
    for(int i = n-1; i >= 0; --i){
        int pos = (bit >> (i*2))&3;
        state[pos][num[pos]++] = i+1;
    }
}

#define ABS(x) ((x) > 0 ? (x) : -(x))

int main(){
    freopen("0Text.txt", "r", stdin);
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int bitstate, endbitstate;
    int C;
    cin >> C;
    int state[4][12];
    int num[4];

    int endstate[4][12] = {0,};
    int endnum[4];

    for(int tc = 1; tc <= C; ++tc){
        int n;
        cin >> n;
        queue<int> Q;

        for(int i = 0; i < 4; ++i){
            cin >> num[i];
            for(int j = 0; j < num[i]; ++j){
                cin >> state[i][j];
            }
        }
        // for(int i = 0; i < 4; ++i){
        //     cin >> endnum[i];
        //     for(int j = 0; j < endnum[i]; ++j){
        //         cin >> endstate[i][j];
        //     }
        // }
        endnum[0] = endnum[1] = endnum[2] = 0;
        endnum[3] = n;

        for(int i = 0; i < n; ++i) endstate[3][n-1-i] = i+1;
        bitstate = stateToBit(state, num);
        endbitstate= stateToBit(endstate, endnum);

        visit[bitstate] = 1;
        tcvisit[bitstate] = tc;
        visit[endbitstate] = -1;
        tcvisit[endbitstate] = tc;

        Q.push(bitstate);
        Q.push(endbitstate);

        while(!Q.empty()){
                int now = Q.front(); Q.pop();

                BitToState(n, state,num, now);

                for(int i = 0; i < 4; ++i){
                    if(num[i] == 0) continue;
                    int top = state[i][num[i]-1];
                    for(int j = 0; j < 4; ++j){
                        if(i == j) continue;
                        if(num[j] && state[j][num[j]-1] < top ) continue;
                        bitstate = now & ~(3 << ((top-1)*2));
                        bitstate |= j <<((top-1)*2);
                        int v;
                        if(tcvisit[bitstate] != tc){
                            tcvisit[bitstate] = tc;
                            int nextcnt;
                            if(visit[now] < 0)  nextcnt = visit[now] - 1;
                            else nextcnt = visit[now]+1;

                            visit[bitstate] = nextcnt;
                            Q.push(bitstate);
                        }
                        else if(((v = visit[now]) * visit[bitstate]) < 0){
                            cout << ABS(v) + ABS(visit[bitstate]) -1 << '\n';
                            goto TCEND;
                        }
                    }
                }
        }
        TCEND:
        int x = 1;
    }
    return 0;
}