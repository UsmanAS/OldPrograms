#include "usiddi4Proj4.h"
//NOTE DEBUG MODE FOR ADD RUNS TWICE SINCE I CALL doesNameExist AND TRAVERSE THE LIST
//SO SHOWS LIST TWICE


void doAdd(QUEUE** q)
{
 /* get group size from input */
 int size = getPosInt();
 if (size < 1)
   {
    printf ("Error: Add command requires an integer value of at least 1\n");
    printf ("Add command is of form: a <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
   }

 /* get group name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: Add command requires a name to be given\n");
    printf ("Add command is of form: a <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
   }

 printf ("Adding group \"%s\" of size %d\n", name, size);

  // add code to perform this operation here
  if(DEBUG == TRUE){
 	displayListInformation(q);
	displayListInformation(q);
  }
  addToList(q, size, name);
}


void doCallAhead (QUEUE** q)
{
 /* get group size from input */
 int size = getPosInt();
 if (size < 1)
   {
    printf ("Error: Call-ahead command requires an integer value of at least 1\n");
    printf ("Call-ahead command is of form: c <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
   }

 /* get group name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: Call-ahead command requires a name to be given\n");
    printf ("Call-ahead command is of form: c <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
   }

 printf ("Call-ahead group \"%s\" of size %d\n", name, size);

 // add code to perform this operation here
  if(DEBUG == TRUE){
 	displayListInformation(q);
	displayListInformation(q);
  }
  addToListCallAhead(q, size, name);
}

void doWaiting (QUEUE** q)
{
 /* get group name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: Waiting command requires a name to be given\n");
    printf ("Waiting command is of form: w <name>\n");
    printf ("  where: <name> is the name of the group that is now waiting\n");
    return;
   }

 printf ("Waiting group \"%s\" is now in the restaurant\n", name);

 // add code to perform this operation here
  if(DEBUG == TRUE)
	displayListInformation(q);
  if(updateStatus(q, name) == TRUE)
	printf("\n\n****Error either name not in list or not a call ahead group\n\n");
}

void doRetrieve (QUEUE** q)
{
 /* get table size from input */
 int size = getPosInt();
 if (size < 1)
   {
    printf ("Error: Retrieve command requires an integer value of at least 1\n");
    printf ("Retrieve command is of form: r <size>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    return;
   }
 clearToEoln();
 printf ("Retrieve (and remove) the first group that can fit at a tabel of size %d\n", size);

 // add code to perform this operation here
  char* name = retrieveAndRemove(q, size);
  printf("Group named %s has been removed.\n", name);
}

void doList (QUEUE** q)
{
 /* get group name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: List command requires a name to be given\n");
    printf ("List command is of form: l <name>\n");
    printf ("  where: <name> is the name of the group to inquire about\n");
    return;
   }
 if(DEBUG == TRUE){
	displayGroupSizeAhead(q, name);
	displayGroupSizeAhead(q, name);
 }
 printf ("Group \"%s\" is behind the following %d groups\n", name, countGroupsAhead(q, name));

 // add code to perform this operation here

  displayGroupSizeAhead(q, name);
}
 
void doDisplay (QUEUE** q)
{
 clearToEoln();
 printf ("Display information about all groups\n");

 // add code to perform this operation here
  if(DEBUG == TRUE)
	  displayListInformation(q);
  displayListInformation(q);
}
