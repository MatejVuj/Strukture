
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
 #include <string.h>

#define MAX_LENGHT 30
#define ERROR_FILE_OPEN -1
#define MAX_BROJ_BODOVA 100

typedef struct {

	char ime[MAX_LENGHT];
	char prezime[MAX_LENGHT];
	int bodovi;

}Student;

int NoRows(FILE*);
int Unos_studenata(int, Student*);
int Ispis_studenata(int, Student*);
int Pronadji_MAX(int, int ,Student*);


int NoRows(FILE* file) {

	int NoRows = 0;
	char c;
	

	file = fopen("Text1.txt", "r");
	

	if (file) {
		while ((c = getc(file)) != EOF) {
			if (c == '\n') {
				NoRows++;
			}
		}
		fclose(file);
		return NoRows + 1;
	}
	
	else {
		return ERROR_FILE_OPEN;
	}
	
}

int Unos_studenata(int broj_studenata, Student* student) {

	int i = 0;

	FILE* file;
	file = fopen("Text1.txt", "r");

	if (file == NULL)
		return ERROR_FILE_OPEN;

	else {

		while (!feof(file) /* == 0 && i < norows*/) {
			//for (i = 0; i < norows; i++) {
			fscanf(file, " %s %s %d", (student + i)->ime, (student + i)->prezime, &(student + i)->bodovi);

			i++;
		}

		if (feof(file) == 0)
			printf("Nije procitano do kraja");
	}


	fclose(file);

	return 0;
}

int Pronadji_MAX(int broj_studenata, Student* s) {
	int i=0;
	int max = 0;

	for (i = 0; i < broj_studenata; i++) {
		if ((s + i)->bodovi > (s + i - 1)->bodovi)
			max = (s + i)->bodovi;
	}
	//printf("\n");
	//printf(" %d", max);

	return max;
}

int Ispis_studenata(int borj_studenata, int max_bodovi, Student* student) {

	int i = 0;

	for (i = 0; i < borj_studenata; i++) {
		printf("Student: %s\t %s\t Bodovi: %d, %f\n", (student + i)->ime, (student + i)->prezime, (student + i)->bodovi, ((float)(student + i)->bodovi / max_bodovi) * 100);
	}

	return 0;
}

int main() {

	int broj_linija = 0;
	
	broj_linija = NoRows("Text1.txt");

	printf("%d \n", broj_linija);

	int unos = 0, ispis =0;
	int i = 0;
	int norows = 0;
	int max_bodovi = 0;
	Student* student = NULL;

	norows = NoRows("Text1.txt");

	student = (Student*)malloc(norows * sizeof(Student));

	unos = Unos_studenata(norows, student);

	max_bodovi = Pronadji_MAX(norows, student);

	ispis = Ispis_studenata(norows, max_bodovi, student);

	free(student);

	return 0;
}