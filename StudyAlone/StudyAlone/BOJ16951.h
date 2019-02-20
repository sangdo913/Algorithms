#include<iostream>

using namespace std;

int arr[1000];
#define ABS(x) ((x) > 0 ? (x) : -(x))

int n,k;
int Do(){
    cin >> n >> k;

    for(int i = 0; i < n; i++) cin >> arr[i];

    int res = 0x3f3f3f3f;
    int block;

    for(int i = 1; i <= 1000; i++){
        int price = 0;
        price += i != arr[0];
        int block = i;
        
        for(int j = 1; j < n; j++){
            block += k;
            price += block != arr[j];
        }
        res = res < price ? res : price;
    }

    cout << res;
    return 0;
}