#include<iostream>
#define MAX(x,y) ((x) >(y) ? (x) : (y))
#define MIN(x,y) ((x) > (y) ? (y) : (x))
int mmax[200002];
int mmin[200002];

using namespace std;

int main(){
    freopen("0Text.txt", "r",stdin);
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, q;
    cin >> n >> q;
    int bn = 1;
    while(bn < n) bn <<=1; bn--;
    for(int i = 1; i <= bn+n; ++i) mmax[i] = 0, mmin[i] = 0x3f3f3f3f;

    for(int i  = 1; i <= n; ++i){
        int x ; 
        cin >> x;
        for(int j = bn + i; j; j>>=1){
            mmin[j] = MIN(mmin[j], x);
            mmax[j] = MAX(mmax[j], x);
        }
    }

    while(q--){
        int l, r;
        cin >> l >> r;
        l+= bn, r+=bn;
        int m ,M;
        m = 0x3f3f3f3f;
        M = 0;

        while(l<=r){
            if(l == r){
                m = MIN(mmin[l], m);
                M = MAX(mmax[l], M);
                break;
            }
            if(l & 1){
                m = MIN(mmin[l], m);
                M = MAX(mmax[l], M);
            }
            if(!(r&1)){
                m = MIN(mmin[r], m);
                M = MAX(mmax[r], M);
            }
            l = (l+1)>>1;
            r = (r-1) >> 1;
        }
        cout << M-m <<'\n';
    }

    return 0;
}