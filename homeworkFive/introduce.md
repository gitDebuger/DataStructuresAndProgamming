# 1 树叶节点遍历

## 1.1 问题描述

从标准输入中输入一组整数，在输入过程中按照左子结点值小于根结点值、右子结点值大于等于根结点值的方式构造一棵二叉查找树，然后从左至右输出所有树中叶结点的值及高度，根结点的高度为1。

提交文件名为`"bst.c"`

## 1.2 输入形式

先从标准输入读取整数的个数，然后从下一行开始输入各个整数，整数之间以一个空格分隔。

## 1.3 输出形式

按照从左到右的顺序分行输出叶结点的值及高度，值和高度之间以一个空格分隔。

## 1.4 样例

输入

```
13
50 38 30 64 58 40 10 73 70 50 60 100 35
```

输出

```
10 4
35 4
40 3
50 4
60 4
70 4
100 4
```

# 2 词频统计

与第三次作业基本相同，除输出词频本身之外，还需要输出根节点、根的右节点和根的右节点的右节点上的单词。

提交文件名为`"words.c"`

# 3 计算器

与第四次作业计算器基本相同，将浮点输出换为整数输出。除此之外，还需要输出根节点、根的左节点和根的右节点上的运算符或数字。

提交文件名为`"compute.c"`

# 4 服务优化

## 4.1 问题描述

假设某机场所有登机口呈树形排列，树的度为3，安检处为树的根，如下图所示。图中的分叉结点即编号大于等于100的节点表示分叉路口，登机口用小于100的编号表示并且其一定是一个叶结点。

