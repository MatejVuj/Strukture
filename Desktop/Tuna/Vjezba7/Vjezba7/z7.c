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
Position ChangeDirectory(Position, StackPosition, char*);
Position ReturnOneBack(StackPosition);
Position pop(StackPosition);
int push(Position, StackPosition);

int main() {
	Directory root = {
		.name_dir = {0},
		.child = NULL,
		.sibling = NULL
	};

	Directory current = {
		.name_dir = {0},
		.child = NULL,
		.sibling = NULL
	};

	Directory previous = {
		.name_dir = {0},
		.child = NULL,
		.sibling = NULL
	};

	Stack st = {
		.dir = NULL,
		.Next = NULL
	};

	menu(&root,&current,&previous,&st);
	return 0;
}

int menu(Position p, Position cur, Position prev, StackPosition stog) {

	StackPosition rootstog = stog;

	int insert = 0, choise = 0;
	char name[MAX_NAME] = { 0 };

	Position Root = CreateDirectory(p, "C:");
	p->child = Root;

	Position current = Root;

	push(current, stog);

	while (choise != 5) {

		choise = ChoiseFunction(insert);

		switch (choise) {
		case 1: 
			printf("\t\nUnesite ime dirtektorija\t");
			scanf(" %s", name);
			current = CreateDirectory(current, name);
			break;
		case 2:
			printf("\t\nUnesite ime u kojem se dirtektoriju zelite nalazit\t");
			scanf(" %s", name);
			current = ChangeDirectory(current,stog,name);
			push(current,stog);
			break;
		case 3:
			if (current != Root) {
				current= pop(stog);
				printf("Nalazite se u %s direktoriju", current->name_dir);
			}
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

int ChoiseFunction(int choise) {

	printf("\t\t\nMENI DOS-NAREDBI\t\n");
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
	sscanf(" %s", q->name_dir);
	
	return 0;
}

Position CreateDirectory(Position Root, char* name) {

	Position q = NULL, current = Root;

	q = (Position)malloc(sizeof(Directory));

	if (q == NULL) {
		printf("Neuspjela alokacija memorije CreateDirectory q");
		return EXIT_ERROR;
	}
	
	//name = InsertName(q);

	strcpy(q->name_dir, name);
	q->child = NULL;
	q->sibling = NULL;

	if (Root->child == NULL) {
		//q->child = Root->child;
		Root->child = q;
		return q;
	}

	else {

		if (strcmp(Root->child->name_dir, name) > 0 ) {
			q->sibling = Root->child;
			Root->child = q;
			return q;
		}
		
		/*else {

			Root = Root->child;

			while (strcmp(name, Root->sibling->name_dir)) 
				Root = Root->sibling;
			
			q->sibling = Root->sibling;
			Root->sibling = q;
		}*/
	}
	//return q;
}

int PrintDIR(Position p) {

	Position temp = NULL;

	temp = p->child;
	
	while (temp != NULL) {
		printf("\t");
		printf(" %s", temp->name_dir);
		temp = temp->sibling;
	}

	printf("\n");

	if (temp == NULL) {
		printf("\t\nDirektorij je prazan\t");
	}
	printf("\n");

	return 0;
}

int Highway(Position current) {

	char name[MAX_NAME] = { 0 };

	StackPosition qs = (StackPosition)malloc(sizeof(Stack));

	if (qs == NULL) {
		printf("\t\nNeuspjela alokacija memorije\t");
		return EXIT_ERROR;
	}

	qs->dir = current;
	qs->Next = NULL;

	return qs;
}

int push(Position current, StackPosition stog) {

	StackPosition q = NULL;

	q = (StackPosition)malloc(sizeof(Stack));

	if (q == NULL) {
		printf("Greska u alokaciji memorije push q");
		return EXIT_ERROR;
	}

	q = Highway(current);
	
	q->Next = stog->Next;
	stog->Next = q;

	return EXIT_SUCCESS;
}

Position pop(StackPosition p) {
	//mozda q ne ide NULL
	StackPosition q = NULL;
	Position temp = NULL;

	if (p->Next == NULL) {
		printf("\n\tPrazan Stog\t\n");
		return NULL;
	}

	/*while (p->Next->Next != NULL)
		p = p->Next;*/

	q = p->Next;
	temp = p->Next->dir;
	p->Next = q->Next;

	free(q);

	return temp;

}

Position ReturnOneBack(StackPosition stog) {
	return pop(stog);
}

Position ChangeDirectory(Position p, StackPosition stack, char* name) {

	p = p->child;

	if (strcmp(p->name_dir, name) == 0) {
		return p;
	}

	while (p != NULL && strcmp(p->name_dir, name) == 0) {
		return p;
		p = p->child;
	}

	if (p == NULL || strcmp(p->name_dir, name) != 0) {
		printf("\t\nDirektorij sa tim imenom ne postoji\t");
		return p;
	}

	else push(p, stack);
	
	return p;

}