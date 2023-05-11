// �ļ�ѹ��-Huffmanʵ��
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode
{ // Huffman���ṹ
    char c;
    int weight; // ���ڵ�Ȩ�أ�Ҷ�ڵ�Ϊ�ַ������ĳ��ִ���
    struct tnode *left, *right;
};
int Ccount[128] = {0};            // ���ÿ���ַ��ĳ��ִ�������Ccount[i]��ʾASCIIֵΪi���ַ����ִ���
struct tnode *Root = NULL;        // Huffman���ĸ��ڵ�
char HCode[128][MAXSIZE] = {{0}}; // �ַ���Huffman���룬��HCode['a']Ϊ�ַ�a��Huffman���루�ַ�����ʽ��
int Step = 0;                     // ʵ�鲽��
FILE *Src, *Obj;

void statCount();   // ����1��ͳ���ļ����ַ�Ƶ��
void createHTree(); // ����2������һ��Huffman�������ڵ�ΪRoot
void makeHCode();   // ����3������Huffman������Huffman����
void atoHZIP();     // ����4������Huffman���뽫ָ��ASCII���ı��ļ�ת����Huffman���ļ�

void print1();                // �������1�Ľ��
void print2(struct tnode *p); // �������2�Ľ��
void print3();                // �������3�Ľ��
void print4();                // �������4�Ľ��

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
    scanf("%d", &Step); // ���뵱ǰʵ�鲽��

    statCount();                           // ʵ�鲽��1��ͳ���ļ����ַ����ִ�����Ƶ�ʣ�
    (Step == 1) ? print1() : 1;            // ���ʵ�鲽��1���
    createHTree();                         // ʵ�鲽��2�������ַ�Ƶ��������Ӧ��Huffman��
    (Step == 2) ? print2(Root) : 2;        // ���ʵ�鲽��2���
    makeHCode();                           // ʵ�鲽��3������RootΪ���ĸ���Huffman��������ӦHuffman����
    (Step == 3) ? print3() : 3;            // ���ʵ�鲽��3���
    (Step >= 4) ? atoHZIP(), print4() : 4; // ʵ�鲽��4����Huffman��������ѹ���ļ��������ʵ�鲽��4���

    fclose(Src);
    fclose(Obj);

    return 0;
}

// ��ʵ�鲽��1����ʼ

void statCount()
{
    char ch;
    while ((ch = fgetc(Src)) != EOF)
    {
        Ccount[ch]++;
    }
    Ccount[0] = 1;
}

// ��ʵ�鲽��1������

// ��ʵ�鲽��2����ʼ
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

// ��ʵ�鲽��2������

// ��ʵ�鲽��3����ʼ
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

// ��ʵ�鲽��3������

// ��ʵ�鲽��4����ʼ

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

// ��ʵ�鲽��4������

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

    printf("\nԭ�ļ���С��%ldB\n", in_size);
    printf("ѹ�����ļ���С��%ldB\n", out_size);
    printf("ѹ���ʣ�%.2f%%\n", (float)(in_size - out_size) * 100 / in_size);
}
