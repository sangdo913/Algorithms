#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int nums[1001];
vector<int> res;

int MAX(int i1, int i2){return i1 < i2 ? i2 : i1;}

struct cmp{
    bool operator()(int i1, int i2){
        return nums[i1] < nums[i2];
    }
};

int A481(){
    int n;

    cin >> n;

    for(int i = 0; i < n; i++){
        int num;
        cin >> num;
        nums[num] = MAX(i, nums[num]);
        res.push_back(num);
    }

    sort(res.begin(),res.end());
    res.resize(unique(res.begin(),res.end())- res.begin());
    
    sort(res.begin(), res.end(), cmp());

    cout << res.size() << '\n';
    for(int i = 0; i < res.size(); i++){
        cout << res[i] << ' ' ;
    }
    return 0;
}