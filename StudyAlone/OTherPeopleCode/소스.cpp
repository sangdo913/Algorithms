#include<iostream>
#include<limits>
#include<queue>
using namespace std;
// 두 개의 벡터를 이어붙이는 곳
void mergef(vector <pair<int, int>>(&v1), vector <pair<int, int>> v2) {
	for (int i = 0, imax = v2.size(); i < imax; i++) {
		v1.push_back(v2[i]);
	}
}
class Client {
public:
	int a, b;
	int pos = 0;
};
int main(int argc, char** argv)
{
	int test_case;
	int T;
	//freopen("input.txt", "r", stdin);
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		// Init.
		int Answer = -1;
		int N, M, K, A, B;
		cin >> N >> M >> K >> A >> B;
		queue <int> wq[3];
		int* a = new int[N + 1];
		int* b = new int[M + 1];
		int* t = new int[K + 1];
		Client* cli = new Client[K + 1];
		for (int i = 1; i <= N; i++) {
			cin >> a[i];
		}
		for (int i = 1; i <= M; i++) {
			cin >> b[i];
		}
		for (int i = 1; i <= K; i++) {
			cin >> t[i];
		}
		int window[10][2] = { { 0 } };
		int imax, i, iter, nCli;

		vector <pair <int, int>> v[5];
		int simult = 0;
		while (v[4].size() < K) {
			for (int k = 1; k <= K; k++) {
				if (!t[k]) {
					switch (cli[k].pos) {
					case 0:
						v[0].push_back(make_pair(k, k)); cli[k].pos++;
						break;
					case 2:
						v[2].push_back(make_pair(cli[k].a, k));
						cli[k].pos++;
						window[cli[k].a][0] = 0; // evacuate the window
						break;
					case 4:
						v[4].push_back(make_pair(k, k));
						cli[k].pos++;
						window[cli[k].b][1] = 0;// evacuate the window
						break;
					default:
						break;
					}
				}
				else {
					t[k]--;
				}
			}

			mergef(v[1], v[0]);
			v[0].clear();
			//// v[2] 창구번호순 정렬
			{
				pair<int, int> tmppair;
				for (int j = 0, jmax = v[2].size() - 2; j <= jmax; j++) {
					for (int i = 1, imax = v[2].size() - j; i < imax; i++) {
						if (v[2][i].first < v[2][i - 1].first) {
							tmppair = v[2][i - 1];
							v[2][i - 1] = v[2][i];
							v[2][i] = tmppair;
						}
					}
				}

				for (int i = 0; i < v[2].size(); i++) {
					for (int j = 0; j < i; j++) {
						if (v[2][i].first < v[2][j].first) {
							tmppair = v[2][j];
							v[2][j] = v[2][i];
							v[2][i] = tmppair;
						}
					}
				}
			}
			///
			mergef(v[3], v[2]);
			v[2].clear();
			iter = v[3].size();
			while (iter) {
				for (int i = 1; i <= M; i++) {
					if (!window[i][1]) {
						nCli = v[3].front().second;
						window[i][1] = nCli;
						t[nCli] = b[i] - 1;
						cli[nCli].b = i;
						cli[nCli].pos = 4;
						v[3].erase(v[3].begin());
						break;
					}
				}
				iter--;
			}
			iter = v[1].size();
			while (iter) {
				for (int i = 1; i <= N; i++) {
					if (!window[i][0]) {
						nCli = v[1].front().second;
						window[i][0] = nCli;
						t[nCli] = a[i] - 1;
						cli[nCli].a = i;
						cli[nCli].pos = 2;
						v[1].erase(v[1].begin());
						break;
					}
				}
				iter--;
			}
		}

		bool first = true;
		for (int k = 1; k <= K; k++) {
			if (cli[k].a == A && cli[k].b == B) {
				if (first) {
					Answer++; // to get rid of -1
					first = false;
				}
				Answer += k;
			}
		}

		cout << "#" << test_case << " " << Answer << endl;
		delete[] a;
		delete[] b;
		delete[] t;
		delete[] cli;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

