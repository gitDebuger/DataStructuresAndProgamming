#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct person{
    char name[25];
    char phoneNumber[12];
    int rank;
};
int cmp(const void* _a, const void* _b){
    struct person* a = (struct person*)_a;
    struct person* b = (struct person*)_b;
    int num = strcmp(a->name, b->name);
    if (num > 0) return 1;
    if (num < 0) return -1;
    return a->rank - b->rank;
}
int main(){
    struct person people[100];
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        scanf("%s %s", people[i].name, people[i].phoneNumber);
        people[i].rank = i;
    }
    qsort(people, n, sizeof(struct person), cmp);
    printf("%s %s\n", people[0].name, people[0].phoneNumber);
    for (int i = 0, j = 1, count = 1; j < n; j++){
        if (strcmp(people[i].name, people[j].name) == 0){
            if (strcmp(people[i].phoneNumber, people[j].phoneNumber) == 0){
                i = j;
                continue;
            }
            printf("%s_%d %s\n", people[j].name, count++, people[j].phoneNumber);
        }
        else{
            printf("%s %s\n", people[j].name, people[j].phoneNumber);
            count = 1;
            i = j;
        }
    }
    return 0;
}