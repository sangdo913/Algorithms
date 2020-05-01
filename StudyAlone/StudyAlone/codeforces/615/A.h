#include<iostream>
#define MAX(x,y) ((x) > (y) ? (x) : (y))

using namespace std;

int main(){
    freopen("0Text.txt", "r", stdin);
    int a,b,c,n;
    int T;
    cin >> T;
    for(int tc = 0; tc < T ; ++tc){
        cin >> a >> b >> c >> n;
        int mmax = a;
        mmax = MAX(mmax, b);
        mmax = MAX(mmax,c);
        n -= mmax - a;
        n -= mmax - b;
        n -= mmax - c;
        if(n < 0 || n%3 != 0) cout <<"NO\n";
        else cout << "YES\n";
    }

    return 0;
}