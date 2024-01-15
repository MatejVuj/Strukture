//Zadatak za oslobađanje praktičnog dijela ispita :
//
//"BookHaven" je knjižnica koja želi unaprijediti svoj sustav praćenja knjiga, autora i korisnika.
//Svaka knjiga ima informacije o naslovu, autoru, godini izdanja i dostupnim primjercima.
//Korisnici mogu posuđivati knjige i vratiti ih nakon nekog vremena.
//
//Program mora korisniku omogućiti :
//a) ispis svih knjiga abecedno(tako da se mogu vidjeti svi podatci o knjizi i korisnici koji trenutno posuđuju knjigu)
//b) ispis svih korisnika abecedno(tako da se mogu vidjeti sve knjige koje je neki korisnik posudio)
//c) pretraživanje knjiga po godini izdanja(tako da se mogu vidjeti sve knjige iz te godine i njihova količina)
//d) pretraživanje knjiga po nazivu autora(tako da se mogu vidjeti sve knjige tog autora i njihova količina)
//e) unos novog korisnika
//f) posudba knjige korisniku
//- može više primjeraka iste knjige posuditi od puta
//- korisnik u sebe nikad ne smije imati više od 5 knjiga sve skupa
//- ako pokušava napravit posudbu koja će ga dovesti preko tog broja program treba upozoriti korisnika na to i ispisati mu broj koliko još knjiga posudit
//- ako korisnik pita za više primjeraka knjige, a knjižnica na stanju nema nema dovoljno treba korisniku omogućiti izbor hoće li posudit to što ima ili ne.
//g) povratak knjiga na stanje
//h) spremi(u datoteku / datoteke spremiti trenutno stanje u knjižnici, tako da kad se idući put pokrene program moguće nastaviti od spremljenog stanja)
//
//Sami odaberite strukturu podataka i format datoteka koju će te koristiti za ovo izvesti.

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_ALLOCATION (-2)
#define ERROR_FILE_OPEN (-1)
#define MAX_LENGHT (256)
#define MAX_BOOKS (80)

// Struktura za informacije o knjizi
struct book;
typedef struct book* BPosition;

// Struktura za informacije o korisniku
struct user;
typedef struct user* UPosition;
struct user {
    char name[100];
    int borrowedBooksCount;
    BPosition borrowedBooks; // Korisnik može posuditi do 5 knjiga
    UPosition Next;
} User;

// Struktura za informacije o knjizi
struct book{
    char title[100];
    char author[100];
    int year;
    int copies;
    UPosition Users;
    BPosition Next;
} Book;

int menu(int);
// Funkcija za ispis knjiga abecedno
void print_books_alphabetically(BPosition head);

// Funkcija za dodavanje knjige u listu
BPosition add_book(BPosition* head, char title[100], char author[100], int year, int copies);

// Funkcija za dodavanje korisnika u listu
UPosition add_user(UPosition* head, char name[100]);

// Funkcija za učitavanje podataka o knjigama iz datoteke
BPosition load_books(BPosition* head, char filename[100]);

// Funkcija za učitavanje podataka o korisnicima iz datoteke
UPosition load_users(UPosition* head, char filename[100]);

BPosition print_books_and_borrowers(BPosition head);

BPosition insert_book_sorted(BPosition* head, BPosition new_book);

int borrow_book(BPosition books, UPosition users);//, char username[100], char title[100]);
BPosition find_book_by_title(BPosition head, char title[100]);
UPosition find_user(UPosition head, char name[100]);

