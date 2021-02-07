#include<iostream>
#include<cstdio>
using namespace std;
int abc[200000][3];
int main(){
    freopen("0Text.txt", "r", stdin);
    int n;
    cin >> n;
    long long res =0;
    int s = 1, e = 2147483647;
    for(int i = 0; i < n; ++i) {
        long long a,b,c;
        cin >> a >> b >> c;
        abc[i][0] = a;
        abc[i][1] = b;
        abc[i][2] = c;
    }
    while(s<e) {
        int m = ((long long)s + e)/2;
        long long allsum = 0;
        for(int i = 0;  i < n; ++i) {
            int a = abc[i][0];
            int b = abc[i][1];
            int c = abc[i][2];
            if(m < a) continue;
            if(b > m) b = m;
            allsum += (b-a)/c + 1;
        }
        if(allsum & 1) e = m;
        else s = m+1;
    }
    int num = 0;
    for(int i = 0; i < n; ++i){
        if(s < abc[i][0] || abc[i][1] < s) continue;
        if((s-abc[i][0])%abc[i][2]) continue;
        num++;
    }
    if(!num) cout << "NOTHING\n";
    else cout << e << ' ' << num << endl;
    return 0;
}