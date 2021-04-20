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

NODE* findEnd(NODE* cur){
    while (cur != NULL && cur->next != NULL)
        cur = cur->next;
    return cur;
}

int compare(ElemType a, ElemType b){// b is the value at the pivot
  if(a > b)
	return 1;
  if(a < b)
	return -1;
  return 0;
}
NODE* partition(NODE* head, NODE* end, NODE* *newHead, NODE* *newEnd){
  NODE* pivot = end;
  NODE* prev = NULL, *cur = head, *tail = pivot;
  
  while(cur != pivot){
	if(cur->val < pivot->val){
		if((*newHead) == NULL)
			(*newHead) = cur;
		prev = cur;
		cur = cur->next;
	}
	else{
		if (prev)
                	prev->next = cur->next;
            	NODE* tmp = cur->next;
            	cur->next = NULL;
	        tail->next = cur;
        	tail = cur;
            	cur = tmp;
	}
  }
  if((*newHead) == NULL)
	(*newHead) = pivot;
  (*newEnd) = tail;

  return pivot;
}

NODE* qsortlinkedR(NODE* head, NODE* end){
  if(!head || head == end)	//Base case
	return head;

NODE* newEnd = NULL;
NODE* newHead = NULL;
NODE* pivot;
  pivot = partition(head, end, &newHead, &newEnd);
  if (newHead != pivot){
        NODE* tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;
 
        newHead = qsortlinkedR(newHead, tmp);
 
        tmp = findEnd(newHead);
        tmp->next =  pivot;
  }
  pivot->next = qsortlinkedR(pivot->next, newEnd);
 
  return newHead;
}

void qsortlinked(LIST* lst){
  lst->front = qsortlinkedR(lst->front, lst->back);
}