int main() {
    // Inicijalizirati potrebne varijable i alocirati memoriju prema potrebi
    // Implementirati glavnu petlju programa s odgovarajućim opcijama za korisnika
    BPosition books = NULL;
    UPosition users = NULL;
    int insert = 0, choise = 0, numBooks = 0;
    char* file_name = { 0 };
    
    while(choise != 9) {
    
        choise = menu(insert);
        switch (choise) {

        case 1:
            load_books(&books,"books.txt");
            break;

        case 2:
            load_users(&users,"users.txt");
            break;

        case 3:
            print_books_and_borrowers(books);
            break;

        case 4:
            //printf("");
            borrow_book(books, users, "Alice", "1984");
            borrow_book(books, users, "Alice", "The_Catcher_in_the_Rye");
            borrow_book(books, users, "Alice", "To_Kill_a_Mockingbird");
            borrow_book(books, users, "Alice", "The_Lord_of_the_Rings");
            borrow_book(books, users, "Alice", "The_Harry_Potter_series");
            break;

        case 5:
            borrow_book(books, users, "Bob", "1984");
            break;

        case 6:
            borrow_book(books, users, "Charlie", "1984");
            break;

        case 7:
            borrow_book(books, users, "Alice", "The_Chronicles_of_Narnia");
            break;

        }

    }
    return 0;
}

int menu(int choise) {
    printf("\n\t*****IZBORNIK*****\t");
    printf("\n\t '1' -> Load books from file\t");
    printf("\n\t '2' -> Load users from file\t");
    printf("\n\t '3' -> Print books abc\t");
    printf("\n\t '4' -> Borrow book \t");
    printf("\n\t '5' -> dodavanje boba za 1984\t");
    printf("\n\t '6' -> dodavanje Charlia za 1984, ali on ne bi smia posudit\t");
    printf("\n\t '7' -> dodavanje Alice opet, ali ne bi smila posudit jer ima vec pet knjiga\t");
    printf("\n\t '8' ->\t");

    printf("\n\tNaredba:\t");
    scanf("%d", &choise);

    return choise;
}

UPosition add_user(UPosition head, char name[100], int borrowedBooksCount) {
    UPosition new_user = (UPosition)malloc(sizeof(struct user));
    if (new_user == NULL) {
        perror("Error allocation add_user");
        exit(EXIT_FAILURE);
    }
    strcpy(new_user->name, name);
    new_user->borrowedBooksCount = borrowedBooksCount;
    new_user->borrowedBooks = NULL;
    new_user->Next = head;

    head = new_user;
}

BPosition add_book(BPosition* head, char title[100], char author[100], int year, int copies) {
    BPosition new_book = (BPosition)malloc(sizeof(struct book));
    if (new_book == NULL) {
        perror("Error allocation add_book");
        exit(EXIT_FAILURE);
    }
    strcpy(new_book->title, title);
    strcpy(new_book->author, author);
    new_book->year = year;
    new_book->copies = copies;
    new_book->Users = NULL;
    new_book->Next = *head;

    *head = new_book;
}

BPosition load_books(BPosition* head, char filename[100]) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char title[100], author[100];
        int year, copies;
        if (sscanf(line, "%99[^,],%99[^,],%d,%d", title, author, &year, &copies) == 4) {
            add_book(head, title, author, year, copies);
        }
    }

    fclose(file);
}

UPosition load_users(UPosition* head, char filename[100]) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    int borrowedBooksCount = 0;
    while (fgets(line, sizeof(line), file)) {
        char name[100];
        if (sscanf(line, "%s,%d", name, borrowedBooksCount) == 2) {
            add_user(head, name, borrowedBooksCount);
        }
    }

    fclose(file);
}

// Funkcija za sortiranje knjiga abecedno
BPosition sort_books_alphabetically(BPosition head) {
    BPosition sorted_books = NULL;

    while (head != NULL) {
        BPosition current_book = head;
        head = head->Next;

        // Umetanje knjige na odgovarajuće mjesto u sortiranu listu
        insert_book_sorted(&sorted_books, current_book);
    }

    return sorted_books;
}

