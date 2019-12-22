#include<iostream>

using namespace std;

int onepan[52][50];
int deleted[52][50];
int turn[52];
int n,m, t;
int myturn;
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};

double mycheck(){
    int ret = 0;
    int nums = 0;
    bool flag = false;
    for(int i = 1; i <=n; ++i){
        for(int j = 0; j < m; ++j){
            int now = onepan[i][((j+turn[i]%m)+m)%m];
            int &del = deleted[i][((j+turn[i]%m)+m)%m];
            if(!del){
                ret += now;
                nums++;
                for(int d = 0; d < 4; ++d){
                    int &ndel = deleted[i + dr[d]][((j+dc[d]+turn[i + dr[d]])%m+m)%m];
                    if(!ndel || ndel == myturn){
                        int& v = onepan[i + dr[d]][((j+dc[d]+turn[i + dr[d]])%m+m)%m];
                        if(v == now){
                            del = ndel = myturn;
                            flag = true;
                        }
                    }
                }
            }
        }
    }
    return flag ? -1.0 : 1.0*ret / nums;
}

int main(){
    freopen("0Text.txt", "r", stdin);
    cin >> n >> m >> t;
    int allsum = 0;
    for(int j = 0; j <m; ++j) {
        deleted[0][j] = deleted[n+1][j] = true;
    }
    for(int i = 1; i <= n; ++i){
        for(int j = 0; j < m; ++j) cin >> onepan[i][j];
    }
    for(myturn = 1; myturn <= t; ++myturn){
        int x,d,k;
        cin >> x >> d >> k;
        for(int i = x; i <= n; i+=x){
            turn[i] += d ? k : -k;
            turn[i] %= m;
        }
        double res = mycheck();
        if(res != -1.0){
            for(int i = 1; i <= n; ++i) for(int j = 0; j < m; ++j){
                if(!deleted[i][j]){
                    if(res > (double)onepan[i][j]) onepan[i][j]++;
                    else if(res < (double)(onepan[i][j])) onepan[i][j]--;
                }
            }
        }
    }
    int sum = 0;
    for(int i =1; i <= n; ++i) for(int j= 0; j< m; ++j) if(!deleted[i][j])sum += onepan[i][j];
    return !(cout << sum);
}