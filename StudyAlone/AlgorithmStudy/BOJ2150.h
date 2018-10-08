#include<iostream>
#include<stack>
#include<algorithm>
#include<vector>

using namespace std;


int v[10001];
bool fin[10001];
vector<int> adj[10001];
vector<vector<int> > scc;
stack<int> st;
int sccs[10001];
int sccnum;

int n, e;
int MIN(int i1, int i2){return i1 < i2 ? i1 : i2;}

int cnt = 0;

int dfs(int node){
    int ret = cnt++;
    v[node] = ret;

    for(int i = 0; i < adj[node].size(); i++){
        int next = adj[node][i];

        if(!v[next]){
            ret = MIN(ret, dfs(next));
        }

        else if (!fin[next]){
            ret = MIN(ret, v[next]);
        }
    } 

    if(ret == v[node]){
        while(true){
            int t = st.top();
            st.pop();

            if(t == node) break;
        }
    }
}

int BOJ2150(){
    cin >> n >> e;

    for(int i = 0; i < e; i++){
        int from, to;
        cin >> from >> to;

        adj[from].push_back(to);
    }

    for(int i = 1; i < n; i++){
        if(!v[i]){
            cnt = 0;
            dfs(i);
        }
    }


    return 0;
}
