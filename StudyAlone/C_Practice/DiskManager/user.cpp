extern bool change_disk(int disk); 
extern bool read_disk(int sector, char* data);
extern bool write_disk(int sector, char* data);
/* 
	함수의 인자로 주어진 것 외에, main.cpp 의 메모리 영역에 접근하는 것은 금지 됩니다.
	user 영역에서 메모리 최대 사용은 5 MB 로 제한됩니다. 별도 스택 메모리 제한 1 MB
	즉 파일의 데이터(*data 인자로 받은 것)를 write_disk, read_disk 를 통해 관리해야합니다.

	인덱스 0 ~ 15 의 16 개의 디스크(disk)가 존재하고
	각 디스크는 0 ~ 1023 인덱스를 가지는 1024 개의 섹터(sector)를 가지고 있다.
	각 섹터에는 char 형 자료를 1024 의 길이까지 저장 가능하고,
	특정 섹터에 데이터를 저장하는 것은 write_disk 함수로,
	데이터를 불러오는 것은 read_disk 함수를 사용하면 된다.
	change_disk 함수로 disk 를 변경할 수 있다.

	위의 함수들을 이용하여 파일을 디스크에 관리하는 함수들을 구현하라 
*/
int tc;
int fid;
#define HASHSIZE 10007
#define rint register int
struct PAGE{
    int head, sector;
    int size;
    PAGE *n, *p;
}pages[16*1024];

PAGE head;
PAGE files[100];
char filename[100][16];
bool isfirst = true;
int myhash[HASHSIZE];
int myvisit[HASHSIZE];

void init(void){
    fid=0;
    tc++;
    head.n = head.p = &head;
    for(rint i = 0; i < 16*1024-1; ++i){
        pages[i].n = &pages[i+1];
        pages[i+1].p = &pages[i];
    }
    head.n = &pages[0];
    pages[0].p = &head;

    head.p = &pages[16*1024-1];
    pages[16*1024-1].n = &head;

    for(rint i = 0; i < 100; ++i) files[i].p = files[i].n = &files[i];

    if(isfirst){
        isfirst = false;
        for(rint i = 0; i < 16; ++i){
            for(rint j = 0; j < 1024; ++j){
                pages[i*1024+j].head =i;
                pages[i*1024+j].sector = j;
            }
        }
    }
}

bool strcmp(char* a, char* b){
    for(rint l = 0; l < 16; ++l) if(a[l] != b[l]) return false;
    return true;
}

PAGE *getoffset(PAGE *h, int& offset){
    register PAGE *ed = h;
    register PAGE *cur = ed->n;
    register int now = 0;
    while(cur != ed && cur->size <= offset) {
        offset -= cur->size; 
        cur = cur->n;
    }
    return cur;
}
char tempdata[1024];
char tempdata2[1024];
char mystack[1024];

void defragment(PAGE* h, PAGE* page){
    if(page == h) return;
    change_disk(page->head);
    read_disk(page->sector, tempdata);
    rint top = 0;
    for(rint i = page->size-1; i >=0; --i) mystack[top++] = tempdata[i];
    register PAGE* del;

    while(true){
        if(page->p == h) break;
        if(page->size + page->p->size > 1024) break;
        change_disk(page->p->head);
        read_disk(page->p->sector, tempdata);
        for(rint i = page->p->size-1; i >=0; --i){
            mystack[top++] = tempdata[i];
        }
        del = page->p;
        page->size += page->p->size;
        del->n->p = del->p;
        del->p->n = del->n;
        
        del->n = &head;
        del->p = head.p;
        head.p->n = del;
        head.p = del;
    }
    rint cnt = 0;
    while(top) tempdata[cnt++] = mystack[--top];

    while(true){
        if(page->n == h) break;
        if(page->size + page->n->size > 1024) break;
        change_disk(page->n->head);
        read_disk(page->n->sector, tempdata2);
        for(rint i = 0; i < page->n->size; ++i){
            tempdata[cnt++] = tempdata2[i];
        }
        page->size += page->n->size;
        del = page->n;
        del->p->n = del->n;
        del->n->p = del->p;

        del->n = &head;
        del->p = head.p;
        head.p->n = del;
        head.p = del;
    }
    change_disk(page->head);
    write_disk(page->sector, tempdata);
}

PAGE* split(int fid, PAGE* pp, int offset){
    register PAGE* p = pp;
    if(offset){
        p = head.n;
        p->size = pp->size - offset;
        p->n->p = p->p;
        p->p->n = p->n;
        change_disk(pp->head);
        read_disk(pp->sector, tempdata);
        pp->size = offset;
        for(rint i = 0; i < p->size; ++i){
            tempdata2[i] = tempdata[offset+i];
        }
        change_disk(p->head);
        write_disk(p->sector, tempdata2);
        p->n = pp->n;
        p->p = pp;
        pp->n->p = p;
        pp->n = p;
    }
    
    return p;
}

int getfileid(char* file){
    rint key =0;
    rint l = 0;
    for(rint i = 0; i < 16; ++i){
        key = ((key<< 5) + file[l++])% HASHSIZE;
    }
    while(myvisit[key] == tc && !strcmp(file,filename[myhash[key]]) ) key = ++key%HASHSIZE;
    if(myvisit[key] != tc){
        myvisit[key] = tc;
        myhash[key] = fid;
        for(rint i = 0; i < 16; ++i) filename[fid][i] = file[i];
        fid++;
    }
    return myhash[key];
}

void read_file(char* filename, int offset, char* data, int size){
    int fid = getfileid(filename);

    PAGE *h = &files[fid];
    PAGE *offsetp = getoffset(h, offset);
    rint cursor = 0;
    
    while(cursor != size){
        rint rsize = offsetp->size - offset;
        change_disk(offsetp->head);
        read_disk(offsetp->sector, tempdata);
        for(rint i = 0; i < rsize; ++i){
            data[cursor++] = tempdata[i+offset];
            if(cursor == size) return;
        }
        offset = 0;
        offsetp = offsetp->n;
    }
}

void insert_file(char* filename, int offset, char* data, int size){
    int fid = getfileid(filename);
    
    PAGE* h = &files[fid];
    PAGE *offsetp = getoffset(h, offset);
    offsetp = split(fid, offsetp, offset);
    
    while(size > 0){
        register PAGE* p = head.n;  
        head.n->n->p = &head;
        head.n = head.n->n;
        if(size < 1024) p->size = size;
        else p->size = 1024;
        size -= 1024;
        change_disk(p->head);
        write_disk(p->sector, data);
        data += 1024;

        p->p = offsetp->p;
        p->n = offsetp;
        
        offsetp->p->n = p;
        offsetp->p = p;
    }
    defragment(h, offsetp);
}

void delete_file(char* filename, int offset, int size){
    int fid = getfileid(filename);
    int endoffset = offset + size;
    PAGE *h = &files[fid];
    PAGE *endp = getoffset(h, endoffset);
    endp = split(fid, endp, endoffset);
    PAGE *offsetp = getoffset(h, offset);
    offsetp = split(fid, offsetp, offset);
    register PAGE *del;
    while(offsetp != endp){
        del = offsetp;
        offsetp = offsetp->n;
        del->n->p = del->p;
        del->p->n = del->n;
        del->n = &head;
        del->p = head.p;
        head.p->n = del;
        head.p = del;
    }
    defragment(h, offsetp);
}