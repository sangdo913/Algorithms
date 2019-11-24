#define SIZE 2000
const int LSIZE=  1000000000/SIZE; 
#define PDIV 6 

struct NODE{
    int id,price, area;
    NODE *prev,*next;
    NODE *prev2, *next2;
}nodes[40000];
int nid;

int nn, mm;

int pakagesize[11];
int rsv[1001][11];

NODE head[LSIZE + 1];
NODE pakagesort[11][1000/PDIV+1];

int frd[1001][1000];
int fsize[1001];

void init(int N, int M)
{
    mm = M;
    nid = 0;
    for (register int i = 1; i <= N; ++i)
    {
        frd[i][0] = i;
        fsize[i] = 1;
        for(register int j = 1; j <=M;++j) rsv[i][j] = 0;
    }
    int plen = 1000/PDIV;
    for(register int i = 1; i <=M; ++i) pakagesize[i] = 0 ; 
    for(register int i = 0; i < LSIZE+1; ++i) head[i].prev = head[i].next = head+i;
    for (register int i = 0; i < 11; ++i) for(register int j = 0; j <= plen; ++j) pakagesort[i][j].prev2 = pakagesort[i][j].next2 = pakagesort[i] + j;
}

void befriend(int uid1, int uid2)
{
    frd[uid1][fsize[uid1]++] = uid2;
    frd[uid2][fsize[uid2]++] = uid1;
}

void add(int pid, int area, int price)
{
	NODE& nn = nodes[nid++];
    nn.id = pid, nn.price = price, nn.area = area;
    nn.next = head+pid/SIZE;
    nn.prev = head[pid/SIZE].prev;

    head[pid/SIZE].prev->next = &nn;
    head[pid/SIZE].prev = &nn;
    pakagesize[area]++;

    register NODE* h = pakagesort[area] + price/PDIV;
    register NODE* ed = h;
    h = h->next2;

    while(h!=ed){
        if(h->price > nn.price) break;
        else if(h->price == nn.price && h->id > nn.id) break;
        h = h->next2;
    }

    nn.prev2 = h->prev2;
    nn.next2 = h;

    h->prev2->next2 = &nn;
    h->prev2 = &nn;
}

void reserve(int uid, int pid)
{
    NODE*cursor=  head[pid/SIZE].next; 
    while(cursor != head +pid/SIZE){
        if(cursor->id == pid){
            rsv[uid][cursor->area]++;
            pakagesize[cursor->area]--;

            cursor->next->prev = cursor->prev;
            cursor->prev->next = cursor->next;
            cursor->next2->prev2 = cursor->prev2;
            cursor->prev2->next2 = cursor->next2;
            return;
        }
        cursor = cursor->next;
    }
}

int recommend(int uid)
{
    int most[11] = {-1000,};
    for(register int i = 0; i < fsize[uid]; ++i){
        int id = frd[uid][i];
        for(register int j = 1; j <= mm; ++j){
            most[j] += rsv[id][j];
        }
    }

    int idx[11] = {0,1,2,3,4,5,6,7,8,9,10};
    for(register int i  =0; i <= mm; ++i){
        int temp = idx[i];
        register int j;
        for(j = i; j&& most[temp] > most[idx[j-1]]; --j){
            idx[j] = idx[j-1];
        }
        idx[j] = temp;
    }

    int ret= 0x3f3f3f3f, price = 1000;
    int mostmost = -1;
    int cprice;
    for(register int i = 0; i <= mm; ++i){
        if(most[idx[i]] < mostmost) return ret;
        if(!pakagesize[idx[i]]) continue;
        mostmost = most[idx[i]];
        register int j;
        for(j = 0; j <=price/PDIV; ++j){
            if(pakagesort[idx[i]][j].next2 != pakagesort[idx[i]] + j){
                cprice = pakagesort[idx[i]][j].next2->price;
                if(cprice < price){
                    price = cprice;
                    ret = pakagesort[idx[i]][j].next2->id;
                }
                else if(cprice == price){
                    ret = pakagesort[idx[i]][j].next2->id < ret ? pakagesort[idx[i]][j].next2->id : ret;
                }
                break;
            }
        }
    }
	return -1;
}