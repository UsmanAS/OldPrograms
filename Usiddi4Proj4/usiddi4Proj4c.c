#include "usiddi4Proj4.h"
#include  <string.h>


void addToList(QUEUE** q, int size, char* name){
  if((*q) == NULL){
	(*q) = malloc(sizeof(QUEUE));
	(*q)->next = NULL;
	(*q)->size = size;
	(*q)->inside = TRUE;
	strcpy((*q)->name,name);
  }
  else{
 	 QUEUE* ptr = *q;
	  while(ptr->next != NULL)
		ptr = ptr->next;
 	 QUEUE* temp = malloc(sizeof(QUEUE));
 	 if(doesNameExist(q, name) == FALSE){
  		strcpy(temp->name,name);
  		temp->size = size;
		temp->inside = TRUE;
		temp->next = NULL;
    		ptr->next = temp;
  	}
  	else
		printf("\n****Error %s already in use****\n\n", name);
  }
}
void addToListCallAhead(QUEUE** q, int size, char* name){
  if((*q) == NULL){
	(*q) = malloc(sizeof(QUEUE));
	(*q)->next = NULL;
	(*q)->size = size;
	(*q)->inside = FALSE;
	strcpy((*q)->name,name);
  }  
  else{
	 QUEUE* ptr = *q;
 	 while(ptr->next != NULL)
		ptr = ptr->next;
 	 QUEUE* temp = malloc(sizeof(QUEUE));
 	 if(doesNameExist(q, name) == FALSE){
  		strcpy(temp->name,name);
  		temp->size = size;
		temp->inside = FALSE;
		temp->next = NULL;
		ptr->next = temp;
 	 }
 	 else
		printf("\n****Error %s already in use****\n\n", name);
  }
}

boolean doesNameExist(QUEUE** q, char* name){
  QUEUE* ptr = *q;
  while(ptr != NULL){
	if(strcmp(ptr->name, name) == 0){
		if(DEBUG == TRUE)
			displayGroupSizeAhead(q, name);
		return TRUE;
	}
	ptr = ptr->next;
  }
  return FALSE;

}

boolean updateStatus(QUEUE** q, char* name){
  QUEUE* ptr = *q;
  if(name == NULL)
	return FALSE;
  while(ptr != NULL){
	if(strcmp(ptr->name, name) == 0){
		if(ptr->inside == TRUE)
			return TRUE;
		ptr->inside = TRUE;
		return FALSE;
	}
  }
  return TRUE;
}

char* retrieveAndRemove(QUEUE** q, int size){
  QUEUE* ptr = *q;
  QUEUE* before = NULL;
  char* name = malloc(sizeof(char)*30);
  while(ptr != NULL){
	if(ptr->size <= size){
		if(DEBUG == TRUE)
			displayGroupSizeAhead(q, name);
		strcpy(name, ptr->name);
		if(before == NULL)
			(*q) = (*q)->next;
		else
			before->next = ptr->next;
		return name;
	}
	before = ptr;
	ptr = ptr->next;
  }
  if(DEBUG == TRUE)
	displayListInformation(q);

}

int countGroupsAhead(QUEUE** q, char* name){
  if(doesNameExist(q, name) == FALSE){
	printf("****Error name does not exist.\n");	
	return -1;
  }
  QUEUE* ptr = *q;
  int i=0;
  for(i = 0; ptr != NULL; i++){
	if(strcmp(ptr->name, name) == 0)
		return i;
	ptr = ptr->next;
  }
  return i;
}

void displayGroupSizeAhead(QUEUE** q, char* name){
  QUEUE* ptr = *q;
  while(ptr != NULL && strcmp(ptr->name,name) != 0){
	printf("Name: %s\nGroup Size: %d\n", ptr->name, ptr->size);
	ptr = ptr->next;
  }
}

void displayListInformation(QUEUE** q){
  QUEUE* ptr = *q;
  while(ptr != NULL){
	printf("Name: %s\nGroup Size: %d\n", ptr->name, ptr->size);
	if(ptr->inside)
		printf("Inside\n");
	else
		printf("Not inside\n");  
	ptr = ptr->next;
  }
}

