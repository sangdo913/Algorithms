#include<iostream>
#include<queue>

using namespace std;

struct A{
    public:
    static const vector<int> CLEAR;
    vector<int> bb;
    A():bb(CLEAR){}
};
const vector<int> A::CLEAR = vector<int>(10,-1);

int main(){
    A haha;
    for(int i =0; i < haha.bb.size(); ++i) cout << haha.bb[i];
    return 0;
}