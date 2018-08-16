#include < stdio.h >
#include < stdlib.h >
#define _CRT_SECURE_NO_WARNINGS

int c1, c2, c3, c4, a;
int x, y, z;
char q;

struct node {
	struct node* next;
	int data;
};

void add(struct node *target, int data) {
	struct node *new_Node = (struct node *)malloc(sizeof(struct node));
	new_Node->data = data;
	new_Node->next = target->next;
	target->next = new_Node;
}

void del(struct node *target) {
	struct node *del_node;
	del_node = target->next;
	target->next = del_node->next;
	free(del_node);
}

int main() {
	int i, j, k, l;
	struct node *head = (struct node*)malloc(sizeof(struct node));
	struct node *temp = (struct node*)malloc(sizeof(struct node));

	for (i = 0; i < 10; i++) {

		scanf("%d", &c1);
		head->next = NULL;
		temp = head;
		printf("%d\n", c1);
		for (j = 0; j < c1; j++) {
			scanf(" %d", &a);
			add(temp, a);
			temp = temp->next;
			printf("%d\n", j);
		}
		printf("\n\n\n\n");
		temp = head;
		scanf("%d", &c2);

		for (j = 0; j < c2; j++) {
			scanf(" \n%c", &q);
			if (q == 'I') {
				scanf("%d%d", &x, &y);

				for (k = 0; k < y; k++) {
					scanf("%d", &c3);
					if (k == 0) {

						for (l = 0; l < x; l++) {
							temp = temp->next;
						}
					}
					add(temp, c3);
					temp = temp->next;
				}
			}

			else if (q == 'D') {
				scanf("%d%d", &x, &y);
				for (l = 0; l < x; l++) {
					temp = temp->next;
				}
				for (l = 0; l < y; l++) {
					del(temp);
				}

			}

			else if (q == 'A') {
				scanf("%d", &x);
				printf("121212121212\n\n\n");
				while (temp->next != NULL) {
					temp = temp->next;
				}
				for (l = 0; l < x; l++) {
					scanf("%d", &c4);
					add(temp, c4);
					temp = temp->next;
				}

			}
			temp = head;
		}

		temp = head->next;
		printf("#%d ", i + 1);
		for (j = 0; j < 10; j++) {
			printf("%d ", temp->data);
			temp = temp->next;
		}
		printf("\n");
	}
	free(head);
	free(temp);
	return 0;
}