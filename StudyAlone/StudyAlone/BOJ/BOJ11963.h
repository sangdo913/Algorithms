#include<algorithm>
#include<iostream>

using namespace std;
int arr1[25000];
int arr2[25000];
bool check[100001];

int main(){
    freopen("0Text.txt", "r", stdin);
    ios_base::sync_with_stdio(0), cout.tie(0), cin.tie(0);
    int n;
    cin >> n;
    for(int i = 0 ; i < n/2; ++i) {
        cin >> arr1[i];
        check[arr1[i]] = true;
    }
    for(int i = 0; i < n/2; ++i){
        cin >> arr2[i];
        check[arr2[i]] = true;
    }
    sort(arr1, arr1+ n/2);
    sort(arr2, arr2 + n/2);
    int cnt = 0;
    for(int i = 2*n, j = n/2-1; i && j >=0; --i){
        if(check[i]) continue;
        if(i > arr1[j]) cnt++;
        else ++i;
        j--;
    }
    for(int i = 1, j = 0; j < n/2 && i <= 2*n; ++i){
        if(check[i]) continue;
        if(i < arr2[j]) cnt++;
        else --i;
        ++j;
    }
    cout << cnt;

    return 0;
}