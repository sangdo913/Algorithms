#include<iostream>
#include<string>

using namespace std;

int main(){
    freopen("0Text.txt", "r", stdin);
    int t;
    cin >> t;
    for(int tc= 1; tc <= t; ++tc){
        string s;
        cin >> s;
        int mindiff = 0;
        int previ = -1;
        for(int i = 0; i < s.size(); ++i){
            if(s[i] == 'R'){
                int diff = i - previ;
                if(diff > mindiff) mindiff = diff;
                previ = i;
            }
        }
        if(mindiff < s.size() - previ) mindiff = s.size() - previ;
        cout << mindiff<<'\n';
    }

    return 0;
}