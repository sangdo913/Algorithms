#include<iostream>

using namespace std;

long long node[400004];
long long lazy[400004];

long long update(const int idx,const long long value,  const int st, const int ed, const int left, const int right){
    if(lazy[idx]){
        node[idx] += lazy[idx]*(ed-st+1);

        if(st != ed){
            lazy[idx*2] += lazy[idx];
            lazy[idx*2+1] += lazy[idx];
        }
        lazy[idx] = 0;
    }

    if(right < st || ed < left) return node[idx];

    if(left <= st && ed <= right){
        node[idx]+= value*(ed-st+1);

        if(st != ed){
            lazy[idx*2] += value;
            lazy[idx*2+1] += value;
        }
        return node[idx];
    }
    
    const int m = (st + ed)/2;

    return node[idx] = update(idx*2, value, st, m, left, right) + update(idx*2+1, value, m+1, ed, left, right);
}

long long get(const int idx, const int st, const int ed, const int left, const int right){
    if(lazy[idx]){
        node[idx] += lazy[idx]*(ed-st+1);

        if(st != ed){
            lazy[idx*2] += lazy[idx];
            lazy[idx*2+1] += lazy[idx];
        }

        lazy[idx] = 0;
    }

    if(right < st || ed < left) return 0;
    else if(left <= st && ed <= right){
        return node[idx];
    }

    const int m = (st+ed)/2;
    return get(idx*2, st, m, left, right) + get(idx*2+1, m+1, ed, left, right);
}

int Do(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n;
    cin >> n;

    for(int i = 1; i <=n; i++){
        int in; 
        cin >> in;

        update(1, in, 1, n, i,i);
    }

    int m;
    cin >> m;
    while(m--){
        int q;
        int f, t;
        long long v;
        cin >> q;
        switch(q){
            case 1:
            cin >> f >>t >> v ;
            update(1,v,1,n,f,t);
            break;
            case 2:
            cin >>f;
            cout << get(1,1,n,f,f) << '\n';
            break;
        }
    }
    return 0;
}