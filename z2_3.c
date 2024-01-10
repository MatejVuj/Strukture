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

int UnosIza(Position);

int UnosIspred(Position);

int Brisi_Osobu(Position);

int UpisUDatoteku(Position, char*);

int CitanjeIzDatoteke(Position, char*);

int IspisListe(Position P);

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

Position Pronadji_za_UnosIza(Position P, char* surname) {

	while (P != NULL && strcmp(P->surname, surname)) {
		P = P->Next;
	}

	if (P == NULL) {
		printf("\nOsoba ne postoji");
		return NULL;
	}

	return P;
}

Position PronadjiPret(Position P, char* surname) {
	
	Position before = P;
	
	P = P->Next;

	while (P != NULL && strcmp(P->surname, surname)) {
		
		before = before->Next;
		P = P->Next;
	}

	if (P == NULL) {
		printf("\nOsoba ne postoji");
		return NULL;
	}

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

int UnosIza(Position P) {

	Position q = NULL;
	
	char surname[MAX_LENGHT] = { 0 };

	q = (Position)malloc(sizeof(osoba));

	if (q == NULL) {
		printf("Neuspjelo alociranje memorije!\n");
		return MEMORY_ALLOCATION_ERROR;
	}

	printf("\nUnesite prezime osobe iza koje zelite dodati novu osobu\n");
	scanf(" %s", surname);

	P = Pronadji_za_UnosIza(P, surname);

	printf("\n---Unesite Osobu koju zelite dodati---\n");
	UnosPodataka(q);

	q->Next = P->Next;
	P->Next = q;
	
	return 0;
}

int UnosIspred(Position P) {
	
	Position q = NULL;
	char surname[MAX_LENGHT] = { 0 };

	q = (Position)malloc(sizeof(osoba));

	if (q == NULL) {
		printf("Neuspjelo alociranje memorije!\n");
		return MEMORY_ALLOCATION_ERROR;
	}

	printf("\nUnesite prezime ispred koje zelite dodati novu osobu\n");
	scanf(" %s", surname);

	if (P == NULL) {
		printf("Osoba sa prezimenom %s nije pronađena.\n", surname);
		free(q);
		return ERROR_EXIT;
	}

	P = PronadjiPret(P, surname);

	printf("\n---Unesite osobu koju zelite dodati---\n");
	UnosPodataka(q);

	q->Next = P->Next;
	P->Next = q;

	return 0;
}

int UpisUDatoteku(Position P, char* file)
{
	FILE* fp = NULL;
	fp = fopen(file, "a");
	if (fp == NULL)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return ERROR_EXIT;
	}
	while (P != NULL)
	{
		fprintf(fp, "Student: %-20s %-20s, godina: %4d\n", P->name, P->surname, P->year);
		P = P->Next;
	}
	fclose(fp);

	return EXIT_SUCCESS;
}

int CitanjeIzDatoteke(Position P, char* file)
{
	FILE* fp = NULL;
	int pom = 0, n = 0, godina = 0;
	char ime[MAX_LENGHT] = { 0 }, prezime[MAX_LENGHT] = { 0 }, pomocna[MAX_LENGHT] = { 0 };
	fp = fopen(file, "r");
	char buff[MAX_LENGHT] = { 0 };
	char* b = buff;
	if (fp == NULL)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return ERROR_EXIT;
	}

	while (P != NULL)
	{
		fscanf(fp, "Student:%s %s, godina %d", P->name, P->surname, &P->year);
		P = P->Next;
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

int IspisListe(Position P)
{
	if (P == NULL)
	{
		printf("Lista je prazna!\n");
		return ERROR_EXIT;
	}

	while (P != NULL)
	{
		printf("Ime: %s\nPrezime: %s\nGodina rodenja: %d\n", P->name, P->surname, P->year);
		P = P->Next;
	}

	return EXIT_SUCCESS;
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
	char file[MAX_LENGHT] = { 0 };
	char file2[MAX_LENGHT] = { 0 };

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
		printf("\n6 -> Unos iza osobe u listi");
		printf("\n7 -> Unos ispred osobe u listi");
		printf("\n8 -> Upis u datoteku");
		printf("\n9 -> Citanje iz datoteke");

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
		
		case '6':
			UnosIza(Head);
			break;

		case '7':
			UnosIspred(Head);
			break;

		case '8':
			printf("Unesite ime datoteke:\n");
			scanf(" %s", file);
			UpisUDatoteku(Head->Next, file);
			IspisListe(Head->Next);
			break;

		case '9':
			printf("Unesite ime datoteke:\n");
			scanf(" %s", file2);
			printf("\n");
			CitanjeIzDatoteke(Head->Next, file2);
			break;

		case '10':
			printf("Kraj programa. Adio!");
			break;

		default:
			printf("\nNE MOZE");

		}

	}

	OslobodiMemoriju(Head);

	return 0;
}
