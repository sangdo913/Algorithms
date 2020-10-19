#include<iostream>
#include<algorithm>
#include<cmath>

using namespace std;

int main(){
    freopen("0Text.txt", "r", stdin);
    int t;
    cin >> t;
    while(t--){
        long long a,b,x,y,n;
        cin >> a >> b >> x >> y >> n;
        long long ta, tb, tn;
        tn = n;
        ta = a;
        tb = b;
        if(a -x < tn){
            ta = x, tn -= (a-x);
        }
        else ta -= tn, tn = 0;
        if(b - y < tn){
            tb = y;
        }
        else tb -= tn;
        long long res1 = ta*tb;
        tn = n;
        ta = b;
        tb = a;
        if(b -y < tn){
            ta = y, tn -= (b-y);
        }
        else ta -= tn, tn = 0;
        if(a - x < tn){
            tb = x;
        }
        else tb -= tn;
        res1 = min(res1, ta*tb);
        cout << res1 << endl;
    }
}