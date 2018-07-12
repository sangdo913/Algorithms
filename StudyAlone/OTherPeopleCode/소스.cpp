#include<iostream>
#include<string>
int insert[26];
int erase[26];
int L, K;
using namespace std;
int min(int i1, int i2);

int findAnswer(string s) {
	int left = 0;
	int right = s.size() - 1;
	int price = 0;
	while (left<right) {
		if (s.at(left) == s.at(right)) {
			left++;
			right--;
		}
		else {
			//그리디 알고리즘
			if (min(insert[s.at(left) - 97], erase[s.at(left) - 97])<min(insert[s.at(right) - 97], erase[s.at(right) - 97])) {
				if (insert[s.at(left) - 97] <erase[s.at(left) - 97]) {
					price += insert[s.at(left) - 97];
					left++;
				}
				else {
					price += erase[s.at(left) - 97];
					left++;
				}
			}
			else {
				if (insert[s.at(right) - 97]  <  erase[s.at(right) - 97]) {
					price += insert[s.at(right) - 97];
					right--;
				}
				else {
					price += erase[s.at(right) - 97];
					right--;
				}
			}
		}

	}

	return price;

}

int min(int a, int b) {
	return a<b ? a : b;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	//freopen("input.txt", "r", stdin);
	cin >> T;
	string s;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> L >> K;
		cin >> s;
		for (int i = 0; i<K; i++)cin >> insert[i] >> erase[i];
		cout << "#" << test_case << " " << findAnswer(s) << endl;
		s.clear();


	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}