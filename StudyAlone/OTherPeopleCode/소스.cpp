#include <iostream>
using namespace std;

int main()
{
	long long n;
	cin >> n;
	if (n % 2 == 0) {
		cout << 0; return 0;
	}

	for (long long i = 3; i*i <= n; i += 2) {
		if (n%i == 0) {
			cout << 0; return 0;
		}
	}

	cout << 1;
	return 0;
}