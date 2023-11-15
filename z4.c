#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX 256
#define FILE_ERROR -1
#define EXIT_SUCCESS 0

struct polinom;
typedef struct polinom* Position;
typedef struct polinom {

	int koef;
	int exp;
	Position Next;

}Polinom;

int Pointers(Position, Position);
int ReadFile(Position, char*);
int InsertSort(Position, Position);
int ZbrojiPolinome(Position, Position, Position);
int PomnoziPolinome(Position, Position, Position);
int IspisListe(Position);
int BrisiSve(Position);

Position Allocate();
Position NewEnter(int, int);

int main() {

	Position Head1 = NULL;
	Position Head2 = NULL;
	Position Head3 = NULL;
	Position Head4 = NULL;


	char file[MAX] = {"potencije.txt"};

	Head1 = Allocate();
	Head2 = Allocate();
	Head3 = Allocate();
	Head4 = Allocate();
	
	ReadFile(Head1, file);

	ZbrojiPolinome(Head1->Next,Head2->Next,Head3->Next);

	IspisListe(Head3->Next);

	PomnoziPolinome(Head1->Next, Head2->Next, Head4->Next);

	IspisListe(Head4->Next);

	BrisiSve(Head1);
	BrisiSve(Head2);
	BrisiSve(Head3);
	BrisiSve(Head4);

	return 0;
}

Position Allocate() {

	Position Head = NULL;

	Head = (Position)malloc(sizeof(Polinom));

	if (Head == NULL) {
	
		printf("Neuspjesno allocirana memorija");
		return NULL;
	}

	return Head;
}

int Pointers(Position p, Position q) {

	q->Next = p->Next;
	p->Next = q;

	return EXIT_SUCCESS;
}

int ReadFile(Position Head, char* file) {

	int koef = 0;
	int exp = 0;
	int temp = 0;
	int counter = 0;
	char buffer[MAX] = { 0 };
	char* p_buffer = buffer;

	FILE* f;
	f = fopen(file, "r");

	if (f == NULL) {
		
		printf("Greska u otvaranju datoteke\n");
		return FILE_ERROR;
	}
	
	fgets(p_buffer, MAX, f);

	while (strlen(p_buffer) != 0) {
		
		temp = sscanf(p_buffer, "%dx^%d %n", &koef, &exp, &counter);

		if (temp == 2) {
			
			Position El = NULL; //clan liste
			El = (Position)malloc(sizeof(Polinom));
			
			El->koef = koef;
			El->exp = exp;
			El->Next = NULL;

			InsertSort(Head, El);

			printf("%dx^%d ", El->koef, El->exp);
		}

		else {
		
			printf("Greska u citanju\n");
		}

		p_buffer += counter;
	}

	return EXIT_SUCCESS;
}

int InsertSort(Position p, Position q) {

	printf("Inserting node with koef = %d and exp = %d\n", q->koef, q->exp);


	Position temp = NULL;
	
	temp = (Position)malloc(sizeof(Polinom));

	if (temp == NULL) {
		printf("Greska u allokaciji\n");
		return FILE_ERROR;
	}

	temp->Next = NULL;

	if (p->koef == 0 || (p->koef + q->koef == 0)) {
		
		printf("Koeficijent je 0\n");
	}

	while (p->Next != NULL && p->Next->exp > q->exp) {
		
		p = p->Next;
	}

	if (p->Next != NULL && p->Next->exp == q->exp) {
	
		p->Next->koef += q->koef;

		free(q);
	}

	else {
	
		temp = NewEnter(temp->koef, temp->exp);
		Pointers(p, temp);

	}

	return EXIT_SUCCESS;
}

Position NewEnter(int koef, int exp) {

	printf("Creating new node with koef = %d and exp = %d\n", koef, exp);


	Position Head = (Position)malloc(sizeof(Polinom));

	if (Head == NULL) {

		printf("Greska u alokaciji memorije");
		return NULL;
	}

	Head->koef = koef;
	Head->exp = exp;
	Head->Next = NULL;

	return Head;

}

int ZbrojiPolinome(Position Head1, Position Head2, Position Head3) {

	Position temp = NULL;
	Position New = NULL;

	temp = (Position)malloc(sizeof(Polinom));

	if (Head1 == NULL || Head2 == NULL) {
	
		printf("Polinom je 0");
		return FILE_ERROR;

	}

	while (Head1 != NULL && Head2 != NULL) {
		
		if (Head1->exp > Head2->exp) {
			
			New = NewEnter(Head1->koef, Head1->exp);

			InsertSort(Head3, New);

			Head1 = Head1->Next;
		}

		else if (Head1->exp < Head2->exp) {
		
			//New = NULL;
			
			New = NewEnter(Head2->koef, Head2->exp);
			
			InsertSort(Head3, New);
			
			Head2 = Head2->Next;
		
		}

		else if (Head1->exp == Head2->exp) {
		
			//New = NULL;

			New = NewEnter(Head1->koef + Head2->koef, Head1->exp);

			InsertSort(Head3, New);

			Head1 = Head1->Next;

			Head2 = Head2->Next;
		}
	}

	/*while (Head1 != NULL) {
		Position node = NewEnter(Head1->koef, Head1->exp);
		InsertSort(Head3, node);
		Head1 = Head1->Next;
	}

	while (Head2 != NULL) {
		Position node = NewEnter(Head2->koef, Head2->exp);
		InsertSort(Head3, node);
		Head2 = Head2->Next;
	}*/


	temp = Allocate();

	if (Head2 == NULL) {
		temp = Head1;
	}

	else if (Head1 == NULL) {
		temp = Head2;
	}

	while (temp != NULL) {
		
		New = NewEnter(temp->koef, temp->exp);

		InsertSort(Head3, New);

		temp = temp->Next;
	}

	return EXIT_SUCCESS;
}

int PomnoziPolinome(Position P1, Position P2, Position P)
{
	Position poz1 = P1;
	Position poz2 = P2;
	Position p3 = NULL;

	p3 = (Position)malloc(sizeof(Polinom));

	while (poz1 != NULL)
	{
		poz2 = P2;
		while (poz2 != NULL)
		{
			p3 = NewEnter(poz1->koef * poz2->koef, poz1->exp + poz2->exp);
			InsertSort(P, poz1);
			poz2 = poz2->Next;
		}
		poz1 = poz1->Next;
	}

	return EXIT_SUCCESS;
}

int IspisListe(Position HeadN) {

	printf("Printing list...\n");

	if (HeadN == NULL) {

		printf("Lista je prazna\n");
		return FILE_ERROR;
	}

	while (HeadN != NULL) {
		printf("%d x^%d + ", HeadN->koef, HeadN->exp);
		HeadN = HeadN->Next;
	}

	printf("\n");

	return EXIT_SUCCESS;

}

int BrisiSve(Position Head) {

	Position temp = NULL;

	while (Head->Next != NULL) {
		
		temp = Head->Next;
		Head->Next = temp->Next;
		free(temp);
	}

	Head->Next = NULL;

	return EXIT_SUCCESS;
}
