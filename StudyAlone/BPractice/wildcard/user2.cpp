#include<iostream>
#include<vector>
using namespace std;
struct v{
    int *arr;
    int _size;
    int __size;
    int size(){
        return __size;
    }
    void push_back(int i){
        if(_size == __size) {
            _size*=2;
            int* temp = new int[_size];
            for(int i = 0; i < __size; ++i) temp[i] = arr[i];
            if(arr) delete[] arr;
            arr = temp;
        }
        arr[__size++] = i;
    }
    void clear() {
        _size = __size = 0;
        if(arr) delete[] arr;
        arr = 0;
    }
    void resize(int i){
        _size = i;
        __size = 0;
        if(arr) delete[] arr;
        arr = new int[i];
    }
};
int tid;
int tc;
int sid;

//nid, cnt, arr
int nid[50001*14][52];
int cnt[50001*14];
v arr[50001*14];
int chk[50001*14];
void clear(){
    for(int i = 0; i < sid; ++i){
        arr[i].clear();
    }
}

void init(){
    tc++;
    cnt[0] = 0;
    arr[0].resize(1);
    for(int i = 0; i < 52; ++i) nid[0][i] = 0;

    for(int i = 1; i < sid; ++i){
        cnt[i] = 0;
        for(int j = 0; j < 52; ++j){
            nid[i][j] = 0;
        }
    }
    sid = 1;
}

void add_str (char *str, int l) {
    int nowid  =0;
    for(int i = 0; i < l; ++i) {
        int c = str[i] - 'a';
        if(!nid[nowid][c]) {
            nid[nowid][c] = sid;
            arr[sid].clear();
            arr[sid].resize(1);
            cnt[sid] = 0;
            sid++;
        }
        nowid = nid[nowid][c];
    }
    cnt[nowid]++;
    if(chk[nowid] != tc){
        chk[nowid] = tc;
        arr[0].push_back(nowid);
        int id = 0;
        for(int i = 0; i < l; ++i) {
            int rid = id;
            for(int j = 0; j < l-i; ++j) {
                int c = str[l-j-1]-'a'+26;
                if(!nid[rid][c]) {
                    nid[rid][c] = sid;
                    arr[sid].clear();
                    arr[sid].resize(1);
                    sid++;
                }
                rid = nid[rid][c];
                arr[rid].push_back(nowid);
            }
            int c = str[i] - 'a';
            id = nid[id][c];
            arr[id].push_back(nowid);
        }
    }
}
struct RES{
    int n, cascade;
};
RES findid(char *str, int l){
    int e = 0, e2 = 0;
    while(e < l && str[e] != '*') e++;
    bool cascade = e != l;
    e2 = l-e-cascade;
    int findid = 0;
    for(int i = 0; i < e; ++i){
        int c = str[i] - 'a';
        findid = nid[findid][c];
        if(findid == 0) return{-1,0};
    }
    for(int i = 0; i < e2; ++i){
        int c = str[l-1-i]-'a' + 26;
        findid = nid[findid][c];
        if(findid == 0) return{-1,0};
    }
    return {findid, cascade};
}

int get_str (char *str, int l){
    RES info = findid(str,l);
    if(info.n == -1) return 0;
    int res= 0;
    if(info.cascade){
        for(int i = 0; i < arr[info.n].size(); ++i){
            res += cnt[arr[info.n].arr[i]];
        }
    }
    else{
        res = cnt[info.n];
    }
    return res;
}
int remove_str (char*str, int l) {
    RES info = findid(str,l);
    if(info.n == -1) return 0;
    int res= 0;
    if(info.cascade){
        for(int i = 0; i < arr[info.n].size(); ++i) {
             res += cnt[arr[info.n].arr[i]];
             cnt[arr[info.n].arr[i]] = 0;
        }
    }
    else{
        res = cnt[info.n];
        cnt[info.n] = 0;
    }
    return res;
}