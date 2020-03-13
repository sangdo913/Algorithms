#include<iostream>

using namespace std;
int arr[100000];
int arr2[100000];

int main(){
    freopen("0Text.txt", "r", stdin);
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> arr[i];
    }

    int res = n == 1 ? 0 : 0x3f3f3f3f;

    for(int k = -1; k <= 1; ++k){
        arr2[0] = arr[0] + k;
        for(int i = -1; i <= 1; ++i){
            int cnt = 0;
            cnt += (k!=0) +(i !=0);
            arr2[1] = arr[1] + i;
            int diff = arr2[1]- arr2[0];
            for(int j = 2; j < n; ++j){
                if(arr[j] - arr2[j-1] == diff+1) {
                    arr2[j] = arr[j] -1;
                    cnt++;
                }
                else if(arr[j] - arr2[j-1] == diff-1){
                    arr2[j] = arr[j] + 1;
                    cnt++;
                }
                else if(arr[j] - arr2[j-1] == diff){
                    arr2[j] = arr[j];
                }
                else cnt = 0x3f3f3f3f;
            }
            if(res > cnt) res = cnt;
        }
    }
    if(res == 0x3f3f3f3f) cout << -1 ;
    else cout << res;
    return 0;
}