#include<iostream>
using namespace std;

int gcd(int a, int b){
    int temp;
    if(a < b){
        temp = a;
        a = b;
        b = temp;
    }
    int r = a%b;
    while(b){
        r = a%b;
        a = b;
        b = r;
    }
    return a;
}
int a,b,g;
int gg;
int n;
int bs(int n){
    long long f = 1;
    long long e = (long long)10e9 * 40000;
    while(f <= e){
        long long m = (f+e)/2;
        long long order = m/a+m/b-m/g;
        if(order < n){
            f = m+1;
        }
        else{
            e = m-1;
        }
    }
    return (e+1)%1000000007;
}
class Solution {
public:
    int nthMagicalNumber(int N, int A, int B) {
        g = A/gcd(A,B)*B;
        a = A, b = B; 
        
        return bs(N); 
    }
};