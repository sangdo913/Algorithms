////////////////////////////
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>

using namespace std;
int DEBUG = 0;

struct DATA {
    int arr[20][20][5];
};


bool chk[400][400];

vector<int> ans;
//L U R D STAY
char mymove[10] = "LURDS";
int dx[] = { 0,-1,0,1, 0 }, dy[] = { -1,0,1,0, 0 };
int mx, my, tx, ty;    int ROW, COL;
int ex, ey;

bool res;    DATA* mp;

int dst(int tx, int ty, int mx, int my) {   // calc Menhatan distance
    return (abs(tx - mx) + abs(ty - my));
}
// check out dst from TESE 
// check out can go left or right
vector<pair<int, int>> v;
bool Move_Mino() {   // check out for this location in TESE 
    int leftx = mx + dx[0], lefty = my + dy[0];   // x : row    y : col
    int rightx = mx + dx[2], righty = my + dy[2];
    int cur_dst = dst(tx, ty, mx, my);   // current distance (tese - mino)
    if (mx == tx && my == ty) return true;

    // leftx  > tx || lefty > ty????   -> comparison 
    if (my < ty) {  // have to go right
        if (righty < COL) {  // dst를 고려 
            if (mp->arr[mx][my][2] == false) {  // No wall to direction 
                if (rightx == tx && righty == ty) return true;
                mx = rightx;   my = righty;
                return false;
            }
            //  else if (mp->arr[mx][my][2] == false /*&& rightx == tx && righty == ty*/) return false;
        }
    }
    else if (my > ty) { // have to go left
        if (lefty >= 0) {
            if (mp->arr[mx][my][0] == false) {
                if (leftx == tx && lefty == ty) return true;
                mx = leftx;   my = lefty;
                return false;
            }
            //  else if (mp->arr[mx][my][0] == false && leftx == tx && lefty == ty) return false;   // meet with tese
        }
    }
    ///////////////////////////////////// Move to up or down /////////////////////////////////////////////////////

    register int upx = mx + dx[1], upy = my + dy[1];
    register int downx = mx + dx[3], downy = my + dy[3];

    if (mx < tx) {
        if (downx < ROW) {
            if (mp->arr[mx][my][3] == false) {
                if (downx == tx && downy == ty) return true;
                mx = downx, my = downy;
                return false;
            }
            //  else if (mp->arr[mx][my][3] == false && downx == tx && downy == ty) return false;
        }
    }
    else if (mx > tx) {
        if (upx >= 0) {
            if (mp->arr[mx][my][1] == false) {
                if (upx == tx && upy == ty) return true;
                mx = upx, my = upy;
                return false;
            }
            //  else if (mp->arr[mx][my][1] == false && upx == tx && upy == ty) return false;
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    return false;
}
// Move Dfs()  ->  Move_Mino();

int tc_no; 

void dfs() {
    int map[20][20] = {};
    map[mx][my] = 8;
    map[tx][ty] = 1;
    if (tx == ex && ty == ey) {  // goal in 
        for (int i = 0; i < 4; i++) {
            if (tx + dx[i] == v[tc_no].first && ty + dy[i] == v[tc_no].second) {
                ans.push_back(i);
                break; 
            }
        }
        res = true;
    }
    int tmpx, tmpy, nx, ny;

    if (res) {
        for (int i = 0; i < ans.size(); ++i) cout << mymove[ans[i]] << ' ';
        cout << endl;
        ans.pop_back();
        return;
    }
   if(DEBUG){
      cout<<"======MINO==========\n";
      for(int i = 0; i < ROW; ++i){
         for(int j = 0; j < COL; ++j){
               cout << map[i][j] << ' ';
         }
         cout << '\n';
      }
      for(int i = 0; i <ans.size(); ++i) cout << mymove[ans[i]] << ' ';
      cout << endl;
      cout<<"================\n";
   }

    // cout << '\n';

 //    for (int i = 0; i < ROW; i++) {
 //       for (int j = 0; j < COL; j++) {
 //          cout << chk[i][j] << ' ';
 //       }
 //       cout << '\n';
 //    }
    for (int i = 0; i < 5; i++) {
        nx = tx + dx[i];  ny = ty + dy[i];

        if (nx >= ROW || nx < 0 || ny >= COL || ny < 0) continue;  // out of range 
      //   if (chk[nx][ny]) continue;

        if (mp->arr[tx][ty][i] == false || mp->arr[tx][ty][i] == 5) {   // can go && no wall          
            tx = nx;    ty = ny;
            tmpx = mx;  tmpy = my;

            bool catched = Move_Mino();
            catched |= Move_Mino();
            if (catched) {
                mx = tmpx, my = tmpy;         // recovery mino 
                tx -= dx[i];    ty -= dy[i];   // recovery TESE 
                continue;
            }
            //if (!Move_Mino())   return;
            //if (!Move_Mino()) return;
            //for check;
            int cx = mx * 20 + tx;
            int cy = my * 20 + ty;
            if (chk[cx][cy]) {
                mx = tmpx, my = tmpy;         // recovery mino 
                tx -= dx[i];    ty -= dy[i];   // recovery TESE 
                continue;
            }

            ans.push_back(i);
            chk[cx][cy] = true;

            dfs();
            map[mx][my] = 0;
            map[tx][ty] = 0;

            ans.pop_back();
            //  chk[cx][cy] = false;

            mx = tmpx, my = tmpy;         // recovery mino 
            tx -= dx[i];    ty -= dy[i];   // recovery TESE 
            map[mx][my] = 8;
            map[tx][ty] = 1;
            if (res) return;
        }
    }
    return;
}

void user_init() {
    v.push_back({ 8, 1 });
    v.push_back({ -1,3 });
    v.push_back({ 0,-1 });
    v.push_back({ 1,14 });
    v.push_back({ 5,14 });
}

int func(DATA* par, pair<int, int> te, pair<int, int> mino, pair<int, int> sz) {
    res = false;
    tx = te.first; ty = te.second;   mx = mino.first; my = mino.second;
    ROW = sz.first, COL = sz.second;
    for (int i = 0; i < 400; ++i) for (int j = 0; j < 400; ++j) chk[i][j] = 0;

    mp = par;
    ex = mp->arr[19][19][0];
    ey = mp->arr[19][19][1];

    cout << ex << ' ' << ey << endl;
    chk[mx * 20 + tx][my * 20 + ty] = true;
   
   
    dfs();
    tc_no++;
    if (res) return 100;
    else return 0;
}