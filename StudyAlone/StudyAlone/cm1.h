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
	// [����] ��ư�� ������ ��� ���� �� �� �ֽ��ϴ�.

	return answer;
}