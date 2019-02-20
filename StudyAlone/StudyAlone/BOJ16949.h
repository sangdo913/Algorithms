#include<iostream>
#include<string>

using namespace std;
string in;
int k;

bool caniter(const string&f, const string&r){
    for(int i = 0; i < f.size(); i++){
        if(f[i] != r[i]) return false;
    }
    return true;
}

#define MAX(x,y) ((x) > (y) ? (x) : (y))

int Do(){
    cin >> in >> k;

    in.resize(in.size() + k);
    int res = 0;

    for(int i = 0; i < in.size(); i++){
        for(int len = 1; len*2+ i <= in.size(); len++){
            string cmp = string(in.begin() + i, in.begin() + len+i);
            string cmp2 = string(in.begin() + i+len, in.begin() + i+2*len);

            bool ch = true;
            for(int i = 0; i < cmp.size(); i++){
                if(cmp[i] && cmp2[i] && cmp[i] != cmp2[i]) {ch = false; break;}
            }
            if(ch){
                res = MAX(res, cmp.size()*2);
            }
        }
    }
    cout << res;
    return 0;
}