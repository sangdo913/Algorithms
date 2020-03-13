#include<iostream>

using namespace std;

int canescape[500][500];
char mymap[500][501];
int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,1,-1};
int conv[256];
int n , m;

int escape(int i, int j){
    if(i < 0 || j <0 || i == n || j == m) return 1;
    int &ret = canescape[i][j];
    if(ret) return ret;
    ret = -1;
    int ni = i + dx[conv[mymap[i][j]]];
    int nj = j + dy[conv[mymap[i][j]]];
    
    return ret = escape(ni,nj);
}

int main(){
    freopen("0Text.txt", "r", stdin);
    cin >> n >> m;
    conv['U'] = 0;
    conv['R'] = 2;
    conv['L'] = 3;
    conv['D'] = 1;
    for(int i = 0; i < n; ++i) cin >> mymap[i];
    int res = 0;
    for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j){
        res += escape(i,j) == 1;
    }

    return !(cout << res << '\n');
}