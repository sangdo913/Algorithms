#include<iostream>

using namespace std;
bool visit[5000001][2];
int Q[5000001*2];

int main(){
    freopen("0Text.txt", "r", stdin);
    int t, a,b;
    cin >> t >> a >> b;
    int fr, re;
    fr = re = 0;
    visit[0][1] = true;
    Q[re++] = 5000001 + 0;
    int mmax = -1;
    while(fr != re){
        int now = Q[fr++];
        int drink = 0;
        if(now > 5000000){
            drink =1;
            now -= 5000001;
        }
        if(mmax < now) mmax = now;
        int next = now+a;
        if(next<= t && !visit[next][drink]){
            visit[next][drink] = 1;
            Q[re++] = next + drink*5000001;
        }
        next = now + b;
        if(next <= t && !visit[next][drink]){
            visit[next][drink] = 1;
            Q[re++] = next + drink*5000001;
        }
        next = now/2;
        if(drink && !visit[next][0]){
            visit[next][0] = 1;
            Q[re++] = next;
        }
    }
    cout << mmax;

    return 0;
}