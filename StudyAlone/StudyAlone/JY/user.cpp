////////////////////////////
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>

using namespace std;

struct DATA {
   int arr[20][20][5];
};


bool chk[20][20];

vector<int> ans;
int dx[] = { 0,-1,0,1, 0 }, dy[] = { -1,0,1,0, 0 };
int mx, my, tx, ty;    int ROW, COL;

bool res;    DATA* mp;

int dst(int tx, int ty, int mx, int my) {   // calc Menhatan distance
   return (abs(tx - mx) + abs(ty - my));
}
// check out dst from TESE 
// check out can go left or right

bool Move_Mino() {   // check out for this location in TESE 
   int leftx = mx + dx[0], lefty = my + dy[0];   // x : row    y : col
   int rightx = mx + dx[2], righty = my + dy[2];
   int cur_dst = dst(tx, ty, mx, my);   // current distance (tese - mino)

                               // leftx  > tx || lefty > ty????   -> comparison 
   if (my < ty) {  // have to go right
      if (righty < COL) {  // dst를 고려 
         if (mp->arr[rightx][righty][2] == false && (rightx != tx && righty != ty)) {  // No wall to direction 
            mx = rightx;   my = righty;
         }
         else if (rightx == tx && righty == ty) return false;
      }
   }
   else if (my > ty) { // have to go left
      if (lefty >= 0) {
         if (mp->arr[leftx][lefty][0] == false) {
            mx = leftx;   my = lefty;
         }
         else if (rightx == tx && righty == ty) return false;   // meet with tese
      }
   }
   ///////////////////////////////////// Move to up or down /////////////////////////////////////////////////////

   register int upx = mx + dx[1], upy = my + dy[1];
   register int downx = mx + dx[3], downy = my + dy[3];

   if (mx < tx) {
      if (downx < ROW) {
         if (mp->arr[downx][downy][1] == false)
            mx = downx, my = downy;

         else if (downx == tx && downy == ty) return false;
      }
   }
   else if (mx > tx) {
      if (upx >= 0) {
         if (mp->arr[upx][upy][3] == false)
            mx = upx, my = upy;

         else if (upx == tx && upy == ty) return false;
      }
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   return true;
}
// Move Dfs()  ->  Move_Mino();

void dfs() {
   if (mp->arr[tx][ty][0] == 5) {  // goal in 
      res = true;
   }
   int tmpx, tmpy, nx, ny;


   if (res) return;

   cout << '\n';
   for (int i = 0; i < ROW; i++) {
      for (int j = 0; j < COL; j++) {
         cout << chk[i][j] << ' ';
      }
      cout << '\n';
   }
   for (int i = 0; i < 5; i++) {
      nx = tx + dx[i];  ny = ty + dy[i];

      if (nx >= ROW || nx < 0 || ny >= COL || ny < 0) continue;  // out of range 
      if (chk[nx][ny]) continue;

      if (mp->arr[nx][ny][i] == false || mp->arr[nx][ny][i] == 5) {   // can go && no wall 
         tx = nx;    ty = ny;
         tmpx = mx;  tmpy = my;
         if (!Move_Mino())   return;
         if (!Move_Mino()) return;
         ans.push_back(i);
         chk[nx][ny] = true;
         dfs();
         chk[nx][ny] = false;
         mx = tmpx, my = tmpy;         // recovery mino 
         tx -= dx[i];    ty -= dy[i];   // recovery TESE 
         if (res) return;
      }
   }
   return;
}

int func(DATA *par, pair<int, int> te, pair<int, int> mino, pair<int, int> sz) {
   tx = te.first; ty = te.second;   mx = mino.first; my = mino.second;
   ROW = sz.first, COL = sz.second;


   mp = par;
   cout << '\n';
   for (int i = 0; i < ROW; i++) {
      for (int j = 0; j < COL; j++) {
         cout << mp->arr[i][j][3] << ' ';
      }
      cout << '\n';
   }

   chk[te.first][te.second] = true;
   dfs();
   chk[te.first][te.second] = true;
   cout << res << '\n';
   if (res) return 100;
   else return 0;
}