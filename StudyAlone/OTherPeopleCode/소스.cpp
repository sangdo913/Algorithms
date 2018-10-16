#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

int a[16][13];
int a1[16][13];
int bb, n, m;

int dx[] = { 0,0,-1,1 };
int dy[] = { 1,-1,0,0 };

typedef struct {
	int x, y;
}point;
queue< point > q;

int ans = 999;

//������� ���� ��� ó�����ش�.
void empty() {
	// 112001�� ��� , string�� �Ἥ 0���� ū ����϶��� ó���� 1121�� ������, ���� map�� �������ش�.
	for (int j = 0; j < m; j++) {
		string s = "";
		for (int i = 0; i < n; i++) {
			if (a[i][j] > 0) {
				s += to_string(a[i][j]);
			}
			a[i][j] = 0;
		}

		for (int i = 0; i < s.size(); i++) {
			a[i][j] = s[i] - '0';
		}
	}
}

void checking(int index) {

	//��ó�� ��ź�� ����
	for (int i = (n - 1); i >= 0; i--) {
		if (a[i][index] != 0) {
			int bbang = a[i][index];
			a[i][index] = 0;
			int x = i, y = index;

			for (int k = 0; k < 4; k++) {
				int nx = x, ny = y;
				for (int BB = 1; BB < bbang; BB++) {
					nx += dx[k];
					ny += dy[k];

					if (0 <= nx && nx < n && 0 <= ny && ny < n) {
						if (a[nx][ny] == 1)
							a[nx][ny] = 0;
						if (a[nx][ny]>1)
							q.push({ nx,ny });
					}
				}
			}
			break;
		}
	}

	//ó�� ��ź ���Ͽ��� ���� ���� �ٸ� �����鵵 ó�����ش�.
	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;
		int bbang = a[x][y];
		a[x][y] = 0;

		q.pop();

		for (int k = 0; k < 4; k++) {
			int nx = x, ny = y;
			for (int BB = 1; BB < bbang; BB++) {
				nx += dx[k];
				ny += dy[k];

				if (0 <= nx && nx < n && 0 <= ny && ny < n) {

					if (a[nx][ny] == 1)
						a[nx][ny] = 0;
					if (a[nx][ny]>1)
						q.push({ nx,ny });
				}
			}
		}
	}

	// ������� ���� ��� ������ ������ ������.
	empty();
}


//������ ����߸��� �ִ� ���
void go() {
	int B[4];
	for (B[0] = 0; B[0]< m; B[0]++)
		for (B[1] = 0; B[1] < m; B[1]++) {
			for (B[2] = 0; B[2] < m; B[2]++) {
				for (B[3] = 0; B[3] < m; B[3]++) {
					for (int i = 0; i < bb; i++) {
						checking(B[i]);
					}
					int result = 0;
					for (int i = 0; i < n; i++) {
						for (int j = 0; j < m; j++) {
							if (a[i][j] > 0)
								result += 1;
							a[i][j] = a1[i][j];
						}
					}
					ans = min(ans, result);

					if (ans == 0) return;

					if (bb < 4) break;
				}
				if (bb < 3)break;
			}
			if (bb < 2)break;
		}
}


//�ʱ�ȭ �Լ�
void init() {
	for (int i = 0; i<16; i++)
		for (int j = 0; j < 13; j++) {
			a[i][j] = 0; a1[i][j] = 0;
		}

	ans = 999;
}

int main() {
	int tc = 0; scanf("%d", &tc);
	for (int t = 1; t <= tc; t++) {
		cin >> bb >> m >> n;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				scanf("%d", &a[i][j]);
				a1[i][j] = a[i][j];
			}

		//���� ���ϰ� x�� ��Ī��Ų��
		int temp = n / 2;

		for (int i = 0; i < temp; i++)
			for (int j = 0; j < m; j++) {
				a[i][j] = a[(n - 1) - i][j];
				a[(n - 1) - i][j] = a1[i][j];
			}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				a1[i][j] = a[i][j];
			}
		}

		go();
		printf("#%d %d\n", t, ans);
		init();
	}

	return 0;
}
