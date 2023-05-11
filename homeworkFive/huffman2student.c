// 文件压缩-Huffman实现
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode
{ // Huffman树结构
    char c;
    int weight; // 树节点权重，叶节点为字符和它的出现次数
    struct tnode *left, *right;
};
int Ccount[128] = {0};            // 存放每个字符的出现次数，如Ccount[i]表示ASCII值为i的字符出现次数
struct tnode *Root = NULL;        // Huffman树的根节点
char HCode[128][MAXSIZE] = {{0}}; // 字符的Huffman编码，如HCode['a']为字符a的Huffman编码（字符串形式）
int Step = 0;                     // 实验步骤
FILE *Src, *Obj;

void statCount();   // 步骤1：统计文件中字符频率
void createHTree(); // 步骤2：创建一个Huffman树，根节点为Root
void makeHCode();   // 步骤3：根据Huffman树生成Huffman编码
void atoHZIP();     // 步骤4：根据Huffman编码将指定ASCII码文本文件转换成Huffman码文件

void print1();                // 输出步骤1的结果
void print2(struct tnode *p); // 输出步骤2的结果
void print3();                // 输出步骤3的结果
void print4();                // 输出步骤4的结果

int main()
{
    if ((Src = fopen("input.txt", "r")) == NULL)
    {
        fprintf(stderr, "%s open failed!\n", "input.txt");
        return 1;
    }
    if ((Obj = fopen("output.txt", "w")) == NULL)
    {
        fprintf(stderr, "%s open failed!\n", "output.txt");
        return 1;
    }
    scanf("%d", &Step); // 输入当前实验步骤

    statCount();                           // 实验步骤1：统计文件中字符出现次数（频率）
    (Step == 1) ? print1() : 1;            // 输出实验步骤1结果
    createHTree();                         // 实验步骤2：依据字符频率生成相应的Huffman树
    (Step == 2) ? print2(Root) : 2;        // 输出实验步骤2结果
    makeHCode();                           // 实验步骤3：依据Root为树的根的Huffman树生成相应Huffman编码
    (Step == 3) ? print3() : 3;            // 输出实验步骤3结果
    (Step >= 4) ? atoHZIP(), print4() : 4; // 实验步骤4：据Huffman编码生成压缩文件，并输出实验步骤4结果

    fclose(Src);
    fclose(Obj);

    return 0;
}

// 【实验步骤1】开始

void statCount()
{
    char ch;
    while ((ch = fgetc(Src)) != EOF)
    {
        Ccount[ch]++;
    }
    Ccount[0] = 1;
}

// 【实验步骤1】结束

