#define ROOM_SIZE 777777
#define NOTE_SIZE 100000
#define ROOM_TYPES 3
#define ST 0
#define STPTR (ST+8*3000*3)
#define MEMPTR (STPTR + 3*4)
#define DES (MEMPTR + 8)
#define NOW (DES + 3*8)
#define DES2 77778
#define DES3 77777
#define DES5 77778

void init_note(char note[NOTE_SIZE], char rooms[ROOM_SIZE]) {
    char **rptr = (char**)(note + MEMPTR);
    *rptr = rooms;
    
    char **des = (char**)(note + DES), **now = (char**)(note + NOW);
    now[0] = rooms;
    now[1] = des[0] = rooms + DES2*2;
    now[2] = des[1] = des[0]+ DES3*3;
    des[2] = des[1] + DES5*5;

}

char *sell_room(char note[NOTE_SIZE], int size) {
    int idx = size-2;
    if(idx == 3) idx = 2;

    int* sp = (int*)(note + STPTR) + idx;
    char* ret = 0;

    if(*sp){
        char** st = ((char*(*)[3000])(note + ST))[idx];
        ret = st[--*sp]; 
    }

    else{
        char ** now = (char**)(note + NOW) + idx, **des = (char**)(note + DES) + idx;
        if(*now >= *des) return 0;
        
        ret = *now; 
        *now += size;
    }
	return ret;
}


void return_room(char note[NOTE_SIZE], char* position) {
    char* memptr = *(char**)(note + MEMPTR);
    int idx= 2;

    if(position < memptr + DES2*2){ idx = 0; }
    else if(position < memptr + (DES2*2 + DES3*3)) idx = 1;

    char**st = ((char*(*)[3000])(note))[idx];
    int *sp = (int*)(note + STPTR);
    st[sp[idx]++] = position;
}