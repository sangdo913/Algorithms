//6782. 현주가 좋아하는 제곱근 놀이
//https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWgqsAlKr9sDFAW0&categoryId=AWgqsAlKr9sDFAW0&categoryType=CODE
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;
vector<long long> pows;

int Do(){
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    
    for(long long int i = 0; i*i <= 1e12; i++){
        pows.push_back(i*i);
    }
    vector<long long> dp(pows.size());

    dp[0] = 0;dp[1] = 1; dp[2] = 1;

    long long num;
    long long idx, dst;

    for(int i =3; i < dp.size(); i++){
        num = i;
        idx = lower_bound(pows.begin(), pows.end(),num) - pows.begin();

        dp[i] = idx*idx -i +  dp[idx] + 1;
    }
    int t; cin >> t;
    
    for(int tc = 1; tc <= t; tc++){
        long long n;
        cin >> n;
        if(n == 2){
            cout << '#' << tc << ' ' << 0 << '\n';
            continue;
        }
        idx = lower_bound(pows.begin(), pows.end(), n) - pows.begin();
        long long cnt = idx*idx - n; 
        cout << '#' << tc <<' '  << cnt + dp[idx] << '\n';
    }
    return 0;
}