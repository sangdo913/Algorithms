#include < stdio.h >
#include < stdlib.h >
 
typedef struct linkedlist {
    struct list* head;
}linkedlist;
 
typedef struct list {
    int data;
    struct list* next;
}node;
 
void insertNode(linkedlist* l, int data, int flag) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;
 
 
    if (l->head == NULL)
    {
        l->head = newNode;
    }
    else {
        if (flag == -1) { //flag=-1 : 끝에 삽입(addNode와 같은 역할)
            node* ptr = l->head;
            while(ptr->next!=NULL) {
                ptr = ptr->next;
            }
            ptr->next = newNode;;
        }
        else if (flag == 0) { //flag=0 : 비어있는 리스트에 첫 node 삽입
            newNode->next = l->head;
            l->head = newNode;
        }
        else { //flag= 정수: list의 flag번째 위치에 node 삽입
            node* ptr = l->head;
            for (int i = 0; i < flag-1; i++) { 
                ptr = ptr->next;
            }
            newNode->next = ptr->next;
            ptr->next = newNode;
        }
    }    
}

void deleteNode(linkedlist* l, int flag) { //flag번 째 node 삭제
    node* ptr = l->head;
    for (int i = 0; i < flag-1; i++) {
        ptr = ptr->next;
    }
    ptr->next = ptr->next->next;
 
}

void addNode(linkedlist* l, int data) { //리스트의 끝에 node 추가
    node* ptr = l->head;
    while(ptr->next!=NULL) {
        ptr = ptr->next;
    }
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;
 
    ptr->next = newNode;
}

int main(void)
{    
    setbuf(stdout, NULL);
    for (int test_case = 1; test_case <= 10; test_case++) {
        int n;
        scanf("%d", &n); //암호문의 길이 입력 받음
        linkedlist *l = (linkedlist*)malloc(sizeof(linkedlist));
        l->head = NULL;
 
        for (int i = 0; i < n; i++) {
            int temp;
            scanf("%d", &temp); //원래 암호문 입력 받아서 리스트에 추가
            insertNode(l, temp, -1);
        }
        int k;
        scanf("%d\n", &k); //명령어의 갯수 입력 받음
        for (int i = 0; i < k; i++) { //갯수만큼 반복해서 명령 실행
            char c;
            scanf("%c ", &c); //명령어 입력 받음
            if (c == 'I') { //I일 경우 list의 a번째부터 b개만큼의 node 삽입
                int a, b;
                scanf("%d %d ", &a,&b);
                for (int j = 0; j < b; j++) {
                    int d;
                    scanf("%d ", &d);
                    insertNode(l, d, a+j);
                }
            }
            else if (c == 'D') { //D일 경우 list의 a번째부터 b개만큼의 node 삭제
                int a, b;
                scanf("%d %d ", &a,&b);
                for (int j = 0; j < b; j++) {
                    deleteNode(l, a);
                }
            }
            else if (c == 'A') { //A일 경우 리스트의 끝에 a개만큼의 node 삽입
                int a;
                scanf("%d ", &a);
                for (int j = 0; j < a; j++) {
                    int d;
                    scanf("%d ", &d);
                    addNode(l, d);
                }
            }
            else {
                printf("error\n");
            }
        }
        printf("#%d", test_case);
        node* ptr = l->head;
        for (int i = 0; i < 10; i++) { //앞부터 열 개의 암호문 출력
            printf(" %d", ptr->data);
            ptr = ptr->next;
        }
        printf("\n");
    }
    return 0;
}