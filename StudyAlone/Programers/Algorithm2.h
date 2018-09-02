#include<vector>
#include<iostream>
#include<algorithm>
#include<functional>
using namespace std;

//조건 (모든 works의 높이를 h로 만들 수 있는가?)
bool canConstruct(int no, vector<int>& works, int h){
    for(int i = 0; i < works.size(); i++){ 
        int minus = works[i] < h ? 0 : works[i] - h;
        no -= minus;
    }
    return no >= 0;
}

//파라메트릭 서치(만들 수 있는 높이들 중에 최고점)
int bs(int no, vector<int>& works){
    int l = 0, r = 1000;
    
    while(l <= r){
        int m = (l+r)/2;
        if(!canConstruct(no, works, m)){
            l = m+1;
        }
        else{
            r = m -1;
        }
    }
    //l이 만들 수 있는 점들의 최고 높이이다.
    return l;
}

int solution(int no, vector<int> works)
{
    sort(works.begin(), works.end(), greater<int>());
    int answer = 0;
    int h = bs(no,works);

    //높이가 최개 1천이기 떄문에 그냥 1부터 풀어도 된다.

    /* 
    int h = 1000;// = bs(no,works);
    
    for(int i = 1000; i >=0; i--){
        if(canConstruct(no,works, i)){
            h = i;
        }
        else break;
    }
    */
    
    //만들 수 있는 높이에서 work 들의 길이가 몇이 되고, no는 얼마나 남는지 계산
    for(int i = 0; i < works.size(); i++){
        int minus = works[i] < h ? 0 : works[i] - h;
        works[i] = h < works[i] ? h : works[i];
        no -= minus;
    }
    
    //no가 남으면 앞에서 부터 1씩 빼줌.
    //만약 2가 넘으면, 파라메트릭 서치에서 1 높은 값이 나왔을거임.
    for(int i = 0; i < works.size();i++){
        if(no==0) break;
        if(works[i]) works[i]--;
        no--;
    }
    
    //이제 남은 work들의 제곱을 더해주면 끝
    for(int i = 0; i < works.size(); i++){
        answer += works[i] * works[i];
    }
    
    return answer;
}