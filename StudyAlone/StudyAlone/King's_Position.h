#pragma once
#include<iostream>

using namespace std;
struct King_Node;
struct King_Data;
struct King_Cod
{
	int x;
	int y;
	bool operator==(King_Cod& c)
	{
		return c.x == x && c.y == y;
	}
};
struct King_Data
{
	int x; int y;
	int count;
	King_Cod king;
	King_Cod empty1;
	King_Cod empty2;
	int direct;
	bool operator==(King_Data &data)
	{
		return x == data.x && y == data.y;
	}
	void set(King_Cod k, King_Cod e1, King_Cod e2, int  dir, int cnt)
	{
		king = k; empty1 = e1; empty2 = e2; direct = dir; count = cnt;
	}
};
struct King_Node
{
	typedef King_Data Data;
	typedef King_Node Node;
	Node* prev;
	Node* next;
	Data value;
	King_Node();
};

King_Node::King_Node()
{
	prev = next = NULL;
}

struct King_Queue
{
	typedef King_Node::Data Data;
	typedef King_Node Node;
	Node* head;
	Node* tail;
	int size;
	King_Queue();
	~King_Queue();
	void push(Data data);
	Data pop();
	bool empty();
};

bool King_Queue::empty()
{
	return size == 0;
}

void King_Queue::push(Data data)
{
	size++;
	Node* newNode = new Node();
	newNode->value = data;

	newNode->next = head->next;
	newNode->prev = head;

	newNode->next->prev = newNode;
	head->next = newNode;
}

King_Queue::Data King_Queue::pop()
{
	if (size == 0) return{ -1,-1,-1 };
	size--;
	Node* rNode = tail->prev;
	Data value = rNode->value;
	tail->prev = rNode->prev;
	rNode->prev->next = tail;

	delete(rNode);
	return value;
}

King_Queue::King_Queue()
{
	head = new Node();
	tail = new Node();
	size = 0;
	head->next = tail;
	tail->prev = head;
}

King_Queue::~King_Queue()
{
	Node* rNode;
	while (head)
	{
		rNode = head;
		head = head->next;
		delete(rNode);
	}
}
#define KING_INF 1000000
char Kings_map[52][52];
int Kings_count[52][52];
int Kings_space_Count[52][52];
int King_memoi[4][52][52];
bool Kings_visit[52][52];
King_Data Kings_Init(int H, int W,King_Data &empty1, King_Data &empty2)
{
	King_Data king;
	bool king_Position_selected = false, firstEmptySelected = false;
	for (int cols = 0; cols <= W + 1; cols++)
	{
		Kings_map[0][cols] = '*';
		Kings_map[H + 1][cols] = '*';
	}
	for (int rows = 1; rows <= H; rows++)
	{
		Kings_map[rows][0] = '*';
		Kings_map[rows][W + 1] = '*';
	}

	for (int rows = 1; rows <= H; rows++)
		for (int cols = 1; cols <= W; cols++)
		{
			cin >> Kings_map[rows][cols];
			for (int dir = 0; dir < 4; dir++)
			{
				King_memoi[dir][rows][cols] = KING_INF;//0;//
			}
			Kings_visit[rows][cols] = false;
			if (Kings_map[rows][cols] == 'X' && !king_Position_selected)
			{
				king.x = cols; king.y = rows;
				king_Position_selected = true; 
			}
			else if (Kings_map[rows][cols] == '.')
			{
				if (firstEmptySelected) empty2 = { cols,rows,0 };
				else
				{
					empty1 = { cols,rows,0 };
					firstEmptySelected = true;
				}
				Kings_map[rows][cols] = 'o';
			}
		}

	Kings_map[king.y][king.x] = 'o';
	Kings_map[king.y + 1][king.x] = 'o';
	Kings_map[king.y + 1][king.x + 1] = 'o';
	Kings_map[king.y][king.x + 1] = 'o';
	return king;
}

