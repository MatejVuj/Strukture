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
    int maxBorrowedBooks;
    BPosition borrowedBooks; // Korisnik moze posuditi do 5 knjiga
    UPosition Next;
} User;

// Struktura za informacije o knjizi
struct book {
    char title[100];
    char author[100];
    int year;
    int copies;
    UPosition Users;
    BPosition Next;
} Book;

int menu(int);

// Funkcija za dodavanje knjige u listu
BPosition add_book(BPosition* head, char title[100], char author[100], int year, int copies);

// Funkcija za dodavanje korisnika u listu
UPosition add_user(UPosition* head, char name[100], int borrowedBooksCount, int maxBorrowedBooks);

// Funkcija za slanje knjiga u insert sort
BPosition sort_books_alphabetically(BPosition head);

// Funkcija za učitavanje podataka o knjigama iz datoteke
BPosition load_books(BPosition* head, char filename[100]);

// Funkcija za učitavanje podataka o korisnicima iz datoteke
UPosition load_users(BPosition books, UPosition users, char filename[100]);

// Funkcija za printanje knjiga abecedno
BPosition print_books_and_borrowers(BPosition head);

// Insert sort 
BPosition insert_book_sorted(BPosition* head, BPosition new_book);

// Funkcija za borrowanje knjiga userima 
int borrow_book(BPosition books, UPosition users, const char* username[100], const char* title[100]);

// Funkcija za racunanje koliko je user posudia knjiga
int books_borrowed_count(UPosition user);

// Funkcija za pronalazenje knjiga po nazivu
BPosition find_book_by_title(BPosition head, const char title[100]);

// Funkcija za pronalazenje usera u listi
UPosition find_user(UPosition head, const char name[100]);

// Funckija za pretrazivanje knjiga po godini
BPosition search_books_by_year(BPosition head);

// Funkcija za pretrazivanje knjiga po autoru
BPosition search_books_by_author(BPosition head);

// SVE FUNCKIJE ZA ISPIS SVIH USERA ABECEDNO

// funkcija za ispis usera abecedno
UPosition print_users_alphabetically(UPosition head);

// Funkcija za sortiranje usera 
UPosition sort_users_alphabetically(UPosition head);

// Funkcija za Inser sort usera
UPosition insert_user_sorted(UPosition* head, UPosition new_user);

// Funkcija za vracanje knjiga u sistem
int return_book(BPosition books, UPosition users, const char* userName, const char* bookTitle);

// Funkcija za omogucavanje posudbe knjiga useru f)
int ask_user(BPosition books, UPosition users);

// Funkcije za azuriranje fileova
int save_books(BPosition head, const char* filename);

int save_users(UPosition head, const char* filename);

int main() {
    BPosition books = NULL;
    UPosition users = NULL;
 
    int insert = 0, choise = 0;
    char name[100] = { 0 };
    char title[100] = { 0 };

    // Ucitavanje knjiga iz datoeke
    books = load_books(&books, "books.txt");

    // Ucitavanje usera iz datoteke
    load_users(books, &users, "users_borrow.txt");

    while (choise != 100) {

        choise = menu(insert);
        switch (choise) {

        case 1:
            books = print_books_and_borrowers(books);

            break;
        case 2:
            users = print_users_alphabetically(users);
            break;

        case 3:
            search_books_by_year(books);

            break;

        case 4:
            search_books_by_author(books);
            break;

        case 5:
            printf("\n\tInsert name of user:\t");
            scanf(" %s", name);

            add_user(&users, name, 0, 5);
            break;

        case 6:
            ask_user(books, &users);
            break;

        case 7:
            printf("\n\tInsert name of user:\t");
            scanf(" %s", name);
            printf("\n\tInsert title of book:\t");
            scanf(" %s", title);
            return_book(books, &users, name, title);
            break;

        case 8:
            save_books(books, "books.txt");
            save_users(users, "users_borrow.txt");
            printf("\tAll saved successfully");
            break;

        case 9:
            return "exit";
            break;

        default:
            printf("That choise does not exist");
        }

    }
    return 0;
}

int menu(int choise) {
    printf("\n\t*****IZBORNIK*****\t");
    printf("\n\t '1' -> Print books abc\t");
    printf("\n\t '2' -> Print users abc\t");
    printf("\n\t '3' -> Search books by year\t");
    printf("\n\t '4' -> Search books by author\t");
    printf("\n\t '5' -> Add User\t");
    printf("\n\t '6' -> Borrow book\t");
    printf("\n\t '7' -> Return book\t");
    printf("\n\t '8' -> Save");
    printf("\n\t '9' -> Exit");

    printf("\n\tNaredba:\t");
    scanf("%d", &choise);

    return choise;
}

