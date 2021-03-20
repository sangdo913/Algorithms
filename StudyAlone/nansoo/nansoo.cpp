#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<fstream>
using namespace std;

int main(){
    vector<string> v;
    fstream f("1Text.txt");
    int chk[10];
    int tc = 1;
    for(int i = 0; i < 100000;++i) {
        tc++;
        string s = to_string(i);
        string z;
        for(int i = 0; i < 5-s.size(); ++i) {
            z.push_back('0');
        }
        z += s;
        bool duple = false;
        bool samepl = true;
        int pl = z[1] - z[0];
        for(int i = 0 ; i < 5; ++i) {
            if(i){
                if(pl != z[i] - z[i-1]){
                    samepl = false;
                }
            }
            if(chk[z[i]-'0'] == tc) {
                duple = true;
                break;
            }
            chk[z[i]-'0'] = tc;
        }

        if(!duple&& chk[9] == tc) v.push_back(z);
    }
    // int cnt = v.size();
    // while(cnt--) {
    //     int a = (rand()*rand())%v.size();
    //     int b = (rand()*rand())%v.size();
    //     if(a!=b){
    //         string t = v[a];
    //         v[a] = v[b];
    //         v[b] = t;
    //     }
    // }
    for(auto it : v){
        f << it << '\n';
    }

    return 0;
}