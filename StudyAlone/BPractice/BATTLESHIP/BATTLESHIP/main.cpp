#include<cstdio>
#include<iostream>
#include<fstream>

using namespace std;

enum COMM { ADD, DELETE, GET };

extern void insert(int, int);
extern void init();
extern void erase(int from, int to);
extern int get(int idx);
extern void allprint();

unsigned long long seed;
unsigned long long myrand() {
	return (seed = (214013LL * seed + 2531011LL));
}

int main()
{
	ofstream my("Text.txt");
	seed = myrand();
	int T = 20, score;
	my << T << endl;
	for (int tc = 1; tc <= T; ++tc) {
		int size = 0;
		score = 100;
		init();
		int cnt = 100000;
		int score = 100;
		 my << cnt << endl;
		for (int i = 0; i < cnt; ++i) {
			int comm, idx, val;
			int from, to;
			int res;
			comm = myrand() % 100;
			if (comm < 2)
				comm = DELETE;
			else if (comm < 8)
				comm = GET;
			else
				comm = ADD;
			if (size < 10000)
				comm = ADD;
			
			my << comm << ' ';

			switch (comm) {
			case ADD:
				if (size)
					idx = myrand() % size;
				else
					idx = 0;
				val = myrand() % 2000000000;
				insert(idx, val);
				my << idx << ' ' << val << endl;
				size++;
				break;

			case DELETE:
				from = myrand() % size;
				to = 0;
				if (size / 100)
					to = myrand() % (size / 100);
				if (from + to >= size)
					to = size - 1;
				else
					to = from + to;

				erase(from, to);
				my << from << ' ' << to << endl;
				size -= to - from + 1;
				break;
			case GET:
				idx = myrand() % size;
				res = get(idx);
				 my << idx << ' ' << res << endl;
				break;
			}
		}
	}
	 printf("total score : %d\n", score);
	return 0;
}