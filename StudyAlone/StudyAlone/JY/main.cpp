#include<iostream>
#include<algorithm>
#include<vector>
#include"user.cpp"
using namespace std;

int map1[20][20][5];

int map2[20][20][5]; int map3[20][20][5];

int map4[20][20][5]; int map5[20][20][5];

// 0 : Can go      1 : wall     3: mino            [0]-> 5 : goal 

// 0: left      1: up       2: right       3: down        4: stop  


vector<DATA> container;

extern int func(DATA* container, pair<int, int> te, pair<int, int> mino, pair<int, int> sz);
/*location & map & wall make */

void make_map1(int row, int col) {
   for (int i = 0; i < col; i++) {
      map1[row - 1][i][3] = true;
      map1[0][i][1] = true;
   }

   for (int i = 0; i < row; i++) {
      map1[i][col - 1][2] = true;
      map1[i][0][0] = true;
   }

   map1[0][0][3] = true;
   map1[0][1][3] = true;
   map1[0][3][2] = true;
   map1[0][4][0] = true;
   map1[0][5][2] = true;
   map1[0][6][0] = true;
   map1[0][7][3] = true;

   map1[1][0][1] = true;
   map1[1][1][1] = true;   map1[1][1][2] = true;
   map1[1][2][0] = true;   map1[1][2][2] = true;   map1[1][2][3] = true;
   map1[1][3][0] = true;   map1[1][3][2] = true;
   map1[1][4][0] = true;   map1[1][4][2] = true;
   map1[1][5][0] = true;   map1[1][5][2] = true;
   map1[1][6][0] = true;
   map1[1][7][1] = true;   map1[1][7][2] = true;   map1[1][7][3] = true;
   map1[1][8][0] = true;

   map1[2][0][2] = true;
   map1[2][1][0] = true;    map1[2][1][3] = true;
   map1[2][2][1] = true;    map1[2][2][2] = true;
   map1[2][3][0] = true;
   map1[2][4][2] = true;    map1[2][4][3] = true;
   map1[2][5][0] = true;    map1[2][5][3] = true;
   map1[2][6][2] = true;    map1[2][6][3] = true;
   map1[2][7][0] = true;    map1[2][7][1] = true;

   map1[3][0][3] = true;
   map1[3][1][1] = true;    map1[3][1][2] = true;
   map1[3][2][0] = true;    map1[3][2][2] = true;
   map1[3][3][0] = true;    map1[3][3][3] = true;
   map1[3][4][1] = true;    map1[3][4][2] = true;
   map1[3][5][0] = true;    map1[3][5][1] = true;
   map1[3][6][1] = true;    map1[3][6][3] = true;
   map1[3][7][3] = true;
   map1[3][8][3] = true;

   map1[4][0][1] = true;    map1[4][0][2] = true;
   map1[4][1][0] = true;    map1[4][1][2] = true;
   map1[4][2][0] = true;    map1[4][2][3] = true;
   map1[4][3][1] = true;
   map1[4][4][2] = true;    map1[4][4][3] = true;
   map1[4][5][0] = true;    map1[4][5][3] = true;
   map1[4][6][1] = true;    map1[4][6][3] = true;
   map1[4][7][1] = true;    map1[4][7][3] = true;
   map1[4][8][1] = true;

   map1[5][1][2] = true;    map1[5][1][3] = true;
   map1[5][2][0] = true;    map1[5][2][1] = true;
   map1[5][3][2] = true;    map1[5][3][3] = true;
   map1[5][4][0] = true;    map1[5][4][1] = true;
   map1[5][5][1] = true;
   map1[5][6][1] = true;    map1[5][6][3] = true;
   map1[5][7][1] = true;    map1[5][7][3] = true;
   map1[5][8][3] = true;

   map1[6][0][2] = true;
   map1[6][1][0] = true;    map1[6][1][1] = true;    map1[6][1][2] = true;
   map1[6][2][0] = true;
   map1[6][3][1] = true;    map1[6][3][2] = true;    map1[6][3][3] = true;
   map1[6][4][0] = true;    map1[6][4][2] = true;
   map1[6][5][0] = true;    map1[6][5][3] = true;
   map1[6][6][1] = true;    map1[6][6][3] = true;
   map1[6][7][1] = true;    map1[6][7][3] = true;
   map1[6][8][1] = true;

   map1[7][0][2] = true;
   map1[7][1][0] = true;
   map1[7][3][1] = true;
   map1[7][5][1] = true;    map1[7][5][2] = true;
   map1[7][6][0] = true;    map1[7][6][1] = true;
   map1[7][7][1] = true;

   map1[7][1][3] = true; // map1 exit


   map1[7][1][0] = 5; 
   return;
}

