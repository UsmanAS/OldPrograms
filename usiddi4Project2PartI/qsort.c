#include <stdio.h>
#include <stdlib.h>
#include "list.h"


int main() {
LIST *lst1;
int i;
int input;

  lst1 = lst_create();

  do{
	printf("Input an integer: \n");
	i = scanf("%d", &input);
	if(i == 1)
		lst_push_front(lst1, (ElemType)input);
	else
		break;
  }while(1);
  i = lst_length(lst1);
  printf("lst_length(lst1) : %i\n", i);

  printf("lst1 contents: \n");
  lst_print(lst1);
  qsortlinked(lst1);
  
  printf("lst1 contents after qsort: \n");
  lst_print(lst1);

  lst_free(lst1);
}
  
