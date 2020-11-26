#include<iostream>
#include<cstdio>
#include<fstream>
#include<string>
#include<cstring>
using namespace std;
#define SIZE 100

int mymap[4][SIZE][SIZE];
int tc = 0;
int Q[4][SIZE*SIZE];
int top[4];
//lu, ld, ru, rd
int dr[4] = {-1,0,1,0};
int dc[4] = {0,1,0,-1};
int ch1[4][2] = {{0,3},{3,2},{1,0},{1,2}};
int ch2[4][2] = {{1,2}, {1,0},{3,2},{3,0}};
int mycnt[SIZE][SIZE];
int myrect;

bool findrect(int (*image)[SIZE]) {
    bool ret = false;
    int lux, luy, rdx, rdy;
    for(int i = 0; i < SIZE; ++i){
        for(int j = 0; j < SIZE; ++j){
            int size = 0x3f3f3f3f;
            int sz;
            int i2 = 0,j2 = 0;
            int rdx = 0,rdy = 0;
            if(mymap[0][i][j] == tc) {
                size = 0x3f3f3f3f;
                mycnt[i][j] = 0;
                int nr = i + dr[ch1[0][0]];
                int nc = j + dc[ch1[0][0]];
                int nr2 = i + dr[ch1[0][1]];
                int nc2 = j + dc[ch1[0][1]];
                int v1 = (nr < 0 || nc < 0 || nr == SIZE || nc == SIZE) ? 0 : image[nr][nc];
                int v2 = (nr2 < 0 || nc2 < 0 || nr2 == SIZE || nc2 == SIZE) ? 0 : image[nr2][nc2];
                int v = image[i][j];
                v1 = v1 < v ? v-v1 : v;
                v2 = v2 < v ? v-v2 : v;
                int size1 = v1 < v2 ? v1 : v2;
                size = size1;
                for(i2 =i + 10; i2 < SIZE; ++i2){
                    if(mymap[1][i2][j] == tc){
                        int nr = i2 + dr[ch1[1][0]];
                        int nc = j + dc[ch1[1][0]];
                        int nr2 = i2 + dr[ch1[1][1]];
                        int nc2 = j + dc[ch1[1][1]];
                        int v1 = (nr < 0 || nc < 0 || nr == SIZE || nc == SIZE) ? 0 : image[nr][nc];
                        int v2 = (nr2 < 0 || nc2 < 0 || nr2 == SIZE || nc2 == SIZE) ? 0 : image[nr2][nc2];
                        int v = image[i2][j];
                        v1 = v1 < v ? v-v1 : v;
                        v2 = v2 < v ? v-v2 : v;
                        int size2 = v1 < v2 ? v1 : v2;
                        size = size < size2 ? size : size2;
                        for(j2 = j+10; j2 < SIZE; ++j2){
                            if(mymap[2][i][j2] == tc && mymap[3][i2][j2] == tc){
                                int nr = i + dr[ch1[2][0]];
                                int nc = j2 + dc[ch1[2][0]];
                                int nr2 = i + dr[ch1[2][1]];
                                int nc2 = j2 + dc[ch1[2][1]];
                                int v1 = (nr < 0 || nc < 0 || nr == SIZE || nc == SIZE) ? 0 : image[nr][nc];
                                int v2 = (nr2 < 0 || nc2 < 0 || nr2 == SIZE || nc2 == SIZE) ? 0 : image[nr2][nc2];
                                int v = image[i][j2];
                                v1 = v1 < v ? v-v1 : v;
                                v2 = v2 < v ? v-v2 : v;
                                int size3 = v1 < v2 ? v1 : v2;
                                size = size < size3 ? size : size3;

                                nr = i2 + dr[ch1[3][0]];
                                nc = j2 + dc[ch1[3][0]];
                                nr2 = i2 + dr[ch1[3][1]];
                                nc2 = j2 + dc[ch1[3][1]];
                                v1 = (nr < 0 || nc < 0 || nr == SIZE || nc == SIZE) ? 0 : image[nr][nc];
                                v2 = (nr2 < 0 || nc2 < 0 || nr2 == SIZE || nc2 == SIZE) ? 0 : image[nr2][nc2];
                                v = image[i2][j2];
                                v1 = v1 < v ? v-v1 : v;
                                v2 = v2 < v ? v-v2 : v;
                                int size4 = v1 < v2 ? v1 : v2;
                                size = size < size4 ? size : size4;
                                 if(size1>0 && size1 == size2 && size2 == size3 && size3 == size4) {
                                    rdx = i2;
                                    rdy = j2;
                                    sz = size;
                                    if(mycnt[i][j] == 1){
                                        goto NXT;
                                    }
                                    mycnt[i][j]++;
                                 }
                                // return true;
                            }
                        }
                    }
                }
                FIND:
                //printf("mcnt: %d size: %d\n", mycnt[i][j],size);
                if(mycnt[i][j] ==1 && size > 0){
                    i2 = rdx;
                    j2 = rdy;
                     printf("(%d %d) (%d %d), %d\n" ,i,j,i2,j2,sz);
                    for(int ii = i; ii <= i2; ++ii){
                        for(int jj = j; jj <= j2; ++jj){
                            image[ii][jj] -= sz;
                            if(image[ii][jj] < 0){
                                int x = 1;
                            }
                        }
                    }
                    if(i2 - i == j2 - j) {
                        printf("len: %d\n", i2-i);
                        myrect++;
                    }
                    // printf("(%d %d), (%d %d),\n", i,j, i2,j2);
                    ret |= true;
                    return ret;
                }
            }
        }
        NXT:
        int x;
    }

    return ret;
}

