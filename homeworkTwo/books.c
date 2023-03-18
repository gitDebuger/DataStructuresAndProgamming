#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct BOOK
{
    char name[55];
    char author[25];
    char press[35];
    char date[15];
};
struct ListNode{
    struct BOOK book;
    struct ListNode* next;
};
typedef struct ListNode* list;
typedef struct ListNode* node;
void insertNext(struct BOOK* cell, node position){
    node tmpCell;
    tmpCell = malloc(sizeof(struct ListNode));
    tmpCell->book = *cell;
    tmpCell->next = position->next;
    position->next = tmpCell;
}
list insert(struct BOOK* cell, list books){
    if (books == NULL){
        books = malloc(sizeof(struct ListNode));
        books->book = *cell;
        books->next = NULL;
        return books;
    }
    node tmpCell;
    if (strcmp((*cell).name, books->book.name) < 0){
        tmpCell = malloc(sizeof(struct ListNode));
        tmpCell->book = *cell;
        tmpCell->next = books;
        return tmpCell;
    }
    node n = books;
    while (n->next){
        if (strcmp((*cell).name, n->next->book.name) < 0){
            insertNext(cell, n);
            return books;
        }
        n = n->next;
    }
    insertNext(cell, n);
    return books;
}
void findAndPrint(list books, const char* keyword){
    node iter = books;
    while (iter){
        if (strstr(iter->book.name, keyword)){
            printf("%-50s%-20s%-30s%-10s\n", 
            iter->book.name, iter->book.author, iter->book.press, iter->book.date);
        }
        iter = iter->next;
    }
}
list delete(list books, const char* keyword){
    node tmpCell;
    while (books && strstr(books->book.name, keyword)){
        tmpCell = books;
        books = books->next;
        free(tmpCell);
    }
    if (books == NULL) return books;
    node iter = books;
    while (iter){
        while (iter->next && strstr(iter->next->book.name, keyword)){
            tmpCell = iter->next;
            iter->next = iter->next->next;
            free(tmpCell);
        }
        iter = iter->next;
    }
    return books;
}
void printAll(list books, FILE* file){
    node iter = books;
    while (iter){
        fprintf(file, "%-50s%-20s%-30s%-10s\n", 
        iter->book.name, iter->book.author, iter->book.press, iter->book.date);
        iter = iter->next;
    }
}
int main(){
    list books = NULL;
    struct BOOK cell;
    char keyword[55];
    int op;
    FILE* fr = fopen("books.txt", "r");
    FILE* fw = fopen("ordered.txt", "w");
    while (fscanf(fr, "%s %s %s %s", cell.name, cell.author, cell.press, cell.date) != EOF){
        books = insert(&cell, books);
    }
    fclose(fr);
    for (;;){
        scanf("%d", &op);
        if (op == 0) break;
        else if (op == 1){
            scanf("%s %s %s %s", cell.name, cell.author, cell.press, cell.date);
            books = insert(&cell, books);
        }
        else if (op == 2){
            scanf("%s", keyword);
            findAndPrint(books, keyword);
        }
        else if (op == 3){
            scanf("%s", keyword);
            books = delete(books, keyword);
        }
    }
    printAll(books, fw);
    fclose(fw);
    return 0;
}