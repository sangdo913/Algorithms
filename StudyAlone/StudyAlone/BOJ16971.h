#include<iostream>
#define MAX(x,y) ((x) > (y) ? (x) : (y))

int arr[1000][1000], n, m;

using namespace std;
int sum[2][1000];
int f[4];

int Do(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    cin >> n >> m;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++)
            cin >> arr[i][j];
    }

    f[1] = arr[0][0];
    f[0] = arr[0][0];
    f[2] = arr[n-1][0];
    f[3] = arr[0][m-1];
    

    for(int i = 1; i < n; i++){
        f[1] += (i == n-1) ?  arr[i][0] : arr[i][0]*2;
        for(int j = 0; j < m; j++){
            sum[0][i] += j && j != m-1? arr[i][j]*2: arr[i][j];
        }
        f[3] += (i == n-1) ? arr[i][m-1] : arr[i][m-1] * 2;
    }

    for(int j = 1; j < m; j++){
        f[0] += j == m-1 ? arr[0][j] : arr[0][j]*2;
        f[2] += j == m-1 ? arr[n-1][j] : arr[n-1][j]*2;

        for(int i = 0; i < n; i++){
            sum[1][j] += i && i != n-1 ? arr[i][j] *2 : arr[i][j];
        }
    }

    f[0] = f[0] < f[2] ? f[0]^=f[2] ^=f[0] ^=  f[2] : f[0];
    f[1] = f[1] < f[3] ? f[1]^=f[3] ^=f[1] ^=  f[3] : f[1];

    int res = 0;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            bool g1 = i> 0 && i!=n-1;
            bool g2 = j > 0 && j != m-1;
            bool g3 =  g1 && g2;
            int gob = g1 + g2 + g3 + 1;
            res += gob*arr[i][j];
        }
    }

    int mm = res;

    for(int i = 1; i < n - 1; i++){
        int diff = f[0] - sum[0][i];

        if(diff + res > mm) {
            mm = diff + res;
        }

    }

    for(int j = 1; j < m - 1; j++){
        int diff = f[1] - sum[1][j];

        if(diff + res > mm){
            mm = diff + res;
        }
    }

    cout << mm;

    return 0;
}