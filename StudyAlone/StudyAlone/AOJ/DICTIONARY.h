#include<iostream>

using namespace std;
int c, n;
int order[26][26];
char word[1000][21];
int wlen[1000];
int conv[128];
char ans[27];
int visit[26];
int tc;
int top;

bool topologicalsort(int id){
    for(int i = 0; i < 26; ++i){
        if(order[id][i] != tc) continue;
        if(visit[i] == tc) return false;
        if(visit[i] == tc+1) continue;
        visit[i] = tc;
        bool res = topologicalsort(i);
        visit[i] = tc+1;
        if(!res) return false;
    }
    ans[top++] = id + 'a';
    return true;
}

int main(){
    freopen("0Text.txt", "r", stdin);
    scanf("%d", &c);
    for(int i = 'a'; i <= 'z'; ++i) conv[i] = i - 'a';
    while(c--){
        bool res = true;
        top = 0;
        tc+=2;
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) {
            scanf("%s ", word[i]);
            wlen[i] = 0;
            while(word[i][wlen[i]]) ++wlen[i];
        }
        for(int i = 1; i < n; ++i){
            int p = i-1, n = i;
            int l = 0;
            while(word[n][l] == word[p][l]) l++;
            if(!word[n][l]) {
                res = false;
                break;
            }
            if(!word[p][l]) continue;
            
            int &o = order[conv[word[p][l]]][conv[word[n][l]]];
            if(o == tc) continue;
            o = tc;
        }
        if(res){
           for(int i = 0; i < 26; ++i){
              if(visit[i] == tc+1) continue;
              visit[i] = tc;
              res &= topologicalsort(i);
              if(!res) break;
              visit[i] = tc+1;
           } 
        }

        if(!res){
            printf("INVALID HYPOTHESIS\n");
        }
        else{
            while(top) printf("%c", ans[--top]);
            printf("\n");
        }
    }
    return 0;
}