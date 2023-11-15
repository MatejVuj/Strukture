#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
#define ERROR -1
#define SUCCESS 0
#define MAX_FILE_NAME 256

struct stog;
typedef struct stog* Position;
typedef struct stog {

	float el;
	Position Next;

}stog;

int Pop(Position);
int Push(Position, float);
int InsertAfter(Position, Position);
int CalculatePostfix(Position, float*);

int main() {

	float a = 0.0f;

	stog Head;
	Head.el = 0.0f;
	Head.Next = NULL;

	CalculatePostfix(&Head, &a);

	printf("%f", a);

	free(Head.Next);

	return SUCCESS;
}

int CalculatePostfix(Position Head, float* r) {

	int n = 0;
	int pom = 0;

	float first = 0.0f, second = 0.0f, result = 0.0f;

	char fname[MAX_FILE_NAME] = {"postfix.txt"};
	char buffer[MAX] = { 0 };
	char* p_buffer = buffer;

	Head = (Position)malloc(sizeof(stog));

	if (Head == NULL) {
		printf("Nije se alociralo");
		return ERROR;
	}

	Head->Next = NULL;
	
	FILE* f = NULL;
	f = fopen("postfix.txt", "r");

	if (f == NULL) {
		printf("Nije otvorilo datoteku");
		return ERROR;
	}

	fgets(p_buffer, MAX, f);

	while (strlen(p_buffer) != 0) {
	
		int br = 0;
		pom = sscanf(p_buffer, "%d %n ", &br, &n);

		if (pom == 1) {
			Push(Head, br);
			p_buffer += n;
			printf("%d", br);
		}

		else {
		
			char c = ' ';
			if (sscanf(p_buffer, "%c %n", &c, &n) == 1) 
				switch (c) {

				case '+':
				{
					first = Pop(Head);
					second = Pop(Head);
					result = first + second;
					Push(Head, result);
					break;
				}

				case '-':
				{
					first = Pop(Head);
					second = Pop(Head);
					result = second - first;
					Push(Head, result);
					break;
				}

				case '*':
				{
					first = Pop(Head);
					second = Pop(Head);
					result = (first) * (second);
					Push(Head, result);
					break;
				}

				case ':':
				{
					first = Pop(Head);
					second = Pop(Head);
					result = second / first;

					if (first == 0) {
						printf("Ne moze se dijelit sa 0");
						return ERROR;
					}

					Push(Head, result);
					break;
				}

				default:
					printf("Ne moze");
					break;

				}

			

			p_buffer += n;
			printf("%c ", c);

		}

	}

	fclose(f);
	*r = Pop(Head);
	return SUCCESS;


}

int InsertAfter(Position p, Position q) {

	q->Next = p->Next;
	p->Next = q;

	return SUCCESS;

}

int Push(Position p, float new) {

	Position q = NULL;

	q = (Position)malloc(sizeof(stog));

	if (q == NULL) {
		printf("Nesupjesna alokacija");
		return ERROR;
	}

	q->el = new;
	InsertAfter(p, q);
	return SUCCESS;

}

int Pop(Position p) {

	if (p->Next == NULL) {
		printf("Nema nista u stogu");
		return ERROR;
	}

	else {
	
		float a = 0.0f;
		Position temp = NULL;
		
		temp = p->Next;
		a = temp->el;
		p->Next = temp->Next;

		free(temp);

		return a;

	}

}

