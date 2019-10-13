#define LSIZE 1000000
#define SIZE 1000

struct NODE{
    int id,price, area;
    NODE *l,*r,*p;
    NODE *prev,*next;
}nodes[40000];
int nid;

NODE pakage[11];
int nn, mm;

int pakagesize[11];
int rsv[1001][11];

NODE head[LSIZE + 1];

bool cmp(NODE* n1, NODE*n2){
    if(n1->price == n2->price){
        return n1->id < n2->id;
    }
    return n1->price < n2->price;
}

int frd[1001][1000];
int fsize[1001];

void insert(NODE* p, NODE* nn){
    while(true){
        if(cmp(nn,p)){
            if(!p->l){
                nn->p = p;
                p->l = nn;
                return;
            }
            p = p->l;
        }
        else{
            if(!p->r){
                nn->p = p;
                p->r = nn;
                return;
            }
            p = p->r;
        }
    }
}

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
    for(int i = 1; i <=M; ++i)pakage[i].r = pakage[i].l=0 , pakagesize[i] = 0, pakage[i].price = 0x3f3f3f3f;
    for(register int i = 0; i < LSIZE; ++i) head[i].prev = head[i].next = head+i;
}

void befriend(int uid1, int uid2)
{
    frd[uid1][fsize[uid1]++] = uid2;
    frd[uid2][fsize[uid2]++] = uid1;
}

void add(int pid, int area, int price)
{
	NODE& nn = nodes[nid++];
    nn.l = nn.r = 0;
    nn.id = pid, nn.price = price, nn.area = area;
    nn.next = head+pid/SIZE;
    nn.prev = head[pid/SIZE].prev;

    head[pid/SIZE].prev = head[pid/SIZE].prev->next = &nn;
    insert(pakage + area, &nn);
    
    nn.next = head + pid/SIZE;
    nn.prev = head[pid/SIZE].prev;

    head[pid/SIZE].prev = head[pid/SIZE].prev->next = &nn;
    pakagesize[area]++;
}

NODE* getleast(NODE* p){
    while(p->l){
        p = p->l;
    }
    return p;
}

void del(NODE *p){
    NODE* sel = 0;
    if(p->l && p->r){
        sel = p->r;
        sel = getleast(sel);
        sel->l = p->l;
        p->l->p = sel;

        if(p->r != sel){
            sel->p->l = sel->r;
            if(sel->r)sel->r->p = sel->p;
            sel->r = p->r;
            p->r->p = sel;
        }
    }
    else if(p->l){
        sel = p->l;
    }
    else if(p->r){
        sel = p->r;
    }

    if(sel) sel->p = p->p;
    if(p->p->l == p) p->p->l = sel;
    else p->p->r = sel;
    p->prev->next = p->next;
    p->next->prev= p->prev;
}

void reserve(int uid, int pid)
{
    NODE*cursor=  head[pid/SIZE].next; 
    while(cursor != head +pid/SIZE){
        if(cursor->id == pid){
            break;
        }
        cursor = cursor->next;
    }
    del(cursor);
    rsv[uid][cursor->area]++;
    pakagesize[cursor->area]--;
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
    for(int i  =0; i <= mm; ++i){
        int temp = idx[i];
        register int j;
        for(j = i; j&& most[temp] > most[idx[j-1]]; --j){
            idx[j] = idx[j-1];
        }
        idx[j] = temp;
    }

    int ret= 0x3f3f3f3f, price = 0x3f3f3f3f;
    int mostmost = -1;
    for(int i = 0; i <= mm; ++i){
        if(most[idx[i]] < mostmost) return ret;
        if(!pakagesize[idx[i]]) continue;
        mostmost = most[idx[i]];
        NODE *n = getleast(pakage[idx[i]].l);

        if(price > n->price){
            ret =n->id;
            price = n->price;
        }
        else if(price == n->price) {
            if(n->id < ret){
                ret = n->id;
                price = n->price;
            }
        }
    }
	return -1;
}