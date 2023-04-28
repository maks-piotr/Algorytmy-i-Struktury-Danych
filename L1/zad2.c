#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <math.h>

typedef struct node node;
typedef struct list list;

struct node {
    int val;
    node* link;
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
    node* temp2;
    while (temp1 != NULL) {
        temp2 = temp1->link;
        free(temp1);
        temp1 = temp2;
    }
    free(l);
}

void addToList(list* l,int pos, int value) { // pos - przed którym elementem zinsertować
    node* newNode = malloc(sizeof(node));
    newNode->val = value;
    if (pos == 0) {
        newNode->link = l->head;
        l->head = newNode;
    }
    else {
        node* prev = l->head;
        if (prev == NULL) {
                return;
            }
        for (int i=1; i < pos; i++) {
            prev = prev->link;
            if (prev == NULL) {
                return;
            }
        }
        node* next = prev->link;
        prev->link = newNode;
        newNode->link = next;
    }
    l->size++;
}
void showList(list* l) {
    node* cur = l->head;
    while (cur != NULL) {
        printf("%d -> ", cur->val);
        cur = cur->link;
    }
    printf("\n\n");
}
int getFromList(list* l,int pos) {
    node* temp = l->head;
    if (temp == NULL) {
        return 0;
    }
    for (int i=0; i < pos; i++) {
        temp = temp->link;
        if (temp == NULL) {
            return 0;
        }
    }
    return temp->val;
}
void delFromList(list* l, int pos) {

    node* temp = l->head;
    node* prev = NULL;
    if (temp == NULL) {
        return;
    }
    if (pos == 0) {
        l->head= l->head->link;
        free(temp);
        l->size--;
        return;
    }
    for (int i=0; i < pos; i++) {
        prev = temp;
        temp = temp->link;
        if (temp == NULL) {
            return;
        }
    }
    node* next = temp->link;
    free(temp);
    prev->link = next;
    l->size--;
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
    while(temp->link != NULL) {
        temp = temp->link;
    }
    temp->link=l2->head;
    l1->size += l2->size;
}


int main() {
   srand(time(NULL));
   list* l = newList();
   printf("Lista dodawanie...\n");
   for (int i = 0; i < 1000; i++) {
       addToList(l,0,rand());
   }
   getAvgAccessTime(l,100);
   getAvgAccessTime(l,200);
   getAvgAccessTime(l,300);
   getAvgAccessTime(l,500);
   getAvgAccessTime(l,700);
   getAvgAccessTime(l,900);
   getAvgRandomAccessTime(l);

   list* l2 = newList();
   for (int i = 0; i < 10; i++) {
       addToList(l2,0,i);
   }
   list* l3 = newList();
   for (int i = 10; i < 30; i++) {
       addToList(l3,0,i);
   }

   printf("Listy przed zmergowaniem:\n");
   showList(l2);
   showList(l3);
   merge(l2,l3);
   printf("Listy po zmergowaniu:\n");
   showList(l2);

   deleteList(l);

   return 0;
}