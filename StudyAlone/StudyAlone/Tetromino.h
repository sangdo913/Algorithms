#pragma once
#include<iostream>
#include<cmath>
#include<cstring>

using namespace std;

int TET_MAP[504][504];

//테트리스 블럭들
int TET[19][4][4] =
{ 
	
{
	1,1,1,1,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0
},
{
	1,0,0,0,
	1,0,0,0,
	1,0,0,0,
	1,0,0,0
},
{
	1,1,0,0,
	1,1,0,0,
	0,0,0,0,
	0,0,0,0
},
{
	1,0,0,0,
	1,0,0,0,
	1,1,0,0,
	0,0,0,0
},
{
	0,1,0,0,
	0,1,0,0,
	1,1,0,0,
	0,0,0,0
},
{
	1,1,1,0,
	1,0,0,0,
	0,0,0,0,
	0,0,0,0
},
{
	1,1,1,0,
	0,0,1,0,
	0,0,0,0,
	0,0,0,0
},
{
	1,1,0,0,
	0,1,0,0,
	0,1,0,0,
	0,0,0,0
},
{
	1,1,0,0,
	1,0,0,0,
	1,0,0,0,
	0,0,0,0
},
{
	1,0,0,0,
	1,1,1,0,
	0,0,0,0,
	0,0,0,0
},
{
	0,0,1,0,
	1,1,1,0,
	0,0,0,0,
	0,0,0,0
},
{
	1,0,0,0,
	1,1,0,0,
	0,1,0,0,
	0,0,0,0
},
{
	0,1,0,0,
	1,1,0,0,
	1,0,0,0,
	0,0,0,0
},
{
	0,1,1,0,
	1,1,0,0,
	0,0,0,0,
	0,0,0,0
},
{
	1,1,0,0,
	0,1,1,0,
	0,0,0,0,
	0,0,0,0
},
{
	1,1,1,0,
	0,1,0,0,
	0,0,0,0,
	0,0,0,0
},
{
	0,1,0,0,
	1,1,0,0,
	0,1,0,0,
	0,0,0,0
},
{
	0,1,0,0,
	1,1,1,0,
	0,0,0,0,
	0,0,0,0
},
{
	1,0,0,0,
	1,1,0,0,
	1,0,0,0,
	0,0,0,0
}
};

int TET_MAX(int x1,int x2)
{
	return x1 > x2 ? x1 : x2;
}

void Tetromino()
{
	memset(TET_MAP, -1, sizeof(TET_MAP));
	int N, M;
	cin >> N >> M;

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			cin >> TET_MAP[i][j];
		}
	}
	bool OutOfIndex = false;
	int max_value = 0;
	// 맵 검사
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			OutOfIndex = false;
			int temp_max = 0;

			//0번부터 18번 테트리스와 대조
			for (int i = 0; i < 19; i++)
			{
				temp_max = 0;
				OutOfIndex = false; // 전에 아웃 오브 인덱스일 수 있으니 테트리스 블럭에 가기 전에 초기화 시켜준다.

				//테트리스 블럭들과 대조 - 만약 테트리스 블록인데 벽에 닿아있으면 다음 테트리스로 넘어간다.
				for (int j = 0; j < 4 && !OutOfIndex; j++)
				{
					for (int k = 0; k < 4; k++)
					{
						if (TET[i][j][k] == 0) continue; // don't care
						if (TET_MAP[r+j][c+k] == -1) // Out Of Index
						{
							OutOfIndex = true;
							break;
						}
						temp_max += TET_MAP[r+j][c+k];
					}
				}

				if (!OutOfIndex) max_value = TET_MAX(max_value, temp_max); // 테트리스가 벽 밖으로 안나갔다면 맥스 값 갱신
			}
		}
	}

	cout << max_value << endl;
}