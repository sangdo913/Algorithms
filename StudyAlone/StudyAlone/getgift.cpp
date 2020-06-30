#include<vector>
#include<string>
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
struct PERSON {
	string name;
};
struct GIFT {
	string name;
    string person;
	int num;
};
ostream& operator<<(ostream& os, const GIFT& i2) {
	// gift 출력부
	return os << i2.name;
}
void print_gift_info(int i, const GIFT& i2) {
	// gift 정보 출력부
	cout << i << "번: " << i2 << " (" << i2.num << " 명)\n";
}
GIFT& set_gift_info(GIFT &g) {
	//gift 입력부
	cin >> g.person >> g.name;
    g.num = 1;
	return g;
}
ostream& operator<<(ostream& os, const PERSON& i2) {
	//person 출력부
	return cout << i2.name;
}
PERSON& set_person_info(PERSON &p) {
	//person 입력부
	cin >> p.name;
	return p;
}
vector<PERSON> people;
vector<GIFT> gift;
int main() {
	freopen("0Text.txt", "r", stdin);
	srand(time(0));
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		GIFT g;
		gift.push_back(set_gift_info(g));
	}
	
	for (int i = 0; i < m; ++i) {
		PERSON p;
		people.push_back(set_person_info(p));
	}
	int cnt = 10000; // 셔플 수
	while (cnt--) {
		int i = rand() % gift.size() % people.size();
		int j = rand() % people.size();
		swap(people[i], people[j]);
	}
	int i = 0;
	cnt = 0;
	cout << "당첨\n";
	for (; i < gift.size() && cnt < people.size(); ++i) {
		print_gift_info(i + 1, gift[i]);
		while (gift[i].num-- && cnt < people.size()) {
			cout << people[cnt++] << ' ';
		}
		cout << "\n\n";
	}
	if (cnt < people.size()) {
		cout << "꽝\n";
		for (; cnt < people.size(); ++cnt) cout << people[cnt] << ' ';
		cout << '\n';
	}
	return 0;
}