// Funkcija za ispis svih knjiga abecedno s informacijama o knjizi i korisnicima
BPosition print_books_and_borrowers(BPosition head) {
    // Sortiranje knjiga abecedno
    BPosition sorted_books = sort_books_alphabetically(head);

    // Ispis svih knjiga i informacija o korisnicima koji posuđuju knjigu
    printf("\nSve knjige abecedno:\n");
    while (sorted_books != NULL) {
        printf("\nTitle: %s, Author: %s, Year: %d, Copies: %d\n", sorted_books->title, sorted_books->author, sorted_books->year, sorted_books->copies);

        // Ispis korisnika koji posuđuju knjigu
        UPosition borrowers = sorted_books->Users;
        if (borrowers != NULL) {
            printf("  Borrowed by:\n");
            while (borrowers != NULL) {
                printf("    - %s\n", borrowers->name);
                borrowers = borrowers->Next;
            }
        }
        else {
            printf("  Currently not borrowed.\n");
        }

        printf("\n");

        sorted_books = sorted_books->Next;
    }
}

// Funkcija za umetanje knjige u sortiranu listu abecedno
BPosition insert_book_sorted(BPosition* head, BPosition new_book) {
    BPosition previous = NULL;
    BPosition current = *head;

    // Pronalaženje pravog mjesta za umetanje knjige
    while (current != NULL && strcmp(current->title, new_book->title) < 0) {
        previous = current;
        current = current->Next;
    }

    // Ažuriranje pokazivača
    if (previous == NULL) {
        new_book->Next = *head;
        *head = new_book;
    }
    else {
        new_book->Next = current;
        previous->Next = new_book;
    }
}

// Funkcija za posudjivanje korisnika
int borrow_book(BPosition books, UPosition users, const char* userName, const char* bookTitle) {
    // Find the book by title
    BPosition selected_book = find_book_by_title(books, bookTitle);

    if (selected_book == NULL) {
        printf("Book not found.\n");
        return 0;
    }

    // Find the user by name
    UPosition selected_user = find_user(users, userName);

    if (selected_user == NULL) {
        printf("User not found.\n");
        return 0;
    }

    if (selected_book->copies > 0 && books_borrowed_count(selected_user) <= 5) {
        // Book is available and user can borrow it
        selected_book->copies--;

        UPosition new_borrower = (UPosition)malloc(sizeof(User));
        strcpy(new_borrower->name, selected_user->name);
        new_borrower->Next = selected_book->Users;
        selected_book->Users = new_borrower;

        BPosition new_borrowed_book = (BPosition)malloc(sizeof(Book));
        strcpy(new_borrowed_book->title, selected_book->title);
        strcpy(new_borrowed_book->author, selected_book->author);
        new_borrowed_book->year = selected_book->year;
        new_borrowed_book->copies = 1;
        new_borrowed_book->Next = selected_user->borrowedBooks;
        selected_user->borrowedBooks = new_borrowed_book;

        printf("Book borrowed successfully.\n");
        return 1;
    }
    else {
        // Book not available or user has borrowed too many books
        printf("Failed to borrow the book.\n");
        return 0;
    }
}

// Funkcija za pronalaženje knjige po naslovu
BPosition find_book_by_title(BPosition head, const char* title) {
    BPosition current_book = head;
    while (current_book != NULL) {
        if (strcmp(current_book->title, title) == 0) {
            return current_book;
        }
        current_book = current_book->Next;
    }
    return NULL;
}

// funkcija za pronalaženje korisnika
UPosition find_user(UPosition head, const char* name) {
    UPosition current_user = head;
    while (current_user != NULL) {
        if (strcmp(current_user->name, name) == 0) {
            return current_user;
        }
        current_user = current_user->Next;
    }

    // User not found, add a new user
    return add_user(&head, name, 1);
}

int books_borrowed_count(UPosition user) {
    int count = 0;
    UPosition current_book = user->borrowedBooks;
    while (current_book != NULL) {
        count++;
        current_book = current_book->Next;
    }
    return count;
}