#include<iostream>
int nodes[2][200004];

bool MIN(int x, int y){
    return x < y;
}
bool MAX(int x, int y){
    return x > y;
}

bool (*cmp[2])(int a, int b) = {MIN, MAX};
int NONE[2] = {0x3f3f3f3f, -1};

int inittree(int id, int nid, int v, int left, int right, int fid){
    if(id < left||right < id) return NONE[fid];
    if(left == right){
        return nodes[fid][nid] = v;
    }
    int m = (left+right)/2;
    int l = nid*2;
    int r = l+1;
    int lv = inittree(id, l, v, left, m, fid);
    int rv = inittree(id, r, v, m+1, right, fid);

    if(!cmp[fid](lv, rv)) {
        lv = rv;
    }
    if(!cmp[fid](nodes[fid][nid], lv)){
        nodes[fid][nid] = lv;
    }
    return nodes[fid][nid];
}

int getvalue(int id, int left, int right, int start, int end, int fid){
    if(right < start || end < left) return NONE[fid];
    if(left <= start && end <= right) return nodes[fid][id];
    int l = id*2;
    int r = l+1;
    int m = (start+end)/2;
    int lv = getvalue(l, left, right, start, m, fid);
    int rv = getvalue(r, left, right, m+1, end, fid);
    if(!cmp[fid](lv,rv)){
        lv = rv;
    }
    return cmp[fid](lv,rv) ? lv : rv;
}

using namespace std;

int main(){
    freopen("0Text.txt", "r",stdin);
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= 4*n; ++i) nodes[0][i] = 0x3f3f3f3f, nodes[1][i] = -1;
    for(int i  = 1; i <= n; ++i){
        int x ; 
        cin >> x;
        inittree(i,1, x, 1,n, 0);
        inittree(i, 1, x, 1, n, 1);
    }

    // int cnt = 0;
    // for(int i =1; cnt < n;){
    //     for(int j = 0; j < (1<<(cnt)); ++j, ++i){
    //         cout << nodes[1][i] << ' ';
    //     }
    //     cnt++;
    //     cout << endl;
    // }
    while(q--){
        int f,t;
        cin >>f >> t;
        // int mmax = getvalue(1,f,t,1,n,1);
        // int mmin = getvalue(1,f,t,1,n,0);
        cout << getvalue(1, f,t, 1, n, 1) - getvalue(1,f,t,1,n,0) << '\n';
    }
    return 0;
}