# 1. 五子棋危险判断

## 1.1 问题描述

已知两人分别执白棋和黑棋在一个围棋棋盘上下五子棋，若同一颜色的棋子在同一条横行、纵行或斜线上连成$5$个棋子，则执该颜色棋子的人获胜。编写程序读入某一时刻下棋的状态，并判断是否有人即将获胜，即：同一颜色的棋子在同一条横行、纵列或斜线上连成$4$个棋子，且该$4$个棋子的两端至少有一端为空位置。

输入的棋盘大小是$19×19$，用数字`0`表示空位置（即没有棋子），用数字`1`表示该位置下了一白色棋子，用数字`2`表示该位置下了一黑色棋子。假设同一颜色的棋子在同一条横行、纵列或斜线上连成的棋子个数不会超过$4$个，并且最多有一人连成线的棋子个数为$4$。

提交文件名为`"chess.c"`

## 1.2 输入形式

从控制台输入用来表示棋盘状态的数字`0`、`1`或`2`；每行输入$19$个数字，各数字之间以一个空格分隔，每行最后一个数字后没有空格；共输入$19$行表示棋盘状态的数字。

## 1.3 输出形式

若有人即将获胜，则先输出即将获胜人的棋子颜色，`1`表示白色棋子，`2`表示黑色棋子，然后输出英文冒号`:`，最后输出连成$4$个棋子连线的起始位置。

棋盘横行自上往下、纵列自左往右从$1$开始计数，横行最小的棋子在棋盘上的横行数和纵列数作为连线的起始位置，若在同一行上，则纵列数最小的棋子位置作为起始位置，两数字之间以一个英文逗号`,`作为分隔符。

`"[12]:[1-19],[1-19]"`

若没有人获胜，则输出`No`

无论输出什么结果，最后都要有回车换行符。

## 1.4 样例

**样例1**

输入

```c
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 2 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 2 0 1 1 2 0 0 0 0 0 0 0
0 0 0 0 0 2 1 1 1 1 2 2 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 2 1 2 0 0 0 0 0 0 0 0
0 0 0 0 0 0 1 1 0 2 2 0 0 0 0 0 0 0 0
0 0 0 0 0 2 0 1 0 0 2 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 1 2 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```

输出

```c
1:9,8
```

**样例2**

输入

```c
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 2 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 2 2 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```

输出

```c
No
```

# 2. 字符串替换

## 2.1 问题描述

编写程序将一个指定文件中某一字符串替换为另一个字符串。要求：

1. 被替换字符串若有多个，均要被替换；
2. 指定的被替换字符串，大小写无关。

提交文件名为`"replace.c"`

## 2.2 输入形式

给定文件名为`"filein.txt"`。从控制台输入两行字符串，字符串不含空格，行末尾都有回车换行符，分别表示被替换的字符串和替换字符串。

## 2.3 输出形式

将替换后的结果输出到文件`"fileout.txt"`中。

## 2.4 样例

控制台输入

```c
in
out
```

filein.txt文件内容

```
#include <stdio.h>
void main()
{
	FILE * IN;
	if((IN=fopen("in.txt","r"))==NULL)
	{
		printf("Can&rsquo;t open in.txt!");
		return;
	}
	fclose(IN);
}
```

fileout.txt文件内容

```
#outclude <stdio.h>
void maout()
{
	FILE * out;
	if((out=fopen("out.txt","r"))==NULL)
	{
		prouttf("Can&rsquo;t open out.txt!");
		return;
	}
	fclose(out);
}
```

# 3. 加密文件

## 3.1 问题描述

有一种加密方法为：其使用一个字母串作为密钥，字母串可以含重复字母，字母个数不超过`50`。假定密钥单词串为`feather`，则先去掉密钥单词中的重复字母得到单词串`feathr`，然后再将字母表中的其它字母以反序追加到`feathr`的后面。

最终得到的对应关系为

