#include<cstdio>

#define HSIZE 3000017
//for hash
struct NODE{
    int id;
    NODE *p, *n;
} nodes[HSIZE];

int chk[HSIZE];
int cnt[HSIZE];
long long hashkey[HSIZE];
int id[HSIZE];
int hsize;
int isfirst[HSIZE];
NODE heads[HSIZE];

int tc;
int nid;
int conv[256];

void init() {
    hsize =0;
    tc++;
    nid = 0;
    int cnt = 1;
    for(int i = 'a'; i <= 'z'; ++i){
        conv[i] = cnt++;
    }
    conv['*'] = cnt++;
}

int mfind(char *str){
    long long mhash = 0;
    while(*str) {
        mhash = (mhash<<5) + conv[*str++];
    }
    int key = mhash%HSIZE;
    while(chk[key] == tc && hashkey[key] != mhash) { key = ++key%HSIZE; }
    if(chk[key] != tc) {
        hashkey[key] = mhash;
        chk[key] = tc;
        heads[key].p = heads[key].n = &heads[key];
        cnt[nid] = 0;
        id[key] = nid++;
    }
    return key;
}

void add_str (char *str, int l) {
    char hash_str[8];        
    int key = mfind(str);
    int idx = id[key];
    cnt[idx]++;

    if(isfirst[idx] != tc) {
        isfirst[idx] = tc;
        NODE &nn = nodes[hsize++];
        nn.id = idx;

        nn.n = heads[key].n;
        nn.p = &heads[key];
        heads[key].n->p = &nn;
        heads[key].n = &nn;

        for(int s = 0; s <=l; ++s){
            for(int e = 0; s+e <=l; ++e){
                int len = 0;
                for(int i = 0; i < s; ++i) {
                    hash_str[len++] = str[i];
                }
                hash_str[len++] = '*';
                for(int i = 0; i < e; ++i){
                    hash_str[len++] = str[l-e+i];
                }
                hash_str[len] = 0;
                key = mfind(hash_str);
                NODE &nn = nodes[hsize++];
                nn.id = idx;
                nn.n = heads[key].n;
                nn.p = &heads[key];
                heads[key].n->p = &nn;
                heads[key].n= &nn;
            }
        }
    }
    return;
}

int get_str (char *str, int l){
    int key = mfind(str);
    NODE*cur = heads[key].n;
    int res = 0;
    while(cur != &heads[key]){
        res += cnt[cur->id];
        cur = cur->n;
    }
    return res;
}

int remove_str (char*str, int l){
    int key = mfind(str);
    NODE*cur = heads[key].n;
    int res = 0;
    while(cur != &heads[key]){
        int idx = cur->id;
        res += cnt[idx];
        cur = cur->n;
        cnt[idx] = 0;
    }
    return res;
}

void clear(){

}