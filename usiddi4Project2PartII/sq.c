#include <stdio.h>
#include <stdlib.h>
#include "sq.h"
//Usman Siddiqui
//usiddi4

typedef struct node{
  int buzzer;
  struct node* next;
}NODE;

typedef struct queue{
  int* arr;
  int size;
  int length;
  int number;
}QUEUE;

struct service_queue {
  NODE* buzzer_bucket;
  QUEUE* the_queue;
  NODE* bribes;
};


void grow(SQ *q){
  QUEUE* ptr = q->the_queue;
  int* tmp;
  tmp = malloc(sizeof(int) * ((ptr->size)*2));
  int i;
  for(i = 0; i<ptr->size;i++)
	tmp[i]=ptr->arr[i];
  free(ptr->arr);
  ptr->arr = tmp;
  (ptr->size) *= 2;
}

void push_front(NODE** node, int buzzer){
  NODE* tmp = malloc(sizeof(NODE));
  tmp->buzzer = buzzer;
  tmp->next = *node;
  *node = tmp;
}

SQ * sq_create() {
SQ *q;

  q = malloc(sizeof(SQ));

  q->the_queue = malloc(sizeof(QUEUE));
  q->the_queue->length = 0;
  q->the_queue->size = 10;
  q->the_queue->arr = malloc(sizeof(int) * (q->the_queue->size));
  q->the_queue->number = 0;

  q->buzzer_bucket = NULL;
  q->bribes = NULL;

  return q;
}

void sq_free(SQ *q) {

  free(q->the_queue->arr);
  free(q->the_queue);
  free(q->bribes);
  free(q->buzzer_bucket);
  free(q);
}

void sq_display(SQ *q) {
  int* list = q->the_queue->arr;
  NODE* ptr = q->bribes;
  int i;

  printf("current-queue contents:\n    [");
  while(ptr != NULL){
	if(list[ptr->buzzer] == 2)
		printf(" %d ", ptr->buzzer);
	ptr = ptr->next;
  }
  for(i = 0; i < q->the_queue->length;i++){
  	if(q->buzzer_bucket != NULL && list[i] == 0)
		i = (q->buzzer_bucket->buzzer)+1;
	if(list[i] == 1)
		printf(" %d ", i);
  }
  printf("]\n");
}

int  sq_length(SQ *q) {
  return q->the_queue->length;
}

int  sq_give_buzzer(SQ *q) {
  NODE* tmp = q->buzzer_bucket;
  QUEUE* ptr = q->the_queue;
  int buzzer;

  if(tmp != NULL){
	buzzer = q->buzzer_bucket->buzzer;
	q->buzzer_bucket = tmp->next;
	free (tmp);
	(ptr->length)--;
  }
  else
	buzzer = ptr->length;
  if(buzzer >= ptr->size)
	grow(q);
  ptr->arr[buzzer] = 1;
  (ptr->length)++;
  (ptr->number)++;
  return buzzer;
}

int sq_seat(SQ *q) {
int buzzer;
QUEUE* ptr = q->the_queue;
NODE* tmp = q->bribes;

  if(ptr->number == 0)
	return -1;
  else if(tmp != NULL){
	buzzer = tmp->buzzer;
	ptr->arr[tmp->buzzer] = 0;
	q->bribes = tmp->next;
	free(tmp);
  }
  else if(q->buzzer_bucket != NULL && ptr->arr[0] != 1){
	buzzer = (q->buzzer_bucket->buzzer)+1;
	ptr->arr[(q->buzzer_bucket->buzzer)+1] = 0;
  }
  else{
	buzzer = 0;
	ptr->arr[0] = 0;
  }
  push_front(&(q->buzzer_bucket), buzzer);
  (ptr->number)--;
  return buzzer;
} 

int sq_kick_out(SQ *q, int buzzer) {
QUEUE* ptr = q->the_queue;
NODE* tmp = q->bribes;

  if(ptr->arr[buzzer] == 1 || ptr->arr[buzzer] == 2){
	if(ptr->arr[buzzer] == 2){
		q->bribes = tmp->next;
		free(tmp);
	}
	q->the_queue->arr[buzzer] = 0;
	(ptr->number)--;
	push_front(&(q->buzzer_bucket), buzzer);
	return 1;
  }
  else
	return 0;
}

int sq_take_bribe(SQ *q, int buzzer) {
QUEUE* ptr = q->the_queue;

  if(ptr->arr[buzzer] == 1 || ptr->arr[buzzer] == 2) {
	q->the_queue->arr[buzzer] = 2;
	push_front(&(q->bribes), buzzer);
	return 1;
  }
  else {
	/* person has to be in line to offer a bribe */
	return 0;
  }
}


