#include <string>
#include <vector>
#include<algorithm>
#include<iostream>

using namespace std;

string solution(string new_id) {
    string answer = "";
    for(int i = 0; i < new_id.size(); ++i){
        if('A' <= new_id[i] && new_id[i] <= 'Z') new_id[i] = new_id[i]-'A' + 'a';
        else if(answer.size() > 0 &&  answer.back() == '.' && new_id[i] == '.') continue;
        
        if(('a' <= new_id[i] && new_id[i] <= 'z') || new_id[i] == '.' || new_id[i] == '-'  || ('0' <= new_id[i] && new_id[i] <= '9') || new_id[i] == '_' || new_id[i] == '.') {
            answer.push_back(new_id[i]);
        }
    }
    if(answer[0] == '.') answer = string(answer.begin()+1, answer.end());
    if(answer.back() == '.') answer.pop_back();
    if(answer.size() == 0) answer.push_back('a');
    if(answer.size() > 15) answer = string(answer.begin(), answer.begin() + 15);
    if(answer.back() == '.') answer.pop_back();
    while(answer.size() < 3) answer.push_back(answer.back());
    
    cout << answer << endl;
    return answer;
}