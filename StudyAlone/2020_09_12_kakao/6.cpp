#include <string>
#include <vector>
#include<queue>
#include<cstdio>
#include<memory.h>
#include<iostream>

using namespace std;
struct MINFO{
    int r,c,r2,c2, chk;
};
#include<string.h>
int dr[4] = {-1,0,1,0};
int dc[4] = {0,1,0,-1};
int chk[1<<12][4][4][5][5];

int solution(vector<vector<int>> board, int r, int c) {
    int cnt = 0;
    memset(chk, 0x3f, sizeof(chk));
    int dest = 0;
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j){
            if(board[i][j]){
                dest |= (1<<board[i][j]);
            }
        }
    }
    int bit = 0;
    queue<MINFO> Q;
    Q.push({r,c,4,4,0});
    chk[0][r][c][4][4] = 0;
    int answer = 0;
    int count = 0;
    while(1) {
        MINFO info = Q.front(); Q.pop();
        int rev = info.r2 < 4 ? board[info.r2][info.c2] : 0;
        int cnt = chk[info.chk][info.r][info.c][info.r2][info.c2];
        
        if(rev == 0) {
            if((cnt + 1 < chk[info.chk][info.r][info.c][info.r][info.c]) && (board[info.r][info.c] && (~info.chk >> board[info.r][info.c])&1)){
                chk[info.chk][info.r][info.c][info.r][info.c] = cnt + 1;
                Q.push({info.r,info.c,info.r,info.c, info.chk});
            }
        }
        else{
            if(board[info.r][info.c] == rev && (info.r != info.r2 || info.c != info.c2)){
                int nchk = info.chk | (1<<board[info.r][info.c]);
                if(chk[nchk][info.r][info.c][4][4] > cnt + 1){
                    chk[nchk][info.r][info.c][4][4] = cnt+1;
                    Q.push({info.r,info.c,4,4,nchk});
                }
            }
            else{
               	if(chk[info.chk][info.r][info.c][4][4] > cnt + 1){
                    chk[info.chk][info.r][info.c][4][4] = cnt+1;
                    Q.push({info.r,info.c,4,4,info.chk});
                }
            }
        }
        
        if(info.chk == dest) return chk[info.chk][info.r][info.c][info.r2][info.c2];
       	for(int d = 0; d < 4; ++d) {
            int nr = info.r + dr[d];
            int nc = info.c + dc[d];
            if(nr < 0 || nc < 0 || nr == 4 || nc == 4) continue;
            if(cnt + 1 < chk[info.chk][nr][nc][info.r2][info.c2]) {
                chk[info.chk][nr][nc][info.r2][info.c2] = cnt+1;
                Q.push({nr,nc,info.r2, info.c2, info.chk});
            }
            
            while(true){
                if((board[nr][nc] && ((~info.chk >> board[nr][nc]) & 1)) || (nr + dr[d] < 0 || nr + dr[d] ==4 || nc + dc[d] < 0 || nc + dc[d] == 4)){
                    break;
                }
                nr += dr[d], nc += dc[d];
            }
            if(cnt + 1 < chk[info.chk][nr][nc][info.r2][info.c2]) {
                chk[info.chk][nr][nc][info.r2][info.c2] = cnt+1;
                Q.push({nr,nc,info.r2,info.c2, info.chk});
            }
        }
    }
    return answer;
}