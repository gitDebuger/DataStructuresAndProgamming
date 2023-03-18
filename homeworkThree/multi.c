#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
struct ITEM{
    int coefficient;
    int exponent;
    struct ITEM* next;
};
typedef struct ITEM* item;
typedef struct ITEM* polynomial;
polynomial insert(polynomial poly, int coef, int expo){
    if (poly == NULL){
        polynomial res = malloc(sizeof(struct ITEM));
        res->coefficient = coef;
        res->exponent = expo;
        res->next = NULL;
        return res;
    }
    if (expo > poly->exponent){
        polynomial res = malloc(sizeof(struct ITEM));
        res->coefficient = coef;
        res->exponent = expo;
        res->next = poly;
        return res;
    }
    if (expo == poly->exponent){
        poly->coefficient += coef;
        return poly;
    }
    item it = poly;
    while (it->next && it->next->exponent > expo){
        it = it->next;
    }
    if (it->next == NULL){
        it->next = malloc(sizeof(struct ITEM));
        it->next->coefficient = coef;
        it->next->exponent = expo;
        it->next->next = NULL;
    }
    else if (it->next->exponent == expo){
        it->next->coefficient += coef;
    }
    else if (it->next->exponent < expo){
        item temp = malloc(sizeof(struct ITEM));
        temp->next = it->next;
        temp->coefficient = coef;
        temp->exponent = expo;
        it->next = temp;
    }
    return poly;
}
polynomial multiply(polynomial poly1, polynomial poly2){
    item item1, item2;
    polynomial ansPoly = NULL;
    for (item1 = poly1; item1 != NULL; item1 = item1->next){
        for (item2 = poly2; item2 != NULL; item2 = item2->next){
            int insCoef = item1->coefficient * item2->coefficient;
            int insExpo = item1->exponent + item2->exponent;
            ansPoly = insert(ansPoly, insCoef, insExpo);
        }
    }
    return ansPoly;
}
int main(){
    polynomial polyA = NULL, polyB = NULL;
    polynomial resPoly = NULL;
    int expo = 0, coef = 0;
    while (scanf("%d %d", &coef, &expo) != EOF){
        polyA = insert(polyA, coef, expo);
        if (getchar() == '\n'){
            break;
        }
    }
    while (scanf("%d %d", &coef, &expo) != EOF){
        polyB = insert(polyB, coef, expo);
    }
    resPoly = multiply(polyA, polyB);
    for (item it = resPoly; it != NULL; it = it->next){
        printf("%d %d ", it->coefficient, it->exponent);
    }
}