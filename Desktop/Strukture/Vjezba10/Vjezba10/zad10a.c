#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 50
#define MAX_LINE 256
#define EXIT_SUCCESS 0
#define ERROR_ALLOCATION -1
#define ERROR_FILE -2

struct Lista_drzave;
typedef struct Lista_drzave* Position;
struct Lista_drzave {

	char name_country;
	Position Next;

}List;

struct node;
typedef struct node* SPosition;
typedef struct node {

	char name_city;
	int population;

	SPosition Left;
	SPosition Right;
	SPosition Next;

}Node;

int ReadFile(Position, char*);

int InicList(Position);

int InsertSortList(Position, Position);
Position InsertList(char*, int*);


int main() {

	Position head;


	return 0;
}

int ReadFile(Position drzava, char* file_name) {
	
	FILE* fp = NULL;
	fp = fopen(file_name, "r");

	if (fp == NULL) {
		printf("\n\tPostovani %s datoteka ne postoji\n", file_name);
		return ERROR_FILE;
	}

	Position head = drzava;
	Position pom = NULL;
	int flag = 0;
	char buffer[MAX_LINE] = { 0 };

	while (!feof(fp)) {
		pom = 0;
		fscanf(fp, " %s", buffer);
		pom = InsertList(buffer, &flag);

		if (pom == NULL && flag == 1) {
			fclose(fp);
			return ERROR_ALLOCATION;
		}
		else if (pom == NULL && flag == 0) {
			fclose(fp);
			return ERROR_ALLOCATION;
		}
		
		InsertSortList(drzava, pom);

	}

	fclose(fp);
	return EXIT_SUCCESS;
}