void make_map2(int row, int col) {
   for (int i = 0; i < col; i++) {
      map2[row - 1][i][3] = true;
      map2[0][i][1] = true;
   }

   for (int i = 0; i < row; i++) {
      map2[i][col - 1][2] = true;
      map2[i][0][0] = true;
   }

   map2[0][0][3] = true;
   map2[0][1][3] = true;
   map2[0][5][3] = true;

   map2[1][0][1] = true;
   map2[1][1][1] = true;
   map2[1][5][1] = true;
   map2[2][3][3] = true;

   map2[3][0][2] = true;
   map2[3][1][0] = true;    map2[3][1][3] = true;
   map2[3][2][2] = true;
   map2[3][3][0] = true;    map2[3][3][1] = true;    map2[3][3][2] = true;
   map2[3][4][0] = true;
   map2[3][7][2] = true;
   map2[3][8][0] = true;

   map2[4][0][2] = true;
   map2[4][1][0] = true;    map2[4][1][1] = true;
   map2[4][7][2] = true;    map2[4][7][3] = true;
   map2[4][8][0] = true;

   map2[5][0][2] = true;
   map2[5][7][1] = true;   map2[5][7][2] = true;
   map2[5][8][0] = true;

   map2[6][3][3] = true;
   map2[6][7][2] = true;
   map2[6][8][0] = true;

   map2[7][3][1] = true;

   map2[0][3][1] = true; // map2 exit


   map2[0][3][0] = 5; 
   return;
}

void make_map3(int row, int col) {
   for (int i = 0; i < col; i++) {
      map3[row - 1][i][3] = true;
      map3[0][i][1] = true;
   }

   for (int i = 0; i < row; i++) {
      map3[i][col - 1][2] = true;
      map3[i][0][0] = true;
   }

   map3[0][0][2] = true;
   map3[0][1][0] = true;
   map3[0][5][3] = true;
   map3[0][7][3] = true;

   map3[1][5][1] = true;
   map3[1][6][2] = true;
   map3[1][7][0] = true;    map3[1][7][1] = true;

   map3[2][4][2] = true;
   map3[2][5][0] = true;

   map3[3][1][3] = true;
   map3[3][3][2] = true;
   map3[3][4][0] = true;
   map3[3][5][3] = true;

   map3[4][1][1] = true;
   map3[4][2][2] = true;
   map3[4][3][0] = true;
   map3[4][5][1] = true;

   map3[5][0][2] = true;    map3[5][0][3] = true;
   map3[5][1][0] = true;    map3[5][1][2] = true;
   map3[5][2][0] = true;
   map3[5][5][2] = true;
   map3[5][6][0] = true;    map3[5][6][3] = true;

   map3[6][0][1] = true;    map3[6][0][3] = true;
   map3[6][1][2] = true;
   map3[6][2][0] = true;
   map3[6][3][2] = true;
   map3[6][4][0] = true;    map3[6][4][3] = true;
   map3[6][6][1] = true;

   map3[7][0][1] = true;
   map3[7][4][1] = true;    map3[7][4][2] = true;
   map3[7][5][0] = true;

   map3[0][0][0] = true; // map3 exit

   map3[0][0][0] = 5; 
   return;
}

