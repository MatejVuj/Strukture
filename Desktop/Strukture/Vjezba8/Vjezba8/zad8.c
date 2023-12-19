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
int Inorder(Position);
int Preorder(Position);
int Postorder(Position);
int Levelorder(Position);
Position Insert(Position, Position);
Position Create(Position, int);

int main(){

	Position Root = NULL;
	Position q;

	int insert = 0, choise = 0;
	int number = 0;

	while (choise != 9) {
		choise = menu(insert);
		switch (choise) {
		case 1:
			printf("\n\tUnesite broj\t");
			scanf("%d", &number);
			q = Create(Root, number);
			Root = Insert(Root,q);
			break;
		case 2:
			printf("\n\tInorder: ");
			Inorder(Root);
			printf("\n");
			break;
		case 3:
			printf("\n\tPostorder: ");
			Postorder(Root);
			printf("\n");
			break;
		case 4:
			printf("\n\tPreorder: ");
			Preorder(Root);
			printf("\n");
			break;
		case 5:
			//Levelorder(Root);
			break;

		case 9:
			break;

		default:
			printf("\n\tNiste odabrali mogucu NAREDBU");
		}
	}

	free(Root);

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

Position Create(Position p, int number) {

	p = (Position)malloc(sizeof(Node));

	if (p == NULL) {
		printf("\n\tNeuspjela alokacija memorije");
		return NULL;
	}

	p->el = number;
	p->left = NULL;
	p->right = NULL;

	return p;
}

Position Insert(Position p, Position q) {

	if (p == NULL)
		return q;

	else if (p->el > q->el)
		p->left = Insert(p->left, q);

	else //if (p->el < p->el)
		p->right = Insert(p->right, q);

	return p;
}

int Inorder(Position p) {

	if (p == NULL)
			return EXIT_SUCCESS;
	Inorder(p->left);
	printf("%d ", p->el);
	Inorder(p->right);
	return EXIT_SUCCESS;
	
}

int Postorder(Position p) {

	if (p == NULL)
		return EXIT_SUCCESS;

	Postorder(p->left);
	Postorder(p->right);
	printf("%d ", p->el);
	return EXIT_SUCCESS;

}

int Preorder(Position p) {

	if (p == NULL)
		return EXIT_SUCCESS;

	printf("%d ", p->el);
	Preorder(p->left);
	Preorder(p->right);
	return EXIT_SUCCESS;

}