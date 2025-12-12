#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int id;
    char title[100];
    char author[100];
    float price;
};

void addBook() {
    struct Book b;
    FILE *fp = fopen("library.dat", "ab");

    printf("\nEnter Book ID: ");
    scanf("%d", &b.id);
    printf("Enter Book Title: ");
    getchar();
    fgets(b.title, 100, stdin);
    b.title[strcspn(b.title, "\n")] = 0;

    printf("Enter Book Author: ");
    fgets(b.author, 100, stdin);
    b.author[strcspn(b.author, "\n")] = 0;

    printf("Enter Book Price: ");
    scanf("%f", &b.price);

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
    printf("\nBook Added Successfully!\n");
}

void displayBooks() {
    struct Book b;
    FILE *fp = fopen("library.dat", "rb");

    if (!fp) {
        printf("\nNo records found.\n");
        return;
    }

    printf("\n--- Book List ---\n");
    while (fread(&b, sizeof(b), 1, fp)) {
        printf("\nID: %d\nTitle: %s\nAuthor: %s\nPrice: %.2f\n", 
               b.id, b.title, b.author, b.price);
    }
    fclose(fp);
}

void searchBook() {
    int id, found = 0;
    struct Book b;
    FILE *fp = fopen("library.dat", "rb");

    printf("\nEnter Book ID to Search: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id == id) {
            printf("\nBook Found:\nID: %d\nTitle: %s\nAuthor: %s\nPrice: %.2f\n",
                   b.id, b.title, b.author, b.price);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nBook Not Found!\n");

    fclose(fp);
}

void deleteBook() {
    int id, found = 0;
    struct Book b;
    FILE *fp = fopen("library.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    printf("\nEnter Book ID to Delete: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id != id) {
            fwrite(&b, sizeof(b), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("library.dat");
    rename("temp.dat", "library.dat");

    if (found)
        printf("\nBook Deleted Successfully!\n");
    else
        printf("\nBook Not Found!\n");
}

void updateBook() {
    int id, found = 0;
    struct Book b;
    FILE *fp = fopen("library.dat", "rb+");

    printf("\nEnter Book ID to Update: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(b), 1, fp)) {
        if (b.id == id) {
            printf("\nEnter New Title: ");
            getchar();
            fgets(b.title, 100, stdin);
            b.title[strcspn(b.title, "\n")] = 0;

            printf("Enter New Author: ");
            fgets(b.author, 100, stdin);
            b.author[strcspn(b.author, "\n")] = 0;

            printf("Enter New Price: ");
            scanf("%f", &b.price);

            fseek(fp, -sizeof(b), SEEK_CUR);
            fwrite(&b, sizeof(b), 1, fp);

            printf("\nBook Updated Successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nBook Not Found!\n");

    fclose(fp);
}

int main() {
    int choice;

    while (1) {
        printf("\n\n=== Library Management System ===\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Search Book\n");
        printf("4. Delete Book\n");
        printf("5. Update Book\n");
        printf("6. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: updateBook(); break;
            case 6: exit(0);
            default: printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}