void make_map4(int row, int col) {
   for (int i = 0; i < col; i++) {
      map4[row - 1][i][3] = true;
      map4[0][i][1] = true;
   }

   for (int i = 0; i < row; i++) {
      map4[i][col - 1][2] = true;
      map4[i][0][0] = true;
   }

   map4[0][0][3] = true;
   map4[0][1][3] = true;
   map4[0][4][2] = true;
   map4[0][5][0] = true;
   map4[0][6][3] = true;
   map4[0][8][2] = true;    map4[0][8][3] = true;
   map4[0][9][0] = true;    map4[0][9][3] = true;
   map4[0][11][3] = true;
   map4[0][12][3] = true;

   map4[1][0][1] = true;    map4[1][0][2] = true;
   map4[1][1][0] = true;    map4[1][1][1] = true;    map4[1][1][2] = true;
   map4[1][2][0] = true;    map4[1][2][2] = true;
   map4[1][3][0] = true;    map4[1][3][2] = true;    map4[1][3][3] = true;
   map4[1][4][0] = true;    map4[1][4][2] = true;
   map4[1][5][0] = true;    map4[1][5][2] = true;
   map4[1][6][0] = true;    map4[1][6][1] = true;    map4[1][6][3] = true;
   map4[1][8][1] = true;    map4[1][8][3] = true;
   map4[1][9][1] = true;    map4[1][9][3] = true;
   map4[1][10][2] = true;   map4[1][10][3] = true;
   map4[1][11][0] = true;   map4[1][11][1] = true;   map4[1][11][3] = true;
   map4[1][12][1] = true;   map4[1][12][3] = true;

   map4[2][2][3] = true;
   map4[2][3][1] = true;
   map4[2][6][1] = true;    map4[2][6][3] = true;
   map4[2][8][1] = true;
   map4[2][9][1] = true;
   map4[2][10][1] = true;   map4[2][10][3] = true;
   map4[2][11][1] = true;   map4[2][11][3] = true;
   map4[2][12][1] = true;

   map4[3][0][2] = true;
   map4[3][1][0] = true;    map4[3][1][2] = true;
   map4[3][2][0] = true;    map4[3][2][1] = true;    map4[3][2][3] = true;
   map4[3][3][2] = true;
   map4[3][4][0] = true;    map4[3][4][2] = true;
   map4[3][5][0] = true;
   map4[3][6][1] = true;
   map4[3][7][2] = true;
   map4[3][8][0] = true;    map4[3][8][2] = true;
   map4[3][9][0] = true;    map4[3][9][3] = true;
   map4[3][10][1] = true;   map4[3][10][3] = true;
   map4[3][11][1] = true;   map4[3][11][3] = true;
   map4[3][12][2] = true;
   map4[3][13][0] = true;

   map4[4][0][2] = true;
   map4[4][1][0] = true;    map4[4][1][2] = true;
   map4[4][2][0] = true;    map4[4][2][1] = true;
   map4[4][3][2] = true;
   map4[4][4][0] = true;    map4[4][4][2] = true;
   map4[4][5][0] = true;    map4[4][5][2] = true;
   map4[4][6][0] = true;    map4[4][6][2] = true;
   map4[4][7][0] = true;    map4[4][7][2] = true;
   map4[4][8][0] = true;
   map4[4][9][1] = true;    map4[4][9][3] = true;
   map4[4][10][1] = true;   map4[4][10][3] = true;
   map4[4][11][1] = true;   map4[4][11][2] = true;
   map4[4][12][0] = true;   map4[4][12][2] = true;
   map4[4][13][0] = true;

   map4[5][0][2] = true;
   map4[5][1][0] = true;    map4[5][1][2] = true;
   map4[5][2][0] = true;    map4[5][2][2] = true;
   map4[5][3][0] = true;
   map4[5][4][2] = true;
   map4[5][5][0] = true;    map4[5][5][2] = true;
   map4[5][6][0] = true;
   map4[5][9][1] = true;    map4[5][9][3] = true;
   map4[5][10][1] = true;   map4[5][10][3] = true;
   map4[5][11][2] = true;
   map4[5][12][0] = true;   map4[5][12][2] = true;
   map4[5][13][0] = true;

   map4[6][0][2] = true;
   map4[6][1][0] = true;    map4[6][1][2] = true;
   map4[6][2][0] = true;    map4[6][2][2] = true;
   map4[6][3][0] = true;    map4[6][3][2] = true;
   map4[6][4][0] = true;    map4[6][4][2] = true;
   map4[6][5][0] = true;    map4[6][5][2] = true;
   map4[6][6][0] = true;    map4[6][6][2] = true;
   map4[6][7][0] = true;    map4[6][7][2] = true;
   map4[6][8][0] = true;
   map4[6][9][1] = true;    map4[6][9][3] = true;
   map4[6][10][1] = true;   map4[6][10][3] = true;
   map4[6][11][2] = true;
   map4[6][12][0] = true;   map4[6][12][2] = true;
   map4[6][13][0] = true;

   map4[7][0][2] = true;
   map4[7][1][0] = true;    map4[7][1][2] = true;
   map4[7][2][0] = true;    map4[7][2][2] = true;
   map4[7][3][0] = true;    map4[7][3][2] = true;
   map4[7][4][0] = true;    map4[7][4][2] = true;
   map4[7][5][0] = true;    map4[7][5][2] = true;
   map4[7][6][0] = true;    map4[7][6][2] = true;
   map4[7][7][0] = true;    map4[7][7][2] = true;
   map4[7][8][0] = true;
   map4[7][9][1] = true;    map4[7][9][3] = true;
   map4[7][10][1] = true;   map4[7][10][3] = true;
   map4[7][11][2] = true;
   map4[7][12][0] = true;   map4[7][12][2] = true;
   map4[7][13][0] = true;

   map4[8][9][1] = true;
   map4[8][10][1] = true;

   map4[1][13][2] = true; // map4 exit


   map4[1][14][0] = 5; 
   return;
}

