
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGHT 50
#define MEMORY_ALLOCATION_ERROR -1

struct Osoba;

typedef struct Osoba* Position;

typedef struct Osoba {

	char name[MAX_LENGHT];
	char surname[MAX_LENGHT];
	int year;
	Position Next;

}osoba;

int UnosP(Position);

int Ispis(Position);

int UnosK(Position);

int UnosPodataka(Position);

int UnosPodataka(Position q)
{
	printf("Unesite ime korisnika:\n");
	scanf(" %s", q->name);
	printf("Unesite prezime korisnika:\n");
	scanf(" %s", q->surname);
	printf("Unesite godinu rodenja korisnika:\n");
	scanf("%d", &q->year);

	return 0;
}

int UnosP(Position P) {
	
	Position q = NULL;

	q = (Position)malloc(sizeof(osoba));

	if (q == NULL) {
		printf("Neuspjelo alociranje memorije!\n");
		return MEMORY_ALLOCATION_ERROR;
	}
	
	UnosPodataka(q);

	q->Next = P->Next;
	P->Next = q;

		return 0;
	
}

int Ispis(Position P) {

	printf("\n----------\n");

	while (P != NULL) {

		printf("\n - %s - %s - %d", P->name, P->surname, P->year);
		P = P->Next;
	}

	return 0;
}

int UnosK(Position P) {

	Position q = NULL;

	q = (Position)malloc(sizeof(osoba));
	if (q == NULL) {
		printf("Neuspjelo alociranje memorije!\n");
		return MEMORY_ALLOCATION_ERROR;
	}
	
	UnosPodataka(q);

	while (P->Next != NULL)
			P = P->Next;

	q->Next = P->Next;
	P->Next = q;
	

	return 0;
}

void OslobodiMemoriju(Position P){
	while (P->Next != NULL)
	{
		Position temp = P->Next;
		P->Next = temp->Next;
		free(temp);
	}

	free(P);
}

int main() {

	Position Head;
	char insert = 0;

	Head = NULL;

	Head = (Position)malloc(sizeof(osoba));

	if (Head == NULL)
	{
		printf("Alokacija memorije nije uspjesna.\n");
		return MEMORY_ALLOCATION_ERROR;
	}

	Head->Next = NULL;


	while (insert != 'z') {
		printf("\nUnesite izbor");
		printf("\nz -> Zavrsetak programa");
		printf("\n1 -> Dodavanje osobe na pocetak liste");
		printf("\n2 -> Ispis Liste");
		printf("\n3 -> Dodavanje na kraj liste");

		printf("\nIzbor -> ");

		scanf(" %c", &insert);

		switch (insert) {
		case '0':
			printf("\nZavrsetak programa");
			break;

		case '1':
			UnosP(Head);
			break;

		case '2':
			Ispis(Head->Next);
			break;

		case '3':
			UnosK(Head);
			break;

		default:
			printf("\nNE MOZE");


		}

	}

	OslobodiMemoriju(Head);

	return 0;
}