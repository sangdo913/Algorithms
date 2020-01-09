#include<iostream>

using namespace std;
int tc, n;
int adj[400][400];
int asize[400];
int info[200][2];

void makevertex(){
    for(int i = 0; i < 2*n; i+=2){
        int j = i+1;
        adj[2*i+1][asize[2*i+1]++] = 2*j;
        adj[2*j+1][asize[2*j+1]++] = 2*i;
    }
    for(int i = 0 ; i < 2*n; ++i){
        for(int j = 0; j < i; ++j){
            if(info[j][1] <= info[i][0] || info[i][1] <= info[j][0] ) continue; 
                adj[2*i][asize[2*i]++] = 2*j+1;
                adj[2*j][asize[2*j]++] = 2*i+1;
        }
    }
}

int mystack[400];
int top;

int scc[400];
int order[400];
int nid;
int sccid;
int mybool[400];
int countsort[400];
int mycount[400];

#define MIN(x,y) ((x) > (y) ? (y) : (x))

int tajanscc(int node){
    order[node] = nid++;
    mystack[top++] = node;
    int id = order[node];

    for(int i = 0; i < asize[node]; ++i){
        int next = adj[node][i];

        if(order[next] == -1){
            order[node] = MIN(tajanscc(next), order[node]);
        }
        else if(scc[next] == -1){
            order[node] = MIN(order[next], order[node]);
        }
    }
    if(id == order[node]){
        while(top){
            int now = mystack[--top];
            scc[now] = sccid;
            if(now == node) break; 
        }
        sccid++;
    }
    return order[node];
}

int main(){
    freopen("0Text.txt", "r", stdin);
    int T;
    int c,d;
    scanf("%d", &T);
    for(tc = 1;tc <= T; ++tc){
        sccid = top = nid = 0;
        scanf("%d", &n);
        for(int i = 0; i < 4*n; ++i) {
            mybool[i] = -1;
            mycount[i] = 0;
            scc[i] = -1;
            asize[i] = 0;
            order[i] = -1;
        }

        for(int i = 0; i < n; i++){
            scanf("%d %d", &info[2*i][0], &info[2*i][1]);
            scanf("%d %d", &info[2*i+1][0], &info[2*i+1][1]);
        }
        makevertex();
        for(int i = 0; i < 4*n; ++i){
            if(scc[i] == -1) tajanscc(i);
        }
        bool res = true;
        for(int i = 0; i < 2*n; ++i){
            if(scc[2*i] == scc[2*i+1]) {
                res = false;
                break;
            }
        }
        if(!res) printf("IMPOSSIBLE\n");
        else{
            printf("POSSIBLE\n");
            for(int i = 0; i < 4*n;++i){
                mycount[scc[i]]++;
            }
            for(int i =sccid-2; i >= 0; --i) mycount[i] += mycount[i+1];
            for(int i = 0; i < 4*n; ++i){
                countsort[--mycount[scc[i]]] = i;
            }
            for(int i = 0; i < 4*n; ++i){
                int id = countsort[i];
                int v = id/2;
                if(mybool[v] != -1) continue;
                mybool[v] = (id & 1);
            }
            for(int i = 0; i < 2*n; i+=2){
                if(mybool[i]) printf("%d %d\n", info[i][0], info[i][1]);
                else printf("%d %d\n", info[i+1][0], info[i+1][1]);
            }
        }
    }
    return 0;
}