![plane.jpg](https://judge.buaa.edu.cn/userfiles/image/2021/1616076254353079599135.jpg)

通过对机场所有出发航班的日志分析，得知每个登机口每天的平均发送旅客流量。作为提升机场服务水平的一个措施，在不改变所有航班相对关系的情况下，即出发时间不变，原在同一登机口的航班不变，仅改变登机口，使得整体旅客到登机口的时间有所减少，即从安检口到登机口所经过的分叉路口最少。

编写程序模拟上述登机口的调整，登机口调整规则如下：

1. 首先按照由大到小的顺序对输入的登机口流量进行排序，流量相同的按照登机口编号由小到大排序
2. 从上述登机口树的树根开始，将登机口按照从上到下，安检口在最上方，从左到右的顺序，依次对应上面排序后将要调整的登机口

提交文件名为`"adjust.c"`

## 4.2 输入形式

首先按层次从根开始依次输入树结点之间的关系。其中分叉结点编号从数字100开始，树根结点编号为100，其它分叉结点编号没有规律但不会重复；登机口为编号小于100的数字，编号没有规律但不会重复，其一定是一个叶结点。树中结点间关系用下面方式描述：

```
R S1 S2 S3 -1
```

其中`R`为分叉结点，从左至右`S1`，`S2`，`S3`分别为树叉`R`的子结点，其可为树叉或登机口。由于树的度为3，`S1`，`S2`，`S3`中至多可以2个为空，最后该行以`-1`和换行符结束。

假设分叉结点数不超过100个。分叉结点输入的顺序不确定，但可以确定输入某个分叉结点信息时，其父结点的信息已经输入。

输入完所有树结点关系后，在新的一行上输入-1表示树结点关系输入完毕。

接下来输入登机口的流量信息，每个登机口流量信息分占一行，分别包括登机口编号(1~99之间的整数)和流量(大于0的整数)。两整数间以一个空格分隔。登机口数目与前面构造树时的登机机口数目一致。

## 4.3 输出形式

按照上述调整规则中排序后的顺序，即按旅客流量由大到小，流量相同的按照登机口编号由小到大，依次分行输出每个登机口的调整结果。先输出调整前的登机口编号，然后输出字符串`->`，再输出要调整到的登机口编号。

## 4.4 样例

输入

```
100 101 102 103 -1
103 14 108 13 -1
101 5 104 6 -1
104 7 8 -1
102 105 106 107 -1
106 1 110 2 -1
108 16 15 -1
107 18 111 17 -1
110 3 4 -1
105 9 109 10 -1
111 20 19 -1
109 11 12 -1
-1
17 865
5 668
20 3000
13 1020
11 980
8 2202
15 1897
6 1001
14 922
7 2178
19 2189
1 1267
12 3281
2 980
18 1020
10 980
3 1876
9 1197
16 980
4 576
```

输出

```
12->5
20->6
8->14
19->13
7->7
15->8
3->9
1->10
9->1
13->2
18->18
6->17
2->16
10->15
11->11
16->12
14->3
17->4
5->20
4->19
```

# 5 基于Huffman码的文件压缩和解压工具

## 5.1 问题描述

编写一程序实现一个利用Huffman编码对一个文件进行压缩和解压的工具hzip.exe。

Huffman压缩文件原理如下：

1. 对正文文件中字符按出现次数进行统计
2. 依据字符频率生成相应的Huffman，未出现的字符不生成
3. 依据Huffman树生成相应字符的Huffman编码
4. 依据字符Huffman编码压缩文件，即按照Huffman编码依次输出源文件字符

说明：

1. 只对文件中出现的字符生成Huffman码
2. 采用ASCII码值为0的字符作为压缩文件的结束符，即可将其出现次数设为1来参与编码
3. 在生成Huffman树时，初始在对字符频率权重由小至大进行排序时，频率相同的字符ASCII编码值小的在前；新生成的权重节点插入到有序权重序列中时，出现相同权重时，插入到其后
4. 遍历Huffman树生成字符Huffman码时，左边为0右边为1
5. 源文件是文本文件，字符采用ASCII编码，每个字符占8位；而采用Huffman编码后，最后输出时需要使用C语言中的位运算将字符Huffman码依次输出到每个字节中。

## 5.2 输入形式

基于Huffman的文件压缩解压工具hzip.exe命令行使用形式如下：

```
hzip [-u] <filename.xxx>
```

当`-u`参数缺省时，对当前目录下文本文件`<filename.txt>`采用Huffman编码方式将文件压缩到文件`<filename.hzip>`中。被压缩的文件必须是以`.txt`为扩展名的文本文件，生成的压缩文件名同文本文件，但扩展名为`.hzip`。

当命令行有`-u`参数时，对当前目录下压缩文件`<filename.hzip>`进行解压，被解压的文件必须是以`.hzip`为扩展名的文件，解压后的文本文件名同压缩文件，但扩展名为`.txt`。

命令hzip.exe应具有一定的对命令行参数错误处理能力，如参数个数不对、参数格式不正确等。下面为命令错误使用及提示信息，错误提示信息显示在屏幕上：

1. ```
	>hzip
	Usage: hzip.exe [-u] <filename>
	```

2. ```
	>hzip srcfile.txt objfile.hzip
	Usage: hzip.exe [-u] <filename>
	```

3. ```
	>hzip -h srcfile.txt
	Usage: hzip.exe [-u] <filename>
	```

4. ```
	>hzip -u myfile.c
	File extension error!
	```

5. ```
	>hzip myfile.c
	File extension error!
	```

## 5.3 输出形式

hzip.exe工具压缩后`<filename.hzip>`文件格式如下：第一部分为ASCII码与Huffman码对照码表，第二部分为以Huffman编码形式的压缩后的文件。

ASCII码与Huffman码对照码表格式如下：

1. 从文件头开始第1个字节为码表长度，即压缩文件时ASCII码与Huffman码对照表中实际字符个数，即字符频率为非0的字符个数，包括文件结束符

2. 从文件头开始第2个字节为相应码表内容，每个码表项依次为每个字符的ASCII码与相应的Huffman码信息，码表项按ASCII码由小至大排列。每个码表项由3部分组成，第1部分为字符ASCII码，占一个字节；第2部分为其对应Huffman码二进制长度，占一个字节；第3部分为其对应Huffman码，占不定长位；每个码表项要占完整字节，多余位要补0。

对hzip.exe工具压缩后的`.hzip`文件执行相应的解压命令将得到压缩前文件。

若命令行参数错误，则错误提示信息显示在屏幕上。

## 5.4 样例

`myfile.txt`文件内容

```
I will give you some advice about life. Eat more roughage; Do more than others expect you to do and do it pains; Remember what life tells you; Do not take to heart every thing you hear. Do not spend all that you have. Do not sleep as long as you want.
```

`myfile.hzip`文件内容

该文件为二进制文件，无法直接显示，需要使用二进制文件查看器查看

![图片4.png](https://judge.buaa.edu.cn/userfiles/image/2021/1619509744054086833.png)

# 6 片段编程

## 6.0 问题描述

补全下面的程序，以完成Huffman编码压缩文件

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 32
struct tnode
{
    char c;                
    int weight;
    struct tnode *left, *right;
};
int Ccount[128] = {0};
struct tnode *Root = NULL;
char HCode[128][MAXSIZE]={{0}};  
int Step = 0;
FILE *Src, *Obj;
void statCount();
void createHTree();
void makeHCode();
void atoHZIP();

void print1();
void print2(struct tnode *p);
void print3();
void print4();

int main()
{
    if((Src=fopen("input.txt","r"))==NULL)
    {
    	fprintf(stderr, "%s open failed!\n", "input.txt");
        return 1;
    }
    if((Obj=fopen("output.txt","w"))==NULL)
    {
        fprintf(stderr, "%s open failed!\n", "output.txt");
        return 1;
    }
    scanf("%d", &Step);  
    statCount();
    (Step==1) ? print1() : 1;       
    createHTree();
    (Step==2) ? print2(Root) : 2;
    makeHCode();
    (Step==3) ? print3() : 3;
    (Step>=4) ? atoHZIP(), print4() : 4;
    fclose(Src);
    fclose(Obj);
    return 0;
}
```

## 6.1 片段1

```c
void statCount()
{
    char ch;
    while ((ch = fgetc(Src)) != EOF)
    {
        Ccount[ch]++;
    }
    Ccount[0] = 1;
}
```

## 6.2 片段2

```c
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
struct ListNode* insert(struct ListNode* head, struct tnode* val)
{
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
```

## 6.3 片段3

```c
void dfs(struct tnode* node, char* password, int position)
{
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
```

## 6.4 片段4

```c
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
```
