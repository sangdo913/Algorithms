#include <iostream>
#include <stdio.h>

using namespace std;

#define DISK_SIZE  20000
#define BUF_SIZE   64
#define MAX_FILE   10

#define MAX_COUNT  (DISK_SIZE * 2 * 50)

int disk[DISK_SIZE];
static int buf[BUF_SIZE];
static int numCount[MAX_FILE];

static int moveCount;
static int diskSize;

static int totalMoveCount;
static int totalDiskSize;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

extern void defragment();

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int getdiskSize()
{
	return diskSize;
}

int readDisk(int* buf, int addr, int size)
{
	if (addr < 0 || addr + size > diskSize)
		return 0;

	for (int i = 0; i < size; i++)
		buf[i] = disk[addr++];

	return size;
}

int move(int from, int to, int size)
{
	if (moveCount < MAX_COUNT)
		moveCount++;

	if (from < 0 || from >= diskSize || to < 0 || to >= diskSize)
		return 0;

	if (size < 1 || size > BUF_SIZE || from + size > diskSize || to + size > diskSize)
		return 0;

	for (int i = 0; i < size; i++)
	{
		buf[i] = disk[from];
		disk[from] = 0;
		from++;
	}

	for (int i = 0; i < size; i++)
	{
		disk[to++] = buf[i];
	}

	return size;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

static int checkDisk()
{
	int checkCount[MAX_FILE];
	for (int i = 0; i<MAX_FILE; i++)
		checkCount[i] = 0;

	int idx = 0;
	while (idx < diskSize)
	{
		int fileID = disk[idx];
		if (checkCount[fileID] != 0)
			return 0;

		for (int i = 0; i<numCount[fileID]; i++)
		{
			if (fileID != disk[idx++])
				return 0;
			checkCount[fileID]++;
		}
	}

	if (disk[diskSize - 1] != 0)
		return 0;

	for (int i = 0; i<MAX_FILE; i++)
	{
		if (checkCount[i] != numCount[i])
			return 0;
	}

	return 1;
}

static void init()
{
	moveCount = 0;

	for (int i = 0; i<MAX_FILE; i++)
		numCount[i] = 0;

	for (int i = 0; i<diskSize; i++)
	{
		numCount[disk[i]]++;
	}
}

int main()
{
	setbuf(stdout, NULL);
	//freopen("sample_input.txt", "r", stdin);

	int T;
	scanf("%d", &T);

	totalMoveCount = 0;
	totalDiskSize = 0;

	for (int tc = 1; tc <= T; tc++)
	{
		scanf("%d", &diskSize);
		for (int i = 0; i<diskSize; i++)
			scanf("%d", &disk[i]);

		init();

		defragment();

		int cnt = MAX_COUNT;
		if (checkDisk() == 1)
			cnt = moveCount;

		printf("#%d %d\n", tc, cnt);

		totalMoveCount += cnt;
		totalDiskSize += diskSize;
	}

	printf("Total diskSize  : %d\n", totalDiskSize);
	printf("Total moveCount : %d\n", totalMoveCount);
}