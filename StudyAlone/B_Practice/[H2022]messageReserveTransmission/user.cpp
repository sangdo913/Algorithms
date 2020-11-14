#define MAXM	3
#define NSIZE 200002
struct STACK;

struct NODE{
    int time;
    STACK *receive;
    STACK *send;
    bool isread;
    int mid;
    int from, to;
}nodes[NSIZE];

bool cmp(int i, int j){
    if(nodes[i].time == nodes[j].time){
        return nodes[i].to > nodes[j].to; 
    }
    return nodes[i].time < nodes[j].time;
}

int _size;
int PQ[NSIZE];
void push(int i){
    int c = ++_size, p = c/2;
    while(p && cmp(i, PQ[p])){
        PQ[c] = PQ[p];
        c = p;
        p = c/2;
    }
    PQ[c] = i;
}

int getchild(int i){
    int l = i*2, r = l+1;
    if(l >= _size) return 0;
    if(r >= _size) return l;
    if(cmp(PQ[l], PQ[r])) return l;
    return r;
}

int pop() {
    int ret = PQ[1];
    int p = 1;
    int c;
    while((c = getchild(p)) && cmp(PQ[c], PQ[_size])){
        PQ[p] = PQ[c];
        p = c;
    }
    PQ[p] = PQ[_size--];
    return ret;
}

int nid;

struct STACK{
    int mid;
    STACK *n, *p;
}stacks[NSIZE];
int sid;

STACK receivebox[1001];
STACK sendbox[1001];

void init(int N)
{
    nid = 0; 
    sid = 0;
    _size = 0;
    for(int i = 1; i <=N; ++i) receivebox[i].n = receivebox[i].p = &receivebox[i], sendbox[i].n = sendbox[i].p = &sendbox[i];
}

void process(int now){
    while(true) {
        if(!_size) break; 
        if(nodes[PQ[1]].time > now) break;
        int idx = pop();
        NODE &n = nodes[idx];
        if(!n.send) continue;
        STACK &send = stacks[sid++];
        send.mid = n.mid;
        send.n = &receivebox[n.to];
        send.p = receivebox[n.to].p;
        receivebox[n.to].p->n = &send;
        receivebox[n.to].p = &send;
        n.receive = &send;
    }
}

void sendMessage(int cTimestamp, int uID1, int uID2, int mID, int scheduleTimestamp)
{
   process(cTimestamp); 
   STACK &receive = stacks[sid++];
   NODE& message = nodes[mID];
   message.from  =uID1;
   message.to = uID2;
   message.isread = false;
   message.mid = mID;
   message.receive = 0;
   message.send = &receive;
   message.time = scheduleTimestamp;

   receive.mid = mID;
   receive.n = &sendbox[uID1];
   receive.p = sendbox[uID1].p;

   sendbox[uID1].p->n = &receive;
   sendbox[uID1].p = &receive;
   push(mID);
}

int retrieveSentbox(int cTimestamp, int uID, int mIDList[MAXM], int uIDList[MAXM], int readList[MAXM])
{
    process(cTimestamp);
    STACK *cur = sendbox[uID].p;
    int i = 0;
    
    for(i = 0; i < 3; ++i, cur= cur->p) {
       if(cur == &sendbox[uID]) break; 
        mIDList[i] = cur->mid;
        uIDList[i] = nodes[cur->mid].to;
        readList[i] = nodes[cur->mid].isread;
    }
	return i;
}

int retrieveInbox(int cTimestamp, int uID, int mIDList[MAXM], int uIDList[MAXM], int readList[MAXM])
{
    process(cTimestamp);
    STACK *cur = receivebox[uID].p;
    int i = 0;
    for(i = 0; i < 3; ++i, cur=cur->p) {
       if(cur == &receivebox[uID]) break; 
        mIDList[i] = cur->mid;
        uIDList[i] = nodes[cur->mid].from;
        readList[i] = nodes[cur->mid].isread;
    }
	return i;
}

int readMessage(int cTimestamp, int uID, int mID)
{
    process(cTimestamp);
    if(nodes[mID].receive && uID == nodes[mID].to) {
        nodes[mID].isread = true;
        return true;
    } 
    if(nodes[mID].send && uID == nodes[mID].from) {
        return true;
    } 
	return false;
}

int deleteMessage(int cTimestamp, int uID, int mID)
{
    process(cTimestamp);
    if(nodes[mID].receive && uID == nodes[mID].to) {
        nodes[mID].receive->n->p = nodes[mID].receive->p;
        nodes[mID].receive->p->n = nodes[mID].receive->n;
        nodes[mID].receive = 0;
        return true;
    } 
    if(nodes[mID].send && uID == nodes[mID].from) {
        nodes[mID].send->n->p = nodes[mID].send->p;
        nodes[mID].send->p->n = nodes[mID].send->n;
        nodes[mID].send = 0;
        return true;
    } 
    return false;
}