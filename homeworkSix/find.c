#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct INDEX{
    char ch;
    int begin;
    int num;
};
struct ListNode{
    char word[24];
    struct ListNode* next;
};
char** createWordsList(FILE* readFile, int* numOfWords){
    char** wordsList = malloc(3500 * sizeof(char*));
    int i = 0;
    char curWord[24];
    while ((fscanf(readFile, "%s", curWord)) != EOF){
        wordsList[i] = malloc(24 * sizeof(char));
        strcpy(wordsList[i], curWord);
        i++;
    }
    *numOfWords = i;
    return wordsList;
}
int sequentialSearch(char* word, char** wordsList, int length, int* ans){
    int i = 0;
    while (i < length && strcmp(word, wordsList[i]) != 0){
        if (strcmp(word, wordsList[i]) < 0){
            *ans = 0;
            return i + 1;
        }
        i++;
    }
    if (i == length){
        *ans = 0;
        return length;
    }
    *ans = 1;
    return i + 1;
}
int binarySearch(char* word, char** wordsList, int length, int* ans){
    int left, right, mid;
    left = 0;
    right = length - 1;
    int times = 0;
    int cmp;
    while (right >= left){
        times++;
        mid = (left + right) / 2;
        cmp = strcmp(word, wordsList[mid]);
        if (cmp == 0){
            *ans = 1;
            return times;
        }
        else if (cmp < 0){
            right = mid - 1;
        }
        else left = mid + 1;
    }
    *ans = 0;
    return times;
}
struct INDEX* createIndex(char** wordsList, int length){
    struct INDEX* index = calloc(26, sizeof(struct INDEX));
    char curChar = wordsList[0][0];
    int len = 1;
    index[0].begin = 0;
    for (int i = 1; i < length; i++){
        if (wordsList[i][0] == curChar){
            len++;
        }
        else{
            index[curChar - 'a'].ch = curChar;
            index[wordsList[i][0] - 'a'].begin = i;
            index[curChar - 'a'].num = len;
            len = 1;
            curChar = wordsList[i][0];
        }
    }
    index[curChar - 'a'].ch = curChar;
    index[curChar - 'a'].num = len;
    return index;
}
int indexSearch(char* word, char** wordsList, int* ans, struct INDEX* index){
    int left, right, mid;
    left = index[word[0] - 'a'].begin;
    right = index[word[0] - 'a'].num + left - 1;
    int times = 0;
    int cmp;
    while (right >= left){
        times++;
        mid = (left + right) / 2;
        cmp = strcmp(word, wordsList[mid]);
        if (cmp == 0){
            *ans = 1;
            return times;
        }
        else if (cmp < 0){
            right = mid - 1;
        }
        else left = mid + 1;
    }
    *ans = 0;
    return times;
}
unsigned int hashValue(char* str){
    unsigned int h = 0;
    char* p;
    for (p = str; *p; p++){
        h = 37 * h + *p;
    }
    return h % 3001;
}
struct ListNode** createHashSet(FILE* readFile){
    struct ListNode** hashSet = calloc(3001, sizeof(struct ListNode*));
    char word[24];
    unsigned int value;
    struct ListNode* temp;
    struct ListNode* newCell;
    while (fscanf(readFile, "%s", word) != EOF){
        value = hashValue(word);
        if (hashSet[value] == NULL){
            hashSet[value] = malloc(sizeof(struct ListNode));
            strcpy(hashSet[value]->word, word);
            hashSet[value]->next = NULL;
        }
        else{
            temp = hashSet[value];
            if (strcmp(word, temp->word) < 0){
                newCell = malloc(sizeof(struct ListNode));
                newCell->next = temp;
                hashSet[value] = newCell;
                strcpy(newCell->word, word);
            }
            else{
                while (temp->next && strcmp(word, temp->next->word) > 0){
                    temp = temp->next;
                }
                newCell = malloc(sizeof(struct ListNode));
                strcpy(newCell->word, word);
                newCell->next = temp->next;
                temp->next = newCell;
            }
        }
    }
    return hashSet;
}
int hashSearch(char* word, struct ListNode** hashSet, int* ans){
    unsigned int value = hashValue(word);
    if (hashSet[value] == NULL){
        *ans = 0;
        return 0;
    }
    int times = 0;
    struct ListNode* temp = hashSet[value];
    int cmp;
    while (temp){
        cmp = strcmp(word, temp->word);
        times++;
        if (cmp < 0){
            *ans = 0;
            return times;
        }
        else if (cmp == 0){
            *ans = 1;
            return times;
        }
        else temp = temp->next;
    }
    *ans = 0;
    return times;
}
int main(){
    FILE* fr = fopen("dictionary3000.txt", "r");
    char word[24];
    int op;
    int lengthOfWordsList;
    char** wordsList;
    int times;
    int ans;
    struct INDEX* index;
    scanf("%s %d", word, &op);
    if (op == 1){
        wordsList = createWordsList(fr, &lengthOfWordsList);
        times = sequentialSearch(word, wordsList, lengthOfWordsList, &ans);
        if (times == lengthOfWordsList + 1){
            printf("0 %d", lengthOfWordsList);
        }
        else printf("%d %d", ans, times);
    }
    else if (op == 2){
        wordsList = createWordsList(fr, &lengthOfWordsList);
        times = binarySearch(word, wordsList, lengthOfWordsList, &ans);
        printf("%d %d", ans, times);
    }
    else if (op == 3){// 5 7
        wordsList = createWordsList(fr, &lengthOfWordsList);
        index = createIndex(wordsList, lengthOfWordsList);
        times = indexSearch(word, wordsList, &ans, index);
        printf("%d %d", ans, times);
    }
    else if (op == 4){// 2 9
        struct ListNode** hashSet = createHashSet(fr);
        times = hashSearch(word, hashSet, &ans);
        printf("%d %d", ans, times);
    }
    return 0;
}