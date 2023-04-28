#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
typedef struct fifo fifo;

struct node {
    int val;
    node* link;
};

struct fifo {
    node* front;
    node* back;
    int size;
};

fifo* newFifo() {
    fifo* f = malloc(sizeof(fifo));
    f->size = 0;
    f->front = NULL;
    f->back = NULL;
    return f;
}
void deleteFifo(fifo* f) {
    node* temp1 = f->front;
    node* temp2;
    while (temp1 != NULL) {
        temp2 = temp1->link;
        free(temp1);
        temp1 = temp2;
    }
    free(f);
}

void addToFifo(fifo* l, int value) {
    node* newNode = malloc(sizeof(node));
    newNode->val = value;
    newNode->link = NULL;
    if (l->size > 0) {
        l->back->link = newNode;
        l->back = newNode;
    }
    else {
        l->back = newNode;
        l->front = newNode;
    }
    l->size++;

}
void showFifo(fifo* l) {
    node* cur = l->front;
    while (cur != NULL) {
        printf("%d -> ", cur->val);
        cur = cur->link;
    }
    printf("\n\n");
}
int getFrontFifo(fifo* l) {
    if (l->front != NULL)
        return l->front->val;
    return 0;
}
void delFromFifo(fifo* l) {
    if (l->front != NULL) {
        node* temp = (l->front)->link;
        free(l->front);
        l->front = temp;
        l->size--;
    }
}


int main() {
   fifo* f = newFifo();
   printf("FIFO dodawanie:\n");
   for (int i = 0; i < 100; i++) {
       if (i%10 == 0 && f->size <= 30) {
           printf("\nFIFO stan przy size %d:\n", f->size);
           showFifo(f);
       }
       printf("+%d ", i);
       addToFifo(f,i);
   }
   printf("\n\nFIFO usuwanie:\n");
   for (int i = 0; i < 100; i++) {
       if (i%10 == 0 && f->size <= 30) {
           printf("\nFIFO stan przy size %d:\n", f->size);
           showFifo(f);
       }
       printf("-%d ", getFrontFifo(f));
       delFromFifo(f);
   }
   printf("\n");
   deleteFifo(f);



   return 0;
}