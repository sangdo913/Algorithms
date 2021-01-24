#include<iostream>
#include<algorithm>

using namespace std;
struct NODE{
    int v;
    NODE *p, *n;
}lists[100002];
int arr[100002];
int dest[100002];
int pos[100002];
int dpos[100002];
int fenwick[100002];

int main(){
    freopen("0Text.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    lists[0].n = &lists[1];
    lists[n+1].p = &lists[n];
    for(int i = 1; i <= n; ++i){
        scanf("%d", &arr[i]);
        pos[arr[i]] = i;
        lists[i].v = i;
        lists[i].p = &lists[i-1];
        lists[i].n = &lists[i+1];
        // printf("%d ", arr[i]);
    }
    // printf("\n");
     
    for(int i = 1; i <= n; ++i){
        scanf("%d", &dest[i]);
    }

    for(int i = 1; i <= n-2; ++i){
        int idx = pos[dest[i]];
        lists[idx].n->p = lists[idx].p;
        lists[idx].p->n = lists[idx].n;
        int v = idx;
        while(v) {
            idx -= fenwick[v];
            v -= v&-v;
        }
        if(!(idx & 1)) {
            int n1 = lists[0].n->v;
            int n2 = lists[0].n->n->v;
            int v1 = arr[n1];
            int v2 = arr[n2];
            pos[v1] = n2;
            pos[v2] = n1;
            arr[n1] = v2;
            arr[n2] = v1;
        }
        v = pos[dest[i]];
        while(v<=n) {
            fenwick[v]++;
            v += v&-v;
        }
        // NODE *cur = lists[0].n;
        // while(cur !=&lists[n+1]){
        //     printf("%d ", arr[cur->v]);
        //     cur = cur->n;
        // }
        // printf("\n");
    }
    // printf("%d %d\n", lists[0].n->v, lists[0].n->n->v);
    if(pos[dest[n-1]] != lists[0].n->v) printf("impossible\n");
    else printf("possible\n");

    // for(int i = 1; i <= n; ++i) printf("%d ", arr[i]);
    // printf("\n");
    // for(int i = 1; i <= n; ++i) printf("%d ", dest[i]);
    // printf("\n");
    return 0;
}