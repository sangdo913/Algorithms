#include <stdio.h>

void init(int n) {

}

void addParty(int index, int m, char names[4][11]) {
	printf("party index %d. member cnt %d, ", index, m);
	for (int i = 0; i < m; i++) {
		printf("%s ", names[i]);
	}
	printf("\n");
}

void closeParty(int index) {

}

void suspendMember(char name[11]) {

}

void recoveryMember(char name[11]) {

}

int search(char names[2][11], int mode) {

	return 0;
}
