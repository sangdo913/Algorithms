#include<iostream>

using namespace std;
int mymap[4][4];
//\1/
int dr[9] = {0,-1,-1,0,1,1,1,0,-1};
int dc[9] = {0,0,-1,-1,-1,0,1,1,1};
struct FISH{
    int x,y;
    int d;
    bool dead;
}f[18];

void move_fish(int mymap[4][4]){
    for(int i = 1; i <= 16; ++i){
        FISH &fish = f[i];
        if(fish.dead) continue;
        int d ;
        int nx, ny;
        for(d = 0; d < 8; ++d){
           nx = fish.x + dr[(f[i].d + d-1)%8 + 1];
           ny = fish.y + dc[(f[i].d + d-1)%8 + 1];
           if(nx < 0 || ny < 0 || nx ==4 || ny == 4) continue;
           if(mymap[nx][ny] == 17) continue;
           break;
        }
        if(nx < 0 || ny < 0 || nx ==4 || ny == 4) continue;
        if(mymap[nx][ny] == 17) continue;
        f[i].d = (f[i].d + d-1)%8 + 1;
        int fid = mymap[nx][ny];
        mymap[f[i].x][f[i].y] = fid;
        mymap[nx][ny] = i;
        f[fid].x = f[i].x;
        f[fid].y = f[i].y;
        f[i].x = nx; f[i].y = ny;
        // //debug
        // for(int i = 0; i < 4; ++i){
        //     for(int j = 0; j < 4; ++j) cout << mymap[i][j] << ' ';
        //     cout << endl;
        // }
    }
}

int dfs(){
    int backup[4][4];
    FISH shark_backup[18];
    int ret = 0;
    move_fish(mymap);
    for(int i = 0; i < 4; ++i) for(int j = 0; j < 4; ++j) backup[i][j] = mymap[i][j];
    for(int i = 1; i <= 17; ++i) shark_backup[i] = f[i];
    FISH&s = shark_backup[17];
    backup[s.x][s.y] = 0;
    int d= s.d;
    while(1){
        s.x += dr[d];
        s.y += dc[d];
        if(s.x < 0 || s.x == 4 || s.y < 0 || s.y ==4) break;
        if(backup[s.x][s.y] != 0){
            int fid = backup[s.x][s.y];
            shark_backup[fid].dead = 1;
            s.d = shark_backup[fid].d;
            backup[s.x][s.y] = 17;
            for(int i = 0; i < 4; ++i) for(int j = 0; j < 4; ++j) mymap[i][j] = backup[i][j];
            for(int i = 1; i <= 17; ++i) f[i] = shark_backup[i];
            // //debug
            // for(int i = 0; i < 4; ++i){
            //     for(int j = 0; j < 4; ++j) cout << mymap[i][j] << ' ';
            //     cout << endl;
            // }
            // cout << endl;
            int res = dfs();
            backup[s.x][s.y] = fid;
            shark_backup[fid].dead = 0;
            if(ret < res + fid) ret = res + fid;
        } 
    }

    return ret;
}
//1 2  3 4  5 6  7 8
//u lu l ld d rd r ru
int main(){
    freopen("0Text.txt", "r", stdin);
    for(int i = 0; i < 4 ;++i) for(int j = 0; j < 4; ++j) {
        int fid;
        cin >> fid >> f[fid].d;
        f[fid].x = i, f[fid].y = j;
        mymap[i][j] = fid;
    }
    int dead = mymap[0][0];
    f[dead].dead = 1;
    f[17] = f[dead];
    mymap[0][0] = 17;
    cout << dead + dfs();
    
    return 0;
}