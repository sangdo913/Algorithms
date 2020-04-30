#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define ull unsigned long long
#define rint register int
#define QSIZE 4000000

extern bool swap(int dir);
int dr[4] = {-1,0,1,0};
int dc[4] = {0,1,0,-1};
int dist[5][5];
int track[5][5];
int Q[QSIZE][2];
int mvisit[5][5];
int query;
int path[5][5];
int dest[5][5];

int getnext(int board[5][5], int d, int r, int c){
    query++;
    rint fr,re;
    fr= re = 0;
    rint p = 0;
    Q[re][0] = r;
    Q[re++][1] = c;
    dest[r][c] = (r<<10)+c;
    int nr, nc;
    while(fr != re){
        nr = Q[fr][0], nc = Q[fr++][1];
        if(board[nr][nc] == d) return ((nr << 10) + nc);
        for(rint d = 0; d < 4; ++d){
            int nnr = nr + dr[d], nnc = nc + dc[d];
            if(nnr < 0 || nnr == 5 || nnc < 0 || nnc == 5) continue;
            if(mvisit[nnr][nnc] == query) continue;
            if(board[nnr][nnc] == -1) continue;
            mvisit[nnr][nnc] = query;
            dest[nnr][nnc] = (nr << 10) + nc;
            Q[re][0] = nnr, Q[re++][1] = nnc;
        }
    }
    return -1;
}
int ST[QSIZE];
void myswap(int board[5][5], int d, int r, int c){
    int nr = r+dr[d], nc = c + dc[d];
    board[nr][nc] ^=board[r][c] ^=board[nr][nc] ^= board[r][c];
}

int go(int board[5][5], int r, int c,int dddr, int dddc, int ddr, int ddc,int pr, int pc){
    for(rint i = 0; i < 5; ++i){
        for(rint j = 0; j < 5; ++j)
            dist[i][j] = 0x3f3f3f3f;
    }
    track[r][c] = -1;
    dist[r][c] = 0;

    int fr, re, top;
    int nr, nc;
    top = fr = re = 0;
    Q[re][0] = r, Q[re++][1] = c;
    while(fr != re){
            nr = Q[fr][0];
            nc = Q[fr++][1];
            if(nr == ddr && nc == ddc) break;
            for(rint d = 0; d < 4; ++d){
                rint nnr = nr + dr[d], nnc = nc + dc[d];
                if(nnr < 0 || nnr == 5 || nnc < 0 || nnc == 5 || dist[nnr][nnc] <= dist[nr][nc] + 1) continue;
                if(board[nnr][nnc] == -1) continue;
                if(nnr == pr && nnc == pc) continue;
                if(dddr == nnr && dddc == nnc) continue;
                dist[nnr][nnc] = dist[nr][nc] + 1;
                Q[re][0] = nnr, Q[re++][1] = nnc;
                track[nnr][nnc] = d;
            }
    }
    while(track[nr][nc] != -1){
        rint d =track[nr][nc];
        ST[top++] = d;
        nr+= dr[(d+2)%4];
        nc += dc[(d+2)%4];
    }
    while(top){
        rint d = ST[--top];
        myswap(board,d,nr,nc);
        nr+=dr[d], nc += dc[d];
        
        swap(d);
    }
    return (nr<<10) + nc;
}

int order[9] = {0,1,2,2,1,0,0,1,2}; 
void solve(int board[5][5], int pattern[3][3], int callCntLimit) {
    int r, c;
    for(int i = 0; i < 5; ++i) for(int j = 0; j < 5; ++j){
            if(!board[i][j]) {
                r = i, c = j;
                break;
            }
    }
    for(int i = 0; i < 9; ++i){
        int ne = getnext(board, pattern[i/3][order[i]],i/3+1, order[i]+1);
        int ddr = (ne >> 10) & 0xff;
        int ddc = ne&0xff;
        int pr,pc;
        pr = -1, pc = -1;
        int need = pattern[i/3][order[i]];
        while(board[i/3+1][order[i]+1] != need){
            int dddr = dest[ddr][ddc] >> 10;
            int dddc = dest[ddr][ddc] &0xf;
            int p = go(board, r,c,ddr,ddc,dddr, dddc,pr,pc);
            r = (p>>10)&0xff, c = p &0xff;
            for(int d = 0; d < 4;++d){
                int nr = r + dr[d], nc = c + dc[d];
                if(nr < 0 || nr == 5 || nc < 0 || nc == 5) continue;
                if(board[nr][nc] ==pattern[i/3][order[i]]){
                    myswap(board, d, r,c);
                    swap(d);
                    ddr = r, ddc = c;
                    r = nr, c = nc;
                    break;
                }
            }
            pr = ddr, pc = ddc;
        }
        board[i/3+1][order[i]+1] = -1;
    }
    return;
}