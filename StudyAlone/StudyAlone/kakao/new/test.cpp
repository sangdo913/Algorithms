#include<iostream>
#include<tuple>
using namespace std;

int main(){
    pair<int,int> pa= {1,32};
    int x,y;
    tuple<int&, int&> (x, y) = pa;
    printf("%d %d\n", x,y);
    return 0;
}