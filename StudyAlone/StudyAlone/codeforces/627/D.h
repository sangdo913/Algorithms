//Pair Of Topics
#include<iostream>
#include<algorithm>

using namespace std;
int T[200000];
int S[200000];
int V[200000];

int main(){
    freopen("0Text.txt", "r", stdin);
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> T[i];
    }
    for(int i = 0; i < n; ++i) cin >> S[i];
    for(int i = 0; i < n; ++i) V[i] = T[i] - S[i];
    sort(V, V + n);
    long long res = 0;
    for(int i = 0; i < n; ++i){
        int j = n-(upper_bound(V, V+n, -V[i]) - V) - (V[i] > 0);
        if(j < 0) j = 0;
        res += j;
    }

    cout << res / 2;
    return 0;
}