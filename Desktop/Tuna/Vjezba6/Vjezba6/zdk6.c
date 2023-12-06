#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define ERROR_ALLOCATION -2
#define ERROR_FILE_OPEN -1
#define MAX_LENGHT 256
#define MAX_RED 1024
#define MAX_NAME 128

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
int ReadFile(RPosition, char*);
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
	Racun Head;

	int pom, year1, month1, day1, year2, month2, day2, no_art = 0;
	float amount_art = 0;
	char name_file[MAX_LENGHT], insert[MAX_LENGHT], name_art[MAX_LENGHT] = { 0 };
	APosition find_art, pom_art = NULL;
	DPosition date1, date2 = NULL;
	RPosition racun = &Head;

	printf("Unesite ime datoteke");
	gets(name_file);
	pom = ReadFile(racun, name_file);

	if (pom != 0)
		return pom;

	PrintRacun(racun->Next);
	
	do {

		pom_art = NULL;
		no_art = 0;
		amount_art = 0;
		racun = &Head;
		printf("\tUnos: ");
		fgets(insert, MAX_LENGHT, stdin);
		sscanf(insert, "%s %d-%d-%d %d-%d-%d", name_art, &year1, &month1, &day1, &year2, &month2, &day2);

		if (strcmp(name_art, "exit") != 0) {
			date1 = date2 = NULL;
			date1 = (DPosition)malloc(sizeof(Date));

			if (date1 == NULL) {
				printf("Greska u alokaciji datuma u main");
				return ERROR_ALLOCATION;
			}

			date1->year = year1;
			date1->month = month1;
			date1->day = day1;

			date2 = (DPosition)malloc(sizeof(Date));

			if (date2 == NULL) {
				printf("Greska u alokaciji datuma u main");
				return ERROR_ALLOCATION;
			}

			date2->year = year2;
			date2->month = month2;
			date2->day = day2;

			racun = racun->Next;
			find_art = NULL;

			while (racun != NULL) {
				if ((DateCompare(racun->date, date1) >= 0) && (DateCompare(racun->date, date2) <= 0)) {
					find_art = FindArticle(&racun->article, name_art);
					if (find_art != NULL) {
						pom_art = find_art;
						amount_art = amount_art + find_art->amount;
						no_art++;
					}

				}

			}
			racun = racun->Next;

			if (pom_art == NULL) {
				printf("\tArtikl nije pronadjen\n");
			}

			else {

				printf("\tArtikl %s je kupljen %d puta \n\t Ukupna kolicna: %.2f\n\t Zarada: %.2f $\n", pom_art->name_article, no_art, amount_art, amount_art * pom_art->price);

			}

			free(date1);
			free(date2);
		}
	}

	while (strcmp(name_art, "exit"));
	DeleteALL(&Head);

	return EXIT_SUCCESS;
	
}

int ReadFile(RPosition racun, char* name_file) {
	
	FILE* file = NULL;
	file = fopen(name_file, "r");

	if (file == NULL) {
		printf("Greska pri otvaranju filea");
		return ERROR_FILE_OPEN;
	}

	RPosition home = racun;
	int flag = 0;
	char buffer[MAX_RED] = { 0 };
	RPosition pom = NULL;

	while (!feof(file)) {
		pom = 0;
		fscanf(file, " %s", buffer);
			pom = InsertRacunList(buffer, &flag);

		if (pom == NULL && flag == 1) {
			fclose(file);
			return ERROR_FILE_OPEN;
		}
		else if (pom == NULL && flag == 0) {
			fclose(file);
			return ERROR_ALLOCATION;
		}
		
		InsertSortRacun(racun, pom);
	}

	fclose(file);
	return EXIT_SUCCESS;

}

