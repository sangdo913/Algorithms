//CPU
//https://www.acmicpc.net/problem/16506

#include<iostream>
#include<string>
#include<map>

using namespace std;

map<string, string> mp;

string conv(int num, int digit){
    string res;
    for(int i = 0; i < digit; i++){
        res += (num&1) + '0';
        num>>=1;
    }
    return string(res.rbegin(), res.rend());
}

int Do(){
    mp.insert({"ADD","0000"});
    mp.insert({"SUB", "0001"});
    mp.insert({"MOV", "0010"});
    mp.insert({"AND", "0011"});
    mp.insert({"OR", "0100"});
    mp.insert({"NOT","0101"});
    mp.insert({"MULT", "0110"});
    mp.insert({"LSFTL", "0111"});
    mp.insert({"LSFTR", "1000"});
    mp.insert({"ASFTR", "1001"});
    mp.insert({"RL", "1010"});
    mp.insert({"RR", "1011"});

    int n;
    cin >> n;

    while(n--){
        string comm;
        int rd,ra,rb;
       cin >> comm >> rd >> ra >> rb; 
       
       string res;
       
       bool isC = *comm.rbegin() == 'C';

        res += mp.find(string(comm.begin(), comm.begin() + comm.size() - isC))->second; 
        res += isC + '0';
        res += '0';
        res += conv(rd, 3);
        res += conv(ra, 3);
        
        rb <<= !isC;
        res += conv(rb, 4);

        cout << res << '\n';
    }
    return 0;
}