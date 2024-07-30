#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct Book {
    int bookId;
    char bookTitle[50];
    char bookAuthor[50];
    char addedDate[12];
} book;

struct Student {
    int studentId;
    char studentName[50];
    char studentClass[50];
    int studentRoll;
    char issuedBookTitle[50];
    char issueDate[12];
} student;

FILE *filePointer;

int main(){

    int choice;

    while(1){
        system("cls");
        printf("<== Library Management System ==>\n");
        printf("1. Add Book\n");
        printf("2. List Books\n");
        printf("3. Remove Book\n");
        printf("4. Issue Book\n");
        printf("5. List Issued Books\n");
        printf("0. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
        case 0:
            exit(0);

        case 1:
            addBook();
            break;

        case 2:
            listBooks();
            break;

        case 3:
            removeBook();
            break;

        case 4:
            issueBook();
            break;

        case 5:
            listIssuedBooks();
            break;

        default:
            printf("Invalid Choice...\n\n");
        }
        printf("Press Any Key To Continue...");
        getch();
    }

    return 0;
}

void addBook(){
    char currentDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(currentDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(book.addedDate, currentDate);

    filePointer = fopen("books.txt", "ab");

    printf("Enter book id: ");
    scanf("%d", &book.bookId);

    printf("Enter book title: ");
    fflush(stdin);
    gets(book.bookTitle);

    printf("Enter author name: ");
    fflush(stdin);
    gets(book.bookAuthor);

    printf("Book Added Successfully\n");

    fwrite(&book, sizeof(book), 1, filePointer);
    fclose(filePointer);
}

void listBooks(){
    system("cls");
    printf("<== Available Books ==>\n\n");
    printf("%-10s %-30s %-20s %s\n\n", "Book ID", "Book Title", "Author", "Date");

    filePointer = fopen("books.txt", "rb");
    while(fread(&book, sizeof(book), 1, filePointer) == 1){
        printf("%-10d %-30s %-20s %s\n", book.bookId, book.bookTitle, book.bookAuthor, book.addedDate);
    }

    fclose(filePointer);
}

void removeBook(){
    int bookId, found = 0;
    system("cls");
    printf("<== Remove Books ==>\n\n");
    printf("Enter Book ID to remove: ");
    scanf("%d", &bookId);

    FILE *tempFile;

    filePointer = fopen("books.txt", "rb");
    tempFile = fopen("temp.txt", "wb");

    while(fread(&book, sizeof(book), 1, filePointer) == 1){
        if(bookId == book.bookId){
            found = 1;
        } else {
            fwrite(&book, sizeof(book), 1, tempFile);
        }
    }

    if(found == 1){
        printf("\n\nDeleted Successfully.\n");
    } else {
        printf("\n\nRecord Not Found!\n");
    }

    fclose(filePointer);
    fclose(tempFile);

    remove("books.txt");
    rename("temp.txt", "books.txt");
}

void issueBook(){
    char currentDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(currentDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(student.issueDate, currentDate);

    int found = 0;

    system("cls");
    printf("<== Issue Books ==>\n\n");

    printf("Enter Book ID to issue: ");
    scanf("%d", &student.studentId);

    filePointer = fopen("books.txt", "rb");

    while(fread(&book, sizeof(book), 1, filePointer) == 1){
        if(book.bookId == student.studentId){
            strcpy(student.issuedBookTitle, book.bookTitle);
            found = 1;
            break;
        }
    }

    if(found == 0){
        printf("No book found with this ID\n");
        printf("Please try again...\n\n");
        return;
    }

    filePointer = fopen("issue.txt", "ab");

    printf("Enter Student Name: ");
    fflush(stdin);
    gets(student.studentName);

    printf("Enter Student Class: ");
    fflush(stdin);
    gets(student.studentClass);

    printf("Enter Student Roll: ");
    scanf("%d", &student.studentRoll);

    printf("Book Issued Successfully\n\n");

    fwrite(&student, sizeof(student), 1, filePointer);
    fclose(filePointer);
}

void listIssuedBooks(){
    system("cls");
    printf("<== Book Issue List ==>\n\n");

    printf("%-10s %-30s %-20s %-10s %-30s %s\n\n", "Student ID", "Name", "Class", "Roll", "Book Title", "Date");

    filePointer = fopen("issue.txt", "rb");
    while(fread(&student, sizeof(student), 1, filePointer) == 1){
        printf("%-10d %-30s %-20s %-10d %-30s %s\n", student.studentId, student.studentName, student.studentClass, student.studentRoll, student.issuedBookTitle, student.issueDate);
    }

    fclose(filePointer);
}
