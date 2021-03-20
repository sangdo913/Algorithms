// DO NOT USE ANY HEAP OR STATIC MEMORY
void init_block(char atbl[100000000], char memory[400000000])
{
	char *mem_addr = (char*)&memory;
	atbl[0] = mem_addr[0];
	atbl[1] = mem_addr[1];
	atbl[2] = mem_addr[2];
	atbl[3] = mem_addr[3];
}

char* alloc_block(char atbl[100000000], int size)
{
	int addr = 0;
	for (int i = 3; i >= 0; i--)
	{
		addr = addr << 8;
		addr = addr | ( 0xff & atbl[i]);
			
	}

	char *mem_addr = (char*)addr;
	
	char* mem_size_start[4];
	mem_size_start[0] = mem_addr;
	mem_size_start[1] = mem_size_start[0] + 4 * 1176480;
	mem_size_start[2] = mem_size_start[1] + 16 * 1176480;
	mem_size_start[3] = mem_size_start[2] + 64 * 1176470;

	int atbl_size_start[4];
	atbl_size_start[0] = 4 + 4 * 4; // mem_addr, each count;
	atbl_size_start[1] = atbl_size_start[0] + 1176480;
	atbl_size_start[2] = atbl_size_start[1] + 1176480;
	atbl_size_start[3] = atbl_size_start[2] + 1176470;
	
	int size_idx;
	int size_count;
	switch(size) {
		case 4:
			size_idx = 0;
			size_count = atbl[4] * 24 + atbl[5] * 16 + atbl[6] * 8 + atbl[7];
			break;
		case 16:
			size_idx = 1;
			size_count = atbl[8] * 24 + atbl[9] * 16 + atbl[10] * 8 + atbl[11];
			break;
		case 64:
			size_idx = 2;
			size_count = atbl[12] * 24 + atbl[13] * 16 + atbl[14] * 8 + atbl[15];
			break;
		case 256:
			size_idx = 3;
			size_count = atbl[16] * 24 + atbl[17] * 16 + atbl[18] * 8 + atbl[19];
			break;

	}

	int atbl_start = atbl_size_start[size_idx];
	char* mem_start = mem_size_start[size_idx];

	// not count full
	if (size_count < 1176470) {
		atbl[atbl_start + size_count] = 1;
		size_count++;

		switch (size) {
		case 4:
			atbl[4] = size_count >> 24;
			atbl[5] = size_count >> 16;
			atbl[6] = size_count >> 8;
			atbl[7] = size_count;
			break;
		case 16:
			atbl[8] = size_count >> 24;
			atbl[9] = size_count >> 16;
			atbl[10] = size_count >> 8;
			atbl[11] = size_count;
			break;
		case 64:
			atbl[12] = size_count >> 24;
			atbl[13] = size_count >> 16;
			atbl[14] = size_count >> 8;
			atbl[15] = size_count;
			break;
		case 256:
			atbl[16] = size_count >> 24;
			atbl[17] = size_count >> 16;
			atbl[18] = size_count >> 8;
			atbl[19] = size_count;
			break;

		}
		mem_start += size_count;


		return mem_start;

	}


	// find empty teeth
	int index_in_size = 0;
	char is_exist = atbl[atbl_start + index_in_size];
	
	while (is_exist==1 && index_in_size < 1176470) {
		index_in_size++;
		is_exist = atbl[atbl_start + index_in_size];
	}


	// all full
	if (index_in_size >= 1176470) 
		return (char*)0;
	


	// alloc
	atbl[atbl_start + index_in_size] = 1;


	mem_start += index_in_size;


	return mem_start;
}

void free_block(char atbl[100000000], char* ptr)
{
	int atbl_size_start[4];
	atbl_size_start[0] = 4 + 4 * 4;
	atbl_size_start[1] = atbl_size_start[0] + 1176480;
	atbl_size_start[2] = atbl_size_start[1] + 1176480;
	atbl_size_start[3] = atbl_size_start[2] + 1176470;

	int addr = 0;
	for (int i = 3; i >= 0; i--)
	{
		addr = addr << 8;
		addr = addr | (0xff & atbl[i]);
	}

	char *mem_addr = (char*)addr;

	int addr_distance = (int)(ptr - mem_addr);
	int size_distance;
	int size_index;
	int atbl_start;

	
	int pre_size = 0;
	// size = 4
	size_distance = 4 * 1176480;
	if (addr_distance < size_distance) {
		atbl_start = atbl_size_start[0];
		size_index = (addr_distance - pre_size) / 4;
		atbl[atbl_start + size_index] = 0;
		return;
	}

	pre_size = size_distance;
	// size = 16
	size_distance += 16 * 1176480;
	if (addr_distance < size_distance) {
		atbl_start = atbl_size_start[1];
		size_index = (addr_distance - pre_size) / 16;
		atbl[atbl_start + size_index] = 0;
		return;
	}


	pre_size = size_distance;
	// size = 64
	size_distance += 64 * 1176470;
	if (addr_distance < size_distance) {
		atbl_start = atbl_size_start[2];
		size_index = (addr_distance - pre_size) / 64;
		atbl[atbl_start + size_index] = 0;
		return;
	}


	pre_size = size_distance;
	// size = 256
	atbl_start = atbl_size_start[3];
	size_index = (addr_distance - pre_size) / 256;
	atbl[atbl_start + size_index] = 0;
	return;
	
}
