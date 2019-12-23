#include<iostream>

using namespace std;
int n;
int myscore[50][9];
int order[9];
int mymax;
int isin[9] = {};
int query;

int getscore(int a, int rusu[4]){
    int ret = a==4;
    a -= a==4;
    int j;
    for(j = 0; j < a; ++j){
        if(rusu[2-j] != -1){
            ret++;
            isin[rusu[2-j]] = 0;
            rusu[2-j] = -1;
        }
    }
    for(j; j < 3; ++j){
        if(rusu[2-j] != -1){
            rusu[2-j+a] = rusu[2-j];
            rusu[2-j] = -1;
        }
    }
    return ret;
}

int simulation(){
    int rusu[4] = {};
    int score = 0;
    int turn = 0;
    for(int i = 0 ; i < n; ++i){
        query++;
        for(int i = 0; i < 3; ++i) rusu[i] = -1;

        int out = 0;
        while(out != 3){
            while(isin[order[turn]] == query) turn = ++turn %9;
            int res = myscore[i][order[turn]];
            if(res) {
                score += getscore(res, rusu);
                rusu[res-1] = order[turn];
                isin[order[turn]] = res != 4 ? query : 0;
            }
            else{
                out++;
            }
            turn = ++turn%9;
        }
    }
    return score;
}

int getres(int l,int visit){
    if(l == 9){
        return simulation();
    }

    int ret = 0;

    if(l == 3){
        order[3] = 0;
        return getres(l+1, visit | 1);
    }

    for(int i = 1; i < 9; ++i){
        if(visit & (1<<i)) continue;
        order[l] = i;
        int res = getres(l+1, visit | (1<<i));
        ret = res < ret ? ret : res;
    }
    return ret;
}

int main(){
    freopen("0Text.txt", "r", stdin);
    cin >> n;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < 9 ; ++j) cin >> myscore[i][j];
    }
    return !(cout << getres(0,0));
}