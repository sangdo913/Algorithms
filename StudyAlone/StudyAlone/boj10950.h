#include<iostream>
#include<string>
#include<set>

using namespace std;

int MIN(int a, int b){return a< b ? a : b;}

int Do(){
    int a, b, c;
    cin >> a >> b >> c;
    a--, b--, c--;
    
    set<int> se[3];

    se[0].insert(a), se[1].insert(b), se[2].insert(c);
    while(true){
        if(se[1].find(a) != se[1].end() && se[2].find(a) != se[2].end()) {
            cout << a+1; return 0;
        }

        else if(se[0].find(b) != se[0].end() && se[2].find(b) != se[2].end())
        {
            cout << b+1 ; return 0;

        }
        else if(se[0].find(c)  !=se[0].end() && se[1].find(c) !=se[1].end()){
            cout << c+1 ; return 0;
        }
        a+= 15;
        b+=28;
        c+= 19;
        se[0].insert(a);
        se[1].insert(b);
        se[2].insert(c);
    }

    return 0;
}
