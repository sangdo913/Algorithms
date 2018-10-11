#pragma once
#include<iostream>

using namespace std;
int n, m;

typedef char SNUM[9];
bool nums[500000];

void cpy(char*dst, char* fr, int len) {
	for (int i = 0; i < len; i++) {
		dst[i] = fr[i];
	}
}


int cmp(char* s1, char*s2) {
	while (*s1 && *s2 && *s1 == *s2) {
		s1++, s2++;
	}
	return *s1 - *s2;
}

struct NODE {
	SNUM num;
	int idx;
	NODE *left, *right, *p;
	NODE() : left(0), right(0) {
	}
	NODE(SNUM inum) :left(0), right(0) {
		cpy(num, inum, 9);
	};
	
};

NODE nodes[700000];

struct MYAL {
	int idx;
	MYAL() :idx(0) {};
	NODE* alloc() {
		return &nodes[idx++];
	}

}al;

struct BST {
	NODE* root;
	
	bool find(SNUM num, int i){
		return find(root, num, i);
	}

	BST() :root(al.alloc()) {};

	bool find(NODE* node, SNUM num, int i) {
		if (node == 0) return false;

		int comp = cmp(num, node->num);
		if (comp > 0) return find(node->right, num,i );
		else if (comp < 0)return find(node->left, num,i);
		else {
			nums[node->idx] = false;
			node->idx = i;
			return true;
		}
	}

	void insert(SNUM num, int i) {
		insert(root, num,i);
	}
	void insert(NODE* node, SNUM num, int i) {
		int comp = cmp(num, node->num);
		if (comp > 0) {
			if(node->right)insert(node->right, num, i);
			else {
				NODE* n = al.alloc();
				cpy(n->num, num, sizeof(node->num));
				n->left = n->right = 0;
				n->idx = i;
				n->p = node;
				node->right = n;
			}
		}
		else if (comp < 0) {
			if (node->left) insert(node->left, num, i);
			else {
				NODE* n = al.alloc();
				n->idx = i;
				cpy(n->num, num, sizeof(node->num));
				n->left = n->right = 0;
				n->p = node;
				node->left = n;
			}
		}
	}

	NODE* findMIN(NODE* node) {
		while (node->left) {
			return findMIN(node);
		}
		return node;
	}

	void del(SNUM num) {
		del(root, num);

	}
	void del(NODE* node, SNUM num) {
		int comp = cmp(num, node->num);
		if (comp > 0) {
			del(node->right, num);
		}
		else if (comp < 0) {
			del(node->left, num);
		}
		else {
			if (node->left == 0 && node->right == 0) {
				if (node->p->left == node) node->p->left = 0;
				else node->p->right = 0;
			}
			else if (node->left && node->right){
				NODE* delnode = findMIN(node->right);
				
				nums[delnode->idx] = false;
				memcpy(node->num, delnode->num, sizeof(delnode->num));
				node->idx = delnode->idx;

				if (delnode == node->right) {
					node->right = delnode->right;
				}
				else {
					delnode->p->left = delnode->right;
				}
			}
			else {
				if (node->left){
					if (node->p->left == node) node->p->left = node->left;
					else node->p->right = node->left;
				}
				else {
					if (node->p->left == node) node->p->left = node->right;
					else node->p->right = node->right;
				}
			}
		}
	}
};
SNUM store[500000];

int BOJ13414() {
	cin >> n >> m;
	
	BST bst;
	
	int size = 0;
	for(int i = 0; i < m; i++){
		cin >> store[i];
		nums[i] = true;
		
		if (bst.find(store[i],i)) {
		}
		else {
			bst.insert(store[i],i);
		}
		
	}

	for (int i = 0; i < m&& size != n ; i++) {
		if (nums[i]) {
			size++;
			cout << store[i] << '\n';
		}
	}
	return 0;
}
