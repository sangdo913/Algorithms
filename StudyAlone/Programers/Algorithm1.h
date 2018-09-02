#include <string>
#include <vector>
#include <iostream>
#include<string>

using namespace std;

//int를 숫자 스트링으로 만듬
string toString(int n){
    string res;
    while(n){
        res.push_back((n%10) + '0');
        n /= 10;
    }
    return res;
}

int res = 0;

//앞 뒤가 같은지 확인
bool isPelin(string& str){
    int len = str.size();
    for(int i = 0; i < len/2; i++){
        if(str[i] != str[len-1-i]) return false;
    }
    return true;
}

int solution(int n, int m) {
    int answer = 0;
    
    //n부터 m까지 숫자를 스트링으로 만들고, 펠린드롬 검사
    for(int i = n; i <= m; i++){
        string str = toString(i);
        answer += isPelin(str);
    }

    return answer;
}