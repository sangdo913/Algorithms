//https://leetcode.com/problems/largest-palindrome-product/
#include<iostream>

using namespace std;

long long makepelin(long long n){
    long long res = n;
    while(n){
        res = res*10 + n%10;
        n/=10;
    }
    return res;
}

class Solution {
public:
    int largestPalindrome(int n) {
        if(n ==1) return 9;
        int b = n;
        long long mul = 10;
        long long n1 = 1;
        while(b){
            if(b&1) n1*=mul;
            mul *= mul;
            b>>=1;
        }
        int min_n = n1/10;
        for(long long a = n1-1; a >= min_n; --a){
            long long p = makepelin(a);
            long long mmax = n1-1;
            for(long long b = n1-1; b*b >= p; --b){
                if(p%b) continue;
                return p%1337;
            }
        }
        return -1;
    }
};