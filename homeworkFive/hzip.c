#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HUFFMAN_CODE_LENGTH 24
#define NUM_OF_CHAR 128
#define SIZE_OF_CHAR 8
#define END_OF_HZIP 0
struct TimesOfChar{
    char ch;
    int times;
};
/* the node of huffman tree */
struct TreeNode{
    char ch;
    int weight;
    struct TreeNode* left;
    struct TreeNode* right;
};
/* use linked list to store the forest */
struct ListNode{
    struct TreeNode* tree;
    struct ListNode* next;
};
struct CODE{
    char ch;
    char length;
    char huffmanCode[HUFFMAN_CODE_LENGTH];
};
struct TranslateTree{
    char ch;
    struct TranslateTree* left;
    struct TranslateTree* right;
};
/* get the name of new file */
/* the category of old file is .txt */
void changeFilenameTxtToHizp(char* oldName, char* newName){
    int i, j;
    for (i = 0; oldName[i] != '.'; i++){
        newName[i] = oldName[i];
    }
    char cate[] = ".hzip";
    for (j = 0; cate[j]; i++, j++){
        newName[i] = cate[j];
    }
    newName[i] = 0;
}
/* function of sort the array of initial forest */
int cmp(const void* _a, const void* _b){
    struct TimesOfChar* a = (struct TimesOfChar*)_a;
    struct TimesOfChar* b = (struct TimesOfChar*)_b;
    if (a->times == b->times){
        return a->ch - b->ch;
    }
    else return a->times - b->times;
}
/* function of insert tree to the forest */
/* maintain an ordered linked list */
struct ListNode* insert(struct ListNode* head, struct TreeNode* val){
    if (head == NULL){
        head = malloc(sizeof(struct ListNode));
        head->next = NULL;
        head->tree = val;
        return head;
    }
    struct ListNode* newCell;
    if (val->weight < head->tree->weight){
        newCell = malloc(sizeof(struct ListNode));
        newCell->tree = val;
        newCell->next = head;
        return newCell;
    }
    struct ListNode* temp = head;
    while (temp->next){
        if (val->weight >= temp->next->tree->weight){
            temp = temp->next;
        }
        else{
            newCell = malloc(sizeof(struct ListNode));
            newCell->tree = val;
            newCell->next = temp->next;
            temp->next = newCell;
            return head;
        }
    }
    temp->next = malloc(sizeof(struct ListNode));
    temp = temp->next;
    temp->next = NULL;
    temp->tree = val;
    return head;
}
/* change sorted array of characters to initial forest */
struct ListNode* initializeForest(struct TimesOfChar* sortedArray){
    struct ListNode* head = malloc(sizeof(struct ListNode));
    struct ListNode* rare = head;
    head->tree = malloc(sizeof(struct TreeNode));
    struct TreeNode* temp = head->tree;
    int i = 0;
    while (sortedArray[i].times == 0) i++;
    temp->ch = sortedArray[i].ch;
    temp->weight = sortedArray[i].times;
    temp->left = temp->right = NULL;
    for (i++; i < NUM_OF_CHAR && sortedArray[i].times; i++){
        rare->next = malloc(sizeof(struct ListNode));
        rare = rare->next;
        rare->tree = malloc(sizeof(struct TreeNode));
        temp = rare->tree;
        temp->ch = sortedArray[i].ch;
        temp->weight = sortedArray[i].times;
        temp->left = temp->right = NULL;
    }
    rare->next = NULL;
    return head;
}
struct TreeNode* changeForestToHuffmanTree(struct ListNode* forest){
    if (forest == NULL) return NULL;
    struct TreeNode* leftTree;
    struct TreeNode* rightTree;
    struct TreeNode* newRoot;
    struct ListNode* temp;
    while (forest->next){
        leftTree = forest->tree;
        rightTree = forest->next->tree;
        temp = forest;
        forest = forest->next;
        free(temp);
        temp = forest;
        forest = forest->next;
        free(temp);
        newRoot = malloc(sizeof(struct TreeNode));
        newRoot->ch = -1;
        newRoot->left = leftTree;
        newRoot->right = rightTree;
        newRoot->weight = leftTree->weight + rightTree->weight;
        forest = insert(forest, newRoot);
    }
    return forest->tree;
}
void dfs(struct TreeNode* node, struct CODE* array, char* password, int position){
    if (node->ch >= 0){
        array[(int)node->ch].ch = node->ch;
        array[(int)node->ch].length = position;
        for (int i = 0; i < position; i++){
            array[(int)node->ch].huffmanCode[i] = password[i];
        }
        return;
    }
    password[position] = 0;
    dfs(node->left, array, password, position + 1);
    password[position] = 1;
    dfs(node->right, array, password, position + 1);
}
void changeHuffmanTreeToDictionary(struct TreeNode* tree, struct CODE* array){
    char password[HUFFMAN_CODE_LENGTH];
    for (int i = 0; i < NUM_OF_CHAR; i++){
        array[i].ch = -1;
    }
    dfs(tree, array, password, 0);
}
void printDictionary(struct CODE* dict, FILE* writeFile){
    char code;
    int j, k, m;
    int time;
    for (int i = 0; i < NUM_OF_CHAR; i++){
        if (dict[i].ch != -1){
            fputc(dict[i].ch, writeFile);
            fputc(dict[i].length, writeFile);
            time = dict[i].length / SIZE_OF_CHAR;
            j = 0;
            for (k = 0; k < time; k++){
                code = 0;
                for (m = SIZE_OF_CHAR - 1; m >= 0; m--, j++){
                    code = code ^ (dict[i].huffmanCode[j] << m);
                }
                fputc(code, writeFile);
            }
            code = 0;
            m = SIZE_OF_CHAR - 1;
            while (j < dict[i].length){
                code = code ^ (dict[i].huffmanCode[j] << m);
                j++;
                m--;
            }
            if (m != SIZE_OF_CHAR - 1){
                fputc(code, writeFile);
            }
        }
    }
}
void printText(FILE* readFile, FILE* writeFile, struct CODE* dict){
    char ascii;
    char waitToPrint = 0;
    char pos = SIZE_OF_CHAR - 1;
    char* codes;
    int len;
    while ((ascii = fgetc(readFile)) != EOF){
        codes = dict[(int)ascii].huffmanCode;
        len = dict[(int)ascii].length;
        for (int i = 0; i < len; i++){
            waitToPrint = waitToPrint ^ (codes[i] << pos--);
            if (pos < 0){
                fputc(waitToPrint, writeFile);
                pos = SIZE_OF_CHAR - 1;
                waitToPrint = 0;
            }
        }
    }
    codes = dict[END_OF_HZIP].huffmanCode;
    len = dict[END_OF_HZIP].length;
    for (int i = 0; i < len; i++){
        waitToPrint = waitToPrint ^ (codes[i] << pos--);
        if (pos < 0){
            fputc(waitToPrint, writeFile);
            pos = SIZE_OF_CHAR - 1;
            waitToPrint = 0;
        }
    }
    if (pos != SIZE_OF_CHAR - 1){
        fputc(waitToPrint, writeFile);
    }
}
void textToHzip(char* filename){
    char newFile[50];
    changeFilenameTxtToHizp(filename, newFile);
    //printf("%s", newFile);
    FILE* fr = fopen(filename, "r");
    FILE* fw = fopen(newFile, "w");
    struct TimesOfChar allChar[NUM_OF_CHAR];
    for (int ch = 0; ch < NUM_OF_CHAR; ch++){
        allChar[ch].ch = ch;
        allChar[ch].times = 0;
    }
    allChar[0].times++;
    int c;
    while ((c = fgetc(fr)) != EOF){
        allChar[c].times++;
    }
    qsort(allChar, NUM_OF_CHAR, sizeof(struct TimesOfChar), cmp);
    struct ListNode* forest = initializeForest(allChar);
    struct TreeNode* HuffmanTree = changeForestToHuffmanTree(forest);
    struct CODE dictionary[NUM_OF_CHAR];
    changeHuffmanTreeToDictionary(HuffmanTree, dictionary);
    char lengthOfDictionary = 0;
    for (int i = 0; i < NUM_OF_CHAR; i++){
        if (dictionary[i].ch != -1){
            lengthOfDictionary++;
        }
    }
    rewind(fr);
    fputc(lengthOfDictionary, fw);
    printDictionary(dictionary, fw);
    printText(fr, fw, dictionary);
    fclose(fr);
    fclose(fw);
}
void changeFileNameHzipToTxt(char* oldName, char* newName){
    int i, j;
    char cate[] = ".txt";
    for (i = 0, j = 0; oldName[i] != '.'; i++, j++){
        newName[j] = oldName[i];
    }
    for (i = 0; cate[i]; i++, j++){
        newName[j] = cate[i];
    }
    newName[j] = 0;
}
struct TranslateTree* createHuffmanTreeFromHzip(FILE* readFile){
    char dictionarySize;
    char curChar;
    char pos;
    char ch;
    char len;
    char times;
    char restLen;
    struct TranslateTree* root = malloc(sizeof(struct TranslateTree));
    struct TranslateTree* curNode;
    root->ch = -1;
    root->left = root->right = NULL;
    dictionarySize = fgetc(readFile);
    for (int i = 0; i < dictionarySize; i++){
        curNode = root;
        curChar = fgetc(readFile);
        len = fgetc(readFile);
        times = len / SIZE_OF_CHAR;
        for (int j = 0; j < times; j++){
            ch = fgetc(readFile);
            for (pos = SIZE_OF_CHAR - 1; pos >= 0; pos--){
                if (((ch >> pos) & 1) == 0){
                    if (curNode->left == NULL){
                        curNode->left = malloc(sizeof(struct TranslateTree));
                        curNode = curNode->left;
                        curNode->ch = -1;
                        curNode->left = curNode->right = NULL;
                    }
                    else{
                        curNode = curNode->left;
                    }
                }
                else{
                    if (curNode->right == NULL){
                        curNode->right = malloc(sizeof(struct TranslateTree));
                        curNode = curNode->right;
                        curNode->ch = -1;
                        curNode->left = curNode->right = NULL;
                    }
                    else{
                        curNode = curNode->right;
                    }
                }
            }
        }
        restLen = len % SIZE_OF_CHAR;
        if (restLen){
            ch = fgetc(readFile);
            for (pos = SIZE_OF_CHAR - 1; pos >= SIZE_OF_CHAR - restLen; pos--){
                if (((ch >> pos) & 1) == 0){
                    if (curNode->left == NULL){
                        curNode->left = malloc(sizeof(struct TranslateTree));
                        curNode = curNode->left;
                        curNode->ch = -1;
                        curNode->left = curNode->right = NULL;
                    }
                    else{
                        curNode = curNode->left;
                    }
                }
                else{
                    if (curNode->right == NULL){
                        curNode->right = malloc(sizeof(struct TranslateTree));
                        curNode = curNode->right;
                        curNode->ch = -1;
                        curNode->left = curNode->right = NULL;
                    }
                    else{
                        curNode = curNode->right;
                    }
                }
            }
        }
        curNode->ch = curChar;
    }
    return root;
}
void outputTxt(FILE* writeFile, FILE* readFile, struct TranslateTree* transformer){
    struct TranslateTree* curNode = transformer;
    char curByte;
    char pos;
    while (fscanf(readFile, "%c", &curByte) != EOF){
        for (pos = SIZE_OF_CHAR - 1; pos >= 0; pos--){
            if (((curByte >> pos) & 1) == 0){
                curNode = curNode->left;
            }
            else{
                curNode = curNode->right;
            }
            if (curNode->ch != -1){
                if (curNode->ch == 0) break;
                fputc(curNode->ch, writeFile);
                curNode = transformer;
            }
        }
    }
}
void hzipToText(char* filename){
    char newFile[50];
    changeFileNameHzipToTxt(filename, newFile);
    FILE* fr = fopen(filename, "r");
    FILE* fw = fopen(newFile, "w");
    struct TranslateTree* codeTree = createHuffmanTreeFromHzip(fr);
    outputTxt(fw, fr, codeTree);
    fclose(fr);
    fclose(fw);
}
int main(int argc, char** argv){
    /* error catch and throw */
    if (argc == 1){
        printf("Usage: hzip.exe [-u] <filename>");
        return 0;
    }
    if (argc == 2){
        char* FileName = argv[1];
        int length = strlen(FileName);
        if (length < 5 || strcmp(".txt", FileName + length - 4) != 0){
            printf("File extension error!");
            return 0;
        }
        textToHzip(FileName);
        /* command line parameter without "-u" */
        /* carry out function changing .txt to .hzip */
    }
    else if (argc == 3){
        if (strcmp(argv[1], "-u") != 0){
            printf("Usage: hzip.exe [-u] <filename>");
            return 0;
        }
        char* FileName = argv[2];
        int length = strlen(FileName);
        if (length < 6 || strcmp(".hzip", FileName + length - 5) != 0){
            printf("File extension error!");
            return 0;
        }
        hzipToText(FileName);
        /* command line parameter with "-u" */
        /* carry out function changing .hizp to .txt */
    }
    return 0;
}