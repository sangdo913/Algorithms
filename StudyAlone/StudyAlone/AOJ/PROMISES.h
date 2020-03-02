#include<iostream>
#define MIN(x,y) ((x) > (y) ? (y) : (x))

using namespace std;

int dist[200][200];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0), cout.tie(0);
    freopen("0Text.txt", "r", stdin);

    int C;
    cin >> C;

    while(C--){
        int v , m, n;
        cin >> v >> m >> n;
        for(int i = 0; i < v; ++i){
            for(int j = 0; j < v; ++j){
                dist[i][j] = 0x3f3f3f3f;
            }
            dist[i][i] = 0; 
        }

        int f, t, c;
        while(m--){
            cin >> f >> t >> c;
            if(dist[f][t] > c){
                dist[f][t] = dist[t][f] = c;
            }
        }
        for(int k = 0; k < v; ++k){
            for(int i = 0; i < v; ++i){
                if(dist[i][k] == 0x3f3f3f3f) continue;
                for(int j = 0; j <v; ++j){
                    dist[i][j] = MIN(dist[i][k] + dist[k][j], dist[i][j]);
                }
            }
        }

        int res =0;
        while(n--){
            cin >> f >> t >> c;
            if(dist[f][t] > c){
                dist[f][t] = dist[t][f] = c;
                for(int i = 0; i < v; ++i){
                    for(int j = i + 1; j < v; ++j){
                        int d = MIN(dist[i][f] + dist[t][j] +c, dist[i][t] + dist[f][j] + c);
                        if(d < dist[i][j]){
                            dist[i][j] = dist[j][i] = d;
                        }
                    }
                }
            }
            else res++;
        }
        cout << res << '\n';
    }
    return 0;
}