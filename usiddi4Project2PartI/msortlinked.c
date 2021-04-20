#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct node {
    ElemType val;
    struct node *next;
} NODE;


struct list_struct {
    NODE *front;
    NODE *back;
    int n;
};

void FrontBackSplit(NODE* source, NODE** frontRef, NODE** backRef){
NODE* fast;
NODE* slow;
  if (source==NULL || source->next==NULL){
	*frontRef = source;
	*backRef = NULL;
  }
  else{
	slow = source;
	fast = source->next;
 
	while (fast != NULL){
		fast = fast->next;
		if (fast != NULL){
			slow = slow->next;
			fast = fast->next;
      		}
    	}
 
    	*frontRef = source;
   	*backRef = slow->next;
    	slow->next = NULL;
  }
}

void MergeSort(NODE** headRef){
  NODE* head = *headRef;
  NODE* a;
  NODE* b;
 
  // Base case
  if ((head == NULL) || (head->next == NULL))
	return;
 
  FrontBackSplit(head, &a, &b); 
 
  MergeSort(&a);
  MergeSort(&b);
  LIST* one = malloc(sizeof(LIST));
  LIST* two = malloc(sizeof(LIST));
  one->front = a;
  two->front = b;
  lst_merge_sorted(one, two);
  *headRef = one->front;
}

void msortlinked(LIST* lst){
  MergeSort(&(lst->front));
}