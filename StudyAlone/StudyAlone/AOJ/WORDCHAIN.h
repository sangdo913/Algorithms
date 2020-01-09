#include<iostream>

using namespace std;

char words[100][11];
int wlen[100];

int adj[256][256][100];
int indeg[256];
int outdeg[256];
int asize[256][256];
int c, n;
char st, ed;
int ans[101];
int cursor;

void canreach(int idx, int wid){
    for(int i = 'a'; i <= 'z'; ++i){
        while(asize[idx][i]){
            int next = adj[idx][i][--asize[idx][i]];
            canreach(i, next);
        }
    }
    ans[cursor++] = wid;
}

int main(){
    freopen("0Text.txt", "r", stdin);
    scanf("%d", &c);

    for(int tc = 0; tc < c; ++tc){
        scanf("%d", &n);
        for(int i = 'a'; i <= 'z'; ++i) {
            indeg[i] = outdeg[i] = 0;
            for(int j = 'a';  j <='z'; ++j)
                asize[i][j] = 0;
        }
        
        for(int i =0; i < n; ++i) {
            scanf("%s", words[i]);
            wlen[i] = 0;
            while(words[i][wlen[i]]) wlen[i]++;
            char st = words[i][0];
            char back = words[i][wlen[i]-1];
            indeg[back]++;
            outdeg[st]++;
            adj[st][back][asize[st][back]++] = i;
        }
        st = -1;
        ed= -1;
        bool allsame = true;
        bool res = true;
        cursor = 0;

        for(int i = 'a'; i <= 'z'; ++i){
            if(outdeg[i] != indeg[i]){
                allsame = false;
                if(outdeg[i] - indeg[i] == 1){
                    if(st != -1){
                        res = false; break;
                    }
                    else st = i;
                }
                else if(outdeg[i] - indeg[i] == -1){
                    if(ed != -1){
                        res = false; break;
                    }
                    else ed = i;
                }
            }
        }
        if(allsame){
            st = words[0][0];
            ed = st;
        }

        if(res) {
            canreach(st,-1);
            cursor--;
            if(cursor != n){
                printf("n %d cursor : %d\n", n, cursor);
                printf("IMPOSSIBLE\n");
            }
            else{
                while(cursor) printf("%s ", words[ans[--cursor]]);
                printf("\n");
            }
        }
        else printf("IMPOSSIBLE\n");
    }
    return 0;
}