| a    | b    | c    | d    | e    | f    | g    | h    | i    | j    | k    | l    | m    | n    | o    | p    | q    | r    | s    | t    | u    | v    | w    | x    | y    | z    |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| f    | e    | a    | t    | h    | r    | z    | y    | x    | w    | v    | u    | s    | q    | p    | o    | n    | m    | l    | k    | j    | i    | g    | d    | c    | b    |

第一行为原文字符，第二行为密文字符，其他字符不进行加密。

编写一个程序，用这种密码加密文件。要加密的文件名为`"encrypt.txt"`，加密后的文件名为`"output.txt"`，输入文件中字母全为小写字母，并且输入密钥也全为小写字母。

提交文件名为`"encrypt.c"`

## 3.2 输入形式

从标准输入中输入密钥串，并从文件`"encrypt.txt"`中读入要加密的内容。

## 3.3 输出形式

加密后结果输出到文件`"output.txt"`中。

## 3.4 样例

标准输入

```
feather
```

encrypt.txt文件内容

```
c language is wonderful.
```

output.txt文件内容

```
a ufqzjfzh xl gpqthmrju.
```

# 4. 通讯录整理

## 4.1 问题描述

读取一组电话号码簿，电话号码簿由姓名和手机号码组成，将重复出现的项删除，姓名和电话号码都相同的项为重复项，只保留第一次出现的项，并对姓名相同手机号码不同的项进行如下整理：

1. 首次出现的项不作处理，第一次重复的姓名后面加`_1`，第二次重复的姓名后面加`_2`，依次类推。号码簿中姓名相同的项数最多不超过`10`个。
2. 最后对整理后的电话号码簿按照姓名进行从小到大排序，并输出排序后的电话号码簿。

提交文件名为`"sort.c"`

## 4.2 输入形式

先从标准输入读取电话号码个数，然后分行输入姓名和电话号码，姓名由不超过`20`个英文小写字母组成，电话号码由`11`位数字字符组成，姓名和电话号码之间以一个空格分隔，输入的姓名和电话号码项不超过`100`个。

## 4.3 输出形式

按照姓名从小到大的顺序分行输出最终的排序结果，先输出姓名再输出电话号码，以一个空格分隔。

## 4.4 样例

输入

```
15
liping 13512345678
zhaohong 13838929457
qiansan 13900223399
zhouhao 18578294857
anhai 13573948758
liping 13512345678
zhaohong 13588339922
liping 13833220099
boliang 15033778877
zhaohong 13838922222
tianyang 18987283746
sunnan 13599882764
zhaohong 13099228475
liushifeng 13874763899
caibiao 13923567890
```

输出

```
anhai 13573948758
boliang 15033778877
caibiao 13923567890
liping 13512345678
liping_1 13833220099
liushifeng 13874763899
qiansan 13900223399
sunnan 13599882764
tianyang 18987283746
zhaohong 13838929457
zhaohong_1 13588339922
zhaohong_2 13838922222
zhaohong_3 13099228475
zhouhao 18578294857
```

# 5. 小型图书管理系统

## 5.1 问题描述

小明同学特别喜欢买书看书。由于书较多，摆放杂乱，找起来非常麻烦。这学期小明同学上了数据结构与程序设计课后，决定改变这种状况：用C开发一个小型图书管理系统。

系统中包含的图书信息有：书名、作者、出版社、出版日期等。首先，图书管理系统对已有的书按书名字典序进行摆放以便查找。该管理系统可以对新书库中图书条目进行如下操作：

1. 录入。新增书录入到书库中，从输入中读入一条图书信息插入到已排序好的图按书文件相关位置处
2. 查找。按书名或书名中关键字信息在书库中查找相关图书信息，若有多本书，按字典序输出。
3. 删除。输入书名或书名中关键字信息，从书库中查找到相关书并将其删除，并更新书库。

## 5.2 输入形式

原始的图书信息保存在当前目录下的`"books.txt"`中。

用户操作从控制台读入首先输入操作功能序号：`1`代表录入操作，`2`代表查找操作，`3`代表删除操作，`0`代表将已更新的图书信息保存到书库中并退出程序；然后在下一行输入相应的操作信息，录入操作后要输入一条图书信息，查找和删除操作后只要输入书名或书名中部分信息。

