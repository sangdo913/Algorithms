#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;
#define ABS(x) ((x) > 0? (x) :-(x))
#define MIN(x,y) ((x) >(y) ? (y) : (x))
#define INF 20000000000000LL;

int arr[2001];
long long dp[2000][2000];
long long dp2[2000][2000];
int n;
vector<int> zip;

int main(){
    freopen("0Text.txt", "r", stdin);
    cin >> n;
    for(int i =0; i < n; ++i){
        cin >> arr[i];
        zip.push_back(arr[i]);
    }
    sort(zip.begin(), zip.end());
    zip.resize(unique(zip.begin(), zip.end()) - zip.begin());

    for(int i = 0; i < n; ++i){
        arr[i] = find(zip.begin(), zip.end(), arr[i]) - zip.begin();
    }

    int nn = zip.size()-1;
    dp[0][0] = ABS(zip[0]-zip[arr[0]]);
    dp2[0][0] = ABS(zip[nn]- zip[arr[0]]);
    for(int i = 1; i <= nn; ++i){
        int rev = nn-i;
        dp[0][i] = MIN(dp[0][i-1], ABS(zip[i] - zip[arr[0]]));
        dp2[0][i] = MIN(dp2[0][i-1], ABS(zip[rev] - zip[arr[0]]));
    }

    for(int i = 1; i < n; ++i){
        dp[i][0] = dp[i-1][0] + ABS(zip[arr[i]] - zip[0]);
        dp2[i][0] = dp2[i-1][0] + ABS(zip[arr[i]] - zip[n-1]);
        for(int j = 1; j <= nn; ++j){
            int rev = nn-j;
            dp[i][j] = MIN(dp[i-1][j] + ABS(zip[arr[i]] - zip[j]), dp[i][j-1]);
            dp2[i][j] = MIN(dp2[i-1][j] + ABS(zip[arr[i]] - zip[rev]), dp2[i][j-1]);
        }
    }
    return !(cout << MIN(dp2[n-1][nn], dp[n-1][nn]));
}