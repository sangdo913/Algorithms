#include <string>
#include <vector>
#include <iostream>
#include<string>

using namespace std;

//int�� ���� ��Ʈ������ ����
string toString(int n){
    string res;
    while(n){
        res.push_back((n%10) + '0');
        n /= 10;
    }
    return res;
}

int res = 0;

//�� �ڰ� ������ Ȯ��
bool isPelin(string& str){
    int len = str.size();
    for(int i = 0; i < len/2; i++){
        if(str[i] != str[len-1-i]) return false;
    }
    return true;
}

int solution(int n, int m) {
    int answer = 0;
    
    //n���� m���� ���ڸ� ��Ʈ������ �����, �縰��� �˻�
    for(int i = n; i <= m; i++){
        string str = toString(i);
        answer += isPelin(str);
    }

    return answer;
}