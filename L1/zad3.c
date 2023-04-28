#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

typedef struct node node;
typedef struct list list;

struct node {
    int val;
    node* next;
    node* prev;
};

struct list {
    node* head;
    int size;
};
list* newList() {
    list* t = malloc(sizeof(list));
    t->size = 0;
    t->head = NULL;
    //list t = { .size = 0, .head = NULL};
    return t;
}
void deleteList(list* l) {
    node* temp1 = l->head;
    temp1->prev->next = NULL;
    node* temp2;
    while (temp1 != NULL) {
        temp2 = temp1->next;
        free(temp1);
        temp1 = temp2;
    }
    free(l);
}


void addToListFront(list* l, int value) {
    node* newNode = malloc(sizeof(node));
    newNode->val = value;
    if (l->size == 0) {
        newNode->next = newNode;
        newNode->prev = newNode;
        l->head = newNode;
    }
    else {
        node* last= l->head->prev;
        newNode->next = l->head;
        newNode->prev = last;
        last->next = newNode;
        if (l->head->next == l->head) {
            l->head->next = newNode;
        }
        last = newNode;
        l->head = newNode;
    }
    l->size++;
}
void showList(list* l) {
    node* cur = l->head;
    for (int i=0; i < l->size; i++) {
        printf("%d -> ", cur->val);
        cur = cur->next;
    }
    printf("\n\n");
}
int getFromList(list* l,int pos) {
    node* temp = l->head;
    if (temp == NULL || pos >= l->size) {
        return 0;
    }
    if (pos <= abs(l->size-pos)) {
        for (int i=0; i < pos; i++) {
            temp = temp->next;
        }
    }
    else {
        for (int i=0; i < l->size-pos; i++) {
            temp = temp->prev;
        }
    }
    return temp->val;
}

void accessList(list* l, int pos) {
    getFromList(l,pos);
}
double getAccessTime(list* l, int pos) {
   struct timeval start, stop;
   gettimeofday(&start,NULL);
   accessList(l,pos);
   gettimeofday(&stop,NULL);
   double time_taken = (double)(stop.tv_usec - start.tv_usec) / 1000 + (double)(stop.tv_sec - start.tv_sec) * 1000;
   return time_taken;
}
void getAvgAccessTime(list* l, int pos) {
   double avg = 0;
   for (int i =0; i < 100000; i++) {
       avg+= getAccessTime(l,pos);
   }
   avg /=100000;
   printf("Sredni czas dostepu elementu %d wynosi %f ms.\n",pos,avg);
}
void getAvgRandomAccessTime(list* l) {
   double avg = 0;
   for (int i =0; i < 100000; i++) {
       avg+= getAccessTime(l,rand()%l->size);
   }
   avg /=100000;
   printf("Sredni czas dostepu elementu losowego wynosi %f ms.\n",avg);
}
void merge(list* l1, list* l2) {
    node* temp = l1->head;
    if (temp == NULL) {
        return;
    }
    l1->head->prev->next = l2->head;
    l2->head->prev = l1->head->prev;
    l1->head->prev = l2->head->prev;
    l1->size += l2->size;

}


int main() {
   srand(time(NULL));
   list* l = newList();
   printf("Lista dodawanie...\n");
   for (int i = 0; i < 1000; i++) {
       addToListFront(l, rand());
   }
   getAvgAccessTime(l,100);
   getAvgAccessTime(l,250);
   getAvgAccessTime(l,400);
   getAvgAccessTime(l,500);
   getAvgAccessTime(l,600);
   getAvgAccessTime(l,750);
   getAvgAccessTime(l,900);
   printf("\n");
   getAvgRandomAccessTime(l);

   list* l2 = newList();
   for (int i = 0; i < 10; i++) {
       addToListFront(l2,i);
   }
   list* l3 = newList();
   for (int i = 10; i < 30; i++) {
       addToListFront(l3,i);
   }

   printf("Listy przed zmergowaniem:\n");
   showList(l2);
   showList(l3);
   merge(l2,l3);
   printf("Listy po zmergowaniu:\n");
   showList(l2);

   return 0;
}