#include<cstdio>
#define rint int
#define M 100000007
#define ABS(x) ((x) < 0 ? -(x) : (x))

void move_trash(int y, int x, int d);

struct INFO{
    int cid;
    int tid;
    int diff;
}infos[10001*4];
int tcan[4][2];
int tsize[4];

unsigned long long mseed = 3;
int mrand() {
    return mseed = ((mseed*214013 + 2531011)%M);
}

int Q[5*1011000];

struct TRASH {
    int x,y;
    int link;
}mtrash[10011];

int tdiff[4][10011];
int iid;
int psize;
int pq[10010*4+1];
int count[4][1000][1000];
int countarr[2010][3500];
int clen[2010];

void mpush(int cid,int tid, rint diff) {
    INFO &info = infos[iid];
    info.cid = cid, info.tid =tid, info.diff = diff;
    rint c = ++psize, p;
    while((p = c/2) && infos[pq[p]].diff > diff){
        pq[c] = pq[p];
        c = p;
    }
    pq[c] = iid++;
}

int getchild(int p){
    int l = p*2, r = l+1;
    if(l > psize) return 0;
    if(r > psize) return l;
    if(infos[pq[l]].diff < infos[pq[r]].diff) return l;
    return r;
}



int tc;

INFO mpop() {
    register INFO& ret = infos[pq[1]];
    int idx = pq[psize--];
    rint diff = infos[idx].diff;
    rint p = 1,c;
    while((c = getchild(p)) && diff > infos[pq[c]].diff){
        pq[p] = pq[c];
        p = c;
    }
    pq[p] = idx;
    return ret;
}
int m[4][1000][1000];
int di[4] = {-1,1,0,0};
int dj[4] = {0,0,-1,1};

int todiff[10011];

void test(int trash_map[1000][1000]) {
    for(rint i = 0; i < 2010; ++i) clen[i] = 0;
    // alen[1] = alen[2] = alen[3] = 0;
    psize = 0;
    ++tc;
    iid = 0;
    psize = 0;
    tsize[3] = tsize[0] = tsize[1] = tsize[2] = 0;
    rint tid = 1;
    for(rint i = 0; i < 1000; ++i) {
        for(rint j = 0; j < 1000; ++j){
            for(rint c = 1; c <= 3; ++c) count[c][i][j] = 0x3f3f3f3f;
            if(trash_map[i][j] > 0) {
                tcan[trash_map[i][j]][0] = i;
                tcan[trash_map[i][j]][1] = j;
            }
            else if(trash_map[i][j] == -1) {
                trash_map[i][j] = tid;
                mtrash[tid].x = i;
                mtrash[tid].link = 0;
                mtrash[tid++].y = j;
            }
        }
    }
    rint idx=0;
    for(rint i = 1; i <= 10000; ++i){
        for(rint j = 1; j <=  3; ++j){
            tdiff[j][i] =ABS(tcan[j][0] - mtrash[i].x) + ABS(tcan[j][1] - mtrash[i].y);
            mpush(j,i, tdiff[j][i]);
        }
    }
    int cnt = 0;
    while(psize) {
       INFO res = mpop(); 
       int tid = res.tid;
       if(tsize[res.cid] == 3500 || mtrash[tid].link) 
        continue;
       tsize[res.cid]++;
       trash_map[mtrash[tid].x][mtrash[tid].y] = res.tid;
       mtrash[tid].link = res.cid;
       todiff[res.tid] = clen[res.diff];
       countarr[res.diff][clen[res.diff]++] = res.tid;
    }
    while(true) {
        rint a = mrand()%10000+1;
        rint b = mrand()%10000+1;
        int f = mtrash[a].link;
        int t = mtrash[b].link;
        int a_f = tdiff[f][a];
        int a_t = tdiff[t][a];
        int b_f = tdiff[f][b];
        int b_t = tdiff[t][b];
        rint mycnt = 0;
        const int LIMIT = 10000;
        while(a_t + b_f  >= a_f + b_t){
             a = mrand()%10000+1;
             b = mrand()%10000+1;
             f = mtrash[a].link;
             t = mtrash[b].link;
             a_f = tdiff[f][a];
             a_t = tdiff[t][a];
             b_f = tdiff[f][b];
             b_t = tdiff[t][b];
            if(mycnt++ == LIMIT) break;
        }

        if(a != b && a_t + b_f  < a_f + b_t) {
            mtrash[a].link = t;
            mtrash[b].link = f;
            int lasta = countarr[a_f][--clen[a_f]];
            int lastb = countarr[b_t][--clen[b_t]];
            todiff[lasta] = todiff[a];
            todiff[lastb] = todiff[b];

            countarr[a_f][todiff[a]] = lasta;
            countarr[b_t][todiff[b]] = lastb;

            todiff[a] = clen[a_t]++;
            todiff[b] = clen[b_f]++;

            countarr[a_t][todiff[a]] = a;
            countarr[b_f][todiff[b]] = b;
        }
        if(mycnt >= LIMIT) break;
    }

    rint f = 0, r = 0;
    for(int c = 1; c<=3; ++c) {
        trash_map[tcan[c][0]][tcan[c][1]] = -2;
        Q[r++] = (c<<20) + (tcan[c][0] << 10) + tcan[c][1];
        count[c][tcan[c][0]][tcan[c][1]] = 0;
    }
    cnt = 0;
    rint dist = 0;
    rint aa = 0;
    while(f != r){
        rint cnt = r-f;
        while(cnt--) {
            int c = (Q[f]>>20);
            int nx = (Q[f]>>10)&0x3ff;
            int ny = Q[f]&0x3ff;
            int tid = trash_map[nx][ny];
            ++f;
            for(rint d = 0; d < 4; ++d){
                int nnx = nx + di[d];
                int nny = ny + dj[d];
                if(nnx < 0 || nnx == 1000 || nny < 0 || nny == 1000) continue;
                int ntid = trash_map[nnx][nny];
                if((!ntid || (ntid != -2 &&  c == mtrash[ntid].link)) && count[c][nnx][nny] > count[c][nx][ny] + 1) {
                    m[c][nnx][nny]  = d^1;
                    count[c][nnx][nny] = count[c][nx][ny] + 1;
                    Q[r++] = (c<<20) + (nnx << 10) + nny;
                }
            }
        }
        dist++;
    }
    for(rint i = 0; i < 2010; ++i){
        // rint cnt = clen[i];
        // printf("%d\n", i);
        // while(cnt--) {
        //     int a = 1;//mrand()%clen[i];
        //     int b = 2;
        //     // int b = mrand()%clen[i];
        //     int temp = countarr[i][a];
        //     // countarr[i][a] = countarr[i][b];
        //     // countarr[i][b] = temp;
        // }

        for(rint j = 0; j < clen[i]; ++j){
            int tid = countarr[i][j];
            int x = mtrash[tid].x, y = mtrash[tid].y;
            int cid = mtrash[tid].link;
            int d = m[cid][x][y];
            while(trash_map[x][y] != -2) {
                move_trash(x,y,d);
                x += di[d];
                y += dj[d];
                d = m[cid][x][y];
            }
        }
    }
        
    int debug =1;
}