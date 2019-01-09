//Auto-Complete
//https://www.acmicpc.net/problem/9991
#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

map<string, int> mp;
vector<string> vec;

int Do(){
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);

    int w, n;
    cin >> w >> n;
    for(int i = 1; i <= w; i++){
        string in;
        cin  >> in;
        mp.insert({in,i});
        vec.push_back(in);
    } 

    sort(vec.begin(), vec.end());
    
    for(int i = 0; i < n; i++){
        int in; string str;
        cin >> in >> str;

        string end = str;
        end[str.size()-1]++;
        int s = lower_bound(vec.begin(),vec.end(), str) - vec.begin();
        int e = lower_bound(vec.begin(), vec.end(), end) - vec.begin();
        
        cout << (s+in-1 >= e ? -1 : mp[vec[s+in-1]]) << '\n';
    }
    
    return 0;
}