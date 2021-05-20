#include<stdio.h>
#include<iostream>
#include<set>
using namespace std;

struct Node {
    int value;
    Node  *next,*prev;
};

int main(){
    // NODE* 
}

//(2번, 4번)
bool checkCycle(Node* head){
    Node* rabbit = head;
    Node* turtle = head;
    if(!rabbit) return false;
    rabbit = rabbit->next;
    if(!rabbit) return false;
    rabbit = rabbit->next;

    turtle = turtle->next;

    while(!rabbit && !turtle){            
        if(rabbit != turtle){
            rabbit = rabbit->next;
            if(!rabbit) return false;
            rabbit = rabbit->next;
            turtle = turtle->next;
        }
        else return true;
    }
    return false;
}
//rabbit = 2 turtle = 3
//rabbit = 4 turtle = 4