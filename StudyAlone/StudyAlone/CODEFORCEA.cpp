#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){
    vector<int> vec;
    vec.resize(3);

    cin >> vec[0] >> vec[1] >> vec[2];

    sort(vec.begin(), vec.end());

    cout << vec[2] - vec[0] - vec[1] +1 << endl;
}
