#include<iostream>
#include<queue>
#include<cstring>
const int QS = 6000000;
using namespace std;

int n;
int info[4001][4001];
int map[2001][2001];
int que[QS];
int que2[2000];
struct atom{
    int r,c,d,e;
} atoms[1001];

int dr[4] = {1,-1,0,0};
int dc[4] = {0,0,-1,1};

int SWEA5648(){
    int t;
    cin >> t;
    for(int tc = 1; tc <= t; tc++){
        cin >> n;
    //    queue<int> que;
        
   //     while(que.size()) que.pop();

       // int c = 0;
/*
        for(int i =1; i <= 1000; i++){
            atoms[i].r = 0;
            atoms[i].c = c++;
            atoms[i].d = 0;
            atoms[i].e = 1;
            que.push(i);
            
        }
        */

int f,r;
f = r = 0;

            memset(info, 0, sizeof(info));
        for(int i = 1; i <= n; i++){
            cin >>atoms[i].c >>  atoms[i].r >> atoms[i].d >> atoms[i].e;
            atoms[i].c = atoms[i].c*2 + 2000;
            atoms[i].r = atoms[i].r*2 + 2000;

            que[r++] = i;
            //que.push(i);
        }

        int res = 0;

        while(f!=r){
            int cnt = r-f;

            int f2 , r2;
            f2 = r2 = 0;
            
            while(cnt--)
            {
                //int i = que.front();
                int i = que[f++];
                //que.pop();

                //info[atoms[i].r][atoms[i].c] = 0;

                if(atoms[i].e == 0) continue;

                int &d = atoms[i].d;

                atoms[i].r += dr[d];
                atoms[i].c += dc[d];

                if(atoms[i].r < 0 || atoms[i].r > 4000 || atoms[i].c < 0 || atoms[i].c> 4000){
                    atoms[i].e = 0;
                    continue;
                }
                
                if(info[atoms[i].r][atoms[i].c]){
                    int boom = info[atoms[i].r][atoms[i].c];
                    res += atoms[boom].e + atoms[i].e;
                    atoms[boom].e = 0;
                    atoms[i].e = 0;
                }

                else{
                    info[atoms[i].r][atoms[i].c] = i;
                    que[r++] = i;
                    que2[r2++] = i;
                }
            }
            
            while(r2!=f2){
                int now = que2[f2++];
                info[atoms[now].r][atoms[now].c] = 0;
            }
        }
        //printf("#%d %d\n", tc, res);
        cout << '#' << tc << ' ' << res << '\n';
    }
    return 0;
}
