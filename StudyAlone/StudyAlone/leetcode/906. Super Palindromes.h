#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
bool nfirst;
vector<long long> vec;
class Solution {
public:
    int superpalindromesInRange(string L, string R) {
        if(!nfirst){
            vec.push_back(1);
            vec.push_back(4);
            vec.push_back(9);
            nfirst = true;
            for(int i = 1; i < 10000; i++) {
                string l = to_string(i),  r = string(l.rbegin(), l.rend());
                long long n = stoll(l+r);
                if(isP(to_string(n*n))) vec.push_back(n*n);
                for(int d = 0; d < 10; d++) {
                    n = (stoll(l + to_string(d) + r));
                    if(isP(to_string(n*n))) vec.push_back(n*n);
                }
            }
            sort(vec.begin(), vec.end());
        }
        long long l = stoll(L), r = stoll(R);
        
        return upper_bound(vec.begin(),vec.end(), r) - lower_bound(vec.begin(),vec.end(), l);
    }
    
    bool isP(string s){
       for(int i = 0, j = s.size()-1; i < j; i++,j--) 
           if(s[i]!= s[j]) return false;
        return true;
    }
};