#include<stdio.h>
#include<time.h>
#include<memory.h>
#include"user.cpp"
extern void read_file(char file_name[36], char data[4096], int pos, int size);
extern void write_file(char file_name[36], char data[4096], int pos, int size);
const int disk_size = 65536 * 512;
char disk[disk_size];
char file_name[100][36];
int  file_size[100];
char file[100][65536];
int gidx;
unsigned long long seed = 3;
static unsigned int pseudo_rand(void)
{
	seed = seed * 25214903917ULL + 11ULL;
	return (unsigned int)(seed >> 16);
}
void read_disk(int sector, char data[512]) {
	if (sector < 0 || 65536 <= sector)
		return;
	memcpy(data, disk + (sector * 512), 512);
}
void write_disk(int sector, char data[512]) {
	if (sector < 0 || 65536 <= sector)
		return;
	memcpy(disk + (sector * 512), data, 512);
}
void _read_file(int index, char data[4096], int pos, int size) {
	if (size > file_size[index]) size = file_size[index];
	if (pos + size > file_size[index]) pos = file_size[index] - size;
	memcpy(data, file[index] + pos, size);
}
void _write_file(int index, char data[4096], int pos, int size) {
	if (pos > file_size[index]) pos = file_size[index];
	if (pos + size > 65536) size = 65536 - pos;
	if (pos + size > file_size[index]) file_size[index] = pos + size;
	memcpy(file[index] + pos, data, size);
}
int main() {
	char data[4096], _data[4096];
	int error, time, score = 0, size;
	for (int i = 0; i < 100; i++) {
		size = (pseudo_rand() % 25) + 10;
		for (int len = 0; len < size; len++)
			file_name[i][len] = (pseudo_rand() % 26) + 'A';
		file_name[i][size] = 0;
	}
	int pos, index, go;
	time = clock();
	for (int i = 0; i < 25000; i++) {
		// printf("%d\n", maxsector);
		if(i%5000 == 0)printf("%d\n",i);
		go = (i < 5000 ? 10 : (pseudo_rand() % 10) + 1);
		gidx= index = pseudo_rand() % 100;
		pos = pseudo_rand() % 65536;
		size = pseudo_rand() % 4096;
		if (go < 10) {
			_read_file(index, _data, pos, size);
			read_file(file_name[index], data, pos, size);
			if (memcmp(data, _data, size)) {
				score += 100000;
                printf("wrong\n");
				for(int i = 0; i < size; ++i){
					if(data[i] != _data[i]){
						int debug=1;
					}
				}
			}
		}
		else {
			for (int i = 0; i < size; i++)
				data[i] = pseudo_rand() % 256;
			// printf("%s\n %d ", file_name[index], index);
			_write_file(index, data, pos, size);
			write_file(file_name[index], data, pos, size);
		}
		for (int j = 0; j < 20; j++) {
			error = pseudo_rand() % (disk_size);
			// printf("error : %d\n", error);
			disk[error] = pseudo_rand() % 256;
		}
	}
	printf("score : %ld\n", score + clock() - time);
}

