#include<iostream>
#include<cstdio>
// User Implement API
struct NODE{
    int i;
    NODE*p,*n;
    NODE* insert(NODE* in){
        in->n = this;
        in->p = p;
        p->n = in;
        p = in;
        return this;
    }
    
}nodes[1000];
int nid = 0;
NODE head[100];
 int main(void) {
     head[0].p = head[0].n = &head[0];
     NODE nn;
     NODE nn2 ;
     nn2.i = 2;
     nn.i = 1;

//insert

    "strr"
    "*strr"
    "s*trr"
    "st*rr"
    "str*r"
    "s*rr"
    "s*r"
    "*rr"

 }
 void addWord(char str[]){

 }
 int  removeWord(char str[]){

 }
 int  searchWord(char str[]){

 }