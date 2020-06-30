#include<vector>
#include<string>
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
struct PERSON {
	string name;
	string number;
};
struct GIFT {
	string name;
	string person;
	int num;
};
ostream& operator<<(ostream& os, const GIFT& i2) {
	// gift ��º�
	return os << i2.name;
}
void print_gift_info(int i, const GIFT& i2) {
	// gift ���� ��º�
	cout << i << "��: " << i2 << " (" << i2.num << " ��) �Ŀ��� : " << i2.person << '\n';
}
GIFT& set_gift_info(GIFT &g) {
	//gift �Էº�
	cin >> g.person >> g.name;
	g.num = 1;
	return g;
}
ostream& operator<<(ostream& os, const PERSON& i2) {
	//person ��º�
	return cout << i2.name << " ("<< i2.number << ')';
}
PERSON& set_person_info(PERSON &p) {
	//person �Էº�
	cin >> p.name >> p.number;
	return p;
}
vector<PERSON> people;
vector<GIFT> gift;
#include<stdio.h>
int nums[10000];
int main() {
	freopen("Text.txt", "r", stdin);
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
	int ccnt = 1000;
	int idx[10000];
	while (ccnt--) {
		for (int i = 0; i < m; ++i) idx[i] = i;
		int cnt = 10000; // ���� ��
		while (cnt--) {
			int i = rand() % gift.size() % people.size();
			int j = rand() % people.size();
			swap(idx[i], idx[j]);
			//swap(people[i], people[j]);
		}
		int i = 0;
		cnt = 0;
		//cout << "��÷\n";
		for (; i < gift.size() && cnt < people.size(); ++i) {
			nums[idx[i]]++;
			//print_gift_info(i + 1, gift[i]);
			//while (gift[i].num-- && cnt < people.size()) {
			//	//cout << people[cnt++] << ' ';
			//}
			//cout << "\n\n";
		}
		//if (cnt < people.size()) {
		//	//cout << "��\n";
		//	//for (; cnt < people.size(); ++cnt) cout << people[cnt] << '\n';
		//	//cout << '\n';
		//}
	}
	cout << "1000�� ��ǰ ���� ���\n";
	for (int i = 0; i < m; ++i) cout << i << "�� �ι� ��÷ �� : "<< nums[i] << '\n';
	cout << endl;
	return 0;
}