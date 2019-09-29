#define STRLEN 17
#define HASHTABLE 200017
#define MAXLEN 300
#define PNUM 100000

struct NODE{
    int score;
    int id;
    char name[17];
    NODE* prev[2], *next[2];
}nodes[PNUM];

NODE list[MAXLEN];
NODE top[HASHTABLE];
int llen[MAXLEN];
int deleted[501];
int arrayList[501][PNUM];
int asize[501];
int size[MAXLEN];
int totalScore = 0;
int qid;
int solved[PNUM];
int tc = 0;

void mymemcpy(char * f, char*t){
    while(*f) *t = *f, ++t, ++f;
    *t = *f;
}

int mystrneq(const char *s1, const char*s2){
    while(*s1 && *s1 == *s2) s1++, s2++;
    return *s1 - *s2;
}

int gethash(const char *s){
    int key = 0;
    while(*s){
        key = ((key<<5) + 5381 +*s)%HASHTABLE;
        ++s;
    }
    return key;
}

void init() {
    qid = 0;
    ++tc;
    for(int i = 0; i < MAXLEN; ++i) for(int j = 0; j < 2;++j) llen[i] = 0, list[i].prev[j] = list[i].next[j] = &list[i], size[i] = 0;
    for(int i = 0; i < HASHTABLE; ++i) for(int j = 0; j < 2; ++j)top[i].next[j] = top[i].prev[j] = &top[i];
    for(int i = 0; i < 501; ++i) deleted[i] = asize[i] = 0;
    totalScore = 0;
}

void add_q(char* name, int point) {
    NODE &nn = nodes[qid];
    nn.id = qid;
    nn.score = point;

    arrayList[point][asize[point]++] = qid;

    nn.next[1] = &list[qid/1000];
    nn.prev[1] = list[qid/1000].prev[1];

    list[qid/1000].prev[1]->next[1] = &nn;
    list[qid/1000].prev[1] = &nn;
    llen[qid/1000]++;

    mymemcpy(name, nn.name);

    int key = gethash(name);

    nn.next[0] = top[key].next[0]; 
    nn.prev[0] = top+key;

    top[key].next[0]->prev[0] = &nn;
    top[key].next[0] = &nn;
    qid++;
}

void solve_specific_num(int num) {
    int count = 0;
    int i;
    for(i = 0; i < MAXLEN; ++i){
        if(count + llen[i] > num) break;
        count+=llen[i];
    }
    NODE* cursor = list + i;
    while(count != num){
        cursor = cursor->next[1];
        ++count;
    }
    totalScore += cursor->score;

    cursor->next[1]->prev[1] = cursor->prev[1];
    cursor->prev[1]->next[1] = cursor->next[1];
    cursor->next[0]->prev[0] = cursor->prev[0];
    cursor->prev[0]->next[0] = cursor->next[0];
    solved[cursor->id] = tc;
    deleted[cursor->score]++;
    llen[i]--;
}

void solve_specific_name(char* name) {
    int key = gethash(name);
    NODE* cursor = top[key].next[0];
    while(cursor != top + key){
        if(!mystrneq(cursor->name, name)) break;
        cursor = cursor->next[0];
    }
    totalScore+=cursor->score;
    for(int i = 0; i < 2; ++i) cursor->prev[i]->next[i] = cursor->next[i], cursor->next[i]->prev[i] = cursor->prev[i];
    solved[cursor->id] = tc;
    llen[(cursor->id)/1000]--;
    deleted[cursor->score]++;
}

int get_total_point() {
    return totalScore;
}

void solve_highest_score(void) {
    int score = 0;
    for(int i = 0; i < 501; ++i) if(asize[i] > deleted[i]) score = i;
    for(int i = 0; i < asize[score]; ++i){
        NODE& n = nodes[arrayList[score][i]];
        if(solved[n.id] != tc){
            solved[n.id] = tc;
            totalScore += score;
            for(int i = 0; i < 2; ++i) n.prev[i]->next[i] = n.next[i], n.next[i]->prev[i] = n.prev[i];
            llen[n.id/1000]--;
            deleted[score]++;
        }
    }
}