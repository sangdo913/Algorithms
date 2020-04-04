#include<iostream>
#include<vector>
#include<set>
using namespace std;
int cnt[26][1501];
int cnt2[26][1501];

char a[1501],b[1501];;
int asize, bsize;
set<vector<int>> se;

int main(){
    freopen("0Text.txt", "r",stdin);
    cin >> a >> b;
    while(a[asize]) asize++;
    while(b[bsize]) bsize++;
    // for(int i = 1; i<= asize; ++i){
    //     for(int j = 0; j < 26; ++j){
    //         cnt[j][i] += cnt[j][i-1];
    //     }
    //     cnt[a[i]-'a'][i]++;
    // }
    // for(int i = 1; i <= bsize; ++i){
    //     for(int j = 0; j < 26; ++j){
    //         cnt2[j][i] += cnt2[j][i-1];
    //     }
    //     cnt2[b[i]-'a'][i]++;
    // }
    int res = 0;
    for(int l = 1; l <= asize; ++l) {
        vector<int> vec(26,0);
        for(int i = 0; i < l; ++i){
            vec[a[i]-'a']++;
        }
        se.insert(vec);

        for(int  i = l; i < asize; ++i){
            vec[a[i]-'a']++;
            vec[a[i-l]-'a']--;
            se.insert(vec);
        }
    }
    
    for(int l = bsize; l >=0; --l){
        vector<int> vec(26,0);
        for(int i = 0; i < l; ++i){
            vec[b[i] - 'a']++;
        }
        if(se.find(vec) != se.end()){
            return !(cout << l);
        }
        for(int i = l; i < bsize; ++i){
            vec[b[i]-'a']++;
            vec[b[i-l]-'a']--;
            if(se.find(vec) != se.end()) return !(cout << l);
        }
    }
    
    cout << 0;
    return 0;
}