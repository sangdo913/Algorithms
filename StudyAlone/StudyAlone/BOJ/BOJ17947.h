#include<iostream>
#define MIN(x,y) ((x) > (y) ? (y) : (x))

using namespace std;
bool discard[400001];
int nums[400001];
#define ABS(x) ((x) > 0 ? (x) : -(x))

int main(){
    freopen("0Text.txt", "r", stdin);
    int n, m, k;
    cin >> n >> m >> k;

    for(int i = 0; i < m; ++i){
        int a, b;
        cin >> a >>b;
        discard[a] = discard[b] = true;
    }
    
    int a, b;
    cin >> a >> b;
    discard[a] = discard[b] = true;
    int value = ABS(a%k-b%k);
    for(int i = 1; i <= 4*n; ++i){
        if(!discard[i]) nums[i%k]++;
    }

    int res = 0;
    for(int i  = 0, j = i + value+1; i < k; ++i){
        if(j < i +value+1) j = i+value+1;
        while(j < k && nums[i] >= nums[j]){
            res += nums[j];
            nums[i] -= nums[j];
            ++j;
        }
        if(j < k) {
            nums[j] -= nums[i];
            res += nums[i];
        }
    }

    cout << MIN(res, m-1);
    return 0;
}