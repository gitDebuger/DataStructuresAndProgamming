/* all the macro */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define VECTOR_LEN 10000
#define FINGERPRINT_LEN 128
#define WORD_LENGTH 85
#define ID_LENGTH 30
#define WEB_NUM 16010
#define STACK_SIZE 200
#define THRESHOLD 3
#define MAX_WORDS 106000
#define SAMPLE_NUM 1000
/* all the macro */

/* all the struct */
struct HashTbl;
struct ListNode;
struct Web;
struct Bucket;
typedef struct HashTbl* HashTable;
typedef struct ListNode* List;
typedef struct ListNode* Node;
typedef struct Web WebInfo;
typedef struct Bucket Buc;
struct HashTbl{
    List* theLists;
    int tableSize;
};
struct ListNode{
    char word[WORD_LENGTH];
    int weight;
    Node next;
};
struct Web{
    char id[ID_LENGTH];
    char fingerprint[FINGERPRINT_LEN];
};
struct Bucket{
    int count;
    int* position;
};
/* all the struct */

/* all the function */
void CreateHashVec(FILE* readFile, char (*hashVec)[FINGERPRINT_LEN], int vecLen, int fingerLen);
unsigned int Hash(const char* key, int tableSize);
HashTable CreateStopWordsList(FILE* readFile);
bool Find(HashTable stopwordsList, const char* word);
void Insert(const char* keyword, HashTable wordsWeight);
void DestroyHashTable(HashTable hh);
void CompareAndPrint(FILE* outFile, WebInfo* webs, WebInfo* curSample, int websNum, int fingerLen);
void PrintFirstSample(WebInfo* webs, WebInfo* curSample, int websNum, int fingerLen);
HashTable CreateFeature(FILE* article, HashTable stopwordsList, int vecLen);
int Cmp(const void* _a, const void* _b);
void AddFeatureWord(HashTable featureList, const char* keyword, int pos);
bool CreateFinger(FILE* articleFile, HashTable featureList, WebInfo* webs, int pos, int vecLen, 
int fingerLen, char (*hashVec)[FINGERPRINT_LEN]);
int FindFeature(const char* word, HashTable featureList);
/* all the function */

int main(int argc, char** argv){
    if (argc < 3) return 1;
    /* if there is no enough parameter */
    /* then exit with code 1 */

    /* change string into number */
    int vectorLength = atol(argv[1]);
    int fingerprintLength = atol(argv[2]);

    /* read hashvalue.txt to array */
    FILE* hashFile = fopen("hashvalue.txt", "r");
    char hashVec[VECTOR_LEN][FINGERPRINT_LEN];
    CreateHashVec(hashFile, hashVec, vectorLength, fingerprintLength);
    fclose(hashFile);
    hashFile = NULL;

    /* read stopwords.txt to hash set */
    FILE* stopwordsFile = fopen("stopwords.txt", "r");
    HashTable stopwords = CreateStopWordsList(stopwordsFile);
    fclose(stopwordsFile);
    stopwordsFile = NULL;

    /* read article.txt and create feature vector */
    FILE* article = fopen("article.txt", "r");
    HashTable featureTable = CreateFeature(article, stopwords, vectorLength);
    rewind(article);

    WebInfo* webs = malloc(WEB_NUM * sizeof(WebInfo));
    int websNum = 0;
    bool flag;
    for (;;){
        flag = CreateFinger(article, featureTable, webs, websNum, vectorLength, 
        fingerprintLength, hashVec);
        if (flag){
            websNum++;
        }
        else break;
    }
    fclose(article);
    //DestroyHashTable(featureTable);
    //free(featureTable);

    WebInfo* samples = calloc(SAMPLE_NUM, sizeof(WebInfo));
    FILE* sample = fopen("sample.txt", "r");
    //featureTable = CreateFeature(sample, stopwords, vectorLength);
    //rewind(sample);
    int samplesNum = 0;
    for (;;){
        flag = CreateFinger(sample, featureTable, samples, samplesNum, vectorLength, 
        fingerprintLength, hashVec);
        if(flag){
            samplesNum++;
        }
        else break;
    }
    fclose(sample);
    DestroyHashTable(featureTable);
    free(featureTable);

    DestroyHashTable(stopwords);
    free(stopwords);

    FILE* result = fopen("result.txt", "w");
    for (int i = 0; i < samplesNum; i++){
        CompareAndPrint(result, webs, &samples[i], websNum, fingerprintLength);
    }
    PrintFirstSample(webs, samples, websNum, fingerprintLength);
    fclose(result);
    free(samples);
    free(webs);
    return 0;
}

void CreateHashVec(FILE* readFile, char (*hashVec)[FINGERPRINT_LEN], int vecLen, int fingerLen){
    char line[FINGERPRINT_LEN + 5];
    for (int i = 0; i < vecLen; i++){
        fgets(line, FINGERPRINT_LEN + 5, readFile);
        for (int j = 0; j < fingerLen; j++){
            hashVec[i][j] = line[j];
        }
    }
}

