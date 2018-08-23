#include<cstdio>
#include<cstring>
int n, m, k;
int info[100][100][2];

//미생물 정보
struct infos {
	int direct; // 방향 1 : 상 2 : 하 3 : 좌 4 : 우
	int num;	// 미생물 개수
	int cod[2];	// 미생물 좌표
} sangs[1001];

int dr[5] = { 0, -1, 1, 0,0 };	// 상하좌우
int dc[5] = { 0,0,0,-1,1 };		// 상하좌우
int conv[5] = { 0, 2,1,4,3 };	// 상 -> 하, 하 -> 상, 좌 -> 우, 우 -> 좌

// 행, 열이 0 이거나 n-1이면 경계로 간다!
bool isOut(int r, int c) {
	return r == 0 || r == n - 1 || c == 0 || c == n - 1;
}

int main() {
	int t;
	scanf("%d\n", &t);

	for (int tc = 1; tc <= t; tc++) {
		scanf("%d %d %d\n", &n, &m, &k);

		//미생물 정보 받기
		for (int i = 1; i <= k; i++) {
			scanf("%d %d %d %d\n", &sangs[i].cod[0], &sangs[i].cod[1], &sangs[i].num, &sangs[i].direct);
		}

		//시간만큼 시뮬레이션 진행
		while (m--) {
			//맵을 초기화 한다!
			memset(info, 0, sizeof(info));

			for (int i = 1; i <= k; i++) {
				infos &m = sangs[i];

				// 미생물 수가 0이면, 사라진 미생물 군집
				if (m.num == 0) continue;

				// 이동 방향으로 이동한다.
				m.cod[0] += dr[m.direct];
				m.cod[1] += dc[m.direct];
				
				// 경계에 닿았을 경우 방향을 반대로 바꾸고, 미생물 수를 반으로 줄인다.
				if (isOut(m.cod[0], m.cod[1])) {
					m.direct = conv[m.direct];
					m.num >>= 1;
				}

				//이미 해당 좌표를 대표하는 미생물이 있는 경우
				if (info[m.cod[0]][m.cod[1]][0]) {
					
					// 해당 좌표를 대표하는 미생물 군집의 번호를 받는다.
					int idx = info[m.cod[0]][m.cod[1]][0];

					//대표 미생물 군집에 자신의 미생물 수를 더한다.
					sangs[idx].num += m.num;

					//만약, 방향을 대표하는 미생물 군집의 미생물 수보다 자신의 미생물 수가 많다면 미생물 군집의 방향을 자신의 방향으로 
					//바꾸고, 방향을 대표하는 미생물 군집의 수를 자신의 미생물 수로 바꾼다!
					if (info[m.cod[0]][m.cod[1]][1] < m.num) {
						info[m.cod[0]][m.cod[1]][1] = m.num;
						sangs[idx].direct = m.direct;
					}

					//처리가 완료되면 자신의 미생물 군집을 사라지게 한다.
					m.num = 0;
				}

				//해당 좌표를 대표하는 미생물 군집이 없으면 자신이 해당 좌표를 대표하는 미생물 군집이 된다.
				else {
				
					info[m.cod[0]][m.cod[1]][0] = i;
					info[m.cod[0]][m.cod[1]][1] = m.num;
				}
			}
		}
		int res = 0;
		// 살아있는 미생물들의 수를 출력한다.
		for (int i = 1; i <= k; i++) res += sangs[i].num;
		printf("#%d %d\n", tc, res);
	}
}


