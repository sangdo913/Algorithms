#include<iostream>

using namespace std;

long long A[200002], B[200001];

int C481(){
    int n, m;
    cin >> n >> m;

    for(int i = 1; i <= n; i++){
        long long num;
        cin >> num;
        A[i] = A[i-1] + num;
    }

    A[n+1] = 3e15;
    
    int idx = 1;
    long long accum = 0;

    while(m--){
        long long to;
        cin >> to;
        while(to - A[idx] > 0){
            idx++;
        }
        cout << idx << ' ' << to - A[idx-1] << '\n';
    }

    return 0;
}