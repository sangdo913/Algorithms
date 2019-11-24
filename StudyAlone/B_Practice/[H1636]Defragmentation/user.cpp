#define DISK_SIZE  20000
#define BUF_SIZE   64
#define MAX_FILE   10

extern int getdiskSize();
extern int readDisk(int* buf, int addr, int size);
extern int move(int from, int to, int size);

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
int nowdisk[DISK_SIZE];
int tempdisk[DISK_SIZE];

struct NODE{
    int fid;
    int pos;
    int size;
    int idx;
    NODE *prev, *next;
}nodes[20000];

NODE file[10]; 
int len;
int cnt[10];
int pos[DISK_SIZE];

void swap(int *a, int *b, int size){
    int temp;
    for(register int i = 0; i < size;++i){
       temp = a[i];
       a[i] = b[i];
       b[i] = temp;
    }
}

void insert(NODE *head, NODE *node){
    node->next = head;
    node->prev = head->prev;

    head->prev->next = node;
    head->prev = node;
}

void del(NODE* node){
    node->prev->next = node->next;
    node->next->prev = node->prev;
}
NODE notused;

void disk_reset(int st, int ed){
    notused.prev = notused.next = &notused;
    for(int i = 0; i < 10; ++i) file[i].prev = file[i].next = file + i;

    for(int i = st; i < ed; ++i) {
        NODE &n = nodes[i];
        n.idx = i;
        n.next = &notused;
        n.prev = notused.prev;

        notused.prev->next =  &n;
        notused.prev = &n;
    }
    int prev= -1;
    NODE* n;

    for(register int i = st; i < ed; ++i) {
        if(prev != nowdisk[i]){
            prev = nowdisk[i];

            n = notused.next;
            n->size = 1;
            n->pos = i;
            n->prev->next = n->next;
            n->next->prev = n->prev;
            n->fid = nowdisk[i];

            n->next = file + n->fid;
            n->prev = file[n->fid].prev;

            file[n->fid].prev->next = n;
            file[n->fid].prev = n;
        }
        else n->size++;

        pos[i] = n->idx;
    }
}

void make(NODE* n, int size){
    if(n->size > size){
        NODE* nn = notused.next;
        del(nn);
        nn->fid = n->fid;
        nn->size = n->size - size;
        nn->pos = n->pos + size;

        insert(file + nn->fid, nn);
        for(int i = 0; i < nn->size; ++i) pos[i+nn->pos] = nn->idx;
    }
}

int swap(NODE* from, NODE* to){
    int res = from->size < to->size? from->size : to->size;
    res = res < BUF_SIZE ? res : BUF_SIZE;

    swap(nowdisk + from->pos, nowdisk + to->pos, res);
    swap(pos + from->pos, pos + to->pos, res);

    move(from->pos, to->pos, res);

    make(from, res); make(to,res);
    
    int temp = from->pos;
    from->pos = to->pos;
    to->pos = temp;
    from->size = to->size = res;

    return res;
}

void go(int* des, int dlen){
    for(register int i = 0; i < len; ++i) nowdisk[i] = tempdisk[i];

    int prev = -1;
    int nid  = 0;
    disk_reset(0, len);

    register NODE* n,*nn;

    int cursor = 0;

    for(int d = 0; d < dlen; ++d){
        int did = des[d];

        int size = cnt[des[d]];
        int alloc = 0;
        int nid, fid;

        while(alloc != size){
           nid = pos[cursor];
           fid = nodes[nid].fid;

           if(fid == did) {
               cursor += nodes[nid].size;
               alloc += nodes[nid].size;
               n = nodes + nid;

               del(n);
               insert(&notused, n);

               continue;
           }

            int res;
            if(fid){
                n = nodes+nid;
                nn = file[0].next;
                swap(n, nn);
            }

           n = file[did].next;
           nn = nodes + pos[cursor];

           res = swap(n, nn);
           del(n);
           insert(&notused, n);

           alloc += res;
           cursor+= res;
           
            disk_reset(cursor, len);
        }
    }
}

int arr[10] = {1,2,3,4,5,6,7,8,9};
int dlen;

void defragment()
{
    len = getdiskSize();
    dlen=0;

    for(int i = 0; i < 10; ++i) cnt[i] = 0;

    readDisk(tempdisk, 0,len); 

    for(int i = 0; i < len; i++){
        if(cnt[tempdisk[i]]++ == 0 && tempdisk[i]) arr[dlen++] = tempdisk[i];
    }
    go(arr, dlen);
}