#include<tuple>
#include<iostream>

using namespace std;

int main() {
	tuple<int, int, int>tp;
	auto i = get<0>(tp);
	i = 2;

	cout << get<0>(tp) << endl;
	return 0;
}