#include<iostream>
#include<queue>

using namespace std;
#define MIN(x,y) ((x) > (y) ? (y) : (x))
#define MID 1000000
int visit[2*MID];
int tcvisit[2*MID];

int main(){
    freopen("0Text.txt", "r", stdin);
    int C;
    int tc = 0;
    cin >> C;
    while(C--){
        int n;
        tc++;
        cin >> n;
        vector<int> info[2];
        info[0].resize(n);
        info[1].resize(n);

        int flag = 0;
        for(int i = 0; i < n; ++i){
            cin >> info[0][i] >> info[1][i];
        }

        priority_queue<pair<int,pair<int,int>>> pq;
        for(int i = 0; i < n; ++i){
            int diff = info[0][i] - info[1][i] + MID;
            int mmin = MIN(info[0][i], info[1][i]);
            if(tcvisit[diff] != tc || (tcvisit[diff] == tc && visit[diff] > mmin)){
                tcvisit[diff] = tc;
                visit[diff] = mmin;
                pq.push({-mmin,{info[0][i], info[1][i]}});
            }
        }

        bool isfind = false;
        while(!pq.empty()){
            pair<int, pair<int, int>> now = pq.top(); pq.pop();
            int a = now.second.first;
            int b = now.second.second;
            if(a == b){
                cout << a << '\n';
                isfind = true;
                break;
            }
            for(int i = 0; i < n; ++i){
                int na = a + info[0][i];
                int nb = b + info[1][i];
                int diff = na-nb + MID;
                int df = na-nb;
                df = df > 0 ? df : -df;
                if(df > 200) continue;
                int mmin = MIN(na, nb);
                if(tcvisit[diff] != tc || (tcvisit[diff] == tc && visit[diff] > mmin)){
                    tcvisit[diff] = tc;
                    visit[diff] = mmin;
                    pq.push({-mmin,{na,nb}});
                }
            }
        }
        if(!isfind) cout << "IMPOSSIBLE\n";
    }

    return 0;
}