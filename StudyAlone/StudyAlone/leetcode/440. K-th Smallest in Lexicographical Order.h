#include<iostream>
using namespace std;

int getnum(long long k, long long prefix){
    long long np = prefix+1;
    int res = 0;
    long long digit = 1;
    while(np*digit <= k){
        res += digit;
        digit*=10;
    }
    if(digit != 1 && prefix*digit <= k && k < np*digit){
        res += k - prefix*digit + 1;
    }
    if(k == prefix) res++;
    return res;
}

int findnum(long long n, long long k, long long prefix){
    if(!k) return prefix;
    prefix*=10;
    for(int i = prefix ? 0 : 1; i < 10; ++i){
        long long np = prefix+i;
        long long remain = getnum(n, np);
        if(k <= remain) return findnum(n, k-1, np);
        k-=remain;
    }
    return -1;
}

class Solution {
public:
    int findKthNumber(int n, int k) {
        int res = findnum(n,k,0);
        return res;
    }
};