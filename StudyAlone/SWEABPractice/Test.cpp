#include<iostream>
#include<unordered_map>
#include<string>

using namespace std;
unordered_multimap<int, string> mp;

int main() {
	mp.insert({ 1, "wef" });
	mp.insert({1, "ythlk" });
	mp.insert({ 2, "re" });

	auto range = mp.equal_range(10);
	if (range.first == mp.end() && range.second == mp.end()) cout << "NULL\n";
	else { cout << "FIND!\n";
	
	for (auto it = range.first; it != range.second; it++) {
		cout << it->second << '\n';
	}
	}
	return 0;
}