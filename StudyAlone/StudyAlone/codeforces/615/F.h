#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;
vector<int> adj[200001];
#define MAX(x,y) ((x) > (y) ? (x) : (y))
int depth[2][200001];
int info[200001];
int infod2[2][200001];
int treesize[200001];
int num;
int a, b, c;
int len1[3];
int info1[3];
int len2[2];
int info2[2];

void getdp(int p, int n){
    priority_queue<pair<int, int>> pq1;
    priority_queue<pair<int, int>> pq2;
    int second = -1;
    info[n] = n;
    treesize[n] = 1;
    if(adj[n].size() == 0) return;
    for(int i = 0; i < adj[n].size(); ++i){
        int nn = adj[n][i];
        if(nn == p) continue;
        getdp(n, nn);
        treesize[n]+= treesize[nn];
        pq1.push({depth[0][nn], nn});
        if(treesize[nn] >= 2) pq2.push({depth[1][nn], nn});
    }
    int size1 = pq1.size() > 3 ? 3 : pq1.size();
    int size2 = pq2.size() > 2 ? 2 : pq2.size();
    for(int i = 0; i < size1; ++i){
        len1[i] = pq1.top().first; 
        info1[i] = pq1.top().second;
        pq1.pop();
    }
    for(int i = 0; i < size2; ++i){
        len2[i] = pq2.top().first;
        info2[i] = pq2.top().second;
        pq2.pop();
    }
    //max depth
    if(size1) {
        depth[0][n] = len1[0]+1;
        info[n] = info[info1[0]];
        if(depth[0][n] > num && treesize[info1[0]] >= 2){
            num = depth[0][n];
            a = n;
            b = info1[0];
            c = info[b];
        }
    }
    //max depth - depth
    if(size1 >= 2){
        depth[1][n] = len1[0] + len1[1] + 2;
        infod2[0][n] = info[info1[0]];
        infod2[1][n] = info[info1[1]];
    }
    if(size2 && depth[1][n] < len2[0] + 1){
        depth[1][n] = len2[0] + 1;
        infod2[0][n] = infod2[0][info2[0]];
        infod2[1][n] = infod2[1][info2[0]];
    }
    if(depth[1][n] > num){
        num = depth[1][n];
        a = n;
        b = infod2[0][n];
        c = infod2[1][n];
    }
    //max depth - depth - depth
    if(size1 >= 3){
        if(num < len1[0] + len1[1] + len1[2]+3){
            num = len1[0] + len1[1] + len1[2] + 3;
            a = info[info1[0]];
            b = info[info1[1]];
            c = info[info1[2]];
        }
    }
    //max (depth-depth) - depth
    for(int i = 0; i < size1; ++i){
        for(int j = 0; j < size2; ++j){
            int i1 = info1[i];
            int i2 = info2[j];
            if(i1 == i2) continue;
            int l1 = len1[i], l2 = len2[j];
            if(num < l1 + l2 + 2){
                num = l1 + l2 + 2;
                a = info[i1];
                b = infod2[0][i2];
                c = infod2[1][i2];
            }
        }
    }
}

int main(){
    freopen("0Text.txt", "r", stdin);
    int n;
    cin >> n;
    for(int i = 1; i < n; ++i) {
        int f, t;
        cin >> f >> t;
        adj[f].push_back(t);
        adj[t].push_back(f);
    }

    getdp(-1,1);
    cout << num << '\n';
    cout << a << ' ' << b <<  ' ' << c;
    return 0;
}