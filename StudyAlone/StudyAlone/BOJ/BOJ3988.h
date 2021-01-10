#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

int arr[1000000];

int main() {
    freopen("0Text.txt", "r",stdin);
    priority_queue<pair<int, int>> pq;

    int n,k;
    scanf("%d %d", &n, &k);

    for(int i = 0; i < n; ++i){
        scanf("%d", &arr[i]);
    }

    sort(arr, arr+n);

    int res = 0x3f3f3f3f;
    for(int j = 0; j < n-k-1;++j){
        pq.push({arr[j] - arr[j+1], j});
    }
    for(int i = 0; i <= k; ++i){
        int M = arr[i+n-k-1] - arr[i];
        while(pq.top().second < i) pq.pop();
        auto [m, a] = pq.top();
        res = min(res, M-m);
        pq.push({arr[i+n-k-1] - arr[i+n-k], i+n-k-1});
    }
    printf("%d\n", res);

    return 0;
}

//segtree
// #include<iostream>
// #include<cstring>
// #include<algorithm>

// using namespace std;

// int arr[1000000];
// int diff[1000000];
// int segtree[1000000*4];

// void init(int i, int idx, int v, int l, int r){
//     if(idx < l || r <= idx){
//         return;
//     }

//     if(l+1 == r){
//         segtree[i] = v;
//         return;
//     }
//     int m = (l+r)/2;
//     init(i*2, idx,v, l, m);
//     init(i*2+1, idx, v, m,r);
//     segtree[i] = min(segtree[i*2], segtree[i]);
//     segtree[i] = min(segtree[i*2+1], segtree[i]);
// }

// int query(int i, int l, int r, int s, int e) {
//     if(e <= l || r <= s) return 0x3f3f3f3f;
//     if(s <= l && r <= e){
//         return segtree[i];
//     }
//     int m = (l+r)/2;
//     int le = query(i*2, l,m, s,e);
//     int ri = query(i*2+1, m,r, s,e);
//     return min(le,ri);
// }

// int main() {
//     freopen("0Text.txt", "r",stdin);
//     memset(segtree, 0x3f, sizeof(segtree));

//     int n,k;
//     scanf("%d %d", &n, &k);

//     for(int i = 0; i < n; ++i){
//         scanf("%d", &arr[i]);
//     }

//     sort(arr, arr+n);
//     for(int i = 1; i < n; ++i) {
//         diff[i-1] = arr[i] - arr[i-1];
//         init(1, i-1, diff[i-1], 0,n);
//     }


//     int res = 0x3f3f3f3f;
//     for(int i = 0; i <= k; ++i){
//         int M = arr[i+n-k-1] - arr[i];
//         int m = query(1, 0,n, i, i+n-k-1);
//         res = min(res, m+M);
//     }
//     printf("%d\n", res);

//     return 0;
// }