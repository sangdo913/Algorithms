#define LN 100000
int arr[LN];

#include<iostream>
#include<cstdio>
#include<ctime>
#include<cstdlib>

using namespace std;
struct Book{
    char name[4];
    int price;
    Book *p, *n;
}book[10000];
Book* mhash[26][26][26];
int bid = 0;

Book* myalloc(char *name, int price){
    mstrcpy(book[bid].name, name);
    book[bid].p = book[bid].n = &book[bid];
    return book[bid++];
}

int main(){
    char name[10][3];
    Book head;
    head.p = head.n = &head;

    for(int i = 0; i <10; ++i){
        for(int j = 0; j < 3; ++j){
            book[bid].name[j] = 'a'+i;
        }
        book[bid].price = rand()%10000+1;
        mhash[book[bid].name[0]-'a'][book[bid].name[1]-'a'][book[bid].name[2]-'a'] = &book[bid];

        book[bid].n = &head;
        book[bid].p = head.p;

        book[bid].n->p = &book[bid];
        book[bid].p->n = &book[bid];

        bid++;
    }
    Book* cur = head.n;
    while(cur != &head) {
       printf("%s\n",cur->name);
       printf("%d\n", cur->price);
       cur= cur->n; 
    }
    
    return 0;
}