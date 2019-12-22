#include<iostream>

using namespace std;

int A[21][21];
int n;

int devide(int r, int c, int d1, int d2){
    int diff= 0x3f3f3f3f;
    int group[6] = {};
    int g;
    if(r + d1+d2 > n || c - d1 < 1 || c + d2 > n) return 0x3f3f3f3f;
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j){
            if(i < r){
                if(j <= c) g = 1;
                else g = 2;
            }
            else if(i > r+d1+d2){
                if(j < c-d1+d2) g = 3;
                else g = 4;
            }
            else{
                int left, right;
                left = r + d1 - i;
                left = left > 0 ? left : -left;
                left += c -d1;
                right = r + d2 - i;
                right = right > 0 ? right : -right;
                right = c + d2 - right;
                if(j < left){
                    if(i < r+d1) g = 1;
                    else g= 3;
                }
                else if (j > right){
                    if(i > r + d2) g = 4;  
                    else g = 2;
                }
                else g = 5;
            }
            group[g]+= A[i][j];
            // printf("%d ", g);
        }
        // printf("\n");
    }
    // printf("\n");
    for(int i = 2; i <=5 ; ++i){
        int j = i;
        while(j != 1 && group[j] < group[j-1]){
            int temp = group[j];
            group[j] = group[j-1];
            group[j-1] = temp;
            j--;
        }
    }
    diff = group[5] - group[1];
    return diff;
}

int main(){
    freopen("0Text.txt", "r", stdin);
    cin >> n;
    for(int i = 1; i <= n; ++i){
        for(int j =1 ; j <= n; ++j)
            cin >> A[i][j];
    }
    int res = 0x3f3f3f3f;
    for(int i = 1; i <= n;++i) for(int j = 1; j <= n; ++j){
        for(int k = 1; k <= n; ++k) for(int l = 1; l <= n; ++l){
            int temp = devide(i,j,k,l);
            res = res < temp ?  res : temp;
        }
    }
    return !(cout << res);
}