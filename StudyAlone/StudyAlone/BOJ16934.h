#include<iostream>
#include<map>
#include<string>
#include<set>

using namespace std;
int n;
map<string, int> id;
set<string> hs;

string conv(int i){
    string res;
    while(i){
        res.push_back(i%10);
        i/=10;
    }

    return string(res.rbegin(), res.rend());
}

int Do(){
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n;
    string in;

    while(n--){
        cin >> in;

        bool check = false;
        for(int i = 1; i <= in.size(); i++){
            if(hs.find(string(in.begin(), in.begin()+i)) == hs.end()){
                check = true, (cout << string(in.begin(), in.begin()+i) << '\n');
                break;
            }
        }

        id[in]++;
        if(!check){
            if(id[in] != 1){
                cout << in << id[in] <<'\n'; 
            }
            else{
                cout << in << '\n';
            }
        }

        for(int i = 1; i <= in.size(); i++){
            hs.insert(string(in.begin(), in.begin() + i));
        }
    }
    string a = "asdf";

    return 0;
}