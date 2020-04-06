#include<iostream> 
#include<algorithm>
using namespace std;
int n,a,b,k;
int arr[200001];
int r[200001];

int main(){
    freopen("0Text.txt", "r", stdin);
    cin >> n >> a >> b >> k;
    int res = 0;
    int rnum = 0;
    for(int i = 0; i < n; ++i) {
        cin >> arr[i];
        int remain = arr[i]%(a+b);
        if(remain && remain <= a) res++;
        else{
            if(remain == 0) remain = a+b;
            remain -= a;
            r[rnum++] = (remain + a-1) / a;
        }
    }

    sort(r, r+rnum);
    for(int i = 0; i < rnum; ++i){
        if(k - r[i] < 0) break;
        k-= r[i];
        res++;
    }
    cout << res << endl;
    
    return 0;
}