UPosition add_user(UPosition* head, char name[100], int borrowedBooksCount, int maxBorrowedBooks) {
    UPosition new_user = (UPosition)malloc(sizeof(struct user));
    if (new_user == NULL) {
        perror("Error allocation add_user");
        exit(EXIT_FAILURE);
    }
    strcpy(new_user->name, name);
    new_user->borrowedBooksCount = borrowedBooksCount;
    new_user->maxBorrowedBooks = maxBorrowedBooks;
    new_user->borrowedBooks = NULL;

    new_user->Next = *head;
    *head = new_user;

    return *head;
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

    return new_book;
}

BPosition load_books(BPosition* head, char filename[100]) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[256] = {0};
    while (fgets(line, sizeof(line), file)) {
        char title[100] = { 0 }, author[100] = { 0 };
        int year = 0, copies = 0;
        if (sscanf(line, "%99[^,],%99[^,],%d,%d", title, author, &year, &copies) == 4) {
            add_book(head, title, author, year, copies);
        }
    }

    fclose(file);
    return *head;
}

UPosition load_users(BPosition books, UPosition users, char filename[100]) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char name[100], bookTitle[100];
        if (sscanf(line, "%99[^,],%99[^\n]", name, bookTitle) == 2) {
            borrow_book(books, users, name, bookTitle);
        }
    }

    fclose(file);
    return users;
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

    // Varijabla koja vraca prvoga u listi
    BPosition first = sorted_books;
    
    // Ispis svih knjiga i informacija o korisnicima koji posudjuju knjigu
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
    return first;
}

