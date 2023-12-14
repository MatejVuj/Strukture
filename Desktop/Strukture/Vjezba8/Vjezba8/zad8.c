#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME 50
#define MAX_LINE 256
#define EXIT_ERROR -1
#define EXIT_SUCCESS 0

struct node;
typedef struct node* Position;
typedef struct node {

	int el;
	Position left;
	Position right;

}Node;

int menu(int);
Position Insert(Position, int);
Position Create(int);

int main(){

	Node root = {
		.el = 0,
		.left = NULL,
		.right = NULL
	};

	Position Root = &root;

	int insert = 0, choise = 0;
	int number = 0;
	int rootnumber = 0;

	printf("\n\tUnesite broj za root\t");
	scanf("%d", &rootnumber);
	Root = Insert(Root, rootnumber);

	while (choise != 9) {
		choise = menu(insert);
		switch (choise) {
			break;
		case 1:
			printf("\n\tUnesite broj\t");
			scanf("%d", &number);
			Insert(Root, number);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;

		case 9:
			break;

		default:
			printf("\n\tNiste odabrali mogucu NAREDBU");
		}
	}

	return 0;
}

int menu(int choise) {

	printf("\n\tIZBORNIK\t\n");
	printf("\n\t1 -> dodajte element");
	printf("\n\t2 -> Ispis inorder");
	printf("\n\t3 -> Ispis preorder");
	printf("\n\t4 -> Ispis postorder");
	printf("\n\t5 -> Ispis level order");
	printf("\n\t9 -> Izlaz");
	printf("\n\tNaredba:\t");
	scanf("%d", &choise);

	return choise;
}

Position Create(int number) {

	Position p;
	p = (Position)malloc(sizeof(Node));

	if (p == NULL) {
		printf("\n\tNeuspjela alokacija memorije");
		return EXIT_ERROR;
	}

	p->el = number;
	p->left = NULL;
	p->right = NULL;

	return p;
}

Position Insert(Position root, int number) {

	if (root == NULL)
		Create(number);

	else if (root->left > root->right)
		root->left = Insert(root->left, number);


	else if (root->left < root->right)
		root->right = Insert(root->right, number);

	return root;
}