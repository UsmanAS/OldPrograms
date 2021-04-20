#include<stdio.h>
#include<string.h>

typedef struct node{
	char* array;
	int size;
	int top;
}stack;

void grow(stack* ptr){
  char* newarr = malloc(sizeof(char)*(ptr->size + 2));
  int i;
  for(i=0; i<ptr->size; i++)
	newarr[i] = ptr->array[i];
  free(ptr->array);
  ptr->array = newarr;
  ptr->size += 2;
}

stack* stack_initialize(){
  stack* new = malloc(sizeof(stack));
  new->top = 0;
  new->array = malloc(sizeof(char)*2);
  new->size = 2;
  return new;
}

void push(stack* ptr, char symbol){
  if(ptr->top + 1 == ptr->size)
	grow(ptr);
  if(stack_empty(ptr) == 0)
	ptr->top = 0;
  else{ 
	ptr->top += 1;
  }
  ptr->array[ptr->top] = symbol;
}

void pop(stack* ptr){
  ptr->top -= 1;
}

int stack_empty(stack* ptr){// 0 is empty 1 is not empty
  if(ptr->top < 0 || ptr->array[0] == NULL)
	return 0;
  return 1;
}

char stack_top(stack* ptr){
  if(ptr->array[ptr->top] == ' '){
	ptr->top -= 1;
	return stack_top(ptr);
  }
  return ptr->array[ptr->top];
}

void reset(stack* ptr){
 	 free (ptr);
	 ptr = stack_initialize();
}

int is_open(char input){
  if(input == '<' || input == '(' || input == '[' || input == '{')
	return 1;
  return 0;
}

int is_close(char input){
  if(input == '>' || input == ')' || input == ']' || input == '}')
	return 1;
  return 0;
}

void main(){
  char* str = malloc(sizeof(char)* 300);
  int size;
  int i, j;
  stack* ptr;

  printf("Usman Siddiqui\nusiddi4@uic.edu\nCS211 Project 2\n\n");
  while(1){
	ptr = stack_initialize();
	printf("Enter an expression.\n");
	fgets(str, 300, stdin);
	if(strcmp(str, "q\n") == 0 || strcmp(str, "Q\n") == 0)
		break;
	size = strlen(str) - 1;
  	for(i=0; i<size; i++){
		if(is_open(str[i])){
 			push(ptr, str[i]);
		}
		else if(is_close(str[i])){
			if(stack_top(ptr) != str[i]-1 && stack_top(ptr) != str[i]-2 && stack_empty(ptr) == 1){// Errors most likely look at pop and push
				if(stack_top(ptr) == '('){
					for(j = 0; j < i; j++)
						printf(" ");
					printf("^ expecting %c\n\n", stack_top(ptr)+1);
				}
				else{
					for(j = 0; j < i; j++)
						printf(" ");
					printf("^ expecting %c\n\n", stack_top(ptr)+2);
				}
				break;
			}
			else if(str[i] != stack_top(ptr)+1 &&  str[i] != stack_top(ptr)+2){
				if(str[i] == ')'){
					for(j = 0; j < i; j++)
						printf(" ");
					printf("^ missing %c\n\n", str[i]-1);
				}
				else{
					for(j = 0; j < i; j++)
						printf(" ");
					printf("^ missing %c\n\n", str[i]-2);
				}
				break;				
			}
			else{
				pop(ptr);
			}
		}
		else
			push(ptr, ' ');
	}
	if(i==size){
		if(ptr-> top > 0){
			if(stack_top(ptr) == '('){
				for(j = 0; j < size+1; j++)
					printf(" ");
				printf("^ missing %c\n\n", stack_top(ptr)+1);
			}
			else{
				for(j = 0; j < size+1; j++)
					printf(" ");
				printf("^ missing %c\n\n", stack_top(ptr)+2);
			}
		}
		else
			printf("Expression is balanced.\n");
	}
	reset(ptr);
  }




}
