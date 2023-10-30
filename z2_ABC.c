
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGHT 50
#define MEMORY_ALLOCATION_ERROR -1
#define ERROR_EXIT -1

struct Osoba;

typedef struct Osoba* Position;

typedef struct Osoba {

	char name[MAX_LENGHT];
	char surname[MAX_LENGHT];
	int year;
	Position Next;

}osoba;

int UnosPodataka(Position);

int UnosP(Position);

int Ispis(Position);

int UnosK(Position);

int Brisi_Osobu(Position);

Position Pronadji(Position);

Position PronadjiPret(Position, char*);

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

Position Pronadji(Position P) {
	char surname[MAX_LENGHT] = { 0 };
	//int i = 1;

	printf("\nUnesite prezime\n");
	scanf(" %s", surname);

	while (P != NULL && strcmp(P->surname, surname)) {

		//if(strcmp(P->surname, surname)==NULL);
		//i++;

		P = P->Next;
	}

	if (P == NULL) {
		printf("\nOsoba ne postoji");
		return NULL;
	}

	printf("\nOSOBA -> %s %s %d\n", P->name, P->surname, P->year);

	return P;
}

Position PronadjiPret(Position P, char* surname) {
	
	Position before = P;
	
	P = P->Next;

	while (P->Next != NULL && strcmp(P->surname, surname)) {
		
		before = before->Next;
		P = P->Next;
	}

	if (P->Next == NULL)
		return NULL;
	else
		return before;
}

int Brisi_Osobu(Position P) {

	Position before, q;
	char surname[MAX_LENGHT] = { 0 };

	printf("\nUnesite prezime\n");
	scanf(" %s", surname);

	before = PronadjiPret(P, surname);

	if (before == NULL) {
		printf("Nema prethodnika, ne moze obrisat");
		return ERROR_EXIT;
	}

	q = before->Next;
	before->Next = q->Next;
	
	free(q);

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
	//char surname[MAX_LENGHT] = {0};

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
		printf("\n4 -> Trazenje po prezimenu");
		printf("\n5 -> Brisanje odredjene osobe");

		printf("\nIzbor -> ");

		scanf(" %c", &insert);

		switch (insert) {
		case 'z':
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

		case '4':
			Pronadji(Head);
			break;
		
		case '5':
			Brisi_Osobu(Head);
			break;

		default:
			printf("\nNE MOZE");

		}

	}

	OslobodiMemoriju(Head);

	return 0;
}