unsigned int Hash(const char* key, int tableSize){
    unsigned int hashVal = 0;
    while (*key){
        hashVal = (hashVal << 5) + *key++;
    }
    return hashVal % tableSize;
}

HashTable CreateStopWordsList(FILE* readFile){
    HashTable wordsList = malloc(sizeof(struct HashTbl));
    wordsList->tableSize = 331;
    wordsList->theLists = calloc(wordsList->tableSize, sizeof(List));

    char word[WORD_LENGTH];
    unsigned int hashValue;
    Node newCell;
    Node temp;
    while (fscanf(readFile, "%s", word) != EOF){
        newCell = malloc(sizeof(struct ListNode));
        strcpy(newCell->word, word);
        hashValue = Hash(word, wordsList->tableSize);
        if (wordsList->theLists[hashValue] == NULL){
            wordsList->theLists[hashValue] = newCell;
            newCell->next = NULL;
        }
        else{
            temp = wordsList->theLists[hashValue];
            if (strcmp(word, temp->word) < 0){
                newCell->next = temp;
                wordsList->theLists[hashValue] = newCell;
            }
            else{
                while (temp->next && strcmp(word, temp->next->word) > 0){
                    temp = temp->next;
                }
                newCell->next = temp->next;
                temp->next = newCell;
            }
        }
    }
    return wordsList;
}

void Insert(const char* keyword, HashTable wordsWeight){
    unsigned int hashVal = Hash(keyword, wordsWeight->tableSize);
    Node newCell;
    Node temp;
    if (wordsWeight->theLists[hashVal] == NULL){
        newCell = malloc(sizeof(struct ListNode));
        newCell->weight = 1;
        strcpy(newCell->word, keyword);
        newCell->next = NULL;
        wordsWeight->theLists[hashVal] = newCell;
        return;
    }
    temp = wordsWeight->theLists[hashVal];
    int cmp = strcmp(keyword, temp->word);
    if (cmp < 0){
        newCell = malloc(sizeof(struct ListNode));
        newCell->weight = 1;
        strcpy(newCell->word, keyword);
        newCell->next = temp;
        wordsWeight->theLists[hashVal] = newCell;
        return;
    }
    if (cmp == 0){
        temp->weight++;
        return;
    }
    while (temp->next){
        cmp = strcmp(keyword, temp->next->word);
        if (cmp < 0){
            newCell = malloc(sizeof(struct ListNode));
            newCell->weight = 1;
            strcpy(newCell->word, keyword);
            newCell->next = temp->next;
            temp->next = newCell;
            return;
        }
        else if (cmp == 0){
            temp->next->weight++;
            return;
        }
        else temp = temp->next;
    }
    newCell = malloc(sizeof(struct ListNode));
    newCell->weight = 1;
    strcpy(newCell->word, keyword);
    newCell->next = NULL;
    temp->next = newCell;
}

void DestroyHashTable(HashTable hh){
    Node temp;
    Node stack[STACK_SIZE];
    int topOfStack = -1;
    for (int i = 0; i < hh->tableSize; i++){
        temp = hh->theLists[i];
        while (temp){
            stack[++topOfStack] = temp;
            temp = temp->next;
        }
        while (topOfStack >= 0){
            free(stack[topOfStack--]);
        }
    }
    free(hh->theLists);
}

void CompareAndPrint(FILE* outFile, WebInfo* webs, WebInfo* curSample, int websNum, int fingerLen){
    Buc buckets[THRESHOLD + 1];
    for (int i = 0; i <= THRESHOLD; i++){
        buckets[i].count = 0;
        buckets[i].position = malloc(WEB_NUM * sizeof(int));
    }
    int val;
    for (int i = 0; i < websNum; i++){
        val = 0;
        for (int j = 0; j < fingerLen; j++){
            val += (webs[i].fingerprint[j] ^ curSample->fingerprint[j]);
        }
        if (val <= THRESHOLD){
            buckets[val].position[buckets[val].count++] = i;
        }
    }
    fprintf(outFile, "%s\n", curSample->id);
    for (int i = 0; i <= THRESHOLD; i++){
        if (buckets[i].count > 0){
            fprintf(outFile, "%d:", i);
            for (int j = 0; j < buckets[i].count; j++){
                fprintf(outFile, "%s ", webs[buckets[i].position[j]].id);
            }
            fputc('\n', outFile);
        }
        free(buckets[i].position);
    }
}

void PrintFirstSample(WebInfo* webs, WebInfo* curSample, int websNum, int fingerLen){
    Buc buckets[THRESHOLD + 1];
    for (int i = 0; i <= THRESHOLD; i++){
        buckets[i].count = 0;
        buckets[i].position = malloc(WEB_NUM * sizeof(int));
    }
    int val;
    for (int i = 0; i < websNum; i++){
        val = 0;
        for (int j = 0; j < fingerLen; j++){
            val += (webs[i].fingerprint[j] ^ curSample->fingerprint[j]);
        }
        if (val <= THRESHOLD){
            buckets[val].position[buckets[val].count++] = i;
        }
    }
    printf("%s\n", curSample->id);
    for (int i = 0; i <= THRESHOLD; i++){
        if (buckets[i].count > 0){
            printf("%d:", i);
            for (int j = 0; j < buckets[i].count; j++){
                printf("%s ", webs[buckets[i].position[j]].id);
            }
            putchar('\n');
        }
        free(buckets[i].position);
    }
}

