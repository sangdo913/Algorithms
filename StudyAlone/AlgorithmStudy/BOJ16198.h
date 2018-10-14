//https://www.acmicpc.net/problem/16198
//BOJ 16198 에너지 모으기

#include<iostream>
#include<vector>

using namespace std;

int MAX(int i1, int i2){return i1 < i2 ? i2 : i1;}

int dfs(vector<int> vec, int e){
    if(vec.size() == 2){
        return e;
    }
    int res = 0;

    for(int i = 1; i < vec.size()-1;i++){
        int ne = e + vec[i-1] *vec[i+1];
        vector<int> nvec = vec;
        nvec.erase(nvec.begin()+ i);
        res = MAX(res, dfs(nvec, ne));
    }

    return res;
}

int BOJ16198(){
    vector<int> vec;
    int n;
    cin  >> n;
    vec.resize(n);
    for(int i = 0; i < n; i++){
        cin >> vec[i];
    }

    cout << dfs(vec, 0);
    
    return 0;
}