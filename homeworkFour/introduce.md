# 1 栈操作

## 1.1 问题描述

假设给定的整数栈初始状态为空，栈的最大容量为100。从标准输入中输入一组栈操作，按操作顺序输出出栈元素序列。

栈操作：1表示入栈操作，后跟一个整数为入栈元素；0表示出栈操作；-1表示操作结束。

提交文件名为`"stack.c"`

## 1.2 输入形式

从标准输入读取一组栈操作，入栈的整数和表示栈操作的整数之间都以一个空格分隔。

## 1.3 输出形式

在一行上按照操作的顺序输出出栈元素序列，以一个空格分隔各元素，最后一个元素后也要有一个空格。

如果栈状态为空时进行出栈操作，或栈满时进行入栈操作，则输出字符串`“error”`并且字符串后也要有一空格。

所有操作都执行完后，栈也有可能不为空。

## 1.4 样例

输入

```
1 3 1 5 1 7 0 0 1 8 0 1 12 1 13 0 0 0 0 1 90 1 89 0 -1
```

输出

```
7 5 8 13 12 3 error 89
```

# 2 C程序括号匹配检查

## 2.1 问题描述

编写一程序检查C源程序文件中`{}()`等括号是否匹配，并输出第一个检测到的不匹配的括号及所对应括号所在的行号（程序中同一类括号只有一个不匹配）。

注意：

1. 除了括号可能不匹配外，输入的C源程序无其它语法错误
2. 字符常量、字符串常量及注释中括号不应被处理，注释包括单行注释`//`和多行注释`/* */`
3. 字符常量和字符串常量中不包含转义字符`\'`和`\"`
4. 程序中出现有意义括号的个数不超过200个

不匹配判断规则：

1. 当检测的程序括号为`{`时，若其前序尚未匹配的括号为`(`，输出该左括号`(`及所在行号
2.  当遇到一个不匹配的右括号`)`或`}`时，输出该右括号及所在行号
3. 当程序处理完毕时，还存在不匹配的左括号时，输出该左括号及所在行号

提交文件名为`"bracket.c"`

## 2.2 输入形式

打开当前目录下文件`"example.c"`查询其括号是否匹配。该文件中每行字符数不超过200。

## 2.3 输出形式

若存在括号不匹配时，应输出首先能判断出现不匹配的括号及其所在的行号。

当出现括号不匹配时，按下面要求输出相关信息：

```
without maching <x> at line <n>
```

其中`<x>`为括号，`<n>`为该括号所在的行号。

若整个程序括号匹配，输出所有括号，中间没有空格。

## 2.4 样例

### 2.4.1 样例1

输入文件`example.c`内容

```
#include<stdio.h>
int main(){
printf("{ hello world }\n"); // }
)
```

输出

```
without maching ')' at line 4
```

### 2.4.2 样例2

输入

```
#include<stdio.h>
int main(){
printf("{ hello world }d\n"); /* }*/
```

输出

```
without maching '{' at line 2
```

### 2.4.3 样例3

输入

```
#include<stdio.h>
int main(){
printf("{ hello world }d\n"); /* }*/
}
```

输出

```
(){()}
```

# 3 计算器

## 3.1 问题描述

从标准输入中读入一个算术运算表达式，计算表达式结果，并输出。

要求：

1. 表达式运算符只有`+ - * /`，表达式末尾的`=`字符表示表达式输入结束，表达式中可能会出现空格
2. 表达式中会出现圆括号，括号可能嵌套，不会出现错误的表达式
3. 表达式中出现的操作数都是十进制整数常量，但要求运算结果为浮点型，例如`5/2`结果应为`2.5`

提交文件名为`"cal.c"`

## 3.2 输入形式

从键盘输入一个以`=`结尾的算术运算表达式。操作符和操作数之间可以有空格分隔。

## 3.3 输出形式

在屏幕上输出计算结果，小数点后保留两位有效数字。

## 3.4 样例

输入

```
24 / ( 1 + 5 / 3 + 36 / 6 / 2 - 2) * ( 12 / 2 / 2 ) =
```

输出

```
19.64
```

# 4 文本编辑操作

## 4.1 问题描述

编写一程序模拟文本编辑操作。

首先从标准输入读取一行字符串，其中字符个数不超过512，该行字符串是已经过n步编辑操作后的结果，n大于0且小于等于10。然后从下一行读取n，以及已发生过的n步编辑操作，编辑操作分行输入，输入格式为：