bool Find(HashTable stopwordsList, const char* word){
    unsigned int hashVal = Hash(word, stopwordsList->tableSize);
    Node temp = stopwordsList->theLists[hashVal];
    int cmp;
    while (temp){
        cmp = strcmp(word, temp->word);
        if (cmp < 0) return false;
        else if (cmp == 0) return true;
        else temp = temp->next;
    }
    return false;
}

HashTable CreateFeature(FILE* article, HashTable stopwordsList, int vecLen){
    char curWord[WORD_LENGTH];
    int len = 0;
    char ch;
    HashTable weightList = malloc(sizeof(struct HashTbl));
    weightList->tableSize = 11003;
    weightList->theLists = calloc(weightList->tableSize, sizeof(List));
    while ((ch = fgetc(article)) != EOF){
        if (isalpha(ch)) curWord[len++] = tolower(ch);
        else if (len > 0){
            curWord[len] = 0;
            if (!Find(stopwordsList, curWord)){
                Insert(curWord, weightList);
            }
            len = 0;
        }
    }
    if (len > 0){
        curWord[len] = 0;
        if (!Find(stopwordsList, curWord)){
            Insert(curWord, weightList);
        }
    }
    Node* words = calloc(MAX_WORDS, sizeof(Node));
    Node temp;
    int pos = 0;
    for (int i = 0; i < weightList->tableSize; i++){
        temp = weightList->theLists[i];
        while (temp){
            words[pos++] = temp;
            temp = temp->next;
        }
    }
    qsort(words, pos, sizeof(Node), Cmp);
    HashTable featureList = malloc(sizeof(struct HashTbl));
    featureList->tableSize = 11003;
    featureList->theLists = calloc(featureList->tableSize, sizeof(List));
    for (int i = 0; i < vecLen; i++){
        AddFeatureWord(featureList, words[i]->word, i);
    }
    DestroyHashTable(weightList);
    free(words);
    free(weightList);
    return featureList;
}

int Cmp(const void* _a, const void* _b){
    Node* a = (Node*)_a;
    Node* b = (Node*)_b;
    if ((*a)->weight == (*b)->weight){
        return strcmp((*a)->word, (*b)->word);
    }
    else return (*b)->weight - (*a)->weight;
}

void AddFeatureWord(HashTable featureList, const char* keyword, int pos){
    unsigned int hashVal = Hash(keyword, featureList->tableSize);
    Node newCell = malloc(sizeof(struct ListNode));
    newCell->weight = pos;
    strcpy(newCell->word, keyword);
    if (featureList->theLists[hashVal] == NULL){
        newCell->next = NULL;
        featureList->theLists[hashVal] = newCell;
        return;
    }
    Node temp = featureList->theLists[hashVal];
    if (strcmp(keyword, temp->word) < 0){
        newCell->next = temp;
        featureList->theLists[hashVal] = newCell;
        return;
    }
    while (temp->next){
        if (strcmp(keyword, temp->next->word) < 0){
            break;
        }
        temp = temp->next;
    }
    newCell->next = temp->next;
    temp->next = newCell;
}

bool CreateFinger(FILE* articleFile, HashTable featureList, WebInfo* webs, int pos, int vecLen, 
int fingerLen, char (*hashVec)[FINGERPRINT_LEN]){
    if(fscanf(articleFile, "%s", webs[pos].id) == EOF){
        return false;
    }
    bool flag = true;
    int* finger = calloc(vecLen, sizeof(int));
    char curWord[WORD_LENGTH];
    int len = 0;
    int position;
    char ch;
    while ((ch = fgetc(articleFile)) != EOF){
        if (isalpha(ch)) curWord[len++] = tolower(ch);
        else if (len > 0){
            curWord[len] = 0;
            position = FindFeature(curWord, featureList);
            if (position >= 0){
                finger[position]++;
            }
            len = 0;
        }
        if (ch == '\f'){
            break;
        }
    }
    if (len > 0){
        curWord[len] = 0;
        position = FindFeature(curWord, featureList);
        if (position >= 0){
            finger[position]++;
        }
    }
    int val;
    for (int col = 0; col < fingerLen; col++){
        val = 0;
        for (int row = 0; row < vecLen; row++){
            if (hashVec[row][col] == '1'){
                val += finger[row];
            }
            else val -= finger[row];
        }
        webs[pos].fingerprint[col] = val > 0 ? 1 : 0;
    }
    free(finger);
    return flag;
}

int FindFeature(const char* word, HashTable featureList){
    unsigned int hashVal = Hash(word, featureList->tableSize);
    if (featureList->theLists[hashVal] == NULL){
        return -1;
    }
    Node temp = featureList->theLists[hashVal];
    int cmp;
    while (temp){
        cmp = strcmp(word, temp->word);
        if (cmp < 0) return -1;
        else if (cmp == 0) return temp->weight;
        else temp = temp->next;
    }
    return -1;
}