void make_map5(int row, int col) {
   for (int i = 0; i < col; i++) {
      map5[row - 1][i][3] = true;
      map5[0][i][1] = true;
   }

   for (int i = 0; i < row; i++) {
      map5[i][col - 1][2] = true;
      map5[i][0][0] = true;
   }

   map5[0][1][2] = true;
   map5[0][2][0] = true;
   map5[0][3][3] = true;
   map5[0][5][3] = true;
   map5[0][6][3] = true;
   map5[0][9][2] = true;    map5[0][9][3] = true;
   map5[0][10][0] = true;
   map5[0][11][3] = true;
   map5[0][12][3] = true;

   map5[1][0][2] = true;
   map5[1][1][0] = true;    map5[1][1][3] = true;
   map5[1][2][3] = true;
   map5[1][3][1] = true;    map5[1][3][2] = true;
   map5[1][4][0] = true;    map5[1][4][2] = true;
   map5[1][5][0] = true;    map5[1][5][1] = true;
   map5[1][6][1] = true;    map5[1][6][3] = true;
   map5[1][7][2] = true;
   map5[1][8][0] = true;
   map5[1][9][1] = true;    map5[1][9][2] = true;    map5[1][9][3] = true;
   map5[1][10][0] = true;   map5[1][10][2] = true;
   map5[1][11][0] = true;   map5[1][11][1] = true;   map5[1][11][2] = true;
   map5[1][12][0] = true;   map5[1][12][1] = true;   map5[1][12][2] = true;
   map5[1][13][0] = true;

   map5[2][1][1] = true;    map5[2][1][2] = true;
   map5[2][2][0] = true;    map5[2][2][1] = true;
   map5[2][3][3] = true;
   map5[2][4][3] = true;
   map5[2][6][1] = true;    map5[2][6][3] = true;
   map5[2][8][3] = true;
   map5[2][9][1] = true;    map5[2][9][2] = true;
   map5[2][10][0] = true;   map5[2][10][2] = true;
   map5[2][11][0] = true;

   map5[3][0][2] = true;
   map5[3][1][0] = true;
   map5[3][3][1] = true;
   map5[3][4][1] = true;    map5[3][4][2] = true;
   map5[3][5][0] = true;    map5[3][5][2] = true;
   map5[3][6][0] = true;    map5[3][6][1] = true;    map5[3][6][3] = true;
   map5[3][8][1] = true;    map5[3][8][2] = true;
   map5[3][9][0] = true;
   map5[3][10][2] = true;
   map5[3][11][0] = true;   map5[3][11][2] = true;
   map5[3][12][0] = true;   map5[3][12][2] = true;
   map5[3][13][0] = true;

   map5[4][0][2] = true;
   map5[4][1][0] = true;    map5[4][1][2] = true;
   map5[4][2][0] = true;    map5[4][2][2] = true;
   map5[4][3][0] = true;    map5[4][3][2] = true;
   map5[4][4][0] = true;    map5[4][4][2] = true;
   map5[4][5][0] = true;
   map5[4][6][2] = true;
   map5[4][7][0] = true;    map5[4][7][2] = true;
   map5[4][8][0] = true;    map5[4][8][2] = true;
   map5[4][9][0] = true;    map5[4][9][2] = true;
   map5[4][10][0] = true;   map5[4][10][2] = true;
   map5[4][11][0] = true;
   map5[4][12][3] = true;
   map5[4][13][3] = true;

   map5[5][1][3] = true;
   map5[5][2][3] = true;
   map5[5][3][3] = true;
   map5[5][4][2] = true;
   map5[5][5][0] = true;    map5[5][5][2] = true;
   map5[5][6][0] = true;
   map5[5][7][2] = true;
   map5[5][8][0] = true;    map5[5][8][2] = true;
   map5[5][9][0] = true;    map5[5][9][2] = true;
   map5[5][10][0] = true;   map5[5][10][2] = true;
   map5[5][11][0] = true;   map5[5][11][2] = true;
   map5[5][12][0] = true;   map5[5][12][1] = true;   map5[5][12][2] = true;
   map5[5][13][0] = true;   map5[5][13][1] = true;

   map5[6][0][3] = true;
   map5[6][1][1] = true;    map5[6][1][3] = true;
   map5[6][2][1] = true;
   map5[6][3][1] = true;    map5[6][3][2] = true;
   map5[6][4][0] = true;    map5[6][4][3] = true;
   map5[6][5][3] = true;
   map5[6][6][2] = true;
   map5[6][7][0] = true;
   map5[6][8][3] = true;
   map5[6][9][2] = true;
   map5[6][10][0] = true;   map5[6][10][3] = true;
   map5[6][12][2] = true;   map5[6][12][3] = true;
   map5[6][13][0] = true;

   map5[7][0][1] = true;    map5[7][0][2] = true;
   map5[7][1][0] = true;    map5[7][1][1] = true;    map5[7][1][2] = true;
   map5[7][2][0] = true;    map5[7][2][2] = true;
   map5[7][3][0] = true;    map5[7][3][2] = true;
   map5[7][4][0] = true;    map5[7][4][1] = true;    map5[7][4][3] = true;
   map5[7][5][1] = true;    map5[7][5][3] = true;
   map5[7][6][2] = true;
   map5[7][7][0] = true;
   map5[7][8][1] = true;
   map5[7][9][3] = true;
   map5[7][10][1] = true;   map5[7][10][3] = true;
   map5[7][11][3] = true;
   map5[7][12][1] = true;   map5[7][12][2] = true;
   map5[7][13][0] = true;

   map5[8][4][1] = true;
   map5[8][5][1] = true;
   map5[8][7][2] = true;
   map5[8][8][0] = true;
   map5[8][9][1] = true;
   map5[8][10][1] = true;
   map5[8][11][1] = true;

   map5[5][13][2] = true; // map5 exit


   map5[5][13][0] = 5; 
   return;
}

