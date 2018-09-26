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
        if (flag == -1) { //flag=-1 : ���� ����(addNode�� ���� ����)
            node* ptr = l->head;
            while(ptr->next!=NULL) {
                ptr = ptr->next;
            }
            ptr->next = newNode;;
        }
        else if (flag == 0) { //flag=0 : ����ִ� ����Ʈ�� ù node ����
            newNode->next = l->head;
            l->head = newNode;
        }
        else { //flag= ����: list�� flag��° ��ġ�� node ����
            node* ptr = l->head;
            for (int i = 0; i < flag-1; i++) { 
                ptr = ptr->next;
            }
            newNode->next = ptr->next;
            ptr->next = newNode;
        }
    }    
}

void deleteNode(linkedlist* l, int flag) { //flag�� ° node ����
    node* ptr = l->head;
    for (int i = 0; i < flag-1; i++) {
        ptr = ptr->next;
    }
    ptr->next = ptr->next->next;
 
}

void addNode(linkedlist* l, int data) { //����Ʈ�� ���� node �߰�
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
        scanf("%d", &n); //��ȣ���� ���� �Է� ����
        linkedlist *l = (linkedlist*)malloc(sizeof(linkedlist));
        l->head = NULL;
 
        for (int i = 0; i < n; i++) {
            int temp;
            scanf("%d", &temp); //���� ��ȣ�� �Է� �޾Ƽ� ����Ʈ�� �߰�
            insertNode(l, temp, -1);
        }
        int k;
        scanf("%d\n", &k); //��ɾ��� ���� �Է� ����
        for (int i = 0; i < k; i++) { //������ŭ �ݺ��ؼ� ��� ����
            char c;
            scanf("%c ", &c); //��ɾ� �Է� ����
            if (c == 'I') { //I�� ��� list�� a��°���� b����ŭ�� node ����
                int a, b;
                scanf("%d %d ", &a,&b);
                for (int j = 0; j < b; j++) {
                    int d;
                    scanf("%d ", &d);
                    insertNode(l, d, a+j);
                }
            }
            else if (c == 'D') { //D�� ��� list�� a��°���� b����ŭ�� node ����
                int a, b;
                scanf("%d %d ", &a,&b);
                for (int j = 0; j < b; j++) {
                    deleteNode(l, a);
                }
            }
            else if (c == 'A') { //A�� ��� ����Ʈ�� ���� a����ŭ�� node ����
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
        for (int i = 0; i < 10; i++) { //�պ��� �� ���� ��ȣ�� ���
            printf(" %d", ptr->data);
            ptr = ptr->next;
        }
        printf("\n");
    }
    return 0;
}