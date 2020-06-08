#include<iostream>

using namespace std;
int blue[4][7];
int green[4][7];
//block1 : 1x1
//block2 : 1x2
//block3 : 2x1

struct COD{
    int x,y;
    int t;
};
enum TYPE {G, B};
int table[2][4] = {{0,1,3,2}, {0,1,2,3}};

COD conv(TYPE t, int b, int x, int y){
    COD res;
    if(t == G){
       res.x = 3-y - (b == 2);
       res.y = 0; 
       res.t = table[t][b];
    }
    else{
        res.x = x;
        res.y = 0;
        res.t = b;
    }
    return res;
}

int blocksize[5] = {0,1,1,2,0};
int blockinfo[5][2][2] = {{},{{0,0}},{{0,0}, {0,1}}, {{0,0}, {1,0}}};

void blockdown(int map[4][7], COD b){
    int j = b.y;
    while(true) {
        if(j == 5) break;
        for(int i = 0; i < blocksize[b.t]; ++i){
            int x = b.x + blockinfo[b.t][i][0];
            int y = j+1 + blockinfo[b.t][i][1]; 
            if(map[x][y] != 0) goto END;
        }
        j++;
    }
    END:
    map[b.x][j] = b.t;
    for(int i =1; i < blocksize[b.t]; ++i){
        int x = b.x + blockinfo[b.t][i][0];
        int y = j + blockinfo[b.t][i][1];
        map[x][y] = 4;
    }
}

void mymove(int map[4][7]){
    int res = 0;
    for(int j = 5; j >= 0; --j){
        for(int i = 0; i < 4 ;++i){
            if(map[i][j] && map[i][j] < 4){
                COD b = {i,j, map[i][j]};
                for(int i =0; i < blocksize[b.t]; ++i){
                    int x = b.x + blockinfo[b.t][i][0];
                    int y = b.y + blockinfo[b.t][i][1];
                    map[x][y] = 0;
                }
                blockdown(map,b);
            }
        }
    }
}
bool myremove2(int map[4][7]){
    int line = 0;
    bool res = 0;
    for(int j = 0; j < 2; ++j){
        for(int i = 0; i < 4; ++i){
            if(map[i][j] != 0){
                line++;
                res = 1;
                break;
            }
        }
    }
    for(int j = 5; line; --line, --j){
        for(int i = 0; i < 4; ++i) map[i][j] = 0;
    }
    return res;
}

int myremove(int map[4][7]){
    int score = 0;
    for(int j = 5; j >= 0; --j){
        int num = 0;
        for(int i = 0; i < 4; ++i){
            num += map[i][j] != 0; 
        }
        if(num == 4){
            score++;
            for(int i = 0; i < 4; ++i) map[i][j] = 0;
        }
    }
    return score;
}

int main(){
    freopen("0Text.txt", "r", stdin);
   int n;
   cin >> n;
   int score = 0;
   for(int i = 0; i < 4; ++i) green[i][6] = blue[i][6] = 1;
   for(int i = 0; i < n; ++i){
       int t, x,y;
       cin >> t >> x >> y;
       COD b = conv(G,t,x,y);
        green[b.x][b.y] = b.t;
        if(b.t == 2) green[b.x][b.y+1] = b.t;
        while(1){
            mymove(green);
            int ret = myremove(green);
            mymove(green);
            bool removed = myremove2(green);
            score += ret;
            if(!ret && !removed) break;
        }
        b = conv(B,t,x,y);
        blue[b.x][b.y] = b.t;
        if(b.t == 2) blue[b.x][b.y+1] = b.t;
        while(1){
            mymove(blue);
            int ret = myremove(blue);
            mymove(blue);
            bool removed = myremove2(blue);
            score+= ret;
            if(!ret && !removed) break;
        }
   } 
    cout << score << '\n';
    int bnum = 0;
    for(int i = 0; i < 4; ++i) for(int j = 0; j < 6; ++j) bnum += (bool)green[i][j] + (bool)blue[i][j];
    cout << bnum;
    return 0;
}