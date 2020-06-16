#include<iostream>
#include<vector>
#include<string>
using namespace std;
int query;
int chk[256];
int cnt[256];
class Solution {
public:
	int getMaxRepetitions(string s1, int n1, string s2, int n2) {
		string s;
		int n = s1.size();
		int m = s2.size();
		for (int i = 0; i < m; ++i) {
			chk[s2[i]] = 1;
			cnt[s2[i]] = 0;
		}
		for (int i = 0; i < n; ++i) {
			if (chk[s1[i]]) {
				s += s1[i];
				cnt[s1[i]]++;
			}
		}
		for (int i = 0; i < m; ++i) {
			if (cnt[s2[i]] == 0) return 0;
		}
		n = s.size();
		int c1 = 0, c2 = 0, prev;
		int p[100] = {};
		int lines[100];
		for (int i = 0; i < n; ++i) p[i] = -1;
		prev = 0;
		int line = 0;
		int aword = 0;
		int words = 0;
		c1 = 0;
		c2 = 0;
		int aline = 1;
		int res = 0;
        //get init
		while (1) {
			if (s[c1] == s2[c2]) {
				if (c2 == m-1) {
					lines[prev] = line;
					res++;
					if (p[prev] != -1) break;
					p[prev] = c1;
					prev = (c1 + 1) % n;
					line = 0;
				}
				c2 = ++c2%m;
			}
			c1 = ++c1 %n;
			if (c1 == 0) {
				if (aline == n1) 
					return res/n2;
				aline++, line++;
			}
		}
        c1 = (1+c1)%n;
		int rep = c1;
		int rline = 0;
		int rword = 0;
        
        //get repeat size
		while (1) {
			rword++;
			rline += lines[c1];
			c1 = (1+p[c1])%n;
			if (rep == c1) break;
		}
        n1 -= aline;
        res = (res + (n1 / rline)* rword);
        n1 -= n1/rline*rline;
        rword = 0;
        
        //get remain
        while(1){
            n1-= lines[c1];
            if(n1 < 0) break;
            res++;
            c1 = (1+p[c1])%n;
        }
            
        res/=n2;
		return res;
	}
};
