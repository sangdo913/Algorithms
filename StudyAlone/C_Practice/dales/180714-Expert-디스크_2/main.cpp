#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <time.h>
#include <memory.h>

// 메모리 제한 4 MB **

static char dummy1[5][1024][1024];
static char disk[16][1024][1024];
static int disk_id;
static int disk_total;
static char file_name[100][16];
static int file_size[100];
static char dummy2[6][1024][1024];

static int SCORE = 0;
static int seed = 3;
static int MOD = 1 << 16;
static int PANELTY = 1000000;

extern void init();
extern void read_file(char* filename, int offset, char* data, int size);
extern void insert_file(char* filename, int offset, char* data, int size);
extern void delete_file(char* filename, int offset, int size);

static int pseudo_rand(void)
{
    seed = seed * 214013 + 2531011;
    return (seed >> 16) & 0x7FFF;
}

static unsigned long hash(const char *str, int str_len)
{
    unsigned long hash = 5381;

    for (int i = 0; i < str_len; i++)
        hash = (((hash << 5) + hash) + str[i]) % MOD;

    return hash % MOD;
}

bool change_disk(int disk)
{
    if (disk >= 16 || disk < 0) return false;
    disk_id = disk;
    return true;
}

bool read_disk(int sector, char* data)
{
    if (sector >= 1024 || sector < 0) return false;
    memcpy(data, &(disk[disk_id][sector][0]), 1024);
    return true;
}

bool write_disk(int sector, char* data)
{
    if (sector >= 1024 || sector < 0) return false;
    memcpy(&(disk[disk_id][sector][0]), data, 1024);
    return true;
}

static void _build(void)
{
    init();

    for (int c = 0; c < 100; c++)
    {
        for (int l = 0; l < 16; l++)
            file_name[c][l] = 'A' + (pseudo_rand() % 26);

        file_size[c] = 0;
    }
}


static void _insert(void)
{
    char data[4096];
    char file_name_arg[17];

    int file = pseudo_rand() % 100;
    int offset = (pseudo_rand() * pseudo_rand()) % (file_size[file] + 1);

    int data_size = pseudo_rand() % 4096 + 1;

    for (register int i = 0; i < data_size; i++)
        data[i] = pseudo_rand() % 255 + 1;

    for (register int i = 0; i < 16; i++)
        file_name_arg[i] = file_name[file][i];

    insert_file(file_name_arg, offset, data, data_size);
    file_size[file] += data_size;
    disk_total += data_size;
}


static void _delete(void)
{
    char file_name_arg[17];
    int file = pseudo_rand() % 100;
    int offset = (pseudo_rand() * pseudo_rand()) % (file_size[file] + 1);
    int data_size = pseudo_rand() % 4096 + 1;

    if (file_size[file] - offset < data_size)
        data_size = file_size[file] - offset;

    if (data_size == 0)
        return;

    for (register int i = 0; i < 16; i++)
        file_name_arg[i] = file_name[file][i];

    delete_file(file_name_arg, offset, data_size);

    file_size[file] -= data_size;
    disk_total -= data_size;
}


static void _verify(int file)
{
    char file_name_arg[17];
    char data[4096];
    int correct_ans = 0;
    int offset = (pseudo_rand() * pseudo_rand()) % (file_size[file]);
    int data_size = pseudo_rand() % 4096 + 1;

    if (file_size[file] - offset < data_size)
        data_size = file_size[file] - offset;


    for (register int i = 0; i < 16; i++)
        file_name_arg[i] = file_name[file][i];

    read_file(file_name_arg, offset, data, data_size);
    int user_ans = hash(data, data_size);
    scanf("%d", &correct_ans);
    if (correct_ans != user_ans)
        SCORE += PANELTY;
}

int main(void)
{
    freopen("sample_input.txt", "r", stdin);
    setbuf(stdout, NULL);
    printf("---------------\n");
    clock_t START = clock();
    for (int T = 0; T < 10; T++)
    {
        _build();
        disk_total = 0;
        while (disk_total < 10*1024*1024)
        {
            switch (pseudo_rand() % 10)
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5: _insert(); break;
                case 6:
                case 7:
                case 8:
                case 9: _delete(); break;
            }
        }

        for (int i = 0; i < 100; i++){
            if (file_size[i] == 0)continue;
            _verify(i);
        }
        printf("tc : %d // score : %d\n", T, SCORE);
    }
    printf("%lf\n", (double)(clock() - START) / (CLOCKS_PER_SEC));
    SCORE += (clock() - START) / (CLOCKS_PER_SEC / 1000);
    printf("SCORE: %d\n", SCORE);
    return 0;
}