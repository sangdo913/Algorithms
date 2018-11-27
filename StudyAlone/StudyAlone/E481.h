#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;
int p[1000];

vector<int> vec;

int MIN(int i1 ,int i2){return i1 < i2 ? i1 : i2;}
int MAX(int i1, int i2){return i1 < i2 ? i2 : i1;}

int E481(){
    int n, w;

    cin >> n >> w;
    
    int mmin = 0, mmax = w;
    int now = 0;

    for(int i = 0; i < n; i++){
        int num;
        cin >> num;
        
        mmin = MIN(mmin + num, mmin);
        mmax = MAX(mmax+ num, mmax);
    }
    cout << (mmin > mmax ? 0 : mmax - mmin +1);
    
    return 0;
}