#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
typedef struct lifo lifo;

struct node {
    int val;
    node* link;
};

struct lifo {
    node* top;
    int size;
};
lifo* newLifo() {
    lifo* l = malloc(sizeof(lifo));
    l->size = 0;
    l->top = NULL;
    return l;
}
void deleteLifo(lifo* l) {
    node* temp1 = l->top;
    node* temp2;
    while (temp1 != NULL) {
        temp2 = temp1->link;
        free(temp1);
        temp1 = temp2;
    }
    free(l);
}
void addToLifo(lifo* l, int value) {
    node* newNode = malloc(sizeof(node));
    newNode->val = value;
    newNode->link = l->top;
    l->top = newNode;
    l->size++;
}
void showLifo(lifo* l) {
    node* cur = l->top;
    while (cur != NULL) {
        printf("%d -> ", cur->val);
        cur = cur->link;
    }
    printf("\n\n");
}
int getTopLifo(lifo* l) {
    if (l->top != NULL)
        return l->top->val;
    return 0;
}
void delFromLifo(lifo* l) {
    if (l->top != NULL) {
        node* temp = (l->top)->link;
        free(l->top);
        l->top = temp;
        l->size--;
    }
}

int main() {
   lifo* l = newLifo();
   printf("LIFO dodawanie:\n");
   for (int i = 0; i < 100; i++) {
       if (i%10 == 0 && l->size <= 30) {
           printf("\nLIFO stan przy size %d:\n", l->size);
           showLifo(l);
       }
       printf("+%d ", i);
       addToLifo(l,i);
   }
   printf("\n\nLIFO usuwanie:\n\n");
   for (int i = 0; i < 100; i++) {
       if (i%10 == 0 && l->size <= 30) {
           printf("\nLIFO stan przy size %d:\n", l->size);
           showLifo(l);
       }
       printf("-%d ", getTopLifo(l));
       delFromLifo(l);
   }
   printf("\n");
   deleteLifo(l);
   return 0;
}