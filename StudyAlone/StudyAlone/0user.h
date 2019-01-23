int mlist[11][50000];
int mlen[11];

int mr[50001];
int mc[50001];
int type[50001];

void init(int N){
    for(int i = 0; i <= 10; i++) mlen[i] = 0;
}

void add(int mId, int mType, int y, int x){
    int& len = mlen[mId];
    mr[mId] = y;
    mc[mId] = x;
    type[mId] = mType;

    
    mlist[0][mlen[0]++] = mlist[mType][len++] = mId;
}

void remove(int mId){
   int& t = type[mId]; 
   int didx = 0;

   for(int i = 0; i < mlen[t]; i++){
       if(mlist[t][i] == mId) break;
   }

    mlist[t][didx] = mlist[t][t-1];
    --t;

    didx = 0;
    for(int i = 0; i < mlen[0]; i++){
        if(mlist[0][i] == mId) break;
    }

    mlist[0][didx] = mlist[0][mlen[0]-1];
    --mlen[0];
}

#define DIST(x,y) ((x)-(y))*((x)-(y))

int search1(int mType, int mY, int mX, int radius){
    int ret = 0;
    radius *= radius;
    for(int  i= 0; i < mlen[mType]; i++){
        int dist = DIST(mr[mlist[mType][i]], mY) + DIST(mc[mlist[mType][i]], mX);
        ret += dist <= radius;
    }

    return ret;
}
int search2(int mType, int mY, int mX, int mList[5]){
    int len = mlen[mType];

    for(int i = 0; i < len; i++){
        int idx = mlist[mType][i];
        int j = 4;
        int dist = mList[4] == 0 ? 0xffffffff : DIST(mY, mr[mList[4]]) + DIST(mX, mc[mList[4]]);
        int dist2 = DIST(mY, mr[idx]) + DIST(mX, mc[idx]);
        for(int i = 0; i < 5; i++){
            if()
        }
    } 
    return 1;
}

/*
void add(int mId, int mType, int y, int x){
    
}
void remove(int mId){
    
}
int search1(int mType, int mY, int mX, int radius){
    return 0;
}
int search2(int mType, int mY, int mX, int mlist[5]){
    return 1;
}
*/