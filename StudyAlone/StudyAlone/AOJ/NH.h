#include<iostream>
#include<string>

using namespace std;

struct NODE{
    char a;
    bool isend;
    NODE* fail;
    int dp[100];
    NODE *childs[26];
}nodes[1000];

NODE root;
int n,m;

NODE* queue[10001];

int dfs(int len, NODE* node){
    if(len == n) {
        return node->isend;
    }
    if(node->dp[len] != -1) {
        return node->dp[len];
    }
    int &ret = node->dp[len];
    if(node->isend){
        ret = 1;
        for(int i = 0; i < n-len; ++i) ret = (ret*26)%10007;
        return ret;
    }
    ret = 0;
    for(int i = 0; i < 26; ++i) {
        if(node->childs[i]) ret = (ret+dfs(len+1, node->childs[i]))%10007;
        else {
            NODE *fail = node->fail;
            while (fail != &root && !fail->childs[i]){
                    fail = fail->fail;
            }
            if(fail->childs[i]){
                ret = (ret + dfs(len+1, fail->childs[i]))%10007;
            }
            else ret = (ret + dfs(len+1, fail))%10007;
        }
    }
    return ret;
}

int main(){
    freopen("0Text.txt", "r", stdin);
    int c;
    cin >> c;
    root.fail = &root;
    while(c--){
        cin >> n >> m;
        int nid = 0;

        for(int i = 0; i < 26; ++i) root.childs[i] = 0;
        for(int i = 0; i < n; ++i) root.dp[i] = -1;
        root.isend = false;

        char str[101];
        for(int i = 0; i < m; ++i){
            cin >> str;
            
            int l = 0;
            NODE* cursor = &root;
            while(str[l]){
                if(!cursor->childs[str[l] - 'a']){
                    cursor->childs[str[l]-'a'] = &nodes[nid];
                    nodes[nid].a = str[l];
                    nodes[nid].isend= false;
                    for(int i = 0;i < 26;++i) nodes[nid].childs[i] = 0;
                    for(int i = 0; i < n; ++i) nodes[nid].dp[i] = -1;
                    nid++;
                }
                cursor = cursor->childs[str[l]-'a'];
                if(!str[l+1]) cursor->isend = true;
                ++l;
            }
        }

        int fr =0, re = 0;
        for(int i = 0; i < 26; ++i){
            if(root.childs[i]){
                root.childs[i]->fail = &root;
                queue[re++] = root.childs[i] ;
            }
        }
        
        while(fr!=re){
            NODE* now = queue[fr++];
            NODE* next;
            for(int i = 0; i < 26; ++i){
                if(now->childs[i]){
                    next = now->childs[i];
                    NODE* fail = now->fail;
                    while(fail != &root && !fail->childs[i]) {
                        fail = fail->fail;
                    }
                    
                    if(fail->childs[i]) next->fail = fail->childs[i];
                    else next->fail = fail;
                    if(next->fail->isend) next->isend = true;
                    queue[re++] = next;
                }
            }
        }
        int ret = 1;
        for(int i = 0; i < n; ++i) ret = (ret*26)%10007;
        cout << (10007+ ret-dfs(0,&root))%10007 << endl;
    }
    return 0;
}