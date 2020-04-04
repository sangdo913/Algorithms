#include<iostream>
#include<algorithm>

using namespace std;
int a[101];
int p[101];

int check[101][102];
int cnt[101];
int dest[101]={};

int main(){
    freopen("0Text.txt", "r", stdin);
    int tc;
    int ch = 1;
    cin >> tc;
    while(tc--){
        ch++;
        int m , n;
        cin >> n >> m;
        for(int i =1 ; i <= 100; ++i) cnt[i] = 0;
        for(int i = 1; i <= n; ++i) {
            cin >> a[i];
            cnt[a[i]]++;
        }
        for(int i = 1; i <= m; ++i) {
            cin >> p[i];
        }
        sort(p+1, p+ m+1);
        for(int i = 1; i <= m; ++i){ 
            check[p[i]][p[i]+1] = check[p[i]+1][p[i]] = ch;
            for(int j = i+1; j <= m; ++j){
                if(j - i == p[j] - p[i]){
                    check[p[i]][p[j]+1] = ch;
                    check[p[j]+1][p[i]] = ch;
                }
            }
        }
        for(int i = 1; i <= 100; ++i){
            cnt[i] += cnt[i-1];
        }
        int idx = 1;
        for(int i = 1; i <= 100; ++i){
            int c = cnt[i]-cnt[i-1];
            while(c--){
                dest[idx++] = i;
            }
        }
        for(int i = n; i; --i){
            while(dest[i] != a[i]){
                int dest = cnt[a[i]]--;
                if(ch != check[i][dest]) goto FAIL;
                int temp = a[dest];
                a[dest] = a[i];
                a[i] = temp;
            }
        }
        cout << "YES\n";
        continue;
        FAIL:
        cout <<"NO\n";
    }

    return 0;
}