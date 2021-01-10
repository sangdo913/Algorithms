#include<iostream>

using namespace std;

int arr[1001][1001];
int mnum[1001][1001];

int main (){
    int h,w,k;
    scanf("%d %d %d\n", &h, &w, &k);
    for(int i = 1; i <= h; ++i){
        for(int j = 1; j <= w; ++j){
            scanf("%d", &arr[i][j]);
        }
    }
    mnum[0][1] = (k-1)*2;
    for(int i = 1;i <= h; ++i){
        for(int j =1; j <= w; ++j){
            mnum[i][j] = mnum[i-1][j]/2 + mnum[i][j-1]/2 + ((mnum[i-1][j] & 1) && !arr[i-1][j]) + ((mnum[i][j-1] & 1 && arr[i][j-1]));
        }
    }
    int r = 1, c = 1;
    while(r <= h && c <= w){
        int now = ((arr[r][c]&1) ^ (mnum[r][c]&1));
        if(now){
            c+=1;
        }
        else r+=1;
    }
    printf("%d %d\n", r,c);
    
    return 0;
}