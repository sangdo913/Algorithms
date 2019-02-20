#include<iostream>

using namespace std;

int Do(){
    int n, k , m;
    cin >> n >> k >> m;

    for(int i = 0; i < n; i++){
        int in;
        cin >> in;
    }

    while(m--){
        int in;
        cin >> in;
        if(in > 0 ){
            if(in >= k){
                k = in - (k-1);
            }
        }
        else{
            in = -in;
            if(n - in +1 <= k){
                int num = k - (n - in + 1);
                k = n - num;
            }
        }
    }

    cout << k;
    return 0;
}