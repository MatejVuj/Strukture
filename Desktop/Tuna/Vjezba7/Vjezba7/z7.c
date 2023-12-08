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
	int directory[MAX_NAME];
	Position child;
	Position sibling;

}Directory;

typedef struct Stack {
	Position dir;
	StackPosition Next;
}stack;


int ChoiseFunction(int);
Position CreateDirectory(Position, char*);

int main() {

	Directory Root, Current, prev;

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

	choise = ChoiseFunction(insert);

	switch (choise) {
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;

	default:
		printf("Niste odabrali mogucu DOS-NAREDBU");
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
	printf("\tOdaberite naredbu\t");
	scanf("%d", &choise);

	return choise;

}

Position CreateDirectory(Position Root, char* name) {

	gets(name);



	return;
}