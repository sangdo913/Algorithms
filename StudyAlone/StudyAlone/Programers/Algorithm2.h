#include<vector>
#include<iostream>
#include<algorithm>
#include<functional>
using namespace std;

//���� (��� works�� ���̸� h�� ���� �� �ִ°�?)
bool canConstruct(int no, vector<int>& works, int h){
    for(int i = 0; i < works.size(); i++){ 
        int minus = works[i] < h ? 0 : works[i] - h;
        no -= minus;
    }
    return no >= 0;
}

//�Ķ��Ʈ�� ��ġ(���� �� �ִ� ���̵� �߿� �ְ���)
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
    //l�� ���� �� �ִ� ������ �ְ� �����̴�.
    return l;
}

int solution(int no, vector<int> works)
{
    sort(works.begin(), works.end(), greater<int>());
    int answer = 0;
    int h = bs(no,works);

    //���̰� �ְ� 1õ�̱� ������ �׳� 1���� Ǯ� �ȴ�.

    /* 
    int h = 1000;// = bs(no,works);
    
    for(int i = 1000; i >=0; i--){
        if(canConstruct(no,works, i)){
            h = i;
        }
        else break;
    }
    */
    
    //���� �� �ִ� ���̿��� work ���� ���̰� ���� �ǰ�, no�� �󸶳� ������ ���
    for(int i = 0; i < works.size(); i++){
        int minus = works[i] < h ? 0 : works[i] - h;
        works[i] = h < works[i] ? h : works[i];
        no -= minus;
    }
    
    //no�� ������ �տ��� ���� 1�� ����.
    //���� 2�� ������, �Ķ��Ʈ�� ��ġ���� 1 ���� ���� ����������.
    for(int i = 0; i < works.size();i++){
        if(no==0) break;
        if(works[i]) works[i]--;
        no--;
    }
    
    //���� ���� work���� ������ �����ָ� ��
    for(int i = 0; i < works.size(); i++){
        answer += works[i] * works[i];
    }
    
    return answer;
}