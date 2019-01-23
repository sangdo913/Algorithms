#include<iostream>
#include<algorithm>

using namespace std;

int n, c;
int pos[200000];

bool canstruct(int m){
    int num = c;
    int p =0;
    for(int i = 1 ; i < c; i++){
        int dist = 0;

        while(dist < m){
            if(p == n-1) return false;
            dist += pos[p+1] - pos[p];
            p++;
        }
    }
    return true;
}

int search(){
    int l = 0, r =1000000000, m;

    while(l<=r){
        m = (l+r)/2;

        if(canstruct(m)){
            l = m + 1;
        }
        else{
            r = m-1;
        }
    }
    return r; 
}
int Do(){
    cin >> n >> c;

    for(int i =0 ; i < n; i++){
        cin >> pos[i];
    }
    sort(pos, pos+n);
    cout << search();

    return 0;
}