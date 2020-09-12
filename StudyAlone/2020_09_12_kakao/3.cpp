#include <string>
#include <vector>
#include<algorithm>
#include<sstream>
#include<iostream>
#include<map>

using namespace std;
struct INFO{
    vector<string> str;
    int score;
    bool operator<(INFO i1){
        return score < i1.score;
    }
};

struct cmp{
};


vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> answer;
    vector<INFO> score(info.size());
    vector<int> myinfo[1<<4];
    map<string, int> myconv;
    myconv["cpp"] = 0;
    myconv["java"] = 1;
    myconv["python"] = 2;
    myconv["-"] = 3;
    
    myconv["backend"] = 0;
    myconv["frontend"] = 1;
    
    myconv["junior"] = 0;
    myconv["senior"] = 1;
    
    myconv["chicken"] = 0;
    myconv["pizza"] = 1;
    map<int, vector<int>> infos; 
    for(int i = 0; i < info.size(); ++i){
        stringstream stream;
        string t;
        stream.str(info[i]);
       	while(getline(stream, t, ' ')){
            score[i].str.push_back(t);
        }
        score[i].score = 0;
        for(int j = 0; j < score[i].str[4].size(); ++j) {
           score[i].score = score[i].score * 10 + score[i].str[4][j]-'0';
        }
        
    }
    sort(score.begin(), score.end());
    for(int i = 0; i < score.size(); ++i){
        for(int b = 0; b < (1<<4); ++b){
            int bb = b;
            int convb = 0;
            for(int cnt = 0; cnt < 4; ++cnt){
                if(bb&1){
                    convb += myconv[score[i].str[cnt]];
                }
                else {
                    convb+= 3;
                }
                convb<<=2;
                bb>>=1;
            }
            infos[convb].push_back(score[i].score);
        }
    }
    for(auto it : query){
        stringstream stream;
        string t;
        stream.str(it);
        vector<string> str;
        int bit = 0;
        while(getline(stream, t, ' ')){
            if(t == "and") continue;
            bit = (bit << 2) + myconv[t];
            str.push_back(t);
        }
        int dscore = 0;
        for(int j = 0; j < str[4].size(); ++j){
            dscore = dscore*10 + str[4][j] - '0';
        }
        int num = 0;
        int idx = lower_bound(infos[bit].begin(), infos[bit].end(), dscore) - infos[bit].begin();
        answer.push_back(infos[bit].size() - idx);
    }
    return answer;
}