// Funkcija za umetanje knjige u sortiranu listu abecedno
BPosition insert_book_sorted(BPosition* head, BPosition new_book) {
    BPosition previous = NULL;
    BPosition current = *head;

    // Pronalazenje pravog mjesta za umetanje knjige
    while (current != NULL && strcmp(current->title, new_book->title) < 0) {
        previous = current;
        current = current->Next;
    }

    // Azuriranje pokazivaca
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
    // Pronalazenje knjige po naslovu
    BPosition selected_book = find_book_by_title(books, bookTitle);

    if (selected_book == NULL) {
        printf("\tBook not found.\n");
        return EXIT_FAILURE;
    }

    // Pronalazenje usera po imenu
    UPosition selected_user = find_user(users, userName);

    if (selected_user == NULL) {
        printf("\tUser not found.\n");
        return EXIT_FAILURE;
    }

    if (selected_book->copies > 0 && books_borrowed_count(selected_user) < selected_user->maxBorrowedBooks) {
        // Kada je knjigu moguce posuditi i user nema vise od 4 posudjene knjige 
        selected_book->copies--;

        UPosition new_borrower = (UPosition)malloc(sizeof(User));
        if (new_borrower == NULL) {
            printf("\tAllocation Error.\n");
            return EXIT_FAILURE;
        }

        // Azuriranje
        strcpy(new_borrower->name, selected_user->name);
        new_borrower->Next = selected_book->Users;
        selected_book->Users = new_borrower;

        BPosition new_borrowed_book = (BPosition)malloc(sizeof(Book));
        if (new_borrowed_book == NULL) {
            printf("\tAllocation Error.\n");
            return EXIT_FAILURE;
        }

        // Azuriranje
        strcpy(new_borrowed_book->title, selected_book->title);
        strcpy(new_borrowed_book->author, selected_book->author);
        new_borrowed_book->year = selected_book->year;
        new_borrowed_book->copies = 1;

        // Azuriranje pokazivaca
        new_borrowed_book->Next = selected_user->borrowedBooks;
        selected_user->borrowedBooks = new_borrowed_book;

        // Povećaj broj posudjenih knjiga za korisnika
        selected_user->borrowedBooksCount++;

        printf("\tBook borrowed successfully.\n");
        return 1;
    }
    else {
        // Book not available or user has borrowed too many books
        printf("\tFailed to borrow the book.\n");
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
UPosition find_user(UPosition *head, const char* name) {
    UPosition current_user = *head;
    UPosition previous_user = NULL;

     // Pronadji usera po imenu
    while (current_user != NULL) {
        if (strcmp(current_user->name, name) == 0) {
            return current_user;
        }

        previous_user = current_user;
        current_user = current_user->Next;
    }

    // User nije pronadjen, stvori novog usera
    UPosition new_user = (UPosition)malloc(sizeof(struct user));
    if (new_user == NULL) {
        perror("\tError allocation find_user");
        exit(EXIT_FAILURE);
    }

    // Azuriranje
    strcpy(new_user->name, name);
    new_user->borrowedBooksCount = 0;
    new_user->maxBorrowedBooks = 5;
    new_user->borrowedBooks = NULL;
    new_user->Next = NULL;

    // Azuriranje pokazivaca
    if (previous_user == NULL) {
        // Novi user je na pocetku liste
        *head = new_user;
    }
    else {
        // Novi user na kraj liste
        previous_user->Next = new_user;
    }

    return new_user;
}

// Funkcija za pregled koliko knjiga je user posudia
int books_borrowed_count(UPosition user) {
    int count = 0;
    BPosition current_book = user->borrowedBooks;

    while (current_book != NULL && count < user->maxBorrowedBooks) {
        count += current_book->copies;
        current_book = current_book->Next;
    }

    return count;
}

// Pretrazi knjige po godini izdanja
BPosition search_books_by_year(BPosition head) {
    BPosition first = head;
    int year = 0;

    printf("\n\tEnter the year: \t");
    scanf("%d", &year);

    printf("\n\tBooks published in %d:\n", year);

    // Ispis svih knjiga sa tom godinom izdanja
    while (head != NULL) {
        if (head->year == year) {
            printf("\tTitle: %s, Author: %s, Copies: %d\n", head->title, head->author, head->copies);
        }
        head = head->Next;
    }
    return first;
}

// Pretrazi knjige po autoru
BPosition search_books_by_author(BPosition head) {
    BPosition first = head;
    char author[100] = { 0 };

    printf("\n\tEnter the author's name: \t");
    scanf("%s", author);

    BPosition current = head;  // Koristi lokalni pokazivač

    printf("\n\tBooks by %s:\n", author);

    while (current != NULL) {
        if (strcmp(current->author, author) == 0) {
            printf("\tTitle: %s, Year: %d, Copies: %d\n", current->title, current->year, current->copies);
        }
        current = current->Next;
    }
    return first;
}

// Funkcija za ispis svih korisnika abecedno s informacijama o posudjenim knjigama
UPosition print_users_alphabetically(UPosition head) {
    // Sortiranje korisnika abecedno
    UPosition sorted_users = sort_users_alphabetically(head);
    // Postavljanje varijable na prvu u listi
    UPosition first = sorted_users;

    printf("\nSvi korisnici abecedno:\n");
    while (sorted_users != NULL) {
        printf("\nUser: %s, Borrowed Books: %d\n", sorted_users->name, books_borrowed_count(sorted_users));

        // Ispis knjiga koje je korisnik posudio
        BPosition borrowed_books = sorted_users->borrowedBooks;
        if (borrowed_books != NULL) {
            printf("  Borrowed Books:\n");
            while (borrowed_books != NULL) {
                printf("    - %s\n", borrowed_books->title);
                borrowed_books = borrowed_books->Next;
            }
        }
        else {
            printf("  No borrowed books.\n");
        }

        printf("\n");

        sorted_users = sorted_users->Next;
    }

    return first;
}

// Funkcija za sortiranje korisnika abecedno
UPosition sort_users_alphabetically(UPosition head) {
    UPosition sorted_users = NULL;
    UPosition current_user = head;

    while (current_user != NULL) {
        UPosition next_user = current_user->Next;
        current_user->Next = NULL;

        // Slanje usera da se sortiraju po abecedi
        insert_user_sorted(&sorted_users, current_user);

        current_user = next_user;
    }

    return sorted_users;
}

// Funkcija za umetanje korisnika u sortiranu listu abecedno
UPosition insert_user_sorted(UPosition* head, UPosition new_user) {
    UPosition previous = NULL;
    UPosition current = *head;
    UPosition first = *head;

    // Pronalazenje pravog mjesta za umetanje korisnika
    while (current != NULL && strcmp(current->name, new_user->name) < 0) {
        previous = current;
        current = current->Next;
    }

    // Azuriranje pokazivaca
    if (previous == NULL) {
        new_user->Next = *head;
        *head = new_user;
    }
    else {
        new_user->Next = current;
        previous->Next = new_user;
    }
    return first;
}

// Funkcija za povratak knjige na stanje
int return_book(BPosition books, UPosition users, const char* userName, const char* bookTitle) {
    // Pronadji knjigu po naslovu
    BPosition returned_book = find_book_by_title(books, bookTitle);

    if (returned_book == NULL) {
        printf("Book not found.\n");
        return EXIT_FAILURE;
    }

    // Pronadji korisnika po imenu
    UPosition returning_user = find_user(users, userName);

    if (returning_user == NULL) {
        printf("User not found.\n");
        return EXIT_FAILURE;
    }

    // Provjeri je li korisnik posudio tu knjigu
    BPosition borrowed_book = returning_user->borrowedBooks;
    BPosition previous_borrowed_book = NULL;

    while (borrowed_book != NULL) {       

        if (strcmp(borrowed_book->title, bookTitle) == 0) {
            // Azuriraj broj primjeraka knjige i vrati knjigu
            returned_book->copies++;

            // Obrisi knjigu iz liste posudjenih knjiga korisnika
            if (previous_borrowed_book == NULL) {
                returning_user->borrowedBooks = borrowed_book->Next;
            }
            else {
                previous_borrowed_book->Next = borrowed_book->Next;
            }

            UPosition user_borrowed = returned_book->Users;
            UPosition previous_user = NULL;

            while (user_borrowed != NULL) {
                if (strcmp(user_borrowed->name, userName) == 0) { 
                    // Obrisi korisnika iz liste, korisnika koji je posudio knjigu
                    if (previous_user == NULL) {
                        returned_book->Users = user_borrowed->Next;
                    }
                    else {
                        previous_user->Next = user_borrowed->Next;
                    }

                    // Smanji broj posudjenih knjiga za korisnika
                    returning_user->borrowedBooksCount--;

                    // Obrisi knjigu i korisnike iz odredjenih lista
                    free(borrowed_book);
                    free(user_borrowed);

                    printf("Book successfully returned.\n");
                    return EXIT_SUCCESS;
                }

                // Azuriranje pokazivaca (kretanje po listi)
                previous_user = user_borrowed;
                user_borrowed = user_borrowed->Next;
            }
        }

        // Azuriranje pokazivaca (kretanje po listi)
        previous_borrowed_book = borrowed_book;
        borrowed_book = borrowed_book->Next;
    }

    printf("User did not borrow that book.\n");
    return EXIT_FAILURE;
}

int save_books(BPosition head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return EXIT_FAILURE;
    }

    while (head != NULL) {
        fprintf(file, "%s,%s,%d,%d\n", head->title, head->author, head->year, head->copies);
        head = head->Next;
    }

    fclose(file);
    return EXIT_SUCCESS;
}

int save_users(UPosition head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return EXIT_FAILURE;
    }

    while (head != NULL) {
        fprintf(file, "%s", head->name);

        // Spremi knjige koje je korisnik posudio
        BPosition borrowed_books = head->borrowedBooks;
        while (borrowed_books != NULL) {
            fprintf(file, ",%s", borrowed_books->title);
            borrowed_books = borrowed_books->Next;
        }

        fprintf(file, "\n");

        head = head->Next;
    }

    fclose(file);
    return EXIT_SUCCESS;
}