int recog(int image[SIZE][SIZE]) {
    tc++;
    // fstream file("0Text.txt");
    
    // for(int i = 0; i < SIZE; ++i) {
    //     for (int j = 0; j < SIZE; ++j) {
    //         string d = "00";
    //         d[0] = image[i][j] / 10 + '0';
    //         d[1] = image[i][j] %10 + '0';
    //         file << d << ' ';
    //     }
    //     file << '\n';
    // }

    top[0] = top[1] = top[2] = top[3] = 0;
    memset(mymap, 0, sizeof(mymap));
    for(int i = 0; i < SIZE; ++i){
        for(int j = 0; j < SIZE; ++j) {
            if(image[i][j] == 0) continue;
            bool ch = true;
            for(int d = 0; d < 4; ++d) {
                int nr = i + dr[ch1[d][0]];
                int nc = j + dc[ch1[d][0]];
                int nr2 = i + dr[ch1[d][1]];
                int nc2 = j + dc[ch1[d][1]];

                int v1 = (nr < 0 || nc < 0 || nr == SIZE || nc == SIZE) ? 0 : image[nr][nc];
                int v2 = (nr2 < 0 || nc2 < 0 || nr2 == SIZE || nc2 == SIZE) ? 0 : image[nr2][nc2];
                if(v1 == image[i][j] && v2 == image[i][j]){
                    continue;
                }
                nr = i + dr[ch2[d][0]];
                nc = j + dc[ch2[d][0]];
                nr2 = i + dr[ch2[d][1]];
                nc2 = j + dc[ch2[d][1]];
                v1 = (nr < 0 || nc < 0 || nr == SIZE || nc == SIZE) ? 0 : image[nr][nc];
                v2 = (nr2 < 0 || nc2 < 0 || nr2 == SIZE || nc2 == SIZE) ? 0 : image[nr2][nc2];
                if(v1 < image[i][j] || v2 < image[i][j]){
                    continue;
                }
                if(ch){
                    mymap[d][i][j] = tc;
                }
            }
        }
    }
    
    bool res = 0;
    int ret = 0;
    myrect = 0;
    while(res = findrect(image)){
        ret++;
    }

	return myrect;   
}