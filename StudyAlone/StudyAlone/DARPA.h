#include<iostream>

using namespace std;
int n, m;
int arr[201];

bool decision(int len){
    int st=0, ed = 1;
    
    for(int i = 0; i < n-1; ++i){
        while(ed != m && arr[ed] - arr[st] < len){
            ed++;
        }
        if(ed == m) return false;
        st = ed;
    }
    return true;
}

int bs(int e){
    int s = 0;
    while(s <= e){
        int m = (s+e)/2;

        if(decision(m)){
            s = m+1;
        }
        else{
            e = m-1;
        }
    }
    return e;
}

int Do(){
    int c;
    cin >> c;
    cout.setf(ios_base::fixed);
    cout.precision(2);

    while(c--){
        double in;
        cin >> n >> m;
        for(int i = 0; i < m; ++i) cin >> in, arr[i] = in*1000;;
        arr[m] = arr[m-1] + 1;
        
        cout << (double)((bs(240000)+5)/10)/100.0 << '\n';
    }
    return 0;
}