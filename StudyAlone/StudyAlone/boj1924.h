#include<iostream>

using namespace std;

int days[12] = {0,31,28,31,30,31,30,31,31,30,31,30};
char yo[7][4] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

int Do(){
    int m, d;
    cin >> m >> d;
    for(int i = 0; i < m; i++){
        d+= days[i];
    }

    cout << yo[d%7];
    return 0;
}