#include<iostream>

using namespace std;

int arr[102][102];
int n, m;

int Do(){
    cin >> n >> m;
    int res = 0;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> arr[i][j];

            if(arr[i][j]) res+=2;
        }
    }

    //FRONT
    for(int i = n+1; i >=1; i--){
        for(int j = 1; j <= m; j++){
            int diff = arr[i-1][j]-arr[i][j];
            if(diff > 0) res += diff;
        }
    }
    //REAR
    for(int i = 0; i <= n; i++){
        for(int j = 1; j <= m; j++){
            int diff = arr[i+1][j]-arr[i][j];
            if(diff > 0) res += diff;
        }
    }
    //LEFT
    for(int j = 0; j <= m; j++){
        for(int i = 1; i <= n; i++){
            int diff = arr[i][j+1]-arr[i][j];
            if(diff > 0) res += diff;
        }
    }
    //RIGFHT
    for(int j = m+1; j >= 1; j--){
        for(int i = 1; i <= n; i++){
            int diff = arr[i][j-1]-arr[i][j];
            if(diff > 0) res += diff;
        }
    }
    cout << res;
    return 0;
}