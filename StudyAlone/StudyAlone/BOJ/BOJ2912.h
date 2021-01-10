#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>

using namespace std;

int arr[300001];
int major[300001*4];
int vote[300001*4];
vector<int> cap[10001];

void update(int i, int idx,int v, int s, int e) {
    if(idx < s) return;
    if(e <= idx) return;
    if(s + 1 == e){
        major[i] = arr[s];
        vote[i] = 1;
        return;
    }
    int l = i*2;
    int r = l+1;
    int m= (s+e)/2;
    update(l, idx, v,s,m);
    update(r, idx, v,m,e);
    if(major[l] == major[r]){
        major[i] = major[l];
        vote[i] = vote[l] + vote[r];
    }
    else if(vote[l] < vote[r]){
        major[i] = major[r];
        vote[i] = vote[r] - vote[l];
    }
    else{
        major[i] = major[l];
        vote[i] = vote[l] - vote[r];
    }
}

pair<int,int> query(int i, int s, int e, int l, int r) {
    if(e <= l || r <= s) return {0,0};
    if(l <= s && e <= r){
        return {major[i], vote[i]};
    }
    int m = (s+e)/2;
    auto[lmajor, li] = query(i*2  , s,m, l,r);
    auto[rmajor, ri] = query(i*2+1, m,e, l,r);
    pair<int,int> res;
    if(lmajor == rmajor){
        res.first = lmajor;
        res.second = li+ri;
    }
    else if(li < ri){
        res.first = rmajor;
        res.second = ri - li;
    }
    else{
        res.first = lmajor;
        res.second = li-ri;
    }
    return res;
}

int main(){
    freopen("0Text.txt","r", stdin);
    int n, c;
    scanf("%d %d\n", &n,&c);
    for(int i = 1; i <= c; ++i) cap[i].clear();
    for(int i = 1; i <= n; ++i) {
        scanf("%d", & arr[i]);
        cap[arr[i]].push_back(i);
        update(1, i, 1, 1, n+1);
    }

    int m;
    scanf("%d", &m);
    for(int i = 0; i < m; ++i){
        int f,t;
        scanf("%d %d", &f, &t);
        auto [ma, num] = query(1, 1, n+1, f,t+1);
        // printf("(%d ~ %d), major:%d num: %d\n",f,t, ma , num);
        bool find = false;
        
        if(num){
            int le = lower_bound(cap[ma].begin(), cap[ma].end(), f)- cap[ma].begin();
            int ri = upper_bound(cap[ma].begin(), cap[ma].end(), t) - cap[ma].begin();
            // printf("%d %d\n", ri,le);
            if(ri - le > (t-f+1)/2) find = true;
        }
        if(find) printf("yes %d\n", ma);
        else printf("no\n");
    }
    return 0;
}