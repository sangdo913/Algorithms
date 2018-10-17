#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int CODEFORCE(){
    vector<int> vec;
    vec.resize(3);
    cin >> vec[0] >> vec[1] >> vec[2];
    sort(vec.begin(), vec.end());

    int i = vec[2] - vec[0] - vec[1] + 1;
     
    cout << (i > 0 ? i  : 0); 
    return 0;
}