RPosition InsertRacunList(char* buffer, int* flag) {
	*flag = 0;
	
	FILE* file = NULL;
	file = fopen(buffer, "r");

	if (file == NULL) {
		printf("Greska u otvaranju filea InsertRacunList");
		*flag = 1;
		return ERROR_FILE_OPEN;
	}

	RPosition q = NULL;
	q = (RPosition)malloc(sizeof(Racun));

	if (q == NULL) {
		printf("Greska u alokaciji memorije q u InsertRacunList");
		fclose(file);
		return ERROR_ALLOCATION;
	}

	InicRacun(q);

	strcpy(q->name_receipt, buffer);
	char buffer2[MAX_RED] = { 0 };
	int number = 0;
	char* p_buffer2 = buffer2;

	while (!feof(file)) {
		APosition article = NULL;

		fgets(buffer2, MAX_RED, file);

		if (number == 0) {
			q->date = InsertDate(buffer2);
			if (q->date == NULL) {
				fclose(file);
				return NULL;
			}
			number++;
		}

		else {
			article = InsertArticle(buffer2);
			if (article == NULL) {
				fclose(file);
				return NULL;
			}

			InsertSortArticle(&q->article, article);
		}
	}

	fclose(file);
	return q;

}

int InicRacun(RPosition racun) {

	memset(racun->name_receipt, 0, MAX_NAME);
	racun->date = NULL;
	racun->Next = NULL;
	InicArticle(&racun->article);
	return EXIT_SUCCESS;

}

int InicArticle(APosition article) {

	article->price = 0;
	article->amount = 0;
	memset(article->name_article, 0, MAX_NAME);
	article->Next = NULL;

}

DPosition InsertDate(char* buffer) {
	
	char* p_buffer = buffer;
	DPosition q = NULL;
	q = (DPosition)malloc(sizeof(Date));

	if (q == NULL) {
		printf("Neuspjela alokacije memorije za InsertDatum");
		return ERROR_ALLOCATION;
	}

	sscanf(p_buffer, "%d - %d - %d", &q->year, &q->month, &q->day);

	return q;
}

APosition InsertArticle(char* buffer) {

	APosition article = NULL;
	article = (APosition)malloc(sizeof(Article));

	if (article == NULL) {
		printf("Neuspjela alokacija memorije u InsertArticle");
		return ERROR_ALLOCATION;
	}

	InicArticle(article);
	sscanf(buffer, "%s %f %f", article->name_article, &article->amount, &article->price);

	return article;
}

int InsertSortArticle(APosition Head, APosition article) {
	
	APosition p = Head;

	while (p->Next != NULL && strcmp(p->Next->name_article, article->name_article) < 0)
		p = p->Next;
	

	article->Next = p->Next;
	p->Next = article;
	return EXIT_SUCCESS;
}

int InsertSortRacun(RPosition racun, RPosition q) {
	
	RPosition p = racun;

	while (p->Next != NULL && DateCompare(p->Next->date, q->date) < 0) {
		p = p->Next;
	}
	q->Next = p->Next;
	p->Next = q;
	return EXIT_SUCCESS;

}

int DateCompare(DPosition date1, DPosition date2) {

	int temp = date1->year - date2->year;

	if (temp == 0) {

		temp = date1->month - date2->month;
		
		if (temp == 0) {
			temp = date1->day - date2->day;
		}
	}

	return temp;
}

int PrintRacun(RPosition p) {
	printf("\n");

	while (p != NULL) {

		printf("\tIme racuna: %s\n", p->name_receipt);
		printf("\tDatum: %d-%d-%d\n", p->date->year, p->date->month, p->date->day);
		printf("\tArtikli: ime\tkolicina\tcijena\n");
		PrintArticle(&p->article);
		printf("\n");
		p = p->Next;
	}
	return EXIT_SUCCESS;
}

int PrintArticle(APosition p) {
	p = p->Next;

	while (p != NULL) {
		printf("%*s", 22, p->name_article);
		printf("%*.2f ", 5, p->amount);
		printf("%*.2f ", 11, p->price);
		printf("\n");
		p = p->Next;
	}
	return EXIT_SUCCESS;
}

APosition FindArticle(APosition a, char* name_article) {

	APosition article = a;

	while (article != NULL) {
		if (strcmp(article->name_article, name_article) == 0) {
			return article;
		}
		article = article->Next;
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
		p ->Next = q->Next;
		free(q);
	}
	return EXIT_SUCCESS;
}