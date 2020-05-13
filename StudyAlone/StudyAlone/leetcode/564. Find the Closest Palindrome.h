#define ll long long
#define ABS(x) ((x) > 0 ? (x) : -(x))
long long diff;
long long res;

void makepelin(string s, int b){
    int n = s.size(); 
    int store = b;
    long long n1 = 0;
    bool changed = false;
    
    for(int i = 0; i < s.size(); ++i) n1 = n1*10 + s[i]-'0';
    for(int i = 0; i <= n/2; ++i){
        if(s[i] < '9' && b %3 == 1) s[i]++;
        else if(s[i] > '0' && b %3 == 2) s[i]--;
        s[n-1-i] = s[i];
        b/=3;
    }
    
    for(int i = 0; i < n/2; ++i){
        if(s[i] != s[n-i-1]) return;
    }
    long long conv = 0;
    for(int i = 0; i < n; ++i){
        conv = conv*10 + s[i]-'0';
    }
    long long d = ABS(conv - n1);
    
    if(d && d < diff){
        diff = d;
        res = conv;
    }
    if(d && d == diff && res > conv){
        res = conv;
    }
}

long long mltoi(const string &s1){
    ll res = 0;
    for(int i = 0; i < s1.size(); ++i){
        res = res*10 + s1[i] - '0';
    }
    return res;
}

ll getsize(ll l){
    ll res = 1;
    while(res <= l) res*=10;
    return res;
}
ll makepelin(ll l1){
    ll cnt = getsize(l1)/10;
    ll res = getsize(l1) * l1;
    ll r = 0;
    while(cnt){
        r = (r*10) + (l1 %10);
        l1 /= 10;
        cnt /= 10;
    }
    return res + r;
}

void middifference(const string &s1){
    string s = s1;
    int n = s.size();
    for(int i = 0; i < n/2; ++i){
        if(s[i] != s[n-1-i]) return;
    }
    ll n1 = mltoi(s1);
    for(int i = s[n/2]-1; i <= s[n/2]+1; ++i){
        if(i <'0' || i >'9') continue;
        s[n/2] = i;
        if((n&1) == 0){
            s[n/2-1] = i;
        }
        ll n2 = mltoi(s);
        ll d = ABS(n1 - n2);
        if(d && diff > d){
            diff = d;
            res = n2;
        }
    }
}

string mltos(){
    string s;
    if(res == 0) return string("0");
    while(res){
        s.push_back(res %10 + '0');
        res /=10;
    }
    return string(s.rbegin(), s.rend());
}
class Solution {
public:
    string nearestPalindromic(string s) {
        int n = s.size();
        long long n1 = 1, n2 = 0;
        for(int i = 0; i < n; ++i){
            n1 *= 10;
            n2 = n2*10 + s[i]-'0';
        }
        n1 += 1;
        diff = ABS(n1-n2);
        res = n1;
        n1 = (n1-2)/10;
        ll d = ABS(n1-n2);
        if(d && diff > d){
            diff = d;
            res = n1;
        }
        else if(d && diff == d && res > n1){
            res = n1;
        }
        
        middifference(s);
        
        int b = 1;
        for(int i  = 0; i <= n/2; ++i){
            b*=3;
        }
        for(int i = 0; i < b; ++i){
            makepelin(s, i);
        }
        return mltos();
    }
};