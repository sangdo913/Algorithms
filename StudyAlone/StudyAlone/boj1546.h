//ЦђБе
//https://www.acmicpc.net/problem/1546

#include<iostream>

using namespace std;

double scores[1000];

int Do(){
    int n;
    double max  = 0;

    cin >> n; 

    for(int i = 0; i < n; i++) {
        cin >> scores[i];
        if(scores[i] > max){
            max = scores[i];
        }
    }

    double res = 0;
    for(int i = 0; i < n; i++){
        res += scores[i] / max*100;
    }

   cout << res/ double(n);
    
    return 0;
}
