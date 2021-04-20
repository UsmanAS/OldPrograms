
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// very incomplete small test program...

int main() {
LIST *lst1;
LIST *lst2 = lst_create();
LIST *lst3 = lst_create();
int i;

  lst1 = lst_create();

  for(i=0; i<5; i++) {
     lst_push_front(lst1, i);
  }
  for(i=0; i<5; i++) {
     lst_push_back(lst1, i);
  }

  for(i = 0; i < 10; i++)
	lst_push_back(lst2, i);
  for(i=0; i<5; i++)
	lst_push_back(lst3, i);

  printf("lst_length(lst1) : %i\n", lst_length(lst1));
  printf("lst1 contents: ");
  lst_print(lst1);


  lst_pop_front(lst1);
  lst_pop_front(lst1);
  printf("lst1 contents after two pops: ");
  lst_print(lst1);



  /** TODO:  test code here! **/
  /** test code for lst_pop_back **/
  lst_pop_back(lst1);
  printf("lst1 contents after pop from back: ");
  lst_print(lst1);
	
  /** test code for lst_count **/

  printf("number of 3's = %i\n", lst_count(lst1, 3));
  printf("number of 0's = %i\n", lst_count(lst1, 0));


  /** test code for lst_print_rev **/
  printf("lst1 printed in reverse order: ");
  lst_print_rev(lst1);

  /** test code for lst_reverse **/
  printf("lst2 before being reversed: ");
  lst_print(lst2);
  lst_reverse(lst2);
  printf("lst2 after being reversed: ");
  lst_print(lst2);
  lst_reverse(lst2);
  
  /** test code for lst_is_sorted **/
  if(1 == lst_is_sorted(lst2))
	printf("lst2 is sorted.\n");
  else
	printf("lst2 is not sorted.\n");
  if(1 == lst_is_sorted(lst1))
	printf("lst1 is sorted.\n");
  else
	printf("lst1 is not sorted.\n");
  /** test code for lst_insert_sorted **/
  printf("lst2 with inserting 5: ");
  lst_insert_sorted(lst2, 5);
  lst_print(lst2);

  /** test code for lst_merge_sorted **/
  printf("lst2 before merge with lst3: ");
  lst_print(lst2);
  printf("lst3 before being merged: ");
  lst_print(lst3);
  lst_merge_sorted(lst2, lst3);
  printf("lst2 after merge with lst3: ");
  lst_print(lst2);
  printf("lst3 after being merged: ");
  lst_print(lst3);

  /** test code for lst_clone **/
  LIST* lst4 = lst_clone(lst1);
  printf("lst4 cloned from lst1: ");
  lst_print(lst4);
  
  /** test code for lst_to_array **/
  ElemType* array = lst_to_array(lst1);
  printf("Array created from lst1 : [");
  for(i=0; i<lst_length(lst1); i++)
	printf(" %d ", array[i]);
  printf("]\n");

  /** test code for lst_from_array **/
  LIST* lst5 = lst_from_array(array, lst_length(lst1));
  printf("List lst5 from previous array: ");
  lst_print(lst5);  
  /** test code for lst_prefix **/
  printf("lst5 before prefix: ");
  lst_print(lst5);
  LIST* lst6 = lst_prefix(lst5, 4);
  printf("lst5 after prefix of 4: ");
  lst_print(lst5);
  printf("Resulting list from prefix lst6: ");
  lst_print(lst6);

  /** test code for lst_filter_leq **/
/*  printf("lst2 before lst filter with cutoff of 4: ");
  lst_print(lst2);
  LIST* lst7 = lst_filter_leq(lst2, 4);
  printf("lst2 after lst filter with cutoff of 4: ");
  lst_print(lst2);
  printf("Resulting list lst7 fromlst filter: ");
  lst_print(lst7);
BROKEN*/

  /** test code for lst_concat **/
  printf("lst2 before concat lst with lst1: ");
  lst_print(lst2);
  lst_concat(lst2, lst1);
  printf("lst2 after concat lst with lst1: ");
  lst_print(lst2);
  printf("lst1 after concatenation with lst2: ");
  lst_print(lst1);

  /** test code for lst_push_back **/

  lst_free(lst1);
}
  
