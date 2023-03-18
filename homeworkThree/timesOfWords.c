#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct listNode{
    char word[50];
    int count;
    struct listNode* next;
};
typedef struct listNode* list;
typedef struct listNode* node;
list insert(list li, const char* word){
    if (li == NULL){
        list re = malloc(sizeof(struct listNode));
        strcpy(re->word, word);
        re->count = 1;
        re->next = NULL;
        return re;
    }
    if (strcmp(word, li->word) < 0){
        list re = malloc(sizeof(struct listNode));
        strcpy(re->word, word);
        re->count = 1;
        re->next = li;
        return re;
    }
    if (strcmp(word, li->word) == 0){
        li->count++;
        return li;
    }
    node no = li;
    while (no->next && strcmp(word, no->next->word) > 0){
        no = no->next;
    }
    if (no->next == NULL){
        no->next = malloc(sizeof(struct listNode));
        no = no->next;
        strcpy(no->word, word);
        no->count = 1;
        no->next = NULL;
    }
    else if (strcmp(word, no->next->word) == 0){
        no->next->count++;
    }
    else{
        node temp = malloc(sizeof(struct listNode));
        strcpy(temp->word, word);
        temp->count = 1;
        temp->next = no->next;
        no->next = temp;
    }
    return li;
}
int main(){
    FILE* fr = fopen("article.txt", "r");
    list wordsList = NULL;
    char word[50];
    int length = 0;
    char ch;
    while ((ch = fgetc(fr)) != EOF){
        if (isalpha(ch)){
            word[length++] = tolower(ch);
        }
        else if (length){
            word[length] = 0;
            wordsList = insert(wordsList, word);
            length = 0;
        }
    }
    for (node no = wordsList; no; no = no->next){
        printf("%s %d\n", no->word, no->count);
    }
    return 0;
}