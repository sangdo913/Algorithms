#include<iostream>
#include<queue>

using namespace std;

int main(){
   vector<int> a;
    // vec.push_back(3);
    // vec.push_back(2);


    // for(auto i : vec){
    //     cout << i << ' ' ;
    // }
    a.resize(10);
    for(int i = 0; i < 10; ++i) a[i] = i;
    for(int i = 0; i < 10; ++i) cout << a[i] << ' ';
    cout << endl;
    cout << 1;
    cout << endl;
    return 0;
}