vector<pair<int, int>> te;
vector<pair<int, int>> mino;    // location 

void init() {
   make_map1(8, 9);
   make_map2(8, 9);
   make_map3(8, 8);
   make_map4(9, 14);
   make_map5(9, 14);
}

pair<int, int> size_tt[5]; 

int main() {
   ios::sync_with_stdio(false);
   cin.tie(0), cout.tie(0);


   size_tt[0] = { 8, 9 };  size_tt[1] = { 8, 9 }; 
   size_tt[2] = { 8, 8 };
   size_tt[3] = { 9, 14 };
   size_tt[4] = { 9, 14 };

   int SCORE = 0;
   DATA d[5];
   init();

   
   memcpy(d[0].arr, map1, sizeof(DATA));
   memcpy(d[1].arr, map2, sizeof(DATA));
   memcpy(d[2].arr, map3, sizeof(DATA));
   memcpy(d[3].arr, map4, sizeof(DATA));
   memcpy(d[4].arr, map5, sizeof(DATA));

   container.push_back(d[0]);
   container.push_back(d[1]);
   container.push_back(d[2]);
   container.push_back(d[3]);
   container.push_back(d[4]);


   te.push_back({ 0,0 });
   te.push_back({ 0,8 });
   te.push_back({ 1,1 });
   te.push_back({ 4,0 });
   te.push_back({ 5,12 });


   mino.push_back({ 2, 2 });  mino.push_back({ 0, 0 });
   mino.push_back({ 0, 0 });   mino.push_back({ 4, 13 });
   mino.push_back({ 3, 6 });

   for (register int testCase = 0; testCase < 5; testCase++) {
      printf("TestCase : %d\n", testCase); 
      SCORE += func(&container[testCase], te[testCase], mino[testCase], size_tt[testCase]);
   }
   printf("total Score :  %d   \n", SCORE);
   return 0;
}