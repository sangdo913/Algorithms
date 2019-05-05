#include<iostream>
#include<cstring>

using namespace std;

int dr[8] = {-1,1,0, 0,1, 1,-1,-1};
int dc[8] = { 0,0,1,-1,1,-1, 1,-1};

char str[101], len, n, m;
char arr[100][101];

int Do(){
    cin >> str;
    cin >> n >> m;
    len = strlen(str);

    for(int i = 0; i < n; ++i) cin >> arr[i];

    for(int i  =0 ; i < n; i++){
        for(int j  = 0; j < m; j++){
            int idx = 0;
            if(arr[i][j] == str[0]){
                int r = i, c = j;
                for(int d = 0; d < 8; d++){
                    r = i, c = j;
                    idx = 1;
                    while(idx != len){
                        r += dr[d], c += dc[d];
                        if(r < 0 || c < 0 || r >= n || c >= m) break;
                        if(arr[r][c] != str[idx]) break;
                        ++idx;
                    }
                    if(idx == len) return!(cout << 1);
                }
            }
        }
    }
    cout << 0;
    return 0;
}