```
op pos str
```

其中`op`为编辑操作命令编码，1表示插入或2表示删除操作；`pos`表示插入或删除的位置；`str`表示已经插入或删除的字符串，字符串中间没有空格。各数据间以一个空格分隔。

然后在空一行后，再分行输入当前将要进行的编辑操作，包括如下四种操作：

1. 插入`1 pos str`

	表示将在`pos`位置插入字符串`str`。

2. 删除`2 pos n`

	表示将从`pos`位置开始删除`n`个字符，若要删除的字符个数多于已有字符个数则按实际字符数删除。

	提示：为了能够撤销删除操作，应按`2 pos str`形式保存命令。

3. 撤销`3`

	表示撤销最近执行的插入或删除操作，可以进行多次撤销操作。

	注意：也可以撤销之前已经发生过的n步编辑操作中的操作。

4. 结束`-1`

	表示退出编辑操作，在屏幕上输出最终编辑后的文本。

要求：

1. 上述所有输入的编辑操作中的字符串str都不包含空白字符，即空格符、制表符或换行符
2. 插入操作中的位置`pos`大于等于0并且小于等于当前文本的字符个数，0位置表示文本第一个字符的位置，若`pos`为当前文本的字符个数，则表示在文本最后插入字符串
3. 删除操作中的位置`pos`大于等于0并且小于当前文字的字符个数
4. 若已无操作可撤销，则再进行撤销操作无效
5. 文本在编辑过程中，总字符个数不会超过512

提交文件名为`"edit.c"`

## 4.2 输入形式

先从键盘输入一行字符串，表示已经经过n步编辑操作后的文本串。

然后在下一行输入一个正整数n，并分行输入n步插入或删除操作，表示按时间先后顺序已进行的操作，格式如上所述。

随后空一行，再分行输入将要进行的编辑操作，格式如上所述。直到输入`-1`操作为止。

## 4.3 输出形式

在屏幕上输出最终编辑后的文本内容。

## 4.4 样例

输入

```
A Stack is a container of objects that are inserted and removed according to the last-in first-out (LIFO) principle.???
4
1 20 ainer
2 0 ???
1 85 -
1 99 (LIFO)
3
2 110 10
1 110 Objects
2 98 1
2 0 1
2 108 10
3
3
3
-1
```

输出

```
A Stack is a container of objects that are inserted and removed according to the last-in first-out  principle.Objects
```

# 5 银行排队模拟

## 5.1 问题描述

一个系统模仿另一个系统行为的技术称为模拟，如飞行模拟器。模拟可以用来进行方案论证、人员培训和改进服务。计算机技术常用于模拟系统中。

生产者消费者是常见的应用模式，见于银行、食堂、打印机、医院、超市等提供服务和使用服务的应用中。这类应用的主要问题是消费者如果等待时间过长，会引发用户抱怨，影响服务质量；如果提供服务者过多，将提高运管商成本。

假设某银行网点有五个服务窗口，分别为三个对私、一个对公和一个外币窗口。银行服务的原则是先来先服务。通常对私业务人很多，其它窗口人则较少，可临时改为对私服务。假设当对私窗口等待服务的客户平均排队人数大于或等于7人时，等待客户将可能有抱怨，影响服务质量，此时银行可临时将其它窗口中一个或两个改为对私服务，当平均排队客户少于7人时，将立即恢复原有业务。设计一个程序用来模拟银行服务。

说明：

1. 增加服务窗口将会增加成本或影响其它业务，因此，以成本增加或影响最小为原则来增加服务窗口，即如果增加一个窗口就能使得按窗口平均等待服务人数小于7人，则只增加一个窗口。一旦按窗口平均等待服务人数小于7人，就减少一个所增加的窗口。

2. 为了简化问题，假设新到客户是在每个服务周期开始时到达。

3. 根据客户业务服务时间将客户分为3类：

	1. 简单业务
	2. 普通业务
	3. 复杂业务

	分别对应花费1-3个时间周期。

4. 当等待服务人数发生变化时，即新客户到达或有客户已接受服务时，及时计算按实际服务窗口平均等待服务人数，并按相应策略调整服务窗口数，即增加或减少额外的服务窗口，但对私窗口不能减少。

