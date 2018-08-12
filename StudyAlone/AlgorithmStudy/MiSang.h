#include<cstdio>
#include<cstring>
int n,m, k;
int info[100][100][2];

struct infos{
    int direct;
    int num;
    int cod[2];
} sangs[1001];

int dr[5] = {0, -1, 1, 0,0};
int dc[5] = {0,0,0,-1,1};
int conv[5] = {0, 2,1,4,3};
bool isOut(int r, int c){
    return r == 0 || r == n-1 || c == 0 || c== n-1; 
}

int MiSang(){
    int t;
    scanf("%d\n", &t);

    for(int tc = 1; tc <= t; tc++){
        scanf("%d %d %d\n", &n, &m, &k);

        for(int i = 1; i <= k; i++){
            scanf("%d %d %d %d\n", &sangs[i].cod[0], &sangs[i].cod[1], &sangs[i].num, &sangs[i].direct);
        }

        while(m--){
            memset(info, 0, sizeof(info));

            for(int i = 1; i <= k; i++){
                infos &m = sangs[i];
                
                if(m.num == 0) continue;

                m.cod[0] += dr[m.direct];
                m.cod[1] += dc[m.direct];
                if(isOut(m.cod[0], m.cod[1])){
                    m.direct = conv[m.direct];
                    m.num >>= 1;
                }
                
                if(info[m.cod[0]][m.cod[1]][0]){
                    int idx = info[m.cod[0]][m.cod[1]][0];
                    sangs[idx].num+= m.num;
                    if(info[m.cod[0]][m.cod[1]][1] < m.num){
                        info[m.cod[0]][m.cod[1]][1] = m.num;
                        sangs[idx].direct = m.direct;
                    }
                    m.num = 0;
                }
                else{
                    info[m.cod[0]][m.cod[1]][0] = i;
                    info[m.cod[0]][m.cod[1]][1] = m.num;
                }
            }
        }
        int res = 0;
        for(int i = 1; i <= k; i++) res += sangs[i].num;
        printf("#%d %d\n", tc, res);
    }
} 


