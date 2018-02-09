#pragma once
#include<iostream>

using namespace std;
//�ʱ�ȭ
void Susung_Init(int tiles[31],int size)
{
	int temp;
	for (int i = 0; i < 31; i++) tiles[i] = 0;
	for (int i = 0; i < size; i++)
	{
		cin >>temp;
		tiles[temp]++;
	}
}
//�ְ� ��Ʈ�� ���Ѵ�.
int SuJung_Get_Max_Bit(long long M)
{
	if (M == 0) return -1;
	long long  std = 1<<30; int cnt = 30;
	while (!(M&std))
	{
		cnt--;
		std >>= 1;
	}
	return cnt;
}
//2^N
long long Susung_pow(int n)
{
	return 1 << n;
}
// ���� ������� �簢���� ������ ������ �� �簢�� �������� ����
int SuJung_Get_Next(long long prev, long long now)
{
	return ((prev / now) << 1) + 1;
}
//���� 2^K�� �簢���� ������ �� �ִ� Ÿ�ϵ��� ������ ���Ѵ�. cnt�� �����ִ� �� Ÿ���� ����
int Make_Tile(int tiles[31], int K, int cnt)
{
	int remains = 1, decrease,result = 0;
	while (K >= 0 && remains != 0 && cnt >= remains)
	{
		if (tiles[K])
		{
			decrease = remains > tiles[K] ? tiles[K] : remains;
			remains -= decrease;
			tiles[K] -= decrease;
			result += decrease;
		}
		remains <<= 2;
		K--;
	}
	if(remains > cnt)
	for (; K >= 0;K--)
	{
		result += tiles[K];
		tiles[K] = 0;
	}
	return cnt > result ? result : cnt;
}

//�ּ� Ÿ���� ���� ���Ѵ�.
int SuJung_Get_Min_Tiles(int *tiles, long long M, int size,int cnt)
{
	int max_bit = SuJung_Get_Max_Bit(M);
	int tile_cnt = 0,remain, iter_cnt, decrease;
	long long prevlength = 0, now_length = M;
	while (cnt>0)
	{
		tile_cnt++;
		now_length = M;
		prevlength = 0;

		//��Ʈ����ŷ�� �̿��Ѵ�.
		for (int bit = max_bit; bit >= 0; bit= SuJung_Get_Max_Bit(now_length))
		{
			decrease = 0;
			iter_cnt = SuJung_Get_Next(prevlength, 1<<bit);
			for (; iter_cnt--;)
				decrease += Make_Tile(tiles,bit, cnt);
			if (decrease)
			{
				prevlength += 1<<bit;
				cnt -= decrease;
				now_length -= 1<<bit;
				if (cnt <= 0) break;
			}
			else break;
		}
	}

	return tile_cnt;
}

void SuJung()
{
	ios::ios_base::sync_with_stdio(false);
	int T,N;
	int tiles[31];
	long long length, tile_made,M;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N >> M;
		int cnt = N;
		Susung_Init(tiles,N);
		int result = SuJung_Get_Min_Tiles(tiles,M,N,cnt);

		cout << '#' << tc << ' ' << result << endl;
	}

}