int gamepan[10][10];

enum TYPE {EMPTY, Ca, Ba, Cr, Su, De, SIZE};
int shipsize[SIZE] = {0,5,4,3,3,2}; 
int dr[4] = {-1,0,1,0};
int dc[4] = {0,1,0,-1};

struct STATE{
    int r, c;
    int cnt;
}states[10][10];

STATE* list[10*10+1];
int lsize;
int game[10][10];
int kind[SIZE];

void push(STATE* s){
    list[++lsize] = s;

    int c = lsize;
    int p = c>>1;

    while(p && list[p]->cnt < s->cnt){
        list[c] = list[p];
        c = p;
        p = c >>1;
    }
    list[c] = s;
}

int getChild(int idx){
    int l = idx<<1;
    int r = l + 1;

    if(l > lsize) return 0;
    if(r > lsize) return l;
    if(list[l]->cnt < list[r]->cnt) return r;
    return l;
}

STATE* pop(){
    STATE* res = list[1];
    STATE* data = list[lsize--];

    int p = 1, c;
    while((c = getChild(p)) && list[c]->cnt > data->cnt){
        list[p] = list[c];

        p = c;
    } 
    list[p] = data;
    return res;
}

int tc;
int cnt;

extern int fire(int r, int c);

bool isin(int r, int c){
    return 0 <= r && r < 10 && 0 <= c && c < 10;
}

bool check(int r, int c, int dir, TYPE t){
    int size = shipsize[t];

    while(size--){
        if(game[r][c] == tc || !isin(r,c)) return false;
        r += dr[dir];
        c += dc[dir];
    }
    return true;
}

void makePQ(){
    lsize = 0;
    for(register int i = 0; i < 10; ++i) for(register int j = 0; j < 10; ++j){
        states[i][j].cnt = 0;
        states[i][j].r = i, states[i][j].c = j;
        for(int k = 1; k < SIZE;++k){
            if(kind[k] == tc) continue;

            for(int d = 0; d < 4; ++d){
                    if(check(i,j,d,(TYPE)k)) states[i][j].cnt+= 10000 - shipsize[k];
            }
        }
        if(states[i][j].cnt) push(states[i] + j);
    }
}

void init(int limit) { }

bool make(STATE* s, TYPE reculsive){
    int d;
    TYPE t, t2;

    if(reculsive == EMPTY) t = (TYPE)fire(s->r, s->c), game[s->r][s->c] = tc;
    else t= reculsive;
    cnt -= (bool)t;

    int r = s->r, c= s->c;
    int nr, nc;
    int remain = shipsize[t]-1;
    int vis = 0;
    int tx[SIZE] , ty[SIZE];
    
    if(t) {
        t2 = t;
        kind[t] = tc;
        for(d = 0; d < 4; ++d){
            nr = r+dr[d], nc = c + dc[d];
            while(isin(nr,nc) && game[nr][nc] != tc && remain && (t2 = (TYPE)fire(nr,nc)) == t){
                cnt--;
                game[nr][nc] = tc;
                remain--;
                nr+=dr[d], nc += dc[d];
            }
            vis |= (1<<t2);
            if(t2 && t != t2) tx[t2] = nr, ty[t2] = nc;

            if(d<2 && remain +1 != shipsize[t]){
                d += 2;
                nr = r + dr[d], nc = c + dc[d];

                while(remain && fire(nr,nc)){
                    cnt--;
                    game[nr][nc] = tc;
                    remain--;
                    nr += dr[d], nc += dc[d];
                }
            } 

            if(!remain){
                for(int i = 1; i < SIZE; ++i){
                    if(i != t && vis & (1<<i)){
                        make(states[tx[i]]+ty[i], (TYPE)i);
                    }
                }
                return true;
            } 
        }
    }
    return false;
}

void play()
{
    cnt = 17;
    STATE* s;
    ++tc;
    while(cnt) while(makePQ(), s = pop(), !make(s, EMPTY));
}