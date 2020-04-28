#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define ull unsigned long long
#define rint register int
#define HSIZE 4000007 
ull myhash[HSIZE][2];
int check[HSIZE];
int tc;
int track[HSIZE];
int mymove[HSIZE];

extern bool swap(int dir);
int dr[4] = {-1,0,1,0};
int dc[4] = {0,1,0,-1};

int myfind(ull c1, ull c2){
    int key = c2%HSIZE;
    while(check[key] == tc && (myhash[key][0] != c1 || myhash[key][1] != c2)) key = ++key%HSIZE;
    if(check[key] == tc) return -1;
    return key;
}
#define SWAP(x,y) ((x)^=(y)^=(x)^=(y))
void myswap(ull b[2], int r, int c, int nr, int nc){
    int ni = (24-nr*5-nc)*3;
    int i = (24-r*5-c)*3;
    ull b1 = (b[ni/63] >> (ni%63)) & 7;
    ull b2 = (b[i/63]>>(i%63))&7;
    b[i/63] = (b[i/63] & ~((7LL << (i%63)))) + (b1<<(i%63));
    b[ni/63] = (b[ni/63] & ~((7LL << (ni%63)))) + (b2<<(ni%63));
}

int Q[HSIZE];
int ST[1000];
void solve(int board[5][5], int pattern[3][3], int callCntLimit) {
    tc++;
    register ull c1 = 0, c2 = 0;
    rint i,j;
    
    for(i = 0; i < 5; ++i){
        for(j = 0; j < 5; ++j){
            c1 <<=3;
            c1 += (c2>>60) & 7;
            c2 <<=3;
            c2 += board[i][j];
        }
    }
    rint key = c2 %HSIZE;
    myhash[key][0] = c1;
    myhash[key][1] = c2;
    track[key] = -1;
    check[key] = tc;
    rint fr = 0, re = 0;
    Q[re++] = key;
    rint last = -1;
    rint maxcorrect = 0;
    int depth = 1;

    while(fr!=re){
        int cnt = re-fr;
        while(cnt--){
            int now = Q[fr++];
            ull b1 = myhash[now][0];
            ull b2 = myhash[now][1];
            rint nowp = 0;
            rint r=0,c=0;
            ull c1 = b1;
            ull c2 = b2;
            rint rr,cc;
            for(i = 24; i >=4; --i){
                rr = i/ 5, cc = i%5;
                board[rr][cc] = c2&7;
                if(board[rr][cc] == 0) r = i/5, c = i%5;
                c2>>=3;
            }
            while(i>=0){
                rr = i/5, cc=i%5;
                board[rr][cc] = c1&7;
                if(!board[rr][cc]) r = i/5, c = i%5;
                c1>>=3;
                i--;
            }
            rint correct = 0;
            for(i = 1; i < 4; ++i) for(j = 1; j < 4; ++j) {
                if(board[i][j] == pattern[i-1][j-1]) correct++;
            }
            if((depth >= 20) && board[2][2] != pattern[1][1]) continue;

            if(correct == 9) {
                last = now;
                goto END;
            }
            if(correct > maxcorrect) maxcorrect = correct;
            if(correct < maxcorrect - (depth >= 10)) continue;

            for(rint d = 0; d <4; ++d){
                int nr = r + dr[d];
                int nc = c + dc[d];
                if(nr < 0 || nr ==5 || nc < 0 || nc == 5)continue;
                register ull ch[2] = {b2,b1};
                myswap(ch,r,c,nr,nc);
                int ret = myfind(ch[1],ch[0]); 
                if(ret != -1){
                    track[ret] = now;
                    check[ret] = tc;
                    mymove[ret] = d;

                    myhash[ret][0] =  ch[1]; myhash[ret][1] = ch[0];
                    Q[re++] = ret;
                }
            }
        }
        depth++;
    }
    END:
    rint top = 0;
    while(last != -1){
        ST[top++] = last;
        last = track[last];
    }
    if(top) --top;
    while(top){
        rint a = ST[--top];
        swap(mymove[a]);
    }
    return;
}