程序执行过程中可以进行多次操作，直到退出程序，即输入操作0。

要求：

1. 原始文件中的图书信息与录入的图书信息格式相同，每条图书信息都在一行上，包括

	1. 书名（不超过`50`个字符）
	2. 作者（不超过`20`个字符）
	3. 出版社（不超过`30`个字符）
	4. 出版日期（不超过`10`个字符）

	只由英文字母和下划线组成，用一个空格分隔。图书信息总条数不会超过`500`。

2. 下划线字符参加排序。

3. 图书不会重名。

## 5.3 输出形式

进行录入和删除操作，系统会更新图书信息，但不会在控制台窗口显示任何信息。

进行查找操作后，将在控制台按书名字典序分行输出查找到的图书信息，书名占`50`个字符宽度，作者占`20`个字符宽度，出版社占`30`个字符宽度，出版日期占`10`个字符宽度，都靠左对齐输出。

最终按字典排序的图书信息保存在当前目录下的`"ordered.txt"`中，每条图书信息占一行，格式与查找输出的图书信息相同。

## 5.4 样例

books.txt中保存的原始图书信息为

```
The_C_programming_language Kernighan Prentice_Hall 1988
Programming_in_C Yin_Bao_Lin China_Machine_Press 2013
Data_structures_and_Algorithm_Analysis_in_C Mark_Allen_Weiss Addison_Wesley 1997
ANSI_and_ISO_Standard_c Plauger Microsoft_Press 1992
Data_structures_and_program_design_in_C Robert_Kruse Pearson_Education 1997
Computer_network_architectures Anton_Meijer Computer_Science_Press 1983
C_programming_guidelines Thomas_Plum Prentice_Hall 1984
Data_structures_using_C Tenenbaum Prentice_Hall 1990
Operating_system_concepts Peterson Addison_Wesley 1983
Computer_networks_and_internets Douglas_E_Come Electronic_Industry 2017
```

标准输入为

```
1
Data_structures_and_C_programs Christopher Addison_Wesley 1988
2
structure
1
The_C_programming_tutor Leon_A_Wortman R_J_Brady 1984
2
rogram
3
rogramming
0
```

标准输出

用户输入`2 structure`后控制台输出

```
Data_structures_and_Algorithm_Analysis_in_C       Mark_Allen_Weiss    Addison_Wesley                1997
Data_structures_and_C_programs                    Christopher         Addison_Wesley                1988
Data_structures_and_program_design_in_C           Robert_Kruse        Pearson_Education             1997
Data_structures_using_C                           Tenenbaum           Prentice_Hall                 1990
```

用户输入`2 rogram`后控制台输出

```
C_programming_guidelines                          Thomas_Plum         Prentice_Hall                 1984
Data_structures_and_C_programs                    Christopher         Addison_Wesley                1988
Data_structures_and_program_design_in_C           Robert_Kruse        Pearson_Education             1997
Programming_in_C                                  Yin_Bao_Lin         China_Machine_Press           2013
The_C_programming_language                        Kernighan           Prentice_Hall                 1988
The_C_programming_tutor                           Leon_A_Wortman      R_J_Brady                     1984
```

ordered.txt文件内容为

```
ANSI_and_ISO_Standard_c                           Plauger             Microsoft_Press               1992      
Computer_network_architectures                    Anton_Meijer        Computer_Science_Press        1983      
Computer_networks_and_internets                   Douglas_E_Come      Electronic_Industry           2017      
Data_structures_and_Algorithm_Analysis_in_C       Mark_Allen_Weiss    Addison_Wesley                1997      
Data_structures_and_C_programs                    Christopher         Addison_Wesley                1988      
Data_structures_and_program_design_in_C           Robert_Kruse        Pearson_Education             1997      
Data_structures_using_C                           Tenenbaum           Prentice_Hall                 1990      
Operating_system_concepts                         Peterson            Addison_Wesley                1983      
```

