#pragma once
#include<iostream>

using namespace std;
inline int KidCar_StrLength(char* str)
{
	int result = 0;
	while (str[result] != '\0')
	{
		result++;
	}
	return result;
}
struct KidCar_State
{
	int x;
	int y;
	int count;
	int command_start;
	KidCar_State()
	{
		command_start = count = x = y = -1;
	}
	void set(int x, int y, int count, int command_start)
	{
		this->x = x; this->y = y; this->count = count; this->command_start = command_start;
	}
};

struct KidCar_Node
{
	typedef KidCar_State Data;
	typedef KidCar_Node Node;
	Node* next;
	Node* prev;
	Data data;
	KidCar_Node()
	{
		next = prev = NULL;
	}
};

struct KidCar_Queue
{
	typedef KidCar_Queue queue;
	typedef KidCar_Node Node;
	typedef KidCar_Node::Data Data;
	Node* front;
	Node* rear;
	bool empty()
	{
		return front->next == rear;
	}
	KidCar_Queue()
	{
		front = new Node();
		rear = new Node();
		rear->prev = front;
		front->next = rear;
	}
	~KidCar_Queue()
	{
		Node* rnode;
		while (front)
		{
			rnode = front;
			front = front->next;
			delete(rnode);
		}
	}
	void push(Data data)
	{
		Node* new_node = new Node();

		new_node->data = data;
		new_node->prev = front;
		new_node->next = front->next;

		front->next->prev = new_node;
		front->next = new_node;
	}

	bool pop(Data &data)
	{
		if (rear->prev == front) return false;
		Node* rnode = rear->prev;
		data = rnode->data;
		rear->prev = rnode->prev;
		rear->prev->next = rear;
		delete(rnode);
		return true;
	}
};

char KidCar_Map[52][52];
int KidCar_Count[52][52][52];
int KidCar_is_Visit[52][52][52];

void KidCar_Go(int &x, int &y, char *str)
{
	if (KidCar_Map[y][x] == 'G')
	{
		x = 0; y = 0;
		return;
	}
	while (*str != '\0')
	{
		enum dir{U=0, R,D,L};
		dir where;
		int dx[4] = { 0,1,0,-1 };
		int dy[4] = { -1,0,1,0 };
		switch (*str)
		{
		case'U':
			where = dir::U;
			break;
		case'D':
			where = dir::D;
			break;
		case'R':
			where = dir::R;
			break;
		case'L':
			where = dir::L;
			break;
		}

		if (KidCar_Map[y + dy[where]][x + dx[where]] != '#')
		{
			y += dy[where]; x += dx[where];
		}
		if(KidCar_Map[y][x] == 'G')
		{
			x = 0; y = 0;
			return;
		}
		str++;
	}
}
int KidCar_Set_Count(int H, int W, int dt_x, int dt_y, int st_x, int st_y,char* str)
{
	int size = KidCar_StrLength(str);
	typedef KidCar_Queue queue;
	typedef queue::Data Data;
	queue que;

	int dx[4] = { 0,1,0,-1 };
	int dy[4] = { -1,0,1,0 };
	for (int command = 0; command <=size; command++)
		for (int r = 1; r <= H; r++)
		{
			for (int c = 1; c <= W; c++)
			{
					KidCar_Count[command][r][c] = 2500;
			}
		}
	//KidCar_Count[0][dt_y][dt_x] = 0;
	Data d;
	Data new_data;
	d.set(dt_x, dt_y, 0, 0);
	que.push(d);
	while (!que.empty())
	{
		que.pop(d);
		if (KidCar_Count[0][d.y][d.x] > d.count)
		{
			KidCar_Count[0][d.y][d.x] = d.count;
			d.count++;
			for (int dir = 0; dir < 4; dir++)
			{
				if (KidCar_Map[d.y + dy[dir]][d.x + dx[dir]] != '#')
				{
					new_data.set(d.x + dx[dir], d.y + dy[dir], d.count, 0);
					que.push(new_data);
				}
			}
		}
	}
	int x, y;
	int min = 10000;
	for (int command = 1; command <=size; command++)
	{
		for (int r = 1; r <= H; r++)
		{
			for (int c = 1; c <= W; c++)
			{
				if (KidCar_Map[r][c] == '#')
				{
					KidCar_Count[command][r][c] = 2500;
					continue;
				}
				x = c; y = r;
				KidCar_Go(x, y, str + command);
				if (x == 0)
				{
					KidCar_Count[command][r][c] = 0;
				}
				else
				{
					KidCar_Count[command][r][c] = KidCar_Count[0][y][x];
				}
			}
		}
	}

	return KidCar_Count[0][st_y][st_x];
}

