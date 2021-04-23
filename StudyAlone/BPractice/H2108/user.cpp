extern void makeCookies(int mID);
#define rint register int
struct LIST{
    int data;
    LIST*n, *p;
}nodes[20000];
int lSize; 
int cookieNum[1001];
struct Order{
    int dayRef;
    int hid;
    int day;
}orders[20000];

struct Cutter{
    int id;
    int size;
    int cookies[10];
} cutters[101];
int nowday;
long long cookieCheck[16];

LIST day[10001];
int mheap[1001][20001];
int orderSize;
int msize;

void heapPush(int idx, int oid){
    int size = ++cookieNum[idx];
    rint* heap = mheap[idx];
    heap[size] = oid;
    
    register int c = size;
    while(c/2 && orders[oid].day < orders[heap[c/2]].day) {
        heap[c] = heap[c/2];
        c >>=1;
    }
    heap[c] = oid;
    cookieCheck[idx/64] |= 1LL<<(idx%64);
}

int heapPop(int hid) {
    int res = mheap[hid][1];
    mheap[hid][1] = mheap[hid][cookieNum[hid]--];
    rint hsize = cookieNum[hid];
    rint *heap = mheap[hid];

    rint p = 1;
    rint c;
    rint o = mheap[hid][1];
    while(p*2 <= hsize){
        c = p*2 + !(p*2+1 > hsize || orders[heap[p*2]].day < orders[heap[p*2+1]].day); 
        if(orders[o].day < orders[heap[c]].day) break;
        heap[p] = heap[c];
        p = c;
    }
    heap[p] = o;

    if(cookieNum[hid] == 0) {
        cookieCheck[hid/64] &= ~(1LL<<(hid%64));
    }
    return res;
}

void init(void)
{
    orderSize = 0;
    lSize = 0;
    for(register int i = 0; i < 16; ++i) cookieCheck[i] = 0;
    for(register int i = 0; i <= 1000; ++i) cookieNum[i] = 0;
    for(register int i = 0; i <=10000; ++i){
        day[i].n = day[i].p = &day[i];
    }
    nowday = 0;
}


void addCookieCutter(int mID, int N, int mShapeList[])
{
    msize = mID;
    Cutter& cutter = cutters[mID];
    cutter.size = N;
    for(register int i = 0; i < N ; ++i){
        int cid = mShapeList[i];
        cutter.cookies[i] = cid;
    }
}

void orderCookie(int mShape, int daysLeft)
{
    daysLeft += nowday;
    Order &order = orders[orderSize];
    order.day = daysLeft*100000 + orderSize;
    order.hid = mShape;
    heapPush(mShape, orderSize);
    order.dayRef = -1;
    if(daysLeft <= 10000){
        LIST& node = nodes[lSize];
        order.dayRef = lSize++;
        node.data = orderSize;
        node.n = &day[daysLeft];
        node.p = day[daysLeft].p;
        day[daysLeft].p->n = &node;
        day[daysLeft].p = &node;
    }
    orderSize++;
}

int checkRemain(int mShape)
{
	return cookieNum[mShape];
}

void newDay(void)
{
    nowday++;
    register LIST *h = &day[nowday];
    register LIST* cur = h->n;
    while(cur !=h){
        if(cur->data != -1){
            int shape = orders[cur->data].hid;
            int cid = -1;
            int check = 0;
            register long long sum = 0;
            for(int i = 1; i <= msize; ++i) {
                register int nowcheck = 0;
                for(register int j = 0; j < cutters[i].size; ++j){
                    int c = cutters[i].cookies[j];
                    nowcheck += (cookieCheck[c/ 64] >> (c%64)) & 1;
                    if(c == shape) nowcheck+=100000;
                }
                if(nowcheck > 100000 && nowcheck > check) {
                    check = nowcheck;
                    cid = i;
                }
            }
            makeCookies(cid);

            for(register int i = 0; i < cutters[cid].size; ++i){
                rint made = cutters[cid].cookies[i];
                if(cookieNum[made] == 0) continue;
                register int del = heapPop(made);
                int delDay =orders[del].dayRef;
                if(delDay != -1) nodes[delDay].data = -1;
            }
        }
        cur = cur->n;
    }
}