struct NODE{
    int id,price;
    NODE *l,*r,*p;
    NODE *prev,*next;
}nodes[40000];
int nid;

NODE pakage[11];
int nn, mm;

int parent[1001];
int pakagesize[11];
int rsv[1001][11];

NODE head[100001];

bool cmp(NODE* n1, NODE*n2){
    if(n1->price == n2->price){
        return n1->id < n2->id;
    }
    return n1->price < n2->price;
}

int frd[1001][1000];

void insert(NODE* p, NODE* nn){
    while(true){
        if(cmp(p,nn)){
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

int getP(int a){
    int pa = parent[a];
    if(pa > 0 ) parent[a] = getP(pa); 
    else return a;
}

void join(int a, int b){
    int pa = getP(a);
    int pb = getP(b);

    if(parent[pa] > parent[pb]){
        pa^=pb^=pa^=pb;
    }
    for(int i = 0; i < -parent[pb]; ++i){
        frd[pa][-(parent[pa]--)] = frd[pb][i];
    }
    parent[pb] = pa;
}

void init(int N, int M)
{
    nn = M;
    nid = 0;
    for (int i = 1; i <= N; ++i)
    {
        parent[i] = -1, frd[i][0] = i;
        for(int j = 1; j <=M;++j) rsv[i][j] = 0;
    }
    for(int i = 1; i <=M; ++i)pakagesize[i] = 0, pakage[i].price = 0x3f3f3f3f;
    for(int i = 0; i < 100000; ++i) head[i].prev = head[i].next = head+i;
}

void befriend(int uid1, int uid2)
{
    join(uid1,uid2);
}

void add(int pid, int area, int price)
{
	NODE& nn = nodes[nid++];
    insert(pakage + area, &nn);
    
    nn.next = head + pid/10000;
    nn.prev = head[pid/10000].prev;

    head[pid/10000].prev = head[pid/10000].prev->next = &nn;
}

void del(NODE *p){
    NODE* sel = 0;
    if(p->l && p->r){
        sel = p->r;
        sel = getleast(sel);
        sel->l = p->l;
    }
    else if(p->l){
        sel = p->l;
    }
    else if(p->r){
        sel = p->r;
    }

    if(p->p->l == p) p->l = sel;
    else p->r = sel;
}

void reserve(int uid, int pid)
{
    NODE*cursor=  head[pid/10000].next; 
    while(cursor != head +pid/10000){
        if(cursor->id == pid){
            break;
        }
        cursor = cursor->next;
    }
    del(cursor);
}

NODE* getleast(NODE* p){
    while(p->l){
        p = p->l;
    }
    return p;
}
int recommend(int uid)
{
    int most[11] = {0,};
    for(int i = 0; i < -parent[uid]; ++i){
        int id = frd[uid][i];
        for(int j = 1; j <= mm; ++j){
            most[j] += rsv[id][j];
        }
    }

    int idx[10] = {1,2,3,4,5,6,7,8,9,10};
    for(int i  =1; i < mm; ++i){
        int temp = idx[i];
        int j;
        for(j = i; j&& most[temp] < most[idx[j-1]]; --j){
            most[idx[j]] = most[idx[j-1]];
        }
        idx[j] = temp;
    }

    int ret, price = 0x3f3f3f3f;
    int mostmost = 0x3f3f3f3f;
    for(int i = 0; i < mm; ++i){
        if(pakagesize[idx[i]] == 0) continue;
        if(most[idx[i]] > mostmost) return ret;
        mostmost = most[idx[i]];
        NODE *n = getleast(&pakage[idx[i]]);

        if(price > n->price) price = n->price;
    }
	return -1;
}