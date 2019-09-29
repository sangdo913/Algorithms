#include <stdio.h>
#include <memory.h>
#include <time.h>
#include"user.cpp"

#define ROOM_SIZE 777777
#define NOTE_SIZE 100000
#define ROOM_TYPES 3

static char rooms[ROOM_SIZE];
static char note[NOTE_SIZE];

static unsigned long long seed = 0722;
static const int MOD = 9;

static int   room_size[ROOM_TYPES] = { 2, 3, 5 };
static char* room_position[ROOM_TYPES][ROOM_SIZE];
static int   room_count[ROOM_TYPES];

extern void init_note(char note[NOTE_SIZE], char rooms[ROOM_SIZE]);
extern char* sell_room(char note[NOTE_SIZE], int size);
extern void return_room(char note[NOTE_SIZE], char* position);

static unsigned int pseudo_rand(void)
{
	seed = seed * 25214903917ULL + 11ULL;
	return (unsigned int)(seed >> 16);
}

static bool valid()
{
	static char cmp_room[MOD][5];

	for (register int type = 0; type < ROOM_TYPES; type++)
		for (register int c = 0; c < room_count[type]; c++)
			if (room_position[type][c] != NULL)
				memset(room_position[type][c], c % MOD, room_size[type]);

	for (register int c = 0; c < MOD; c++) memset(cmp_room[c], c, 5);

	int cnt = 0;
	for (register int type = 0; type < ROOM_TYPES; type++)
		for (register int c = 0; c < room_count[type]; c++){
			register char* position = room_position[type][c];
			if (position == NULL) continue;
			cnt++;
			if ((position < rooms) || (position + room_size[type] > rooms + ROOM_SIZE)) return false;
			if (memcmp(position, cmp_room[c % MOD], room_size[type]) != 0) return false;
		}
	if (cnt == 0) return false;
	return true;
}


int main()
{
	int sold_rooms = 0;
	int profit = 0;
    freopen("0Text.txt", "r", stdin);
	scanf("%d", &seed);

	for (int c = 0; c < ROOM_TYPES; c++){
		room_position[c][0] = NULL;
		room_count[c] = 1;
	}

	init_note(note, rooms);
    int cnt = 100000;

	while (sold_rooms != ROOM_SIZE)
	{
        if(sold_rooms >= cnt){
            cnt+=100000;
            if(cnt >= ROOM_SIZE) cnt = ROOM_SIZE - 10;
            int debug = 1;
        }
		register int type = pseudo_rand() % ROOM_TYPES;
		register int index;

		register char* position = sell_room(note, room_size[type]);
		room_position[type][room_count[type]++] = position;

		if (position != NULL)
		{
			sold_rooms += room_size[type];
			profit += room_size[type];
			memset(position, 9, room_size[type]);
		}
		else profit -= room_size[type];

		type = pseudo_rand() % ROOM_TYPES;
		if (room_count[type] <= 0)
			break;
		index = pseudo_rand() % room_count[type];

		if (room_position[type][index] != NULL)
		{
			return_room(note, room_position[type][index]);
			room_position[type][index] = NULL;
			sold_rooms -= room_size[type];
		}
	}

	int SCORE = profit;
	if (valid() == false) SCORE = 0;
	//printf("SCORE: %d\n", SCORE);
	if (SCORE >= 1555888)
		printf("PASS\n");
	else
		printf("FAIL\n");

	return 0;
}
