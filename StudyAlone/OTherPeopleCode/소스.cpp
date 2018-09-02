#include<vector>
#include<iostream>
#include<algorithm>
#include<functional>
#include<queue>
using namespace std;

//조건 (모든 works의 높이를 h로 만들 수 있는가?)
bool canConstruct(int no, vector<int>& works, int h) {
	for (int i = 0; i < works.size(); i++) {
		int minus = works[i] < h ? 0 : works[i] - h;
		no -= minus;
	}
	return no >= 0;
}

//파라메트릭 서치(만들 수 있는 높이들 중에 최고점)
int bs(int no, vector<int>& works) {
	int l = 0, r = 1000;

	while (l <= r) {
		int m = (l + r) / 2;
		if (!canConstruct(no, works, m)) {
			l = m + 1;
		}
		else {
			r = m - 1;
		}
	}
	//l이 만들 수 있는 점들의 최고 높이이다.
	return l;
}

int solution(int no, vector<int> works)
{
	sort(works.begin(), works.end(), greater<int>());
	int answer = 0;
	int h = bs(no, works);

	//높이가 최개 1천이기 문에 그냥 1부터 풀어도 된다.

	/*
	int h = 1000;// = bs(no,works);

	for(int i = 1000; i >=0; i--){
	if(canConstruct(no,works, i)){
	h = i;
	}
	else break;
	}
	*/

	priority_queue<int> pq;
	//만들 수 있는 높이에서 work 들의 길이가 몇이 되고, no는 얼마나 남는지 계산
	for (int i = 0; i < works.size(); i++) {
		int minus = works[i] < h ? 0 : works[i] - h;
		works[i] = h < works[i] ? h : works[i];
		pq.push(works[i]);
		no -= minus;
	}

	//남은 것이 많으면 pq에서 높은 것 부터 제거
	while (no) {
		int now = pq.top();
		pq.pop();
		now--;
		no--;
		pq.push(now);
	}
	
	//이제 남은 work들의 제곱을 더해주면 끝
	while (pq.size()) {
		answer += pq.top()*pq.top();
		pq.pop();
	}

	return answer;
}