#include<iostream>

using namespace std;

int arr[100001];
int sums[200001];
int n, m;
#define MIN(x,y) ((x) > (y) ? (y) : (x))

void insertsum(int i){
    while(i){
        sums[i]++;
        i -= i&-i;
    }
}

int getsum(int i){
    int ret =0;
    while(i <= 2*n){
        ret += sums[i];
        i += i&-i;
    }
    return ret;
}

int main(){
    ios_base::sync_with_stdio(0), cout.tie(0), cin.tie(0);
    freopen("0Text.txt", "r", stdin);
    cin >> n >> m;
    for(int i = 0; i < n; ++i){
        cin >> arr[i];
        arr[i] =arr[i] < m ? 1 : -1;
    }
    long long res = 0;
    int p = n;
    for(int i = 0; i < n; ++i){
        insertsum(p);
        p += arr[i];
        res += getsum(p);
    }
    
    cout << res;

    return 0;
}