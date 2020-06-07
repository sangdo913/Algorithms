#include<iostream>
#include<string>
#include<vector>

using namespace std;
string table[10] ={"", "One ", "Two ", "Three ", "Four ", "Five ", "Six ", "Seven ", "Eight ", "Nine "};
string digittable[10] = {"", "", "Twenty ", "Thirty ", "Forty ", "Fifty ", "Sixty ", "Seventy ", "Eighty ", "Ninety " };
string tentable[10] = {"Ten ", "Eleven ", "Twelve ", "Thirteen ", "Fourteen ", "Fifteen ", "Sixteen ", "Seventeen ", "Eighteen ", "Nineteen "};
string table000[4] = {"", "Thousand ", "Million ", "Billion "};
string conv(int num){
    string res;
    if(num / 100){
        res += table[num/100] + "Hundred ";
        num%=100;
    }
    if(num/10){
        if(num/10 == 1){
            res += tentable[num%10];
            num = 0;
        }
        else{
            res += digittable[num/10];
            num %= 10;
        }
    }
    if(num){
        res += table[num];
    }
    return res;
}
class Solution {
public:
    string numberToWords(int num) {
        if(!num) return "Zero";
        vector<string> res;
        int cnt = 0;
        while(num){
            string ret = conv(num%1000);
            if(ret.size())
                res.push_back(conv(num%1000) + table000[cnt]);
            num/=1000;
            cnt++;
        }
        string r;
        while(res.size()){
            r += res.back();
            res.pop_back();
        }
        r.pop_back();
        return r;
    }
};