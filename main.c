#include <stdio.h>
#include <stdlib.h>
typedef struct Book
{
    int id;
    char title[31];
    char author[31];
    char genre[31];
    int year;
    int isAvailable;
}Book;

int addBooks(Book *books, int size)
{
    FILE *file = fopen("library.bin", "ab");
    if(!file)
    {
        printf("File could not be opened");
        exit(1);
    }
    fwrite(books, sizeof(Book), size, file);
    fclose(file);
    return size;
}

int findBookByAuthor(char *author)
{
    FILE *file = fopen("library.bin", "rb");
    if(!file)
    {
        printf("File could not be opened");
        exit(1);
    }
    Book book;
    int found = 0;
    while (fread(&book, sizeof(Book), 1, file))
    {
        if(strcmp(book.author, author) == 0)
        {
            found = 1;
            printf("\nBook found!\n");
            printf("Book id: %d\n", book.id);
            printf("Book title: %s\n", book.title);
            printf("Book author: %s\n", book.author);
            printf("Book genre: %s\n", book.genre);
            printf("Book year: %d\n", book.year);
            if(book.isAvailable == 1)
            {
                printf("The book is available\n");
            }
            else
            {
                printf("The book is not available\n");
            }
        }
    }
    if(found == 0)
    {
        printf("Such book was not found.");
        exit(1);
    }
    fclose(file);
}

int countAvailableBooks()
{
    FILE *file = fopen("library.bin", "rb");
    if(!file)
    {
        printf("File could not be opened");
        exit(1);
    }
    Book book;
    int count = 0;
    while (fread(&book, sizeof(Book), 1, file))
    {
        if (book.isAvailable == 1)
        {
            count++;
        }
    }
    fclose(file);
    return count;
}

void changeBookInformation(int id)
{
    FILE *file = fopen("library.bin", "rb+");
    if(!file)
    {
        printf("File could not be opened");
        exit(1);
    }
    Book book;
    int found = 0;
    while (fread(&book, sizeof(Book), 1, file))
    {
        if(book.id == id)
        {
            found = 1;
            printf("Enter title: ");
            scanf("%s", book.title);
            getchar();
            printf("Enter author: ");
            scanf("%s", book.author);
            getchar();
            printf("Enter genre: ");
            scanf("%s", book.genre);
            getchar();
            printf("Enter year: ");
            scanf("%d", &book.year);
            printf("Enter availability : ");
            scanf("%d", &book.isAvailable);
            fseek(file, -sizeof(Book), SEEK_CUR);
            fwrite(&book, sizeof(Book), 1, file);
            break;
        }
    }
    if (!found)
    {
        printf("Book with ID %d not found.\n", id);
    }
    fclose(file);
}
int main()
{
    printf("---Welcome to the library management system!---");
    printf("\nWhat would you like to do?\n1)Add books               2)Change Book Information\n3)Find books from author   4)Check books count\n");
    int choice = 0;
    scanf("%d", &choice);
    char id;
    char author[31];
    switch(choice)
    {
    case 1:
        printf("How many books would you like to add?\n");
        int count = 0;
        scanf("%d", &count);
        Book *books = (Book*) malloc(count*sizeof(Book));
        for(int i= 0; i<count; i++)
        {
            printf("\nPlease enter ID for book %d: ", i+1);
            scanf("%d", &books[i].id);
            printf("Please enter book name: ");
            scanf("%s", books[i].title);
            getchar();
            printf("Please enter book author: ");
            scanf("%s", books[i].author);
            getchar();
            printf("Please enter book genre: ");
            scanf("%s", books[i].genre);
            getchar();
            printf("Please enter book year: ");
            scanf("%d", &books[i].year);
            printf("Please enter book if the book is available or not: ");
            scanf("%d", &books[i].isAvailable);
            while(books[i].isAvailable != 1 && books[i].isAvailable != 0)
            {
                printf("Please enter correct availability (1/0): ");
                scanf("%d", &books[i].isAvailable);
            }
        }
        printf("Successfully added %d books", addBooks(books, count));
        break;
    case 2:
        printf("Which books would you like to modify?\n");
        scanf("%d", &id);
        changeBookInformation(id);
        break;
    case 3:
        printf("Which author would you like to look for?\n");
        scanf("%s", author);
        findBookByAuthor(author);
        break;
    case 4:
        printf("There are %d books available right now.", countAvailableBooks());
        break;
    default:
        printf("You did not enter a correct option.");
        break;
    }
    return 0;
}
