#include<iostream>
#include<cstring>

using namespace std;

int arr[102][102], n, l;
int dr[4] = {-1,0,1,0}, dc[4] = {0,1,0,-1};
int ABS(int i) {return i > 0 ? i : -i;}

bool canbuild(int r, int c,int d, int dst){
    r += dr[d];
    c += dc[d];

    for(int i = 0; i < l; i++){
        if(arr[r][c] == -1) return false;
        else if(arr[r][c] != dst) return false;
    }
    return true;
}

bool construct(int r, int c, int d){
    while(arr[r+dr[d]][c+dc[d]] != -1){
        if(arr[r + dr[d]][c + dc[d]] != arr[r][c]){
                if(!canbuild(r,c,d,arr[r][c] + 1) && !canbuild(r,c,d,arr[r][c]-1)) return false;
                r+= l*dr[d], c+= l*dc[d];
        }
        r+=dr[d];
        c+=dc[d];
    }
    return true;
}

int Do(){
    cin >> n >> l;
    memset(arr, -1, sizeof(arr));
    for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) cin >> arr[i][j];

    int res = 0;
    for(int i = 1; i <=n; i++) res += construct(i,1, 1), res+= construct(1,i,2);
    cout << res;
    return 0;
}