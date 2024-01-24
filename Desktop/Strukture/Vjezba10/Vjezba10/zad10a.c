#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define ERROR -1
#define MAX 100

struct _tree;
typedef _tree* Position;
typedef struct _tree
{
	char cityName[MAX];
	int population;
	Position left;
	Position right;
}tree;

struct _list;
typedef _list* ListPosition;
typedef struct _list
{
	char stateName[MAX];
	ListPosition Next;
	Position TreeP;
}list;

int ReadCountryFromFile(ListPosition, char*);
Position ReadCityFromFile(char*);
int InsertSortedCountries(ListPosition, ListPosition);
Position InsertSortedCities(Position, Position);
int cityCmp(Position, Position);
int InsertAfter(ListPosition, ListPosition);
int PrintList(ListPosition);
int PrintInOrder(Position);
ListPosition FindCountryByName(ListPosition, char*);
int PrintCitiesBiggerThan(Position, int);

int main()
{
	struct _list head;
	head.Next = NULL;
	ListPosition state = NULL;
	char filename[MAX] = { 0 }, name[MAX] = { 0 };
	int minPopulation = 0;
	printf("Insert filename > ");
	scanf("%s", filename);
	ReadCountryFromFile(&head, filename);
	PrintList(head.Next);

	printf("\nInsert name of a country > ");
	scanf("%s", name);
	state = FindCountryByName(&head, name);

	printf("%s", state->stateName);
	printf("\nInsert minimal population > ");
	scanf("%d", &minPopulation);
	PrintCitiesBiggerThan(state->TreeP, minPopulation);

	return EXIT_SUCCESS;
}

int ReadCountryFromFile(ListPosition P, char* filename)
{
	FILE* fp = NULL;
	char name[MAX] = { 0 }, file[MAX] = { 0 };
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		perror("Failed in file opening!\n");
		return ERROR;
	}
	while (!feof(fp))
	{
		fscanf(fp, "%s %s", name, file);
		ListPosition Q = NULL;
		Q = (ListPosition)malloc(sizeof(list));
		if (Q == NULL)
		{
			perror("Failed in dynamic allocation!\n");
			return ERROR;
		}
		strcpy(Q->stateName, name);
		Q->Next = NULL;
		Q->TreeP = NULL;

		InsertSortedCountries(P, Q);
		Q->TreeP = ReadCityFromFile(file);
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

int InsertSortedCountries(ListPosition P, ListPosition Q)
{
	ListPosition head = P;
	while (head->Next != NULL && strcmp(head->Next->stateName, Q->stateName) < 0)
		head = head->Next;

	InsertAfter(head, Q);
	return EXIT_SUCCESS;
}

int InsertAfter(ListPosition P, ListPosition Q)
{
	Q->Next = P->Next;
	P->Next = Q;
	return EXIT_SUCCESS;
}

int PrintList(ListPosition P)
{
	while (P != NULL)
	{
		printf("%s ", P->stateName);
		P = P->Next;
	}
	return EXIT_SUCCESS;
}

Position ReadCityFromFile(char* filename)
{
	Position root = NULL;
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
		Position Tree = NULL;
		Tree = (Position)malloc(sizeof(tree));
		strcpy(Tree->cityName, name);
		Tree->population = number;
		Tree->right = NULL;
		Tree->left = NULL;
		root = InsertSortedCities(root, Tree);
	}
	PrintInOrder(root);
	printf("\n");
	fclose(fp);
	return root;
}

Position InsertSortedCities(Position P, Position Q)
{
	int result = 0;
	if (P == NULL)
		return Q;
	result = cityCmp(P, Q);
	if (result > 0)
		P->left = InsertSortedCities(P->left, Q);
	else if (result < 0)
		P->right = InsertSortedCities(P->right, Q);
	else
	{
		free(Q);
	}
	//else free node

	return P;
}

int cityCmp(Position P, Position Q)
{
	int result = 0;
	result = P->population - Q->population;
	if (result == 0)
		result = strcmp(P->cityName, Q->cityName);
	return result;
}

int PrintInOrder(Position P)
{
	if (P == NULL)
		return EXIT_SUCCESS;
	PrintInOrder(P->left);
	printf("%s %d\t", P->cityName, P->population);
	PrintInOrder(P->right);
	return EXIT_SUCCESS;
}

ListPosition FindCountryByName(ListPosition P, char* name)
{
	ListPosition head = P;
	while (head->Next != NULL)
	{
		if (strcmp(head->stateName, name) == 0)
			return head;
		head = head->Next;
	}
	return NULL;
}

int PrintCitiesBiggerThan(Position P, int minPopulation)
{
	if (P == NULL)
		return EXIT_SUCCESS;
	PrintCitiesBiggerThan(P->left, minPopulation);
	if (P->population > minPopulation)
		printf("%s %d", P->cityName, P->population);
	PrintCitiesBiggerThan(P->right, minPopulation);
	return EXIT_SUCCESS;
}