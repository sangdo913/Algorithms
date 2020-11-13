#include<iostream>
#include<fstream>
#include<ctime>
#define ADDMAX 10000
#define ADDINIT 1000
#define QUERY_MAX 100000

#define MAKETEST 0

#if MAKETEST  
#include"hyeon9.cpp"
#else
// #include"hyeon9.cpp"
#include"user3.cpp"
// #include"user2.cpp"
#endif

#define CASCADE 30
#define RANDOM 90

#define ADD 40
#define SEARCH 100

#define TC 1

using namespace std;

unsigned long long seed;
unsigned long long mrand(){
    return seed = (seed*214013 + 2531011)%(int)(1e9 + 7);
}

extern void init();
extern void add_str (char *str, int l);
extern int get_str (char *str, int l);
extern int remove_str (char*str, int l);
extern void clear();
int slen;
char str_table[50000][7];
int str_len[50000];

void make_str(fstream *f, int l){
    str_len[l] = mrand()%6+1;
    for(int i = 0; i < str_len[l]; ++i) {
        str_table[l][i] = mrand()%26 + 'a';
    }
    str_table[l][str_len[l]] = 0;
}

int get_res(fstream *f){
    int res = -1;
    if(f){
        (*f) >> res;
    }
    return res;
}

int make_query_str(char *str, int l, char * qstr){
    int cascade = mrand()%100;
    if(cascade > RANDOM){
        l = mrand()%6+1;
        for(int i = 0; i < l; ++i) {
            qstr[i] = mrand()%26 + 'a';
        }
        int a = mrand()%2;
        if(a){
            qstr[mrand()%l] = '*';
        }
        qstr[l] = 0;
        return l;
    }
    if(cascade > CASCADE){
        for(int i = 0; i <= l; ++i){
            qstr[i] = str[i];
        }
        return l;
    }

    int s = (mrand()*214013LL + 2531011LL)%(l+1);
    int e = (mrand()*214013 + 2531011LL)%(l-s+1);
    int qlen = 0;
    for(int i = 0; i < s; ++i){
        qstr[qlen++] = str[i];
    }
    qstr[qlen++] = '*';
    for(int i = l-e; i < l; ++i){
        qstr[qlen++] = str[i];
    }
    qstr[qlen] = 0;
    return qlen;
}

int main() {
#if (MAKETEST)
    fstream file("0Text.txt");
#else
    freopen("0Text.txt", "r", stdin);
#endif
    int add_count = 0;
    char query_str[8];
    clock_t s,e;
    s = clock();
    for (int tc = 1; tc <= TC; ++tc) {
#if (MAKETEST)
        seed = rand();
        file << seed << endl;
#else
        cin >> seed;
#endif
        int score = 100;
        slen = 0;
        init();
        int query= QUERY_MAX;
        while(slen < ADDINIT){
            make_str(0,slen);
            // printf("ADD: %s\n",str_table[slen]);
            add_str(str_table[slen], str_len[slen]);
            slen++;
        }
        int res, user_res, sid;
        int s,e,l, qlen;

        while(query--) {
            int comm = mrand()%100;
            if(comm < ADD) {
                if(slen < ADDMAX) {
                    int duple = mrand()%100;
                    if(duple < 10){
                        make_str(0,slen);
                        // printf("ADD: %s\n",str_table[slen]);
                        add_str(str_table[slen], str_len[slen]);
                        slen++;
                    }
                    else{
                        int sid = mrand()%slen;
                        // printf("ADD: %s\n",str_table[sid]);
                        add_str(str_table[sid], str_len[sid]);
                    }
                }
                else query++;
            }
                
            else if(comm < SEARCH) {
                res = get_res(0);
                sid = mrand()%slen;
                qlen = make_query_str(str_table[sid], str_len[sid], query_str);
                user_res = get_str(query_str, qlen);
#if (MAKETEST)
                file << user_res << endl;
#else
                cin >> res;
#endif
                // printf("SEARCH: query(%s), %d\n",query_str, user_res);
                if(user_res != res){
                    score = 0;
                }
            }
            else {
                res = get_res(0);
                sid = mrand()%slen;
                qlen = make_query_str(str_table[sid], str_len[sid], query_str);
                user_res = remove_str(query_str, qlen);
#if (MAKETEST)
                file << user_res << endl;
#else
                cin >>res;
#endif
                 printf("REMOVE: query(%s), %d\n",query_str, user_res);
                if(user_res != res){
                    score = 0;
                }
            }
        }
        printf("#%d : %d\n", tc, score);
    }
    printf("TIME:%lf\n", (clock()-s)/1000.0);
    clear();
    return 0;
}