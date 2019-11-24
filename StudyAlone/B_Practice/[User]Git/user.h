void Branch(const char *str);
void Commit(int line_idx, int operation, const char *str, char* commit_message);
void Checkout(const char *str, int commit_idx, char *msg);
int GetDocument(char str[][15]);
#define HSIZE 10017

struct LINE{
    char str[16];
    int i;
    int len;
    LINE*prev, *next;
} lines[1024*1000];

int remains[1024*1000];
int rlen;

int llen,clen;
int _lsize,_csize;

struct COMMIT{
    COMMIT* p;
    char str[21];
}*commits;

struct BRANCH{
    COMMIT* cid;
    char str[16];
    int slen;
    LINE head;
}branches[1001];
int blen;

int myhash[HSIZE];
BRANCH *now;

int mystrcpy(const char *f, char *t){
    int res = 0; 
    while(*f) *(t++) = *(f++),res++;
    *t = 0;
    return res;
}

int mystrcmp(char *a, char *b){
    while(*a && *a == *b) ++a, ++b;
    return *a - *b;
}

void Init();

void Init() {
    for(int i = 0; i < 1024*1000; ++i) remains[i] = i,lines[i].i = i;
    rlen = 1024*1000;

    if(_csize)delete[](commits);
    commits = new COMMIT[10];
    _csize = 10;
    clen = 0;

    blen = 1;
    branches[0].head.next = branches[0].head.prev = &branches[0].head;
    branches[0].cid = 0;
    branches[0].slen = 0;
}

unsigned int gethash(const char *str){
    unsigned int ret = 0;
    while(*str){
        ret = (ret + (*str << 5) +5381) % HSIZE;
        str++;
    }
    return ret;
}

// LINE* linealloc(){
//     if(llen == _lsize){
//         LINE* l = new LINE[_lsize*2];
//         for(register int i = 0; i < _lsize; ++i) {
//             l[i].i = i;
//             l[i].len = mystrcpy(lines[i].str, l[i].str), 
//             l[i].prev = l + lines[i].prev->i;
//             l[i].next = l + lines[i].next->i;
//         }
//         delete[](lines);
//         _lsize = _lsize*2;
//     }
//     lines[llen].i = llen;
    
//     return lines + llen++;
// }

COMMIT* commitalloc(){
    if(clen == _csize){
        COMMIT* c = new COMMIT[_csize*2];
        for(register int i = 0; i < _csize; ++i){
            c[i].p = commits[i].p;
            mystrcpy(commits[i].str, c[i].str);
        }
        delete[](commits);
        commits = c;
        _csize *=2;
    }

    return commits+ clen++;
}

void Branch(const char *str) {
    unsigned int h = gethash(str);
    
    while(myhash[h] != -1) h = ++h%HSIZE;
    myhash[h] = blen;
    BRANCH &nb = branches[blen++];
    nb.head.next = nb.head.prev = &nb.head;
    nb.cid = now->cid;

    LINE* cursor = now->head.next;

    while(cursor != &now->head){
        cursor = cursor->next;
        LINE* nn = lines + remains[--rlen];
        nn->len = mystrcpy(cursor->str, nn->str);
        nn->prev= nb.head.prev;
        nn->next = &nb.head;
        
        nb.head.prev->next = nn;
        nb.head.prev = nn;
    }

    mystrcpy(str, nb.str);
};


void Commit(int line_idx, int operation, const char *str, char* commit_message) {
    COMMIT *nc = commitalloc();
    nc->p = now->cid;
    now->cid = nc;

    mystrcpy(commit_message, nc->str);
    LINE *line = &now->head;
    line_idx++;

    while(line_idx--){
        if(line->next == &now->head){
            LINE* nl = line +  remains[--rlen];
            nl->len = 0;
            nl->prev= now->head.prev;
            nl->next = &now->head;

            now->head.prev->next = nl;
            now->head.prev = nl;
        }
        line = line->next;
    }

    switch(operation){
        case 0:
        line->len += mystrcpy(str,line->str + line->len);
        break;
        case 1:
        line->len = mystrcpy(str,line->str);
        break;
        case 2:
        line->prev->next = line->next;
        line->next->prev = line->prev;
        remains[rlen++] = line->i;
        break;
    }
}
void Checkout(const char *str, int commit_idx, char *msg) {
    unsigned int h = gethash(str);
    while(mystrcpy(str, branches[myhash[h]].str)) h = ++h%HSIZE;
    COMMIT *c = branches[myhash[h]].cid;

    while(commit_idx--) c = c->p;

    msg = c->str;
}
int GetDocument(char str[][15]) {
    LINE *cursor = now->head.next;
    int idx = 0;
    while(cursor != &now->head){
        mystrcpy(cursor->str, str[idx]);
        idx++;
    }
	
	return idx;
}