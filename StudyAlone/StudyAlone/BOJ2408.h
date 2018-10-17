#include<iostream>
#include<vector>

using namespace std;

vector<int> s;
vector<int> now;
char oper;

int MAX(int i1, int i2){return i1 < i2 ? i2 : i1;}

string rev(string& s){
    string res = string(s.rbegin(), s.rend());
    return res;
}

vector<int> add(vector<int> &s1, vector<int>&s2){
    int size = MAX(s1.size(), s2.size())+1;
    vector<int>res(size, 0);

    s1.resize(size);
    s2.resize(size); 

    for(int i = 0; i < size; i++){
        res[i] = s1[i] + s2[i];
    }
    for(int i = 0; i < size;i++){
        res[i+1] += res[i] / 10;
        res[i] = res[i]%10;
    }
    int i = res.size()-1;
    while(res.back())res.pop_back();
    return res; 
}

void cpm(vector<int> &v1){
    v1.pop_back();
    for(int i =0 ;i < v1.size(); i++){
        v1[i] = -v1[i];
    }
}

vector<int> mul(vector<int> v1, vector<int>&v2){
    int size = v1.size() +v2.size();
    vector<int> res(size, 0);

    for(int i = 0; i < v1.size(); i++){
        for(int j = 0; j < v2.size(); j++){
            res[i+j] += v1[i]*v2[j];
        }
    }
    

    for(int i = 0; i < size-1; i++){
        res[i+1] += res[i] / 10;
        res[i] = res[i]%10;
    } 
    while(res.back()) res.pop_back();

    return res;
}

vector<int> div(vector<int> &v1, vector<int> v2){
    int size = v2.size() - v1.size();

    for(int i = size; i >= 0 ; i++){
        vector<int> d;
        int cnt = i;
        while(cnt--) d.push_back(0);
        for(int j = 0; j < v1.size(); j++){
            d.push_back(v1[j]);
        }

    }
}

bool bigger(vector<int> &v1, vector<int> &v2){
    if(v1.size() > v2.size()) return true;
}
int BOJ2408(){
    int n;
//    cin >> n;
    int a[5] = {1,2,3,4,5};
    int b[3] = {4,4,5};

    vector<int> v1, v2; 
    for(int i = 0; i < 5; i++) v1.push_back(a[i]);
    for(int i = 0; i < 3; i++) v2.push_back(a[i]);

    vector<int> res = add(v1,v2);
    int x = 0;
    return 0;
}