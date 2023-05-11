#include <stdio.h>
#include <stdlib.h>
struct STUDENT{
    int id;
    char name[24];
    int seatNum;
};
typedef struct STUDENT student;
int cmp(const void* _a, const void* _b){
    student* a = (student*)_a;
    student* b = (student*)_b;
    if (a->seatNum == b->seatNum){
        return a->id - b->id;
    }
    return a->seatNum - b->seatNum;
}
int cmp2(const void* _a, const void* _b){
    student* a = (student*)_a;
    student* b = (student*)_b;
    return a->id - b->id;
}
int main(){
    FILE* fr = fopen("in.txt", "r");
    FILE* fw = fopen("out.txt", "w");
    student people[100];
    int numOfStudents;
    scanf("%d", &numOfStudents);
    for (int i = 0; i < numOfStudents; i++){
        fscanf(fr, "%d %s %d", &people[i].id, people[i].name, &people[i].seatNum);
    }
    qsort(people, numOfStudents, sizeof(student), cmp);
    int m, n, q;
    m = people[numOfStudents - 1].seatNum;
    n = numOfStudents;
    q = m < n ? m : n;
    int front, rare, num;
    for (front = 0, rare = numOfStudents - 1, num = 1; num <= q; num++){
        while (num < people[front].seatNum && num <= q){
            people[rare--].seatNum = num++;
        }
        if (num > q) break;
        while (num == people[front].seatNum) front++;
    }
    int maxNum = 0;
    for (int i = 0; i < numOfStudents; i++){
        if (maxNum < people[i].seatNum){
            maxNum = people[i].seatNum;
        }
    }
    for (int i = 1; i < numOfStudents; i++){
        if (people[i].seatNum == people[i - 1].seatNum){
            people[i].seatNum = maxNum + 1;
            maxNum++;
        }
    }
    qsort(people, numOfStudents, sizeof(student), cmp2);
    for (int i = 0; i < numOfStudents; i++){
        fprintf(fw, "%d %s %d\n", people[i].id, people[i].name, people[i].seatNum);
    }
    return 0;
}