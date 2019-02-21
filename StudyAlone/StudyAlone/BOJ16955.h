#include<iostream>

using namespace std;

char arr[10][11];
int dr[4][2] ={
    {0,0},{1,-1}, {1,-1}, {1,-1}
};
int dc[4][2] = {
    {1,-1},{0,0}, {-1,1}, {1,-1}
};

int Do(){
    for(int i = 0; i < 10; i++) cin >> arr[i];

    for(int i = 0; i < 10; i++) for(int j = 0; j < 10; j++){
        if(arr[i][j] == '.'){
            for(int d = 0; d < 4; d++){
                int t = 1;
                for(int d2 = 0; d2 < 2; d2++){
                    int num = 0;
                    int r = i+ dr[d][d2], c = j + dc[d][d2];
                    while(0<=r && r < 10 &&0 <= c && c < 10 && arr[r][c] == 'X') num++, r += dr[d][d2], c+= dc[d][d2];
                    t += num;
                }
                if(t >= 5) return !(cout << 1);
            }
        }
    }
    cout << 0;
    return 0;
}