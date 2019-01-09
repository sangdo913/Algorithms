//Mirror Field
//https://www.acmicpc.net/problem/9993
#include<iostream>

using namespace std;

enum DIR {U, R, D, L};
int dir;
int conv[256][4];
char arr[1000][1001];
int n,m;
int dr[4] = {-1,0,1,0};
int dc[4] = {0,1,0,-1};

bool isout(int r, int c){
    return r < 0 || c < 0 || r >= n || c >= m;
}

int ting(int r, int c){
    int cnt = 0;
    while(cnt <= n*m){
        if(isout(r,c)) return cnt;

        cnt++;
        dir = conv[arr[r][c]][dir];
        r += dr[dir];
        c += dc[dir];
    }

    return 0x3f3f3f3f;
}

int MAX(int a, int b){return a< b ? b : a;}

int Do(){
    int res = 0;

    conv['/'][U] = R;
    conv['/'][R] = U;
    conv['/'][D] = L;
    conv['/'][L] = D;
    conv['\\'][U] = L;
    conv['\\'][R] = D;
    conv['\\'][D] = R;
    conv['\\'][L] = U;

    cin >> n >> m;
    for(int i = 0; i < n; i++){
            cin >> arr[i];
        }

    for(int i = 0; i < m; i++){
        dir =  2;
        res = MAX(res, ting(0,i)); 

        dir = 0;
        res = MAX(res, ting(n-1, i));
        
    }

    for(int i =0; i < n; i++){
        dir = 1;
        res = MAX(res, ting(i,0));
        
        dir = 3;
        res = MAX(res, ting(i, m-1));
    }

    cout << (res == 0x3f3f3f3f ? -1 : res);
    return 0;
}