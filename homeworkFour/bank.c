#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/* 维护五个窗口的状态和客户队列的状态 */
/* 每个时间周期更新窗口状态和客户队列的状态 */
/* 对于客户队列，分别用两个指针指向队列头和尾 */
/* 最后输出整个队列的状态 */
/* 窗口结构体包含当前窗口是否营业，是否空闲以及多少个时间周期之后转为空闲 */
/* 客户结构体包含业务类型，到达时间以及等待总时间 */
struct WINDOW{
    bool isFree;
    int numOfPeriod;
};
struct CLIENT{
    int category;
    int arrivePeriod;
    int waitTime;
};
typedef struct WINDOW window;
typedef struct CLIENT client;
/* 问题处理阶段 */
/* 0.将到达客户加入等待队列 */
/* 1.判断是否需要增加窗口 */
/* 2.窗口处理用户服务，包括将等待客户移出等待队列，以及更新窗口空闲状态 */
/* 3.增加等待队列中用户的等待时间 */
/* 4.判断是否需要减少窗口 */
/* 注意：减少服务窗口时，不影响当前正在接受服务的用户的服务状态，*/
/* 也就是说如果需要关闭该窗口，也会在服务完这个用户之后才会正式关闭 */
int main(){
    window wins[5]; // 五个窗口，前三个为对私窗口，后面两个分别为对公和外币
    int numOfPeriod; // 时间周期总数
    int* cliPerPeriod; // 每个周期客户数量
    client* customers; // 客户队列
    int totalClients = 0; // 客户总数
    scanf("%d", &numOfPeriod);
    cliPerPeriod = malloc(numOfPeriod * sizeof(int));
    for (int i = 0; i < numOfPeriod; i++){
        scanf("%d", cliPerPeriod + i);
        totalClients += cliPerPeriod[i];
    }
    customers = malloc(totalClients * sizeof(client));
    int front = 0;
    int rear = 0;
    int cate;
    int totalWindows = 3; // 初始窗口总数设置为3
    // 初始化窗口状态
    for (int i = 0; i < 5; i++){
        wins[i].isFree = true;
        wins[i].numOfPeriod = 0;
    }
    int curPeriod = 0;
    for (int i = 0; i < numOfPeriod; i++){
        // 第一步，将当前时间周期到达的客户加入等待队列
        curPeriod++;
        for (int j = 0; j < cliPerPeriod[i]; j++){
            scanf("%d", &cate);
            customers[rear].arrivePeriod = curPeriod;
            customers[rear].category = cate;
            rear++;
        }
        // 第二步，排队人数增加，按需调整窗口数量
        if ((rear - front) / totalWindows >= 7){
            if (totalWindows == 3){
                if (rear - front < 28) totalWindows = 4;
                else totalWindows = 5;
            }
            else totalWindows = 5;
        }
        // 第三步，各个窗口轮询，空闲窗口从等待队列中获取客户
        for (int j = 0; j < totalWindows; j++){
            if (rear == front) break; // 等待队列已经空置，结束轮询
            if (wins[j].isFree){
                wins[j].numOfPeriod = customers[front].category;
                wins[j].isFree = false;
                customers[front].waitTime = curPeriod - customers[front].arrivePeriod;
                front++;
            }
        }
        // 第四步，经过一个时间周期，更新窗口空闲状态
        for (int j = 0; j < 5; j++){
            if (wins[j].numOfPeriod > 0){
                wins[j].numOfPeriod--;
                if (wins[j].numOfPeriod == 0){
                    wins[j].isFree = true;
                }
            }
        }
        // 第五步，窗口数量减少，按需调整窗口数量
        if ((rear - front) / totalWindows < 7){
            if (totalWindows == 5){
                if (rear - front >= 21) totalWindows = 4;
                else totalWindows = 3;
            }
            else totalWindows = 3;
        }
    }
    // 不再有客户到达，继续服务等待队列中的用户
    while (rear > front){
        curPeriod++;
        // 窗口轮询
        for (int j = 0; j < totalWindows; j++){
            if (rear == front) break; // 等待队列已经空置，结束轮询
            if (wins[j].isFree){
                wins[j].numOfPeriod = customers[front].category;
                wins[j].isFree = false;
                customers[front].waitTime = curPeriod - customers[front].arrivePeriod;
                front++;
            }
        }
        // 经过一个时间周期，更新窗口空闲状态
        for (int j = 0; j < 5; j++){
            if (wins[j].numOfPeriod > 0){
                wins[j].numOfPeriod--;
                if (wins[j].numOfPeriod == 0){
                    wins[j].isFree = true;
                }
            }
        }
        // 窗口数量减少，按需调整窗口数量
        if ((rear - front) / totalWindows < 7){
            if (totalWindows == 5){
                if (rear - front >= 21) totalWindows = 4;
                else totalWindows = 3;
            }
            else totalWindows = 3;
        }
    }
    // 打印输出结果
    for (int i = 0; i < totalClients; i++){
        printf("%d : %d\n", i + 1, customers[i].waitTime);
    }
    return 0;
}