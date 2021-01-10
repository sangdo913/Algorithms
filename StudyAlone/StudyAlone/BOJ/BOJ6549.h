#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

int st[1000000][2];
int h [1000000];
int main(){
    freopen("0Text.txt", "r", stdin);
    int top = 0;
    int n;
    while(1){
        scanf("%d", &n);
        if(!n) break;
        top = 0;
        for(int i = 0; i < n; ++i) scanf("%d", &h[i]);
        // printf("%d\n", n);
        // for(int i = 0; i < n; ++i){
        //     printf("%d ", h[i]);
        // }
        //     printf("\n");

        long long res = 0;
        for(int i = 0; i < n; ++i){
            int right = top-1;
            int prev = i;
            while(top && st[top-1][0] >= h[i]){
                res = max(res, (i -st[top-1][1])*(long long)st[top-1][0]);
                prev = st[top-1][1];
                top--;
            }
            st[top][0] = h[i];
            st[top++][1] = prev;
        }

        for(int i = 0; i < top; ++i){
            res = max(res, (long long)st[i][0] * (n - st[i][1]));
            // printf("h: %d\n", st[i][0]);
            // printf("%d %d\n", st[i][0], st[i][1]);
        }
        printf("%lld\n", res);
    }

    return 0;
}