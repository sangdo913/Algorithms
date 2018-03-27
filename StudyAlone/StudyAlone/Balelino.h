#pragma once
#include<iostream>
#include<queue>
#include<algorithm>
#include<string.h>
#include<vector>
#include<stdint.h>
using namespace std;
struct Balelino_Group
{
	bool bang;
	int x,y;
	vector<int> adj;
	Balelino_Group()
	{
		adj.clear();
	}
};
struct Balelino_Cod
{
	int r;
	int c;
	int num;
	bool operator==(Balelino_Cod c2)
	{
		return r == c2.r && c == c2.c;
	}
};

struct Balelino_Info
{
	typedef Balelino_Cod cod;
	int n;
	int m;
	cod st, dt;
	vector<Balelino_Group> groups;
	vector<vector<bool> > adj;

	int group[34][34];
	int map[34][34];
	int stNum;
	int dtNum;

	long long res;
	int dx[8] = { 1,   2,2,1,-1,-2,-2,-1 };
	int dy[8] = { -2, -1,1,2, 2, 1,-1,-2 };
	void init()
	{
		memset(map, -1, sizeof(map));
		
		groups.clear();
		groups.resize(0);
		for(int i = 0 ; i<adj.size();i++)
		{
			adj[i].clear();
			adj[i].resize(0);
		}

		scanf("%d %d", &n, &m);
		st = { 0,0 };
		dt = { 0,0};
		for (int r = 2; r < n + 2; r++)
		{
			for (int c = 2; c < m + 2; c++)
			{
				scanf("%d", &map[r][c]);
				if (map[r][c] == 3) st = { r,c};
				else if (map[r][c] == 4) dt = { r,c };
				else if (map[r][c] == 2) map[r][c] = -1;
			}
		}
		map[st.r][st.c] = 1;
		map[dt.r][dt.c] = 1;
	}
	long long result()
	{
		return res;
	}
	void Group()
	{
		int gSize = 0;
		bool isGroup[34][34] = {false};

		for(int i = 2; i< n + 2;i++)
		{
			for(int j = 2; j < m + 2; j++)
			{
				if(map[i][j] == 0)
				{
					group[i][j] = groups.size();
					groups.push_back(Balelino_Group());
					groups[gSize].x = j;
					groups[gSize].y = i;
					groups[gSize++].bang = false;
				}
			}
		}

		for(int i = 2; i<n+2;i++)
		{
			for(int j = 2; j<m+2;j++)
			{
				if(!isGroup[i][j] && map[i][j] == 1) 
				{
					groups.push_back(Balelino_Group());
					groups[gSize].x = j;
					groups[gSize].y = i;
					groups[gSize].bang = true;
					MakeGroup(i,j,gSize++,isGroup);
				}
			}
		}
		stNum = group[st.r][st.c];
		dtNum = group[dt.r][dt.c];
	}

	void MakeAdj()
	{
		adj.resize(groups.size());
		for(int i = 0; i<adj.size();i++)
		{
			adj[i].resize(adj.size(),false);
		}

		for(int i = 0 ; i < groups.size(); i++)
		{
			if(groups[i].bang)
			{
				break;
			}

			for(int d = 0 ; d < 8 ; d++)
			{
				int nextR = groups[i].y +dy[d];
				int nextC = groups[i].x + dx[d];
				if(map[nextR][nextC] == -1 )continue;
				else if (map[nextR][nextC] == 1)
				{
					for(int j = 0; j< groups[group[nextR][nextC]].adj.size(); j++)
					{
						adj[groups[group[nextR][nextC]].adj[j]][i] = true;
						adj[i][groups[group[nextR][nextC]].adj[j]] = true;
					}
				}
				else
				{
					adj[group[nextR][nextC]][i] = true;
					adj[i][group[nextR][nextC]] = true;
				}
			}
		}

		for(int i = 0 ; i<groups[stNum].adj.size();i++)
		{
			adj[stNum][groups[stNum].adj[i]] = true;
		}
		
		for(int i = 0 ; i<groups[dtNum].adj.size();i++)
		{
			adj[groups[dtNum].adj[i]][dtNum] = true;
		}
	}
	
	void MakeGroup(int r,int c,int groupNum, bool isGroup[34][34])
	{
		isGroup[r][c] = true;
		group[r][c] = groupNum;
		for(int d = 0; d<8;d++)
		{
			int nextR = r+dy[d];
			int nextC = c+dx[d];
			if(map[nextR][nextC] == 0) groups[groupNum].adj.push_back(group[nextR][nextC]);
			else if((map[r+dy[d]][c + dx[d]] == -1) || (isGroup[nextR][nextC])) continue;
			else if(map[nextR][nextC] == 1) MakeGroup(nextR,nextC,groupNum, isGroup);

		}
	}

	int Dance()
	{
		vector<long long> nums;
		vector<long long> timeCheck;
		queue<int> q;
		
		q.push(stNum);
		int t = 0;
		int size = 1;
		int now,next;
		nums.resize(groups.size(), 0);
		nums[stNum] = 1;

		timeCheck.resize(groups.size(),-1);
		bool end = false;
		while(q.size())
		{
			now = q.front();
			q.pop();

			if(now == dtNum) 
			{
				end = true;
			}

			for(int i = 0 ; i<adj.size(); i++)
			{
				if(!adj[now][i]) continue;
				if(timeCheck[i] == -1)
				{
					q.push(i);
					timeCheck[i] = t+1;
					nums[i] = nums[now];
				
				}
				else if(timeCheck[i] > t)
				{
					nums[i]+= nums[now];
				}
			}
			
			size--;
			if(size == 0)
			{
				if(end) 
				{
					res = nums[dtNum];
					return t == 0 ? 0 : t-1;
				}
				size = q.size();
				t++;
			}
		}

		return -1;
	}

}Balelino_info;

int Balelino()
{
	Balelino_info.init();
	Balelino_info.Group();
	Balelino_info.MakeAdj();
	int num = Balelino_info.Dance();
	printf("%d\n", num);
	if (num != -1) printf("%lld\n", Balelino_info.result());

	return 0;
}