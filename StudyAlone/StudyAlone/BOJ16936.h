#include<iostream>
#include<set>

using namespace std;

set<long long> se;

long long n, arr[100];
long long res[100];

int Do(){
    cin >> n;
    for(int i = 0; i < n; i++) cin >>arr[i], se.insert(arr[i]);

    long long num;
    int two=1000, three=-1;

    long long temp = arr[0];

    for(int i = 0; i < n; i++){
        int ttwo = 0, tthree = 0;
        temp = arr[i];
        while(temp%2LL==0LL) ttwo++, temp/=2LL;
        temp = arr[i];
        while(temp%3LL ==0LL) tthree++, temp/=3LL;

        if(ttwo <= two && tthree >= three){
            num = arr[i], two = ttwo, three = tthree;
        }
    }

    res[0] = num;
    for(int i = 1; i < n; i++){
        if(num%3LL == 0LL && se.find(num/3LL) !=se.end()){
            num = *se.find(num/3LL);
            res[i] = num;
        }
        else{
            num = *se.find(num*2LL);
            res[i] = num; 
        }
    }

    for(int i = 0; i < n; i++) cout << res[i] << ' ';

    return 0;
}