int KidCar_Get_Min(int H, int W, int st_x, int st_y, int dt_x, int dt_y, int min, char* str)
{

	if (min == 0) return 0;
	typedef KidCar_Queue queue;
	typedef queue::Data Data;
	Data d;
	queue que;
	int size = KidCar_StrLength(str);
	d.set(st_x, st_y, 0, 0);
	que.push(d);
	int changes;
	int dx[5] = { 0,1,0,-1,0 };
	int dy[5] = { -1,0,1,0,0 };
	for (int i = 0; i <= size; i++)
		for (int j = 0; j <= H+1; j++)
			for (int k = 0; k <=W+1; k++) KidCar_is_Visit[i][j][k] = 10000;
	KidCar_is_Visit[0][st_y][st_x] = 0;
	Data newData;
	enum dir {U=0,R,D,L,NO};
	while (!que.empty())
	{
		que.pop(d);
		changes = d.count + KidCar_Count[d.command_start][d.y][d.x];
		min = min > changes ? changes : min;

		newData.set(d.x, d.y, d.count, d.command_start);
		for (int i = d.command_start; i < size; i++)
		{
			dir where;
			switch (str[i])
			{
			case 'U':
				where = dir::U;
				break;
			case 'R':
				where = dir::R;
				break;
			case'D':
				where = dir::D;
				break;
			case 'L':
				where = dir::L;
				break;
			default:
				where = dir::NO;
			break;
			}
			newData.command_start++;
			if (KidCar_Map[newData.y + dy[where]][newData.x + dx[where]] == '#')
			{
				where = dir::NO;
			}
			newData.x += dx[where]; newData.y += dy[where]; 	
			if (KidCar_is_Visit[newData.command_start][newData.y][newData.x]<= newData.count) continue;
			que.push(newData);
			KidCar_is_Visit[newData.command_start][newData.y][newData.x] = newData.count;
		}
		if (d.count >= min) continue;
		d.count++;
		for (int dir = 0; dir < 4; dir++)
		{
			if (KidCar_Map[d.y + dy[dir]][d.x + dx[dir]] == '#') continue;
			if (KidCar_is_Visit[d.command_start][d.y + dy[dir]][d.x + dx[dir]]  <= d.count ) continue;
			newData.set(d.x + dx[dir], d.y + dy[dir], d.count, d.command_start);
			que.push(newData);
			KidCar_is_Visit[d.command_start][d.y + dy[dir]][d.x + dx[dir]] = d.count;
		}
		if (d.command_start + 1 <= size && KidCar_is_Visit[d.command_start + 1][d.y][d.x] > d.count)
		{
			newData.set(d.x, d.y, d.count, d.command_start + 1);
			que.push(newData);
			KidCar_is_Visit[d.command_start + 1][d.y][d.x] = d.count;
		}
	}

	return min;
}

int Kid_Car_Robot()
{
	typedef KidCar_Queue queue;
	typedef queue::Data Data;
	char str[51],temp;
	enum dir{ U = 0, R = 1, D = 2, L = 3	};
	int T,H,W;
	int st[2],dt[2];
	cin >> T;// scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> H >> W;//scanf("%d %d", &H, &W);
		for (int cols = 0; cols <= W+1; cols++)
		{
			KidCar_Map[0][cols] = '#'; KidCar_Map[H+1][cols] = '#';
		}
		for (int row = 1; row <= H; row++) KidCar_Map[row][0] = KidCar_Map[row][W + 1] = '#';
		for (int r = 1; r <= H; r++)
		{
			for (int c = 1; c <= W; c++) 
			{
				cin >> KidCar_Map[r][c];//scanf("%c", &KidCar_Map[r][c]);
				if (KidCar_Map[r][c] == 'S')
				{
					st[0] = r; st[1] = c;
				}
				else if (KidCar_Map[r][c] == 'G')
				{
					dt[0] = r; dt[1] = c;
				}
			}
		}
		scanf("%s", str);
		int min = KidCar_Set_Count(H, W, dt[1], dt[0], st[1], st[0], str);
		
		min = KidCar_Get_Min(H, W, st[1], st[0],dt[1],dt[0], min, str);
		printf("#%d %d\n", tc, min);
	}
	return 0;
}