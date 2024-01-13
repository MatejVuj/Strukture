#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define ERROR_ALLOCATION (-2)
#define ERROR_FILE_OPEN (-1)
#define MAX_LENGHT (256)
#define MAX_RED (1024)
#define MAX_NAME (128)

//lista pojedinog racuna sa artiklima
struct Article;
typedef struct Article* APosition;
typedef struct Article {
	char name_article[MAX_LENGHT];
	float price;
	float amount;
	APosition Next;
}Article;

//lista za datume
struct Date;
typedef struct Date* DPosition;
typedef struct Date {
	int year;
	int month;
	int day;
}Date;

//lista za racune
struct Racun;
typedef struct Racun* RPosition;
typedef struct Racun {
	char name_receipt[MAX_LENGHT];
	DPosition date;
	Article article;
	RPosition Next;
}Racun;

//Funkcije
int PrintMenu();
int ReadFile(char*, RPosition);
int InsertSortRacun(RPosition, RPosition);
int InicRacun(RPosition);
int InicArticle(APosition);
int InsertSortArticle(APosition, APosition);
int DateCompare(DPosition, DPosition);
int PrintRacun(RPosition);
int PrintArticle(APosition);
int DeleteALL(RPosition);
int DeleteArticle(APosition);
RPosition InsertRacunList(char*, int*);
DPosition InsertDate(char*);
APosition InsertArticle(char*);
APosition FindArticle(APosition, char*);

int main() {
	Racun head;
	InicRacun(&head);
	int pom, year1, month1, day1, year2, month2, day2, no_art = 0;
	float amount_art = 0;
	char name_file[MAX_LENGHT], insert[MAX_LENGHT], name_art[MAX_LENGHT] = { 0 };
	APosition find_art, pom_art = NULL;
	DPosition date1, date2 = NULL;
	RPosition racun = &head;

	printf("\tUnesite ime glavne datoteke:\t");
	gets(name_file);
	pom = ReadFile(name_file, racun);
	if (pom != 0)
		return pom;
	PrintRacun(racun->Next);
	PrintMenu();
	//SEARCH DIO
	do {
		pom_art = NULL;
		no_art = 0;
		amount_art = 0;
		racun = &head;
		printf("\tVas unos:   ");
		fgets(insert, MAX_LENGHT, stdin);
		sscanf(insert, "%s %d-%d-%d %d-%d-%d", name_art, &year1, &month1, &day1, &year2, &month2, &day2);
		if (strcmp(name_art, "exit") != 0) {
			date1 = date2 = NULL;
			date1 = (DPosition)malloc(sizeof(Date));
			if (date1 == NULL) {
				printf("Greska alokcije datuma prilikom trazenja!\n");
				return ERROR_ALLOCATION;
			}
			date1->year = year1;
			date1->month = month1;
			date1->day = day1;
			date2 = (DPosition)malloc(sizeof(Date));
			if (date2 == NULL) {
				printf("Greska alokcije datuma prilikom trazenja!\n");
				return ERROR_ALLOCATION;
			}
			date2->year = year2;
			date2->month = month2;
			date2->day = day2;
			racun = racun->Next;
			find_art = NULL;
			while (racun != NULL) {
				if ((DateCompare(racun->date, date1) >= 0) && (DateCompare(racun->date, date2) <= 0)) {
					find_art = InsertArticle(&racun->article, name_art);
					if (find_art != NULL) {
						pom_art = find_art;
						amount_art = amount_art + find_art->amount;
						no_art++;
					}
				}
				racun = racun->Next;
			}
			if (pom_art == NULL) {
				printf("\tArtikl nije pronaden!\n");
			}
			else {
				printf("\tArtikl %s je kupljen % d puta!\n\tUkupna kolicina: %.2f\n\tZarada:%.2f kn\n", pom_art->name_article, no_art, amount_art, amount_art * pom_art->price);
				printf("\t**********************************\n");
			}
			free(date1);
			free(date2);
		}
	} while (strcmp(name_art, "exit"));
	DeleteALL(&head);
	return EXIT_SUCCESS;
}

