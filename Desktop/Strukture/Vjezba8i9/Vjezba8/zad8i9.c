#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NAME 50
#define MAX_LINE 256
#define EXIT_ERROR -1
#define EXIT_SUCCESS 0
#define LOWER 10
#define UPPER 90

struct node;
typedef struct node* Position;
typedef struct node {

	int el;
	Position left;
	Position right;

}Node;

int menu(int);
int Inorder(Position);
int InorderFile(Position, char*);
int Preorder(Position);
int Postorder(Position);
int Levelorder(Position);
int Height(Position);
int CurrentLevel(Position, int);
int Replace(Position);
int rnd();
int DeleteAll(Position);
//int PrintInFile(Position, char*);
Position Insert(Position, Position);
Position Create(Position, int);
Position FindElement(Position, int);
Position DeleteElement(Position, int);
Position FindMax(Position);
Position FindMin(Position);


int main(){

	Position Root = NULL;
	Position q;

	int insert = 0, choise = 0;
	int number = 0;
	int i = 0, n = 10;
	//char file[MAX_LINE] ="brojevi.txt";
	char file[MAX_LINE] = { 0 };
	printf("\tUnesite ime datoteke\t");
	gets(file);
	//srand(unsigned(time(0)));

	Position element;
	element = (Position)malloc(sizeof(Node));

	while (choise != 9) {
		choise = menu(insert);
		switch (choise) {
		/*case 1:
			printf("\n\tUnesite broj\t");
			scanf("%d", &number);
			q = Create(Root, number);
			Root = Insert(Root,q);
			break;*/

		case 1:
			printf("\n\tUnosenje brojeva\t");
			q = Create(Root, 2);
			Root = Insert(Root, q);
			q = Create(Root, 5);
			Root = Insert(Root, q);
			q = Create(Root, 7);
			Root = Insert(Root, q);
			q = Create(Root, 8);
			Root = Insert(Root, q);
			q = Create(Root, 11);
			Root = Insert(Root, q);
			q = Create(Root, 1);
			Root = Insert(Root, q);
			q = Create(Root, 4);
			Root = Insert(Root, q);
			q = Create(Root, 2);
			Root = Insert(Root, q);
			q = Create(Root, 3);
			Root = Insert(Root, q);
			q = Create(Root, 7);
			Root = Insert(Root, q);
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
			printf("\n\tLevelorder: ");
			Levelorder(Root);
			printf("\n");
			break;

		case 6:
			printf("\n\tKoji element zelite izbrisati");
			scanf("%d", &number);
			Root = DeleteElement(Root, number);
			printf("\n");
			break;

		case 7:
			printf("\n\tKoji element zelite pronaci");
			scanf("%d", &number);
			element = FindElement(Root, number);
			if (element != NULL)
				printf("Element %d is found!\n", number);
			break;

		case 8:
			Replace(Root);
			break;

		case 9:
			InorderFile(Root, file);
			break;

		case 11:
			for (i = 0; i < 10; i++) {
				q = Create(Root, rnd());
				Root = Insert(Root, q);
			}
			break;

		case 101:
			DeleteAll(Root);

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
	printf("\n\t6 -> Izbrisi element");
	printf("\n\t7 -> pronadji element");
	printf("\n\t8 -> replace");
	printf("\n\t9 -> Ispis Inordera u file");
	printf("\n\t11 -> Random borjevi");
	printf("\n\t101 -> Izbrisi sve");
	printf("\n\tNaredba:\t");
	scanf("%d", &choise);

	return choise;
}

Position Create(Position p, int number) {
	//stvara element prije postavljanja u stablo
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
	//Inserta u elemetnt u stablo
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

int Levelorder(Position p) {

	int h = Height(p);
	int i = 0;

	for (i = 1; i <= h; i++) {
		CurrentLevel(p, i);
	}
	return EXIT_SUCCESS;
}

int Height(Position p) {
	//od roota do kraja stabla tj. zadnjeg lsita

	int right = 0;
	int left = 0;

	if (p == NULL)
		return EXIT_SUCCESS;

	else {
	
		left = Height(p->left);
		right = Height(p->right);

		if (left > right) 
			return (left + 1);
		
		else 
			return (right + 1);
		
	}

}

int CurrentLevel(Position p, int level) {
	//printa trenutni level
	if (p == NULL)
		return EXIT_SUCCESS;

	if (level == 1)
		printf("%d ", p->el);

	else if (level > 1) {
		CurrentLevel(p->left, level - 1);
		CurrentLevel(p->right, level - 1);
	}

	return EXIT_SUCCESS;

}

Position FindElement(Position p, int data) {

	if (p == NULL) {
		printf("Element ne postoji");
		return NULL;
	}

	if (p->el == data)
		return p;

	else if (p->el > data) {
		p->left = FindElement(p->el, data);
		return p;
	}

	else {
		p->right = FindElement(p->el, data);
		return p;
	}

}

Position DeleteElement(Position p, int data) {
	
	if (p == NULL)
		return NULL;
	
	if (p->el < data)
		p->right = DeleteElement(p->right, data);

	else if (p->el > data)
		p->left = DeleteElement(p->left, data);

	else {
		
		if (p->left) {
			Position temp = FindMax(p->left);
			p->el = temp->el;
			p->left = DeleteElement(p->left, temp->el);
		}

		else if (p->right) {
			Position temp = FindMin(p->right);
			p->el = temp->el;
			p->right = DeleteElement(p->right, temp->el);
		}

		else {
			free(p);
			return NULL;
		}
	}
	return p;
}

Position FindMax(Position p) {

	if (p == NULL) {
		printf("Error");
		return NULL;
	}

	while (p->left != NULL)
		p = p->left;

	return p;
}

Position FindMin(Position p) {

	if (p == NULL) {
		printf("Error");
		return NULL;
	}

	while (p->right != NULL)
		p = p->right;

	return p;
}

int DeleteAll(Position p) {
	
	if (p == NULL)
		return EXIT_SUCCESS;

	DeleteAll(p->right);
	DeleteAll(p->left);
	free(p);
	return EXIT_SUCCESS;
}

int Replace(Position p) {

	if (p == NULL)
		return EXIT_SUCCESS;

	int temp = p->el;
	p->el = Replace(p->left) + Replace(p->right);

	return p->el + temp;
}

int rnd() {
	
	int number = 0;
	number = (rand() % (UPPER - LOWER)) + LOWER;
	return number;
}

int InOrderF(Position p, FILE* fp) {

	if (p == NULL)
		return EXIT_SUCCESS;
	InOrderF(p->left, fp);
	fprintf(fp, "%d ", p->el);
	InOrderF(p->right, fp);
	return EXIT_SUCCESS;

}

int InorderFile(Position p, char* filename) {

	FILE* fp = fopen(filename, "w");

	if (fp == NULL){
		printf("Error in file opening!\n");
		return EXIT_ERROR;
	}

	InOrderF(p, fp);
	fclose(fp);

	return EXIT_SUCCESS;
	
}