#include<iostream>
#include<string.h>
#define MAX(x,y) ((x) < (y) ? (y) : (x))
#define MIN(x,y) ((x) > (y) ? (y) : (x))

using namespace std;
int dist[2][501][501];
int drunkencheck[501];

int main(){
    freopen("0Text.txt", "r", stdin);
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int v, e;
    cin >> v >> e;
    for(int i = 1; i <= v; ++i){
        cin >> drunkencheck[i];
    }
    memset(dist, 0x3f, sizeof(dist));

    for(int i = 1; i <=v; ++i){
        for(int j = 0; j <= 100; ++j) dist[j][i][i] = 0;
    }

    while(e--){
        int f, t, d;
        cin >> f >> t >> d;
        if(dist[0][f][t] > d){
            for(int i = 0; i < 101; ++i) dist[i][f][t] = d;
        }
    }

    for(int k = 1; k <= v; ++k){
        for(int i = 1; i <= v; ++i){
            for(int l = 0; l <= 100; ++l){
                for(int j = 1; j <= v; ++j){
                }
            }
        }
    }

    int T;
    cin >> T;
    while(T--){
        int f,t ;
        cin >> f >> t;
        cout << dist[1][f][t] << '\n';
    }

    return 0;
}