// #define ll long long
// #define ABS(x) ((x) > 0 ? (x) : -(x))
// long long diff;
// long long res;

// void makepelin(string s, int b){
//     int n = s.size(); 
//     int store = b;
//     long long n1 = 0;
//     bool changed = false;
    
//     for(int i = 0; i < s.size(); ++i) n1 = n1*10 + s[i]-'0';
//     for(int i = 0; i <= n/2; ++i){
//         if(s[i] < '9' && b %3 == 1) s[i]++;
//         else if(s[i] > '0' && b %3 == 2) s[i]--;
//         s[n-1-i] = s[i];
//         b/=3;
//     }
    
//     for(int i = 0; i < n/2; ++i){
//         if(s[i] != s[n-i-1]) return;
//     }
//     long long conv = 0;
//     for(int i = 0; i < n; ++i){
//         conv = conv*10 + s[i]-'0';
//     }
//     long long d = ABS(conv - n1);
    
//     if(d && d < diff){
//         diff = d;
//         res = conv;
//     }
//     if(d && d == diff && res > conv){
//         res = conv;
//     }
// }

// long long mltoi(const string &s1){
//     ll res = 0;
//     for(int i = 0; i < s1.size(); ++i){
//         res = res*10 + s1[i] - '0';
//     }
//     return res;
// }

// ll getsize(ll l){
//     ll res = 1;
//     while(res <= l) res*=10;
//     return res;
// }
// ll makepelin(ll l1){
//     ll cnt = getsize(l1)/10;
//     ll res = getsize(l1) * l1;
//     ll r = 0;
//     while(cnt){
//         r = (r*10) + (l1 %10);
//         l1 /= 10;
//         cnt /= 10;
//     }
//     return res + r;
// }

// void middifference(const string &s1){
//     string s = s1;
//     int n = s.size();
//     for(int i = 0; i < n/2; ++i){
//         if(s[i] != s[n-1-i]) return;
//     }
//     ll n1 = mltoi(s1);
//     for(int i = s[n/2]-1; i <= s[n/2]+1; ++i){
//         if(i <'0' || i >'9') continue;
//         s[n/2] = i;
//         if((n&1) == 0){
//             s[n/2-1] = i;
//         }
//         ll n2 = mltoi(s);
//         ll d = ABS(n1 - n2);
//         if(d && diff > d){
//             diff = d;
//             res = n2;
//         }
//     }
// }

// string mltos(){
//     string s;
//     if(res == 0) return string("0");
//     while(res){
//         s.push_back(res %10 + '0');
//         res /=10;
//     }
//     return string(s.rbegin(), s.rend());
// }
// class Solution {
// public:
//     string nearestPalindromic(string s) {
//         int n = s.size();
//         long long n1 = 1, n2 = 0;
//         for(int i = 0; i < n; ++i){
//             n1 *= 10;
//             n2 = n2*10 + s[i]-'0';
//         }
//         n1 += 1;
//         diff = ABS(n1-n2);
//         res = n1;
//         n1 = (n1-2)/10;
//         ll d = ABS(n1-n2);
//         if(d && diff > d){
//             diff = d;
//             res = n1;
//         }
//         else if(d && diff == d && res > n1){
//             res = n1;
//         }
        
//         middifference(s);
        
//         int b = 1;
//         for(int i  = 0; i <= n/2; ++i){
//             b*=3;
//         }
//         for(int i = 0; i < b; ++i){
//             makepelin(s, i);
//         }
//         return mltos();
//     }
// };

long long mstol(string s){
    long long ret = 0;
    for(int i = 0; i < s.size(); ++i){
        ret = ret*10 + s[i]-'0';
    }
    return ret;
}

string mltos(long long v){
    string ret;
    while(v){
        ret.push_back(v%10 + '0');
        v/=10;
    }
    reverse(ret.begin(),ret.end());
    if(ret.size() == 0) return "0";
    return ret;
}

#define ABS(x) ((x) > 0 ? (x) : -(x))
class Solution {
public:
    string nearestPalindromic(string n) {
        vector<long long> vec;
        long long digit = 1;
        long long num = mstol(n);
        for(int i = 0; i < n.size(); ++i) digit*=10;
        vec.push_back(digit+1);
        if(digit/10 > 0) vec.push_back(digit/10-1);
        
        long long prefix = mstol(string(n.begin(), n.begin() + n.size()/2))-1;
        string n1, rev;
        for(int i = 0; i < 3; ++i){
            if(prefix+i >= 0){
                n1 = mltos(prefix+i);
                if(n.size()%2) n1.push_back(n[n.size()/2]);
                rev = mltos(prefix+i);
                n1 += string(rev.rbegin(), rev.rend());
                vec.push_back(mstol(n1));
            }
        }
        
        if(n.size()%2){
            for(int i = 0; i < n.size()/2; ++i){
                n[n.size()-1-i] = n[i];
            }
            n[n.size()/2]--;
            for(int i = 0; i < 3; ++i){
                if('0'<= n[n.size()/2]&& n[n.size()/2] <= '9'){
                    vec.push_back(mstol(n));
                }
                n[n.size()/2]++;
            }
        }
        
        long long abs = 0x3f3f3f3f3f3f3f3f;
        long long res;
        for(int i = 0; i < vec.size(); ++i){
            long long diff = ABS(vec[i]-num);
            if(vec[i] == num) continue;
            if(diff < abs){
                res = vec[i];
                abs = diff;
            }
            else if(diff == abs){
                if(res >vec[i]){
                    res = vec[i];
                }
            }
        }
        
        return mltos(res);
    }
};