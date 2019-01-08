//Cow Baseball
//https://www.acmicpc.net/problem/9873

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int Do(){
    vector<int> vec;
    int n;
    cin >> n;
    
    while(n--){
        int in;
        cin >> in;
        vec.push_back(in);
    }

    sort(vec.begin(), vec.end());

    int res = 0;

    for(int i = 0; i < vec.size(); i++){
        for(int j = i+1;j < vec.size(); j++){
            int diff = vec[j] - vec[i];
            int s = lower_bound(vec.begin(), vec.end(), vec[j] + diff) - vec.begin();
            int e = upper_bound(vec.begin(), vec.end(), vec[j] + 2*diff) - vec.begin(); 
            res += e - s;
        }
    }
    
    cout << res;

    return 0;
}