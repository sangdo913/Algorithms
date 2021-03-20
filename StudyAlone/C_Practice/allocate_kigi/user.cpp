/*
main 문을 읽고 해석하여 LOSS 를 최소화해라
*/

#if !CSIZE
#define CSIZE 5000
#endif
#define M 1000000007
#define CNT 2500000
#define rint register int
long long mseed = 7;
int pos[250000][2];
int ploss[5][250000];
int client[5][250000];
int clilen[5];
int where[250000];
int mrand() {
    return mseed = (mseed*214011 + 2531011)%M;
}
struct NODE{
    long long diff;
    int from, to,i;
};
NODE pq[1000001];
int _size;

int getchild(int i){
    rint l = i*2, r = l+1;
    if(l > _size) return 0;
    if(r > _size) return l;
    if(pq[l].diff < pq[r].diff) return l;
    return r;
}

void push(long long diff, int from, int to,int i){
    ++_size;
    int p, c = _size;
    while((p = c/2) && pq[p].diff > diff){
        pq[c] = pq[p];
        c = p;
    }
    pq[c] = {diff,from,to,i};
}

NODE pop(){
    register NODE ret = pq[1];
    register NODE data= pq[_size--];
    rint p = 1,c;
    while((c = getchild(p)) && pq[c].diff < data.diff){
        pq[p] = pq[c];
        p = c;
    }
    pq[p] = data;
    return ret;
}

void test(void* param)
{
    rint plen = 0;
    clilen[1] = clilen[2] = clilen[3] = clilen[4] = 0;
    int CBx[5];
    int CBy[5];
    int clen = 0;
    char (*arr)[CSIZE] = (char(*)[CSIZE])param;
    for(rint i = 0; i < CSIZE; ++i) {
        for(rint j = 0; j < CSIZE; ++j){
            if(arr[i][j]< 0){
                CBx[-arr[i][j]] = i;
                CBy[-arr[i][j]] = j;
                continue;
            }
            else if(arr[i][j] > 0){
                pos[plen][0] = i; pos[plen][1] = j;
                plen++;
            }
        }
    }
    int dx[5], dy[5];
    _size =0;
    for(int i = 0; i < plen; ++i) {
        rint mmin = 0x3f3f3f3f;
        rint mid = -1;
        rint x = pos[i][0];
        rint y = pos[i][1];
        for(rint s = 1; s < 5; ++s) {
            rint dx = x - CBx[s];
            rint dy = y - CBy[s];
            ploss[s][i] = dx*dx +dy*dy;
            if(mmin > ploss[s][i]) {
                mid = s;
                mmin = ploss[s][i];
            }
        }
        arr[x][y] = mid;
        where[i] = clilen[mid];
        client[mid][clilen[mid]++] = i;
    }
    bool con = true;
    while(con) {
        con = false;
        for(rint i = 1; i <= 4; ++i) {
            if(clilen[i] <= 67500){
                continue;
            }
            con = true;
            _size = 0;
            rint cnt = clilen[i] - 67500;
            for(rint id = 0; id < clilen[i]; ++id) {
                rint idx = client[i][id];
                rint x = pos[idx][0];
                rint y = pos[idx][1];
                for(rint j = 1; j < 5; ++j) {
                    if(j == arr[x][y]) continue;
                    push(((long long)ploss[j][idx] +((clilen[j] >= 67500) - 1)*50000000LL) - ploss[i][idx], i, j, idx);
                }
            }
            while(cnt) {
                NODE now = pop();
                rint x = pos[now.i][0];
                rint y = pos[now.i][1];
                if(arr[x][y] != i) continue;
                
                if(clilen[now.to] >= 67500) continue;
                rint last = client[now.from][--clilen[now.from]];
                client[now.to][clilen[now.to]] = now.i;
                client[now.from][where[now.i]] = last;
                where[last] = where[now.i];
                where[now.i] = clilen[now.to]++; 
                arr[x][y] = now.to;
                cnt--;
            }
        }
    }

    rint cnt = CNT;
    while(cnt) {
        rint pa = mrand()%plen;
        rint pb = mrand()%plen;
        rint ax = pos[pa][0];
        rint ay = pos[pa][1];
        rint bx = pos[pb][0];
        rint by = pos[pb][1];
        rint i1 = arr[ax][ay];
        rint i2 = arr[bx][by];
        while(i1 == i2) {
            pb = mrand()%plen;
            bx = pos[pb][0];
            by = pos[pb][1];
            i2 = arr[bx][by];
        }
        if(ploss[i1][pa] - ploss[i2][pa] + ploss[i2][pb] - ploss[i1][pb] > 0) {
            client[i1][where[pa]] = pb;
            client[i2][where[pb]] = pa;
            rint t = where[pa];
            where[pa] = where[pb];
            where[pb] = t;
            arr[ax][ay] = i2;
            arr[bx][by] = i1;
        }
        cnt--;
    }
}