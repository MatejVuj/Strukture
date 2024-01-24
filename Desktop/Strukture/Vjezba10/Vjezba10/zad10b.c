#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define ERROR -1
#define MAX 100

struct _list;
typedef struct _list* ListPosition;
typedef struct _list
{
	char cityName[MAX];
	int population;
	ListPosition Next;
}list;

struct _tree;
typedef struct _tree* Position;
typedef struct _tree
{
	char stateName[MAX];
	Position right;
	Position left;
	ListPosition ListP;
}tree;


int PrintInOrder(Position);
int PrintList(ListPosition);
int DeleteAll(Position);
int PrintBiggerThan(ListPosition, int);
int CountriesCompare(Position, Position);
int CityCompare(ListPosition, ListPosition);
int InsertAfter(ListPosition, ListPosition);
int InsertSortedCities(ListPosition, ListPosition);
Position ReadCountriesFromFile(Position, char*);
Position FindCountryByName(Position, char*);
Position InsertCountriesSorted(Position P, Position Q);
ListPosition MakeNew(char*, int);
ListPosition ReadCitiesFromFile(char*);


int main()
{
	Position root = NULL;
	Position newroot = NULL;
	struct _list head;
	head.Next = 0;
	int minpopulation = 0;
	char filename[MAX] = { 0 }, wantedcountry[MAX] = { 0 };
	printf("Insert filename > ");
	scanf("%s", filename);
	root = ReadCountriesFromFile(root, filename);
	PrintInOrder(root);

	printf("\nInsert name of a country > ");
	scanf("%s", wantedcountry);
	newroot = FindCountryByName(root, wantedcountry);
	printf("%s", newroot->stateName);

	printf("\nInsert minimal population > ");
	scanf("%d", &minpopulation);
	PrintBiggerThan(newroot->ListP, minpopulation);

	deleteAll(root);
	deleteAll(newroot);
	return EXIT_SUCCESS;
}

Position ReadCountriesFromFile(Position P, char* filename)
{
	FILE* fp = NULL;
	char countryname[MAX] = { 0 }, cityfile[MAX] = { 0 };
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		perror("Failed in file opening!\n");
		return NULL;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%s %s", countryname, cityfile);
		Position Q = NULL;
		Q = (Position)malloc(sizeof(tree));
		if (Q == NULL)
		{
			perror("Failed in dynamic allocation!\n");
			return NULL;
		}
		strcpy(Q->stateName, countryname);
		Q->left = NULL;
		Q->right = NULL;
		//Q->ListP = NULL;
		Q->ListP = ReadCitiesFromFile(cityfile);
		P = InsertCountriesSorted(P, Q);
	}
	fclose(fp);
	return P;
}

Position InsertCountriesSorted(Position P, Position Q)
{
	int result = 0;
	if (P == NULL)
		return Q;
	result = CountriesCompare(P, Q);
	if (result > 0)
		P->left = InsertCountriesSorted(P->left, Q);
	else
		P->right = InsertCountriesSorted(P->right, Q);
	return P;
}

int CountriesCompare(Position P, Position Q)
{
	int result = 0;
	result = strcmp(P->stateName, Q->stateName);
	return result;
}

int PrintInOrder(Position P)
{
	if (P == NULL)
		return EXIT_SUCCESS;
	PrintInOrder(P->left);
	printf("%s ", P->stateName);
	PrintInOrder(P->right);
	return EXIT_SUCCESS;
}

ListPosition ReadCitiesFromFile(char* filename)
{
	struct _list head;
	head.Next = NULL;
	FILE* fp = NULL;
	char name[MAX] = { 0 };
	int number = 0;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		perror("Failed in file opening!\n");
		return NULL;
	}
	while (!feof(fp))
	{
		fscanf(fp, "%s %d", name, &number);
		ListPosition Q = NULL;
		Q = MakeNew(name, number);
		InsertSortedCities(&head, Q);
		printf(" %s ", head.Next->cityName);
	}
	//PrintList(&head);
	fclose(fp);
	return head.Next;
}

ListPosition MakeNew(char* name, int number)
{
	ListPosition Q = NULL;
	Q = (ListPosition)malloc(sizeof(list));
	if (Q == NULL)
	{
		perror("Failed in dynamic allocation!\n");
		return NULL;
	}
	strcpy(Q->cityName, name);
	Q->population = number;
	Q->Next = NULL;
	return Q;
}

int InsertSortedCities(ListPosition P, ListPosition Q)
{
	ListPosition head = P;
	if (head == NULL)
		return EXIT_SUCCESS; //VAZNO !!
	int result = 0;
	result = CityCompare(P, Q);
	while (head->Next != NULL && result > 0)
		head = head->Next;

	InsertAfter(head, Q);
	return EXIT_SUCCESS;
}

int CityCompare(ListPosition P, ListPosition Q)
{
	int result = 0;
	result = P->population - Q->population;
	if (result == 0)
		result = strcmp(P->Next->cityName, Q->cityName);
	return result;
}

int InsertAfter(ListPosition P, ListPosition Q)
{
	Q->Next = P->Next;
	P->Next = Q;
	return EXIT_SUCCESS;
}

int PrintList(ListPosition P)
{
	if (P->Next == NULL)
	{
		perror("The list is empty!\n");
		return ERROR;
	}
	while (P->Next != NULL)
	{
		printf(" %s ", P->Next->cityName);
		P = P->Next;
	}
	return EXIT_SUCCESS;
}

Position FindCountryByName(Position current, char* name)
{
	if (current == NULL)
		return NULL;
	if (strcmp(current->stateName, name) == 0)
		return current;
	else if (strcmp(current->stateName, name) > 0)
		current->left = FindCountryByName(current->left, name);
	else if (strcmp(current->stateName, name) < 0)
		current->right = FindCountryByName(current->right, name);
}

int PrintBiggerThan(ListPosition P, int x)
{
	printf("Cities with population bigger than %d are:\n", x);
	if (P->Next == NULL)
	{
		perror("The list is empty!\n");
		return ERROR;
	}
	while (P->Next != NULL)
	{
		if (P->Next->population > x)
			printf(" %s ", P->Next->cityName);
		P = P->Next;
	}
	return EXIT_SUCCESS;
}

int DeleteAll(Position P)
{
	if (P == NULL)
		return EXIT_SUCCESS;
	DeleteAll(P->left);
	DeleteAll(P->right);
	free(P);
	return EXIT_SUCCESS;
}