5. 只在获取新客户(不管到达新客户数是否为0)时，才按策略调整服务窗口数。进一步讲，增加服务窗口只在有客户到达的周期内进行，也就是说增加窗口是基于客户的感受，银行对增加窗口是不情愿的，因为要增加成本，一旦不再有新客户来，银行是不会再增加服务窗口的。一旦有客户去接受服务，即等待客户减少，银行将根据策略及时减少服务窗口。因此，在每个周期内，有客户去接受服务后要马上判断是否减少服务窗口，因为能减少成本，银行是积极的。

6. 本问题中假设对公和对外币服务窗口在改为对私服务时及服务期间没有相应因公或外币服务新客户到达，即正好空闲，同时要求以增加成本或影响最小为前提，来尽最大可能减少对私服务客户等待时间。

提交文件名为`"bank.c"`

## 5.2 输入形式

首先输入一个整数表示时间周期数，然后下一行输入每个时间周期到达的客户人数；再依次分行输入每个时间周期到达的因私业务的客户类别。

注意：一个时间周期指的是银行处理一笔业务的平均处理时间，可以是一分钟、三分钟或其它。每行中的整数之间以一个空格分隔。

例如

```
6
2 5 8 11 15 6
1 3
2 2 1 3 2
......
```

## 5.3 输出形式

每个客户等待服务的时间周期数。输出形式如下：

```
<consumer> : <time>
```

其中`<consumer>`为用户序号，`<time>`为等待周期数，后面为换行符

## 5.4 样例

输入

```
4
2 5 13 11
1 3
2 2 1 3 2
1 1 1 1 3 3 2 2 1 2 3 1 1
3 3 2 1 3 1 1 3 1 3 3
```

输出

```
1 : 0
2 : 0
3 : 0
4 : 0
5 : 2
6 : 2
7 : 2
8 : 1
9 : 2
10 : 3
11 : 3
12 : 4
13 : 4
14 : 4
15 : 6
16 : 7
17 : 7
18 : 8
19 : 8
20 : 9
21 : 8
22 : 9
23 : 10
24 : 11
25 : 12
26 : 12
27 : 12
28 : 13
29 : 13
30 : 14
31 : 15
```

# 6 函数调用关系

## 6.1 问题描述

给定某能正常运行结束的用户函数调用栈信息，当一个函数被调用时将入栈，当调用返回时，将出栈。

编写程序，对函数调用栈信息进行分析，依据函数入栈和出栈信息，分析函数调用关系，即一个函数调用了哪些不同函数。并按运行时调用序输出调用关系。

说明：

1. 在一个函数中，同一函数有可能被调用多次，输出调用关系时只输出一次；若一个函数没有调用其它函数，则不输出调用关系
2. 函数运行时调用序是指函数在调用栈中的出现序
3. 程序中不存在递归调用。函数名符合C语言标识符的规定，函数名长度不超过20，每个函数最多调用不超过10个不同函数，程序中用户定义的函数个数不超过100

算法提示：当一个函数入栈时，它就是当前栈顶函数调用的一个函数。

提交文件名为`"func.c"`

## 6.2 输入形式

假设用`8`表示函数入栈操作，用`0`表示当前函数出栈。

当操作为`8`入栈时，输入形式为：

```
<op> <funcname>
```

当操作为`0`出栈时，输入形式为：

```
<op>
```

所有入栈操作和出栈操作都是从标准输入分行输入，假设调用栈中函数个数最多不超过200。开始时，调用栈为空，当调用栈再次为空时，输入结束。

## 6.3 输出形式

按运行时调用先后顺序输出函数调用关系到标准输出，每行为一个函数的调用关系信息。包括函数名及被调用函数。函数与被调用函数间用一个英文冒号`:`分隔，被调用函数间用一个英文逗号`,`分隔，最后一个函数名后为换行符。若一个函数没有调用其它函数，则不输出。

## 6.4 样例

输入

```
8 main
8 input
0
8 mysqrt
0
8 findA
0
8 findB
8 area
8 mysin
0
8 mycos
0
8 mysqrt
0
0
0
8 findC
8 area
8 mysin
0
0
8 mysqrt
8 max
0
0
0
8 output
0
0
```

输出

```
main:input,mysqrt,findA,findB,findC,ouput
mysqrt:max
findB:area
area:mysin,mycos,mysqrt
findC:area,mysqrt
```
