#include<cstdio>
#define rint register int
#define CSIZE 5000
#define LIMIT 67500
char (*mymap)[CSIZE];
int tc;

struct INFO {
    int i, diff, control;
} infos[1000000];

int PQ[250000*4 + 1];
int pqsize1;
int PQ2[(250000)*4 + 1];
int control_size[4];
int diff[4][250000];
int con[1000000];

int arr1[250000];
int arr2[250000];
int arr[250000][2];
int asize1, asize2;
int pos1[4];
int pos2[4];
int plen1;
int plen2;
int pos[4][2];
long long mseed;
int myrand(){
    return mseed = ((mseed*214011 + 2531011)%1000000007);
}

int nid;
void push(int *pq, int *size, int i, int diff, int control) {
    INFO &info = infos[nid];
    info.i = i; info.diff = diff, info.control = control;
    rint p, c = ++(*size);
    while((p = c/2) && infos[PQ[p]].diff > diff){
        PQ[c] = PQ[p];
        c = p;
    }
    PQ[c] = nid;
    nid++;
}

int getchild(int *pq, int size, int p){
    int l = p*2;
    int r = l+1;
    if(l > size) return 0;
    if (r > size) return l;
    return infos[pq[l]].diff < infos[pq[r]].diff  ? l:r;
}

int pop(int *pq, int *size){
    int res = pq[1];
    rint p = 1,c;
    rint last = pq[(*size)--];
    rint diff = infos[last].diff;
    
    while((c = getchild(pq, *size, p)) && infos[pq[c]].diff < diff){
        pq[p] = pq[c];
        p = c;
    }
    pq[p] = last;
    return res;
}
int end1, end2;
int chk[250000];
int gsize[4] = {0,0,0,0};

void solution() {
    nid = 0;
    gsize[0] = gsize[1] = gsize[2] = gsize[3] = 0;
    // printf("solution\n");
    control_size[0] = control_size[1] = control_size[2] = control_size[3] = 0;
    // printf("%d %d %d\n", asize1, asize2, asize1+asize2);
    rint psize = 0;
    pqsize1 = 0;

    rint asize = 0;
    for(rint i = 0; i < asize1; ++i){
        arr[asize][0] = arr1[i]>>15; 
        arr[asize++][1] = arr1[i]&0x7fff;
    }
    for(rint i = 0; i < asize2; ++i){
        arr[asize][0] = arr2[i]>>15;
        arr[asize++][1] = arr2[i]&0x7fff;
    }
    for(rint g = 0; g < 4; ++g){
        for(rint i = 0; i < 250000; ++i){
            rint dx = pos[g][0] - arr[i][0];
            rint dy = pos[g][1] - arr[i][1];
            diff[g][i] = (dx-dy)*(dx-dy);

            push(PQ, &pqsize1, i, (dx-dy)*(dx-dy), g);
        }
    }
    // printf("nid:%d %d\n", nid, asize);
    int prev = -1;
    while(pqsize1){
       register int res = pop(PQ, &pqsize1); 
       if(infos[res].diff < prev){
           int debug=1;
       }
       prev = infos[res].diff;
       if(gsize[infos[res].control] < LIMIT){
           int id = infos[res].i;
           if(chk[id] == tc) continue;
           chk[id] = tc;
           gsize[infos[res].control]++;
           con[id] = infos[res].control+1;
       }
    }
    // printf("gsize: %d %d %d %d %d\n", gsize[0], gsize[1], gsize[2], gsize[3], gsize[0] + gsize[1] + gsize[2] + gsize[3]);
    for(rint i = 0; i < 250000; ++i){
        mymap[arr[i][0]][arr[i][1]] = con[i];
    }
    int cnt =0;
    for(rint i = 0; i < 5000000; ++i){
        rint a = myrand()%250000;
        rint b = myrand()%250000;
        int ca = con[a]-1;
        int cb = con[b]-1;
        if(gsize[cb] >= LIMIT) {
            cnt++;
            if(diff[ca][a] + diff[cb][b] > diff[cb][a] + diff[ca][b]) {
                con[a] = cb+1;
                con[b] = ca+1;
                mymap[arr[a][0]][arr[a][1]] = cb+1;
                mymap[arr[b][0]][arr[b][1]] = ca+1;
            }
        }
        else{
            if(diff[ca][a] > diff[cb][a]){
                cnt++;
                con[a] = cb+1;
                mymap[arr[a][0]][arr[a][1]] = cb+1;
                gsize[ca]--;
                gsize[cb]++;
            }
        }
    }
    printf("%d\n", cnt);
    DONE = 1;
}

void test1(void* param) {
    tc++;
    asize1 = 0;
    mymap = (char(*)[CSIZE]) param;
    plen1 = 0;
    for(rint i = 0; i < 2500; ++i){
        for(rint j = 0; j < CSIZE; ++j) {
            if(mymap[i][j] < 0) {
                pos[-mymap[i][j]-1][0] = i;
                pos[-mymap[i][j]-1][1] = j;
            }
            else if(mymap[i][j] > 0){
                arr1[asize1++] = (i<<15) + j;
            }
        }
    }
    end1 = tc;
    while(end2 != tc);
    solution();
}

void test2(void* param) {
    asize2 = 0;
    // printf("t2\n");
    mymap = (char(*)[CSIZE]) param;
    plen2 = 0;
    for(rint i = 2500; i < CSIZE; ++i){
        for(rint j = 0; j < CSIZE; ++j){
            if(mymap[i][j] < 0){
                pos[-mymap[i][j]-1][0] = i;
                pos[-mymap[i][j]-1][1] = j;
            }
            else if(mymap[i][j] > 0){
                arr2[asize2++] = (i<<15) + j;
            }
        }
    }
    end2 = tc;
}