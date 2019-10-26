#include<iostream>
#include<queue>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

bool cmp(const string& a, const string&b){
    if(a.size() != b.size()) return a.size() <b.size();
    int n;
    for(n = a.size()-1; n && a[n] == b[n]; --n);
    return a[n] < b[n];
}

vector<string> vec;
int ain(){
    int n; 
    cin >> n;
    queue<string> que;
    for(char a = '0'; a <= '9'; ++a) {
        string in ;
        in.push_back(a);
        que.push(in);
        vec.push_back(in);
    }

    while(vec.size() < 1000000 && que.size()){
        int cnt = que.size();
        while(cnt--){
            string str = que.front();
            string next;
            que.pop();

            for(char a = *str.rbegin() + 1; a<='9'; ++a){
                next = str + a;
                vec.push_back(next);
                que.push(next);
            }
        }
    }
    sort(vec.begin(), vec.end(), cmp);
    if(--n >= vec.size()) return !(cout << -1);
    reverse(vec[n].begin(), vec[n].end());
    cout << vec[n];

    return 0;
}