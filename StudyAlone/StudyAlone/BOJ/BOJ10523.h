#include<iostream>
#include<cmath>
#include<stdlib.h>

using namespace std;

int X[100000];
int Y[100000];

unsigned long long myseed = 0;
unsigned long long myrand(){
    return myseed = (214013LL*myseed + 2531011LL);
}

long long ccw(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3){
    return (x1 * y2 + x2*y3 + x3 * y1 - x1*y3 - x2*y1 - x3*y2);
}

int main(){
    freopen("0Text.txt", "r", stdin);
    myseed = 256591;
    int n;
    double p;
    cin >> n;
    cin >> p;
    if(n == 1 || n ==2){
        cout<<"possible";
        return 0;
    }

    for(int i = 0; i < n; ++i){
        cin >> X[i] >> Y[i];
    }
    int cnt = 100;
    while(cnt--){
        int a = ((unsigned int)myrand())%n;
        int b =  ((unsigned int)myrand())%n;
        if(a==b){
            b = (a+1)%n;
        }
        int num = 2;
        for(int i = 0; i < n; ++i){
            if(i == a || i == b) continue;
            if(!ccw(X[a],Y[a], X[b], Y[b], X[i], Y[i])) num++;
        }
        
        if((double)num >= n*p/100.0){
            cout << "possible";
            return 0;
        }
    }
    cout << "impossible";
    return 0;
}