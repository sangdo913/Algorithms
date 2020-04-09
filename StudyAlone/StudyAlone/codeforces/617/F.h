#include<iostream>
#define MAX(x,y) ((x) > (y) ? (x) : (y))

using namespace std;
struct query{
    int a, b,g;
}queries[5000];
int n, m;
int p[32][5001];
int adj[5001][5001];
int asize[5001];
int Q[5000];
int depth[5001];
int index[5001][5001];
int visit[5001];
int order[5000][2];

int main(){
    freopen("0Text.txt", "r", stdin);
    cin >> n;

    int bnum =0;
    int bs = 1;
    while(bs<n) {
        bnum++;
        bs<<=1;
    }

    for(int i = 1; i < n; ++i){
        int a, b;
        cin >> a >> b;
        adj[a][asize[a]++] = b;
        adj[b][asize[b]++] = a;
        order[i][0] = a;
        order[i][1] = b;
    }
    int fr, re;
    fr = re = 0;
    Q[re++] = 1;
    depth[1] = 1;
    while(fr !=re){
        int now = Q[fr++];
        for(int i = 0; i < asize[now]; ++i) {
            int next = adj[now][i];
            if(depth[next]) continue;
            depth[next] = depth[now] + 1;
            p[0][next] = now;
            Q[re++] = next;
        }
    }

    for(int i = 1; i < bnum; ++i){
        for(int j = 1; j <= n; ++j){
            p[i][j] = p[i-1][p[i-1][j]];
        }
    }

    cin >> m;
    for(int i = 0; i < m; ++i){
        int a,b,g;
        cin >> a >> b  >> g;
        
        if(depth[a] < depth[b]){ a^=b^=a^=b;}
        queries[i].a = a;
        queries[i].b = b;
        queries[i].g = g;
        int diff = depth[a]-depth[b];
        int ii = 0;
        while(diff) {
            if(diff & 1) {
                a = p[ii][a];
            }
            ++ii;
            diff>>=1;
        }
        if(a != b){
            for(int i = bnum; i>=0; --i){
                if(p[i][a] != p[i][b]){
                    a = p[i][a];
                    b = p[i][b];
                }
            }
            a = p[0][a];
            b = p[0][b];
        }
        int d = a;
        a = queries[i].a;
        b = queries[i].b;
        while(a != d){
            index[a][p[0][a]] = MAX(index[a][p[0][a]], g);
            a = p[0][a];
        }
        while(b != d){
            index[b][p[0][b]] = MAX(index[b][p[0][b]], g);
            b = p[0][b];
        }
    }

    for(int i = 0; i < m; ++i){
        int a = queries[i].a, b = queries[i].b, g = queries[i].g;
        int diff = depth[a]-depth[b];
        int ii = 0;
        while(diff){
            if(diff & 1){
                a = p[ii][a];
            }
            diff>>=1;
            ii++;
        }
        if(a != b){
            for(int i = bnum; i>=0; --i){
                if(p[i][a] != p[i][b]){
                    a = p[i][a];
                    b = p[i][b];
                }
            }
            a = p[0][a];
            b = p[0][b];
        }
        int d = a;
        a = queries[i].a;
        b = queries[i].b;
        int num = 0x3f3f3f3f;
        while(a != d){
            int pa = p[0][a];
            if(index[a][pa] < num){
                num = index[a][pa];
            }
            a = p[0][a];
        }
        while(b != d){
            int pa = p[0][b];
            if(index[b][pa] < num){
                num = index[b][pa];
            }
            b = p[0][b];
        }
        if(g != num) goto FAIL;
    }
    for(int i = 1; i < n; ++i){
        int a = order[i][0];
        int b = order[i][1];
        if(depth[a] < depth[b]) { a^=b^=a^=b; }
        if(index[a][b] == 0) index[a][b] = 1;
        cout << index[a][b] << ' ';
    }
    return 0;
    FAIL:
    cout <<-1;
    
    return 0;
}