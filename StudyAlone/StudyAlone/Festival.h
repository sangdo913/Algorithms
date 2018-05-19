#include<cstring>
#include<cstdio>

int Festibal()
{
	int costs[1001];
	int t;
	scanf("%d\n", &t);
	while(t--)
	{
		int l, n, cost;
		scanf("%d %d\n", &n, &l);
		memset(costs, 0, sizeof(costs));

		for(int i = 1; i <= n; i++)
		{
			scanf("%d \n", &cost);
			costs[i] = costs[i - 1] + cost;
		}

		double min = 1000000;

		for(int i = l; i <= n; i++)
		{
			for(int j = 1; j + i - 1 <= n; j++)
			{
				double sum = 0;
				sum = (double)(costs[j + i - 1] - costs[j - 1]) / (double)i;
				if(sum < min) min = sum;
			}
		}

		printf("%.12lf\n", min);
	}
	return 0;
}
