#include<iostream>
#include<queue>
#include<tuple>
#include<cstring>

using namespace std;
#define ABS(x) ((x) > 0 ? (x) : -(x))
#define MIN(x,y) ((x) > (y) ? (y) : (x))

int check[3][20001];

int main(){
    freopen("0Text.txt", "r", stdin);
    int tc;
    cin >> tc;
    int ch = 1;
    while(tc--){
        ch++;
        priority_queue<tuple<int ,int, int, int, int>> pq;
        int a[4], b[3], cnt, now;
        int nn[3];
        cin >> a[0] >> a[1] >> a[2];
        memset(check,0x3f,sizeof(check));

        int res = 0x3f3f3f3f;
        for(int i = 1; i <= 10000; ++i){
            int cnt = ABS(i - a[0]);
            if(check[0][i] > cnt){
                check[0][i] = cnt;
                pq.push({-cnt, 1,i,a[1],a[2]});
            }
        }
        while(!pq.empty()){
            tie(cnt, now, b[0],b[1], b[2]) = pq.top(); pq.pop();
            cnt = -cnt;
            if(now == 3){
                cout << cnt << '\n';
                cout << b[0] << ' ' << b[1] << ' ' << b[2] << '\n';
                break;
            }
            for(int i = 0; i < 3; ++i) nn[i] = b[i];
            int nxt = b[now-1];
            int temp = nxt;
            while(nxt <= 20000){
                nn[now] = nxt;
                int cnt = 0;
                for(int i = 0; i < 3; ++i) cnt+= ABS(a[i] - nn[i]);
                if(check[now][nxt] > cnt){
                    check[now][nxt] = cnt;
                    pq.push({-cnt, now+1, nn[0], nn[1], nn[2]});
                }
                nxt+=temp;
            }
        }
    }
    return 0;
}