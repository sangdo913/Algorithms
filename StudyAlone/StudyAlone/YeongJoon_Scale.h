#include<cstdio>
int YeongJoon_Parent[100001];
int YeongJoon_Value[100001];

int YeongJoon_Find(int index,int &data)
{
	if (YeongJoon_Parent[index]<0)
	{
		data = 0;
		return index;
	}

	YeongJoon_Parent[index] = YeongJoon_Find(YeongJoon_Parent[index],data);
	data += YeongJoon_Value[index];
	YeongJoon_Value[index] = data;
	return YeongJoon_Parent[index];
}

void YeongJoon_Union(int index1, int index2, int value)
{
	int data1 = 0, data2 = 0;
	int parent1 = YeongJoon_Find(index1, data1);
	int parent2 = YeongJoon_Find(index2, data2);
	if ( parent1== parent2 ) return;
	if (YeongJoon_Parent[parent1] < YeongJoon_Parent[parent2])
	{
		YeongJoon_Value[parent2] = data1 + value - data2;
		YeongJoon_Parent[parent1] += YeongJoon_Parent[parent2];
		YeongJoon_Parent[parent2] = parent1;
	}
	else
	{
		YeongJoon_Value[parent1] = data2 - value - data1;
		YeongJoon_Parent[parent2] += YeongJoon_Parent[parent1];
		YeongJoon_Parent[parent1] = parent2;
	}
}


int YeongJoon_Get(int index1, int index2)
{
	int data1 = 0, data2 = 0;
	if (YeongJoon_Find(index1, data1) == YeongJoon_Find(index2, data2))
	{
		return data2 - data1;
	}
	else
	{
		return -10000000;
	}
}
int YeongJoon_Scale()
{
	int T, N, M,a,b,w;
	char command;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) 
	{
		scanf("%d %d", &N, &M);
		for (int i = 1; i <= N; i++)
		{
			YeongJoon_Value[i] = 0;
			YeongJoon_Parent[i] = -1;
		}
		printf("#%d",tc);
		for (int i = M; i--;)
		{
			scanf("\n%c %d %d",&command, &a, &b);
			switch (command)
			{
			case'!':
				scanf("%d", &w);
				YeongJoon_Union(a, b, w);
				break;
			case'?':
				int result = YeongJoon_Get(a, b);
				if (result > -10000000)
				{
					printf(" %d", result);
				}
				else
				{
					printf(" UNKNOWN");
				}
				break;
			}
		}
		printf("\n");
	}
	return 0;
}