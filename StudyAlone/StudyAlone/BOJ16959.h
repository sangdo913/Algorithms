#include<iostream>
#include<vector>
#include<queue>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<cstring>

using namespace std;

int dr[3][8] = {
    {-1,1,0,0},{-1,-1,1,1},{-1,-2,-2,-1,1,2,2,1}
};
int dc[3][8] = {
    {0,0,-1,1}, {-1,1,-1,1},{-2,-1,1,2,-2,-1,1,2} };
int dlen[3] = {4, 4, 8};

struct COD{
    int r,c,num, mal;
};

int n;
int arr[10][10];


bool inque[3][10][10][102];
vector<int> vec;
int d;

int Do(){
    d++;
    ios_base::sync_with_stdio(false), cout.tie(0), cin.tie(0);

    srand(time(0)+d);
    queue<COD> que;

    memset(inque,false,sizeof(inque));
    
    n = rand()%8 + 3;
    for(int i = 1; i <= n*n; i++){
        vec.push_back(i);
    }

    COD now, next;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
//        cin >> arr[i][j];
        int v = rand()%vec.size();
        arr[i][j] = vec[v];
        vec.erase(find(vec.begin(), vec.end(), arr[i][j]));
        if(arr[i][j] == 1) now.r = i , now.c =j;
    }
    
    now.num = 2;
    for(int i  =0; i < 3; i++) now.mal = i, que.push(now), inque[now.mal][now.r][now.c][now.num] = true;

    int t = 0;
    cout  << n <<'\n';
    for(int i = 0 ; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << arr[i][j] << ' ';
        }
        cout << '\n';
    }
    cout <<'\n';

    while(que.size()){
        int cnt = que.size();

        while(cnt--){
            now = que.front(); que.pop();
            if(now.num == n*n+1) return!(cout << "res " << t << '\n' << '\n'); 

            for(int d = 0; d < dlen[now.mal]; d++){
                next = now;
                next.r += dr[now.mal][d], next.c += dc[now.mal][d];

                while(0<=next.r && next.r < n && 0<=next.c && next.c < n){
                    next.num = now.num + (arr[next.r][next.c] == now.num);

                    if(!inque[next.mal][next.r][next.c][next.num]){
                        inque[next.mal][next.r][next.c][next.num] = true;
                        que.push(next);
                    } 

                    next.r += dr[now.mal][d], next.c += dc[now.mal][d];

                    if(now.mal == 2) break;
                }
            }

            for(int mal = 0; mal < 3; mal++){
                if(now.mal == mal) continue;
                next = now;
                next.mal = mal;
                if(inque[next.mal][next.r][next.c][next.num]) continue;
                inque[next.mal][next.r][next.c][next.num] = true;
                que.push(next);
            }
        }

        t++;
    }

    cout << "wrong";
    return 0;
}