int ask_user(BPosition books, UPosition users) {
    char name[MAX_LENGHT] = { 0 };
    char title[MAX_LENGHT] = { 0 };
    int number = 0;

    printf("\n\tInsert name of user:\t");
    scanf(" %s", name);

    UPosition currentUser = find_user(users, name);

    printf("\n\tUser borrowed: %d books, user can borrow %d more books\n", currentUser->borrowedBooksCount, (currentUser->maxBorrowedBooks - currentUser->borrowedBooksCount));

    printf("\n\tHow many books do you wish to borrow:\t");
    scanf("%d", &number);

    if (number < 0 || number >(currentUser->maxBorrowedBooks - currentUser->borrowedBooksCount)) {
        printf("\n\tInvalid number of books. You can borrow at most %d more books.\n", (currentUser->maxBorrowedBooks - currentUser->borrowedBooksCount));
        return 0;
    }

    for (int i = 0; i < number; ++i) {
        printf("\n\tInsert title of book #%d:\t", i + 1);
        scanf(" %s", title);

        BPosition currentBook = find_book_by_title(books, title);

        if (currentBook == NULL || currentBook->copies == 0) {
           
            printf("\n\tBook '%s' not available for borrowing.\n", title);
            continue;
        }

        printf("\n\tThe book '%s' is available. Do you want to borrow it? (1 for Yes, 0 for No):\t", title);
        int borrowDecision = 0;
        scanf("%d", &borrowDecision);

        if (borrowDecision == 1) {
        
            borrow_book(books, &currentUser, name, title);
        }
        else {
          
            printf("\n\tYou chose not to borrow the book '%s'.\n", title);
        }
    }

    return 1;
}