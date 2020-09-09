#define MAX_WORD_LIST 50000
#define RANGE 3500
#define rint register int

struct NODE{
    int idx;
    char c;
    NODE *p, *n;
} nodes[50000];
int N;

NODE myhash[26*26*26][50000/RANGE+1];
int conv[256];
char *str;

void init(int n, char Word[])
{
    N = n;
    int cnt = 0;
    for(int i = 'a'; i <= 'z'; ++i) conv[i] = cnt++;
    for(rint i = 0; i < 26*26*26; ++i){
        for(rint j = 0; j <= n/RANGE; ++j)
            myhash[i][j].p = myhash[i][j].n = &myhash[i][j];
    }

    str = Word;

    for(register int  i = 0; i <= n-3; ++i) {
        rint key = conv[Word[i]]*26*26 + conv[Word[i+1]]*26+conv[Word[i+2]];
        nodes[i].idx = i;
        str[i] = Word[i];
        NODE &head = myhash[key][i/RANGE];
        nodes[i].p = head.p;
        nodes[i].c = Word[i];
        nodes[i].n = &head;
        head.p->n = &nodes[i];
        head.p = &nodes[i];
    }
}

#define GETHASH(str, i) conv[str[i]]*26*26 + conv[str[i+1]]*26 + conv[str[i+2]]

int change(char str1[], char str2[])
{
    rint k1 = conv[str1[0]]*26*26 + conv[str1[1]]*26 + conv[str1[2]];
    rint nidx = -1;
    rint res = 0;
    register NODE* nxt;
    for(register int i = 0; i <= N/RANGE; ++i) {
        for(register NODE* head = myhash[k1][i].n; head != &myhash[k1][i]; head = nxt){
            rint idx = head->idx;
            if(idx < nidx) continue;
            res++;
            nidx = idx+3;
            nxt = head->n;
            while(nxt != &myhash[k1][i] && nxt->idx < nidx) nxt = nxt->n;

            str[idx] = str2[0];
            str[idx+1] = str2[1];
            str[idx+2] = str2[2];

            for (rint j = (idx-2 < 0 ? 0 : idx-2); j < (idx+3 < N-2 ? idx+3 : N-2); ++j) {
                rint k1 = GETHASH(str, j);
                register NODE* h = &myhash[k1][j/RANGE];
                nodes[j].p->n = nodes[j].n;
                nodes[j].n->p = nodes[j].p;
                
                register NODE* cur = h->n;

                while(h!= cur && j > cur->idx) {
                    cur = cur->n;
                }

                nodes[j].n = cur;
                nodes[j].p = cur->p;
                cur->p->n = &nodes[j];
                cur->p = &nodes[j];
            }
        }
    }
    return res;
}

void result(char Result[])
{
    for(rint i = 0; i < N; ++i){
        Result[i] = str[i];
    }
}
