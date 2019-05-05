#include<iostream>
#include<cstring>

using namespace std;

const int MOD = 1000000009;
int conv[256], len; 
char arr[1000001];

int Do(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    cin >>arr;

    len = strlen(arr);
    conv['d'] = 10;
    conv['c'] = 26;

    long long res = 1;
    for(int i = 0; i < len; i++){
        res *= conv[arr[i]] - (i && (arr[i] == arr[i-1]));
        res %= MOD;
    }

    cout << res;

    return 0;
}