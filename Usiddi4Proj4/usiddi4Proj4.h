#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;

boolean DEBUG;

typedef struct queue{
  char name[30];
  int size;
  boolean inside;
  struct queue* next;
}QUEUE;


void clearToEoln();

int getNextNWSChar();

int getPosInt();

char *getName();

void clearToEoln();

int main(int argc, char **argv);

void doAdd(QUEUE** q);

void doCallAhead(QUEUE** q);

void doWaiting(QUEUE** q);

void doRetrieve(QUEUE** q);

void doList(QUEUE** q);

void doDisplay(QUEUE** q);

void addToList(QUEUE** q, int size, char* name);

void addToListCallAhead(QUEUE** q, int size, char* name);

boolean doesNameExist(QUEUE** q, char* name);

boolean updateStatus(QUEUE** q, char* name);

char* retrieveAndRemove(QUEUE** q, int size);

int countGroupsAhead(QUEUE** q, char* name);

void displayGroupSizeAhead(QUEUE** q, char* name);

void displayListInformation(QUEUE** q);
