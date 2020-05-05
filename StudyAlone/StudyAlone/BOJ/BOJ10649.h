#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;
int info[20][3];
int idx[20];
int n,h;
#define MIN(x,y) ((x) > (y) ? (y) : (x))
#define MAX(x,y) ((x) > (y) ? (x) : (y))
enum INFO {L, W, F};
bool cmp(int a, int b){
    return info[a][W] + info[a][F] > info[b][W] + info[b][F];
}
int res = -1;

void getdp(int i, int t, int s){
    if(t >= h){
        res = MAX(s, res);
        return;
    }
    if(i == n) return;
    int ii = idx[i];
    if(s >= info[ii][W]) getdp(i+1, t+info[ii][L], MIN(s - info[ii][W], info[ii][F]));
    getdp(i+1, t, s);
}

int main(){
    freopen("0Text.txt", "r", stdin);
    cin >> n >> h;
    for(int i = 0; i < n; ++i){
        idx[i] = i;
        cin >> info[i][0] >> info[i][1] >> info[i][2];
    }
    sort(idx, idx + n, cmp);
    getdp(0,0,0x3f3f3f3f);
    if(res == -1) cout <<"Mark is too tall\n";
    else cout << res<<'\n';

    return 0;
}