#include <cstdio>
#include <ctime>

extern bool change_disk(int disk);
extern bool read_disk(int sector, char* data);
extern bool write_disk(int sector, char* data);

void init(void) {

}

void read_file(char* filename, register int offset, char* data, int size) {

}

void insert_file(char* filename, int offset, char* data, int size) {

}

void delete_file(char* filename, register int offset, int size) {

}