// 【实验步骤2】开始
struct ListNode
{
    struct tnode *tree;
    struct ListNode *next;
};
struct TimesOfChar
{
    char ch;
    int times;
};
int cmp(const void *_a, const void *_b)
{
    struct TimesOfChar *a = (struct TimesOfChar*)_a;
    struct TimesOfChar *b = (struct TimesOfChar*)_b;
    if (a->times == b->times)
    {
        return a->ch - b->ch;
    }
    else
        return a->times - b->times;
}
struct ListNode *initializeForest()
{
    struct TimesOfChar chars[128];
    for (int i = 0; i < 128; i++)
    {
        chars[i].ch = (char)i;
        chars[i].times = Ccount[i];
    }
    qsort(chars, 128, sizeof(struct TimesOfChar), cmp);
    struct ListNode *head = malloc(sizeof(struct ListNode));
    struct ListNode *rare = head;
    head->tree = malloc(sizeof(struct tnode));
    struct tnode *temp = head->tree;
    int i = 0;
    while (chars[i].times == 0)
        i++;
    temp->c = chars[i].ch;
    temp->weight = chars[i].times;
    temp->left = temp->right = NULL;
    for (i++; i < 128; i++)
    {
        rare->next = malloc(sizeof(struct ListNode));
        rare = rare->next;
        rare->tree = malloc(sizeof(struct tnode));
        temp = rare->tree;
        temp->c = chars[i].ch;
        temp->weight = chars[i].times;
        temp->left = temp->right = NULL;
    }
    rare->next = NULL;
    return head;
}
struct ListNode* insert(struct ListNode* head, struct tnode* val){
    if (head == NULL){
        head = malloc(sizeof(struct tnode));
        head->tree = val;
        head->next = NULL;
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
void createHTree()
{
    struct tnode* leftTree;
    struct tnode* rightTree;
    struct tnode* newRoot;
    struct ListNode* temp;
    struct ListNode* forest = initializeForest();
    Root = NULL;
    while (forest->next){
        leftTree = forest->tree;
        rightTree = forest->next->tree;
        temp = forest;
        forest = forest->next;
        free(temp);
        temp = forest;
        forest = forest->next;
        free(temp);
        newRoot = malloc(sizeof(struct tnode));
        newRoot->c = -1;
        newRoot->weight = leftTree->weight + rightTree->weight;
        newRoot->left = leftTree;
        newRoot->right = rightTree;
        forest = insert(forest, newRoot);
    }
    Root = forest->tree;
}

// 【实验步骤2】结束

// 【实验步骤3】开始
void dfs(struct tnode* node, char* password, int position){
    if (node->c >= 0){
        int i;
        for (i = 0; i < position; i++){
            HCode[(int)node->c][i] = password[i] + '0';
        }
        HCode[(int)node->c][i] = 0;
        return;
    }
    password[position] = 0;
    dfs(node->left, password, position + 1);
    password[position] = 1;
    dfs(node->right, password, position + 1);
}
void makeHCode()
{
    char password[MAXSIZE];
    dfs(Root, password, 0);
}

// 【实验步骤3】结束

// 【实验步骤4】开始

void atoHZIP()
{
    char ascii;
    unsigned char waitToPrint = 0;
    char pos = 7;
    rewind(Src);
    while ((ascii = fgetc(Src)) != EOF){
        for (int i = 0; HCode[(int)ascii][i]; i++){
            waitToPrint = waitToPrint ^ ((HCode[(int)ascii][i] - '0') << pos--);
            if (pos < 0){
                fputc(waitToPrint, Obj);
                printf("%x", waitToPrint);
                pos = 7;
                waitToPrint = 0;
            }
        }
    }
    for (int i = 0; HCode[0][i]; i++){
        waitToPrint = waitToPrint ^ ((HCode[0][i] - '0') << pos--);
        if (pos < 0){
            fputc(waitToPrint, Obj);
            printf("%x", waitToPrint);
            pos = 7;
            waitToPrint = 0;
        }
    }
    if (pos != 7){
        fputc(waitToPrint, Obj);
        printf("%x", waitToPrint);
    }
}

// 【实验步骤4】结束

void print1()
{
    int i;
    printf("NUL:1\n");
    for (i = 1; i < 128; i++)
        if (Ccount[i] > 0)
            printf("%c:%d\n", i, Ccount[i]);
}

void print2(struct tnode *p)
{
    if (p != NULL)
    {
        if ((p->left == NULL) && (p->right == NULL))
            switch (p->c)
            {
            case 0:
                printf("NUL ");
                break;
            case ' ':
                printf("SP ");
                break;
            case '\t':
                printf("TAB ");
                break;
            case '\n':
                printf("CR ");
                break;
            default:
                printf("%c ", p->c);
                break;
            }
        print2(p->left);
        print2(p->right);
    }
}

void print3()
{
    int i;

    for (i = 0; i < 128; i++)
    {
        if (HCode[i][0] != 0)
        {
            switch (i)
            {
            case 0:
                printf("NUL:");
                break;
            case ' ':
                printf("SP:");
                break;
            case '\t':
                printf("TAB:");
                break;
            case '\n':
                printf("CR:");
                break;
            default:
                printf("%c:", i);
                break;
            }
            printf("%s\n", HCode[i]);
        }
    }
}

void print4()
{
    long int in_size, out_size;

    fseek(Src, 0, SEEK_END);
    fseek(Obj, 0, SEEK_END);
    in_size = ftell(Src);
    out_size = ftell(Obj);

    printf("\n原文件大小：%ldB\n", in_size);
    printf("压缩后文件大小：%ldB\n", out_size);
    printf("压缩率：%.2f%%\n", (float)(in_size - out_size) * 100 / in_size);
}
