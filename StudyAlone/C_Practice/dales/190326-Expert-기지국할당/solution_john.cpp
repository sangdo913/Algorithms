/*
방법 1. 그냥 받자마자 4개중 젤가까운데 넣고 꽉차있을때 다음 가까운데 넣음 (LOSS: 8,803,322,100,320 / Time: 10s 미만)
방법 2. 
	1) 전체 cell 거리순(dis: 가장 가까운 nb까지 거리) sort
	2) 거리순으로 넣기
	3) 한 nb가 꽉차면 여분의 nb 중 제일 가까운것으로 dis 업데이트, sort table에 insert
	(LOSS: 8,706,299,537,689 / Time: 37s) => insert가 매우 오래걸림
방법 3. swtech 댓글 읽고 생각해보기
*/

#define SIZE 5000
#define MAX_COUNT 250000
#define FULL_NB 67500

extern int DONE;

char *_cells;
char **_CELLS;

int nb[4][2]; // y, x
int nb_count[4];

typedef struct cell {
	int y, x, dis, nb;
}CELL;
CELL cells[MAX_COUNT];
int cell_cnt;

void quickSort(int first, int last) {
	int pivot;
	int i;
	int j;
	CELL temp;

	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;

		while (i < j)
		{
			while (cells[i].dis <= cells[pivot].dis && i < last)
			{
				i++;
			}
			while (cells[j].dis > cells[pivot].dis)
			{
				j--;
			}
			if (i < j)
			{
				temp = cells[i];
				cells[i] = cells[j];
				cells[j] = temp;
			}
		}

		temp = cells[pivot];
		cells[pivot] = cells[j];
		cells[j] = temp;

		quickSort(first, j - 1);
		quickSort(j + 1, last);
	}
}

int getDistance(int sy, int sx, int dy, int dx) { // source destination
	return (sy - dy)*(sy - dy) + (sx - dx)*(sx - dx);
}

void getEachMinDistance() {
	int dis, min_dis, min_nb;
	CELL cell;
	for (size_t i = 0; i < 250000; i++)
	{
		min_dis = 0x7fffffff;
		cell = cells[i];
		for (size_t j = 0; j < 4; j++)
		{
			dis = getDistance(nb[j][0], nb[j][1], cell.y, cell.x);
			if (dis < min_dis) {
				min_dis = dis;
				min_nb = j;
			}
		}
		cells[i].dis = min_dis; cells[i].nb = min_nb;
	}
}
void findSecondNB(int cells_idx) {
	CELL cell = cells[cells_idx];
	int dis, min_dis=0x7fffffff, min_nb;
	for (size_t i = 0; i < 4; i++)
	{
		if (nb_count[i] >= FULL_NB) continue;
		dis = getDistance(nb[i][0], nb[i][1], cell.y, cell.x);
		if (dis < min_dis) {
			min_dis = dis;
			min_nb = i;
		}
	}
	cells[cells_idx].dis = min_dis; cells[cells_idx].nb = min_nb;
}
void insert(int cells_idx) {
	int dis = cells[cells_idx].dis;

	int s = cells_idx, e = MAX_COUNT - 1;
	int m = MAX_COUNT - 1;
	while (s < e) {
		m = (s + e) / 2;
		if (s == m || e == m) break;
		if (cells[m].dis == dis) break;
		else if (cells[m].dis < dis) {
			s = m;
		}
		else {
			e = m;
		}
	}

	// pull
	CELL cell = cells[cells_idx];
	for (size_t i = cells_idx; i < m; i++)
	{
		cells[i] = cells[i + 1];
	}
	cells[m] = cell;
}
void assignMostCells() {
	int i = 0;
	CELL cell;
	while (i < MAX_COUNT * 0.9) {
		cell = cells[i];
		 
		if (nb_count[cell.nb] >= FULL_NB) {
			findSecondNB(i);
			insert(i);
		}
		else {
			nb_count[cell.nb]++;
			_CELLS[0][SIZE * cell.y + cell.x] = cell.nb + 1;
			i++;
		}
	}
}
void test1(void* param) 
{
	_cells = (char *)param;
	_CELLS = &_cells;

	nb_count[0] = nb_count[1] = nb_count[2] = nb_count[3] = cell_cnt = 0;

	int cell;
	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < SIZE; j++)
		{
			cell = _CELLS[0][SIZE * i + j];
			if (cell < 0) {
				nb[-1 * cell - 1][0] = i;
				nb[-1 * cell - 1][1] = j;
			}
			if (cell > 0) {				
				cells[cell_cnt].y = i; cells[cell_cnt].x = j;
				cell_cnt++;
			}
		}
	}
	
	getEachMinDistance();
	quickSort(0, MAX_COUNT - 1);
	assignMostCells();

    DONE = 1;
}

void test2(void* param)
{
    //DONE = 1;
}
/*

expert 시험을 15번째 보고 있는 장수생입니다.

최종적으로 6878대 나왔으며, 로직은 다음과 같습니다.

1) 25만개의 사용자 각각에 대해서 기지국 1~4까지의 dx^2 + dy^2 거리값 계산해두고
2) 사용자마다 기지국 가까운 순서대로 sorting
3) 사용자마다 다음의 값으로 point 계산 (두번째 가까운 기지국 거리값 - 첫번째 가까운 기지국 거리값) * a + (3번째 가까운 기지국 거리값 - 2번째 가까운 기지국 거리값) * b + (4번째 가까운 기지국 거리값 - 3번째 가까운 기지국 거리값) * c
4) point 내림차순으로 사용자 전체정렬 (index 낮은 사용자<나중에 배정되면 손해를 많이 볼수 있는 사용자>가 먼저 기지국 할당되어야 한다는 생각)
5) 정렬된 순서대로 첫번째 사용자부터 본인에게 가장 가까운 기지국 할당
6) 기지국 할당하다가 하나의 기지국이 max(67500) 되면 나머지 3개의 기지국으로 point 재계산 후 정렬
7) 정렬된 순서대로 5)에 이은 사용자부터 본인에게 가장 가까운 기지국 할당
8) 기지국 할당하다가 또 하나의 기지국이 max가 되면 나머지 2개의 기지국으로 재계산 (이때는 2개뿐이기 때문에 최적할당을 할 수 있음)
9) 나머지 할당

10) 남은 1시간 동안, 위 3)의 a,b,c를 수정해가며 a,b,c 최적값을 찾았습니다.

thread는 처음 봤는데, 딱히 용도를 파악하지 못하고 함수 하나로만 구현했습니다.
1~3등 분들 점수가 괴수같지만, 실낱같은 기대를 하고 있습니다....
15수간 눈팅만 하다가 혹시나 도움이 될까, 처음으로 댓글 달아봅니다.
*/