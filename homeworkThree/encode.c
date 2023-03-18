#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct ListNode{
    char letter;
    struct ListNode* next;
};
typedef struct ListNode* list;
typedef struct ListNode* position;
int main(){
    FILE* fr = fopen("in.txt", "r");
    FILE* fw = fopen("in_crpyt.txt", "w");
    char key[35];
    int k = 0;
    char chread;
    while ((chread = getchar()) != EOF){
        if (chread < 32 || chread > 126) break;
        key[k++] = chread;
    }key[k] = 0;
    bool hashTableKeyToList[95] = {false};
    // use a hash table to flag what number is used

    // create the circle key list
    list keyList = malloc(sizeof(struct ListNode));
    position pos = keyList;
    pos->letter = key[0];
    hashTableKeyToList[key[0] - 32] = true;
    for (int i = 1; key[i]; i++){
        if (!hashTableKeyToList[key[i] - 32]){
            pos->next = malloc(sizeof(struct ListNode));
            pos = pos->next;
            pos->letter = key[i];
            hashTableKeyToList[key[i] - 32] = true;
        }
    }
    for (char ch = 32; ch <= 126; ch++){
        if (!hashTableKeyToList[ch - 32]){
            pos->next = malloc(sizeof(struct ListNode));
            pos = pos->next;
            pos->letter = ch;
            hashTableKeyToList[ch - 32] = true;
        }
    }
    pos->next = keyList;

    // create the hash map of clear letter to ciphertext letter
    char hashMap[95];
    char firstLetter;
    char ch;
    position temp;
    firstLetter = keyList->letter;
    while (pos->next != pos){
        ch = pos->next->letter;
        temp = pos->next;
        pos->next = temp->next;
        free(temp);
        for (int i = 1; i < (int)ch; i++){
            pos = pos->next;
        }
        hashMap[ch - 32] = pos->next->letter;
    }
    hashMap[pos->letter - 32] = firstLetter;
    free(pos);
    pos = NULL;
    keyList = NULL;
    temp = NULL;

    // Convert plain text to ciphertext
    while ((ch = fgetc(fr)) != EOF){
        if (ch < 32 || ch > 126) fputc(ch, fw);
        else fputc(hashMap[ch - 32], fw);
    }
    fclose(fr);
    fclose(fw);
    fr = fw = NULL;
    return 0;
}