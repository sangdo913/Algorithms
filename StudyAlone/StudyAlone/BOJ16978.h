#include<iostream>
#include<vector>

using namespace std;

long long value[400004];

struct COD{
    int idx;
    int l, r;
};

vector<COD> vec[100001];
long long res[100001]; int rlen;
int store[100001][2];
int slen = 1;

long long update(const int idx, const long long v, const int st, const int ed, const int l, const int r){
    if(r < st || ed < l){ return value[idx];}
    else if(l <= st && ed <=r){
        value[idx] = v; 
        return value[idx];
    }

    const int m = (st+ed)/2;
    return value[idx] = update(idx*2, v, st,m, l, r)  + update(idx*2+1, v, m+1, ed, l, r);
}

long long get(const int idx, const int st ,const int ed, const int l, const int r){
    if(r < st || ed < l) return 0;

    else if(l <= st && ed <= r){
        return value[idx];
    }

    const int m = (st + ed) /2;
    return get(idx*2, st, m, l,r) + get(idx*2+1, m+1, ed, l,r);
}

int Do(){
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int n, m, v, q, f,t,k;
    cin >> n;
    for(int i =1; i <= n; i++){
        cin >> v;
        update(1,v, 1,n, i,i);
    }

    cin >> m;
    while(m--){
        cin >> q;
        switch(q){
            case 1:
            cin >> f >> v;
            store[slen][0] = f;
            store[slen++][1] = v;
            break;
            case 2:
            cin >> k >> f >> t;
            vec[k].push_back({rlen++,f,t});
            break;
        }
    }


    for(int j = 0;j < vec[0].size(); j++){
        int idx = vec[0][j].idx;
        res[idx] = get(1,1,n,vec[0][j].l, vec[0][j].r);
    }

    for(int i = 1; i < slen; i++){
        update(1,store[i][1],1,n,store[i][0], store[i][0]);

        for(int j = 0; j < vec[i].size(); j++){
            int idx = vec[i][j].idx;
            res[idx] = get(1, 1, n, vec[i][j].l,vec[i][j].r);
        }
    }

    for(int i = 0; i < rlen; i++){
        cout << res[i] << '\n';
    }

    return 0;
}