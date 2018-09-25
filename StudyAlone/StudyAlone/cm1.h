#include <vector>
#include <iostream>
using namespace std;

bool thereis[100001];
bool solution(vector<int> arr)
{
	bool answer = true;
	
	int max = 0;
	for (int i = 0; i < arr.size(); i++) {
		thereis[arr[i]] = true;
	}
	for (int i = 1; i <= arr.size(); i++) {
		if (arr[i] == false) return false;
	}
	// [실행] 버튼을 누르면 출력 값을 볼 수 있습니다.

	return answer;
}