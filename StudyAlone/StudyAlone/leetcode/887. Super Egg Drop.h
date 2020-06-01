#define MAX(x,y) ((x) > (y) ? (x) : (y))  
bool isfirst = 1;
int dp[101][10001];
class Solution {
public:
    int superEggDrop(int K, int N) {
        if(isfirst) {
            isfirst = !isfirst;
            for(int i=1; i <= 10000; ++i) dp[1][i] = i;
            for(int k = 2; k <= 100; ++k){
                int cur = 1;
                for(int n = 1; n <= 10000; ++n){
                    int mmin = 0x3f3f3f3;
                        while(cur<= n) {
                            int num = MAX(dp[k-1][cur-1], dp[k][n-cur]);
                            if( num +1 < mmin) mmin = num+1, cur++;
                            else break;
                        }
                    dp[k][n] = mmin;
                    cur--;
                }
            }
        }
       return dp[K][N];
}
};