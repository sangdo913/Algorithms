#include<iostream>
#include<string.h>

using namespace std;
int n;
int arr[2001];
int sum[27][2002];
int sum2[27][2002];

int main(){
    freopen("0Text.txt","r",stdin);
    int t;
    cin >> t;
    while(t--) {
        cin >> n;
        for(int i = 1; i <= n+1; ++i) for(int j = 1; j <= 26; ++j) sum[j][i] = 0, sum2[j][i] = 0;
        for(int i = 1; i <= n; ++i) {
            cin >> arr[i];
            for(int j = 1; j <= 26; ++j) sum[j][i] = sum[j][i-1];
            sum[arr[i]][i]++;
        }
        for(int i = n; i >= 1; --i){
            for(int j = 1; j <= 26; ++j){
                sum2[j][i] = sum2[j][i+1];
            }
            sum2[arr[i]][i]++;
        }

        int res = 1;
        for(int i = 1; i <= 26; ++i){
            int st = 1;
            int ed = n;
            int dst = 1;
            while(true){
                while(st <= n && sum[i][st] !=dst) st++;
                while(ed >= 1 && sum2[i][ed] != dst) ed--;
                if(ed <= st) break;
                if(res < dst *2) res = dst*2;
                if(st + 1 <= ed -1){
                    int mmax = 0;
                    for(int k = 1; k <= 26; ++k){
                        int temp = sum[k][ed-1] - sum[k][st] + dst*2;
                        if(mmax < temp) mmax = temp;
                    }
                    if(res < mmax) res = mmax;
                }
                dst++;
            }
        }
        cout << res << '\n';
    }
    return 0;
}