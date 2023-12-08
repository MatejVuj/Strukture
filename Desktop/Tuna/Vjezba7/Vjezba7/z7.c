#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_LINE 256
#define EXIT_ERROR -1
#define EXIT_SUCCESS 0 

typedef struct Directory* Position;
typedef struct Stack* StackPosition;
typedef struct Directory {

	char name_dir[MAX_NAME];
	Position child;
	Position sibling;

}Directory;

typedef struct Stack {
	Position dir;
	StackPosition Next;
}stack;


int ChoiseFunction(int);
Position CreateDirectory(Position, char);
int InsertName(Position);
int PrintDIR(Position);
Position ReturnToPreviousDIR(Position);

int main() {

	Directory Root, Current, prev;
	Position temp, p;

	Root.child = NULL;
	Root.sibling = NULL;
	Current.child = NULL;
	Current.sibling = NULL;
	prev.child = NULL;
	prev.sibling = NULL;

	stack Head;
	Head.Next = NULL;
	Position p_root = &Root;

	int insert = 0, choise = 0;

	while(choise != 5) {

		choise = ChoiseFunction(insert);

		switch (choise) {
		case 1:
			temp = CreateDirectory(&Root, NULL);
			CurrentFunction(temp);
			while (p->child != temp) {
				p = p->child;
			}
			PrevFunction(p);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			PrintDIR(Root.child);
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

	printf("\tMENI DOS-NAREDBI\t\n");
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

Position CreateDirectory(Position Root, char name) {

	Position q = NULL;

	q = (Position)malloc(sizeof(Directory));

	if (q == NULL) {
		printf("Neuspjela alokacija memorije CreateDirectory q");
		return EXIT_ERROR;
	}

	name = InsertName(q);

	while(Root->child != NULL)
		Root = Root->child;
	
	q->child = Root->child;
	Root->child = q;
	q->sibling = Root->sibling;

	return q;
}

int PrintDIR(Position p) {

	Position q = NULL;
	q = (Position)malloc(sizeof(Directory));

	if (q == NULL) {
		printf("\t\nNeuspjela alokacija memorije PrintDIR q\t");
		return EXIT_ERROR;
	}

	printf("\n");
	
	while (p != NULL) {
		printf("\t");
		printf(" %s", p->name_dir);
		p = p->child;
	}

	printf("\n");

	return 0;
}

Position CurrentFunction(Position p) {

	Position Current;

	Current->child = NULL;
	Current->sibling = NULL;

	Current = p;

	return Current;
}

Position PrevFunction(Position p) {

	Position prev;

	prev->child = NULL;
	prev->sibling = NULL;

	prev = p;

	return prev;
}

Position ReturnToPreviousDIR(Position p) {

	


}