bool Kings_Can_Move(int x, int y,int direct)
{
	enum Dir{U = 0,R,D,L};
	bool result = true;
	Dir dir;
	dir = (Dir)direct;

	int dx[2][4] = { {0,2,0,-1}, {1,2,1,-1} };
	int dy[2][4] = { {-1,0,2,0},{-1,1,2,1} };
	
	result &= Kings_map[y + dy[0][dir]][x + dx[0][dir]] != '*';
	result &= Kings_map[y + dy[1][dir]][x + dx[1][dir]] != '*';
	return result;
}
int Kings_Number_Of_Move(King_Data king,int H, int W, King_Data empty1, King_Data empty2)
{
	typedef King_Queue queue;
	queue que;
	King_Data d = { 1,1,0 }, newData;
	for (int i = 1; i <= H; i++)
	{
		for (int j = 1; j <= W; j++)
		{
			Kings_count[i][j] = KING_INF;
		}
	}
	Kings_count[1][1] = 0;
	que.push(d);
	enum Dir{U=0,R,D,L};
	Dir dir;
	int dx[4] = { 0,1,0,-1 };
	int dy[4] = { -1,0,1,0 };
	
	while (!que.empty())
	{
		d = que.pop();
		
		for (int dir = 0; dir < 4; dir++)
		{
			if (Kings_count[d.y + dy[dir]][d.x + dx[dir]] <= d.count) continue;
			if (Kings_Can_Move(d.x, d.y, dir))
			{

				newData = { d.x + dx[dir], d.y + dy[dir], d.count + 1 };
				Kings_count[newData.y][newData.x] = newData.count;
				que.push(newData);
			}
		}
	}

	return Kings_count[king.y][king.x];
}

inline bool Kings_Space_Can_Move(King_Data pos)
{
	return Kings_map[pos.y][pos.x] !='*' && Kings_map[pos.y][pos.x] != 'X';
}


int Kings_Get_Number_Of_Between_Two_Points(King_Data from, King_Data to,int H, int W)
{
	typedef King_Queue queue;
	typedef King_Data Data;
	queue que;
	Data d;
	Data newData;
	for (int i = 1; i <= H; i++)
		for (int j = 1; j <= W; j++)
			Kings_space_Count[i][j] = KING_INF;
	d = { from.x, from.y, 0 };
	Kings_space_Count[d.y][d.x] = 0;

	que.push(d); 
	int dx[4] = { 0,1,0,-1 };
	int dy[4] = { -1,0,1,0 };
	int nextX, nextY, nextCount;
	int returnCount = KING_INF;
	while (!que.empty())
	{
		newData = que.pop();
		if (newData == to)
		{
			returnCount = newData.count;
			break;
		}
		for (int dir = 0; dir < 4; dir++)
		{
			nextX = newData.x + dx[dir];
			nextY = newData.y + dy[dir];
			nextCount = newData.count + 1;
			if (Kings_Space_Can_Move({ nextX,nextY,0 }))
			{
				if (Kings_space_Count[nextY][nextX] > nextCount)
				{
					Kings_space_Count[nextY][nextX] = nextCount;
					que.push({ nextX,nextY,nextCount });
				}
			}
		}
	}
	return returnCount;
}



int Kings_Get_Number_Of_Empty_Move(King_Data destiny1, King_Data destiny2, King_Data empty1, King_Data empty2,int H, int W)
{
	int path1, path2;
	path1 = Kings_Get_Number_Of_Between_Two_Points(empty1, destiny1,H,W) + Kings_Get_Number_Of_Between_Two_Points(empty2, destiny2, H, W);
	path2 = Kings_Get_Number_Of_Between_Two_Points(empty2, destiny1, H, W) + Kings_Get_Number_Of_Between_Two_Points(empty1, destiny2, H, W);
	path1 = path1 > path2 ? path2 : path1;
	path1 = path1 >= KING_INF ? KING_INF : path1;
	return path1;
}