int PrintMenu() {
	printf("\t**********************************\n");
	printf("\t              SEARCH\n");
	printf("\t PRIMJER: kruh 2023-8-1 2021-8-9\n");
	return EXIT_SUCCESS;
}
int ReadFile(char* name_file, RPosition racun) {
	FILE* fp = NULL;
	fp = fopen(name_file, "r");
	if (fp == NULL) {
		printf("Postovani, datoteka %s se nije ispravno otvorila!\r\n", name_file);
		return ERROR_FILE_OPEN;
	}
	RPosition home = racun;
	int flag = 0;
	char buffer[MAX_RED] = { 0 };
	RPosition pom = NULL;
	while (!feof(fp)) {
		pom = 0;
		fscanf(fp, " %s", buffer);
		pom = InsertRacunList(buffer, &flag);
		if (pom == NULL && flag == 1) {
			fclose(fp);
			return ERROR_ALLOCATION;
		}
		else if (pom == NULL && flag == 0) {
			fclose(fp);
			return ERROR_ALLOCATION;
		}
		InsertSortRacun(racun, pom);

	}
	fclose(fp);
	return EXIT_SUCCESS;
}
RPosition InsertRacunList(char* buffer, int* flag) {
	*flag = 0;
	FILE* fp = NULL;
	fp = fopen(buffer, "r");
	if (fp == NULL) {
		printf("Postovani, datoteka %s se nije ispravno otvorila!\r\n", buffer);
		*flag = 1;
		return NULL;
	}
	RPosition q = NULL;
	q = (RPosition)malloc(sizeof(Racun));
	if (q == NULL) {
		printf("Greska alokacije racuna!\n");
		fclose(fp);
		return NULL;
	}
	InicRacun(q);
	strcpy(q->name_receipt, buffer);
	char buffer2[MAX_RED] = { 0 };
	int br = 0;
	char* pok = buffer2;
	while (!feof(fp)) {
		APosition	artikl = NULL;
		fgets(buffer2, MAX_RED, fp);
		if (br == 0) {
			q->date = InsertDate(buffer2);
			if (q->date == NULL) {
				fclose(fp);
				return NULL;
			}
			br++;
		}
		else {
			artikl = InsertArticle(buffer2);
			if (artikl == NULL) {
				fclose(fp);
				return NULL;
			}
			InsertSortArticle(&q->article, artikl);
			//PREPOZNAVANJE DATUMA TJ. PRVI REDAK U RACUNU
		}

	}
	fclose(fp);
	return q;
}
int InicRacun(RPosition racun) {
	memset(racun->name_receipt, 0, MAX_NAME);
	racun->date = NULL;
	racun->Next = NULL;
	InicArticle(&racun->article);
	return EXIT_SUCCESS;
}
int InicArticle(APosition art) {
	art->price = 0;
	art->amount = 0;
	memset(art->name_article, 0, MAX_NAME);
	art->Next = NULL;
	return EXIT_SUCCESS;
}
DPosition InsertDate(char* buffer) {
	char* pok = buffer;
	DPosition p = NULL;
	p = (DPosition)malloc(sizeof(Date));
	if (p == NULL) {
		printf("Greska alokacije datuma!\n");
		return NULL;
	}
	sscanf(pok, "%d-%d-%d", &p->year, &p->month, &p->day);

	return p;
}
APosition InsertArticle(char* buffer) {
	APosition art = NULL;
	art = (APosition)malloc(sizeof(Article));
	if (art == NULL) {
		printf("Greska alokacije artikla!\n");
		return NULL;
	}
	InicArticle(art);
	sscanf(buffer, "%s %f %f", art->name_article, &art->amount, &art->price);
	return art;
}
int InsertSortArticle(APosition head, APosition articl) {
	APosition p = head;
	while (p->Next != NULL && strcmp(p->Next->name_article, articl->name_article) < 0) {
		p = p->Next;
	}
	articl->Next = p->Next;
	p->Next = articl;
	return EXIT_SUCCESS;
}
int InsertSortRacun(RPosition racun, RPosition pom) {
	RPosition p = racun;
	while (p->Next != NULL && DateCompare(p->Next->date, pom->date) < 0)
		p = p->Next;
	pom->Next = p->Next;
	p->Next = pom;
	return EXIT_SUCCESS;
}
int DateCompare(DPosition date1, DPosition date2) {
	//pozitivan broj ako je prvi datum mladi,negativan ako je stariji
	int pom = date1->year - date2->year;
	if (pom == 0) {
		pom = date1->month - date2->month;
		if (pom == 0) {
			pom = date1->day - date2->day;
		}
	}
	return pom;
}
int PrintRacun(RPosition p) {
	printf("\n");
	while (p != NULL) {
		printf("\tIme racuna: %s\n", p->name_receipt);
		printf("\tDatum: %d-%d-%d\n", p->date->year, p->date->month, p->date->day);
		printf("\tArtikli: naziv\tkolicina  cijena\n");
		PrintArticle(&p->article);
		printf("\n");
		p = p->Next;
	}
	return EXIT_SUCCESS;
}
int PrintArticle(APosition p) {
	p = p->Next;
	while (p != NULL) {
		printf("%*s ", 22, p->name_article);
		printf("%*.2f ", 5, p->amount);
		printf("%*.2f ", 11, p->price);
		printf("\n");
		p = p->Next;
	}
	return EXIT_SUCCESS;
}
APosition FindArticle(APosition a, char* name_articlee) {
	APosition artikl = a;
	while (artikl != NULL) {
		if (strcmp(artikl->name_article, name_articlee) == 0)
			return artikl;
		artikl = artikl->Next;
	}
	return NULL;
}
int DeleteALL(RPosition p) {
	RPosition q;
	while (p->Next != NULL) {
		free(p->date);
		DeleteArticle(&p->article);
		q = p->Next;
		p->Next = q->Next;
		free(q);
	}
	return EXIT_SUCCESS;
}
int DeleteArticle(APosition p) {
	APosition q;
	while (p->Next != NULL) {
		q = p->Next;
		p->Next = q->Next;
		free(q);
	}
	return EXIT_SUCCESS;
}