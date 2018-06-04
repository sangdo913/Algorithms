#include <iostream>
#include <stdlib.h>
#include"user.h"
#define MAX 30000

using namespace std;

extern int makeBlock(int module[][4][4]);

int main(void)
{
    static int module[MAX][4][4];

    srand(3); // 3 will be changed

    for (int tc = 1; tc <= 10; tc++)
    {
        for (int c = 0; c < MAX; c++)
        {
            int base = 1 + (rand() % 6);
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					module[c][y][x] = base + (rand() % 3);
				}
			}
        }
		cout << "#" << tc << " " << makeBlock(module) << endl;
    }

	return 0;
}