#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_LINE 256
#define EXIT_ERROR -1
#define EXIT_SUCCESS 0 

struct directory;
struct stack;
typedef struct directory* Position;
typedef struct stack* StackPosition;
typedef struct directory {

	char name_dir[MAX_NAME];
	Position child;
	Position sibling;

}Directory;

typedef struct stack {
	Position dir;
	StackPosition Next;
}Stack;


int ChoiseFunction(int);
Position CreateDirectory(Position, char*);
int InsertName(Position);
int PrintDIR(Position);
Position ReturnToPreviousDIR(Position);
Position ChangeDirectory(Position, StackPosition, char*);

int main() {
	Directory root = {
		.name_dir = {0},
		.child = NULL,
		.sibling = NULL
	};

	Stack st = {
		.dir = NULL,
	.Next = NULL
	};

	menu(&root,&st);
	return 0;
}

int menu(Position p, StackPosition stog) {

	Position Root = p;
	Position current = p;

	StackPosition rootstog = stog;

	int insert = 0, choise = 0;
	char name[MAX_NAME] = { 0 };

	while (choise != 5) {

		choise = ChoiseFunction(insert);

		switch (choise) {
		case 1: 
			current = CreateDirectory(current, name);
			break;
		case 2:
			current = ChangeDirectory(current,stog,name);
			break;
		case 3:
			break;
		case 4:
			PrintDIR(current);
			break;
		case 5:
			break;

		default:
			printf("Niste odabrali mogucu DOS-NAREDBU");
		}
	}


	return 0;
}

ChoiseFunction(int choise) {

	printf("\t\nMENI DOS-NAREDBI\t\n");
	printf("\t1 - md -> stvara direktorij\n");
	printf("\t2 - cd dir -> promjeni direktorij\n");
	printf("\t3 - cd.. -> idi nazad\n");
	printf("\t4 - dir -> ispisi sadrzaja direktorija\n");
	printf("\t5 - izlaz\n");
	printf("\tNaredba\t");
	scanf("%d", &choise);

	return choise;

}

int InsertName(Position q) {

	printf("\tUnesite naziv direktorija\t");
	scanf(" %s", q->name_dir);
	
	return 0;
}

Position CreateDirectory(Position Root, char* name) {

	Position q = NULL, current = Root;

	q = (Position)malloc(sizeof(Directory));

	if (q == NULL) {
		printf("Neuspjela alokacija memorije CreateDirectory q");
		return EXIT_ERROR;
	}
	
	q->child = NULL;
	q->sibling = NULL;

	name = InsertName(q);

	if (Root->child == NULL) {
		//q->child = Root->child;
		Root->child = q;
		return q;
	}

	else {

		if (Root->child->sibling != NULL && strcmp(Root->child->name_dir, q->name_dir)>0) {
			q->child = Root->child;
			Root->child = q;
			return current;
		}
		
		else {

			Root = Root->child;

			while (Root->sibling != NULL && strcmp(q->name_dir, Root->sibling->name_dir) <0) 
				Root = Root->sibling;
			
			q->sibling = Root->sibling;
			Root->sibling = q;
		}
	}
	return current;
}

int PrintDIR(Position p) {

	p = p->child;

	if (p == NULL) {
		printf("\t\nDirektorij je prazan\t");
	}
	printf("\n");
	
	while (p != NULL) {
		printf("\t");
		printf(" %s", p->name_dir);
		p = p->sibling;
	}

	printf("\n");

	return 0;
}

Position ChangeDirectory(Position p, StackPosition stack, char* name) {

	Position temp = NULL;
	Position q = (Position)malloc(sizeof(Directory));

	temp = p->child;

	q->child = NULL;
	q->sibling = NULL;

	name = InsertName(q);

	if (temp == NULL) {
		printf("\t\nNema se sta prominit\t");
		return p;
	}

	else {
		
		while (temp != NULL) {
			if (strcmp(temp->name_dir, q->name_dir) < 0) {
				push(p, stack);
				return temp;
			}
			temp = temp->child;
		}
	
		if (temp == NULL) {
			printf("\t\nDirektorij sa tim imenom ne postoji\t");
		}

		return p;
	}

}

Position pop(StackPosition p) {
	//mozda q ne ide NULL
	StackPosition q = NULL;
	Position temp = NULL;

	if (p->Next == NULL) {
		printf("\n\tPrazan Stog\t\n");
		return EXIT_ERROR;
	}

	while (p->Next->Next != NULL)
		p = p->Next;
	
	q = p->Next;
	p->Next = q->Next;
	temp = q->dir;

	free(q);

	return temp;

}

int push(Position current, StackPosition p) {

	StackPosition q = NULL;

	q = (StackPosition)malloc(sizeof(Directory));

	if (q == NULL) {
		printf("Greska u alokaciji memorije push q");
		return EXIT_ERROR;
	}

	while (p->Next != NULL) 
		p = p->Next;
	
	q->Next = p->Next;
	p->Next = q;

	q->dir = current;

	return EXIT_SUCCESS;
}