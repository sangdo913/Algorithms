#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

using namespace std;

struct cmp{
    bool operator()(const string &s1, const string &s2){
        string p = s1+s2;
        string p2 = s2+s1;
        return p < p2;
    }
};

int main(){
    freopen("0Text.txt", "r", stdin);

    int n, k;
    cin >> k >> n;
    vector<int> vec(k);
    for(int i = 0; i < k; ++i) {
        cin >> vec[i];
    }
    sort(vec.begin(), vec.end());
    vector<string> str(n);
    for(int i = 0; i < k; ++i){
        str[i] = to_string(vec[i]);
    }
    for(int i = k; i < n; ++i) {
        str[i] = to_string(vec.back());
    }
    sort(str.begin(), str.end(),cmp());
    string res;
    // for(auto it : str){
    //     cout << it << ' ';
    // }
    //cout << endl;

    for(int i = n-1; i >= 0; --i){
        res += str[i];
    }
    cout << res << endl;
    return 0;
}