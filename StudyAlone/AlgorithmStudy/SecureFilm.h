#include<cstdio>
#include<cstring>

int d, w, k;
int film[13][20];
int changed[13];
bool check(int num){
    int numA = 0, numB = 0;
    int c = changed[0] == -1 ? film[0][num] : changed[0];

    if(c == 0){
        numA = 1;
    }
    else{
        numB = 1;
    }
    int ret = 0;
    for(int i = 1; i < d; i++){
        int check= changed[i] == -1 ? film[i][num]:changed[i];
        if(check == 0) {
            numA++;
            numB = 0;
            ret = ret > numA ? ret : numA;
        }
        else{
            numB++;
            numA = 0;
            ret = ret > numB? ret : numB;
        }
    }

    return ret >= k;
}
bool change(int cnt,int visit){
    for(int i = 0; i < (1 << cnt); i++){
        memset(changed, -1, sizeof(changed));

        int bit = i;
        int tvisit = visit;
        for(int idx = 0; idx < d; idx++){
            if(tvisit & 1){
                changed[idx] = bit&1;
                bit >>= 1;
            }
            tvisit >>= 1;
        }    
        bool can = true;
        for(int n = 0; n < w; n++){
            if(!check(n)) {
                can = false;
                break;
            }
        }
        if(can) return true;
    }
    return false;
}

int getZeros(int i){
    int idx = 0;
    while((i & 1) == 0){
        idx++;
        i >>= 1;
    }
    return idx;
}
int SecureFilm(){
    int t;
    scanf("%d\n", &t);

    for(int tc = 1; tc <= t; tc++){
        scanf("%d %d %d\n", &d, &w, &k);

        for(int i = 0; i < d; i++){
            for(int j = 0; j < w; j++){
                scanf("%d\n", &film[i][j]);
            }
        }
        int res = d;

        memset(changed, -1, sizeof(changed));
        bool pass = true;
        for(int i = 0; i < w; i++){
            if(check(i)) continue;
            pass = false;
            break;
        }

        if(pass){
            printf("#%d 0\n", tc);
            continue;
        }
        for(int i = 1; i < d && res == d; i++){
            int visit = (1 << i) - 1;
            while(visit < (1<<d)){
                if(change(i,visit)) {
                    res = i;
                    break;
                }
                int temp = (visit | ((visit & -visit)-1));
                visit = (temp + 1) | (((~temp & -~temp)-1) >> (getZeros(visit)+1));
            }
        }
        printf("#%d %d\n", tc, res);
    }
    return 0;
}