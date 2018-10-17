#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

int CodeforcesC(){
    int n;
    cin >> n;
    string a;
    cin >> a;
    sort(a.begin(), a.end());
    cout << a;
    return 0;
}