int Kings_Make_Number_Of_Move(King_Data data, int H, int W)
{
	King_Data d, newData;
	d = data;
	King_Cod king;
	typedef King_Queue queue;
	typedef King_Cod Cod;
	typedef King_Data Data;
	queue que;
	que.push(data);
	int nextX, nextY, nextCount;
	int dx[4] = { 0,1,0,-1 };
	int dy[4] = { -1,0,1,0 };
	int emptyX[2][4] = { { 0,-1,0,2 },{ 1,-1,1,2 } };
	int emptyY[2][4] = { { 2,0,-1,0 },{ 2,1,-1,1 } };
	int desX[2][4] = { { 0,1,0,0 },{ 1,1,1,0 } };
	int desY[2][4] = { { 0,0,1,0 },{ 0,1,1,1 } };
	int kingX[3] = { 0,1,1 };
	int kingY[3] = { 1,0,1 };
	Data des1, des2, empty1, empty2;
	int result = KING_INF;
	for (int i = 0; i < 4; i++) King_memoi[i][data.king.y][data.king.x] = 0;
	while (!que.empty())
	{
		d = que.pop();
		if (King_memoi[d.direct][d.king.y][d.king.x] < d.count) continue;
		king = d.king;
		if (king.x == 1 && king.y == 1) continue;

		empty1 = { d.empty1.x, d.empty1.y };
		empty2 = { d.empty2.x, d.empty2.y };
		for (int dir = 0; dir < 4; dir++)
		{
			if (!Kings_Can_Move(king.x, king.y, dir)) continue;
			nextX = king.x + dx[dir];
			nextY = king.y + dy[dir];
			
			des1 = { nextX + desX[0][dir],nextY + desY[0][dir] };
			des2 = { nextX + desX[1][dir],nextY + desY[1][dir] };
			Kings_map[king.y][king.x] = 'X';
			Kings_map[king.y+kingY[0]][king.x + kingX[0]] = 'X';
			Kings_map[king.y + kingY[1]][king.x + kingX[1]] = 'X';
			Kings_map[king.y + kingY[2]][king.x + kingX[2]] = 'X';
			Kings_map[empty1.y][empty1.x] = '.';
			Kings_map[empty2.y][empty2.x] = '.';

			
			nextCount = Kings_Get_Number_Of_Empty_Move(des1, des2, empty1, empty2, H, W);

			
			Kings_map[king.y][king.x] = 'o';
			Kings_map[king.y + kingY[0]][king.x + kingX[0]] = 'o';
			Kings_map[king.y + kingY[1]][king.x + kingX[1]] = 'o';
			Kings_map[king.y + kingY[2]][king.x + kingX[2]] = 'o';
			Kings_map[empty1.y][empty1.x] = 'o';
			Kings_map[empty2.y][empty2.x] = 'o';
			if (nextCount == KING_INF) continue;
			nextCount++;
			nextCount += d.count;

			if (King_memoi[dir][nextY][nextX] <= nextCount) continue;
			newData.count = nextCount;
			newData.king = { nextX,nextY };
			newData.empty1 = { nextX + emptyX[1][dir], nextY + emptyY[1][dir] };
			newData.empty2 = { nextX + emptyX[0][dir], nextY + emptyY[0][dir] };
			newData.direct = dir;

			King_memoi[dir][nextY][nextX] = nextCount;
			que.push(newData);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		result = result > King_memoi[i][1][1] ? King_memoi[i][1][1] : result;
	}
	return result;
}




int Kings_Get_Min_Number_Of_Move(int H, int W, King_Data king, King_Data empty1, King_Data empty2,int direct)
{
	if (king.x == 1 && king.y == 1) return 0;
	//if (King_memoi[direct][king.y][king.x] == -1) return KING_INF;
	if (King_memoi[direct][king.y][king.x] > 0) return King_memoi[direct][king.y][king.x];

	//King_visit[king.y][king.x] = true;
	King_Data des1, des2;
	King_Data e1, e2;
	int dx[4] = { 0,1,0,-1 };
	int dy[4] = { -1,0,1,0 };
	int emptyX[2][4] = { {0,-1,0,2},{1,-1,1,2} };
	int emptyY[2][4] = { {2,0,-1,0},{2,1,-1,1} };
	int desX[2][4] = { {0,1,0,0},{1,1,1,0} };
	int desY[2][4] = { {0,0,1,0},{0,1,1,1} };
	int nextX, nextY, nextCount;
	int nextSum = 0;
	int resultSumTemp;
	int resultSum = KING_INF;
	for (int d = 0; d < 4; d++)
	{
		nextX = king.x + dx[d];
		nextY = king.y + dy[d];
		nextCount = king.count - 1;
		if (!Kings_Can_Move(king.x, king.y, d)) continue;

		if (Kings_count[nextY][nextX] > king.count)
		{
			continue;
		}
		//if (King_visit[nextY][nextX]) continue;//if (Kings_count[nextY][nextX] != nextCount) continue;
		//if (King_memoi[d][nextY][nextX] <= sum) continue;
		//King_memoi[d][nextY][nextX] = sum;
		des1 = { nextX + desX[0][d],nextY + desY[0][d],0 };
		des2 = { nextX + desX[1][d],nextY + desY[1][d],0 };
		e1 = { nextX + emptyX[0][d], nextY + emptyY[0][d],0 };
		e2 = { nextX + emptyX[1][d], nextY + emptyY[1][d],0 };
		nextSum = Kings_Get_Number_Of_Empty_Move(des1, des2, empty1, empty2, H, W);
		if (nextSum == KING_INF)
		{
			//King_memoi[d][nextY][nextX] = -1;
			continue;
		}
		Kings_map[empty1.y][empty1.x] = 'o';
		Kings_map[empty2.y][empty2.x] = 'o';

		Kings_map[des1.y][des1.x] = 'X';
		Kings_map[des2.y][des2.x] = 'X';
		Kings_map[e1.y][e1.x] = '.';
		Kings_map[e2.y][e2.x] = '.';
		nextSum++;
		resultSumTemp = Kings_Get_Min_Number_Of_Move(H, W, {nextX,nextY,nextCount}, e1, e2,d);
		Kings_visit[king.y][king.x] = false;
		Kings_map[des1.y][des1.x] = 'o';
		Kings_map[des2.y][des2.x] = 'o';
		Kings_map[e1.y][e1.x] = 'X';
		Kings_map[e2.y][e2.x] = 'X';
		Kings_map[empty1.y][empty1.x] = '.';
		Kings_map[empty2.y][empty2.x] = '.';

		if (resultSumTemp == KING_INF)
		{
			//King_memoi[0][nextY][nextX] = King_memoi[1][nextY][nextX] = King_memoi[2][nextY][nextX] = King_memoi[3][nextY][nextX] = -1;
			//King_memoi[d][nextY][nextX] = -1;
			continue;
		}
		//King_memoi[d][nextY][nextX] = resultSumTemp;
		resultSumTemp += nextSum;
		resultSum = resultSum > resultSumTemp ? resultSumTemp : resultSum;

	}

	King_memoi[direct][king.y][king.x] = resultSum;
	//King_visit[king.y][king.x] = false;
	return resultSum;

}

int Kings_Position()
{
	int T,H,W;
	King_Data king, empty1, empty2;
	char store; int result;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		result = -1;
		cin >> H >> W;
		king = Kings_Init(H, W, empty1, empty2);
		//king.count = Kings_Number_Of_Move(king, H, W, empty1, empty2);

		//for (int i = 1; i <= H; i++)
		//{
		//	for (int j = 1; j <= W; j++)
		//	{
		//	cout.width(8);
		//	cout << Kings_count[i][j];
		//	}
		//	cout << endl;
		//}
		//result = Kings_Get_Min_Number_Of_Move(H, W, king, empty1, empty2, 0);
		King_Data d;
		d.empty1 = { empty1.x,empty1.y };
		d.empty2 = { empty2.x, empty2.y };
		d.king = { king.x, king.y };
		d.count = 0;
		d.direct = 0;
		result = Kings_Make_Number_Of_Move(d, H, W);
		result = result == KING_INF ? -1 : result;
		cout << '#' << tc << ' ' << result << endl;
	}


	return 0;
}