/*
  Name: DataBase
  Author: Wil C
  Date: 27/02/06 03:39
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//______________________________________________________________________________
#pragma MegaData
//______________________________________________________________________________
#define size 100
//______________________________________________________________________________
typedef struct node {
  char *value;
  char *caption;
  struct node *next;
} *node;
//______________________________________________________________________________
typedef struct list {
  node first;
  struct list *next;
} *list;
//______________________________________________________________________________
typedef struct mainList {
  list head;
} *mainList;
//______________________________________________________________________________
mainList megaData;
//______________________________________________________________________________
node new_node(char *value, char *caption) {
  node newNode = (node) malloc(size);
  newNode->value = value;
  newNode->caption = caption;
  newNode->next = NULL;
  return newNode;
}
//______________________________________________________________________________
list new_list() {
  list voidList = (list) malloc(size);
  voidList->first = NULL;
  voidList->next = NULL;
  return voidList;
}
//______________________________________________________________________________
mainList new_mainList() {
  mainList voidMainList = (mainList) malloc(size);
  voidMainList->head = new_list();
  return voidMainList;
}
//______________________________________________________________________________
void init() {
  megaData = new_mainList();
}
//______________________________________________________________________________
mainList addNode(mainList ml, node n) {
  if (ml->head->first == NULL) {
    ml->head->first = n;
  } else {
    list tempList = megaData->head;
    while (tempList->next != NULL) {
      tempList = tempList->next;
    }
    if (tempList->first == NULL) {
      tempList->first = n;
    } else {
      node tempNode = tempList->first;
      while (tempNode->next != NULL) {
        tempNode = tempNode->next;
      }
      tempNode->next = n;
    }  
  }
  return ml;
}
//______________________________________________________________________________
mainList addList(mainList ml, list l) {
  if (ml->head->first == NULL) {
    ml->head = l;
  } else {
    list temp = ml->head;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = l;
  }
  return ml;
}
//______________________________________________________________________________
char *getValue(int n) {
  if (megaData->head->next != NULL) {
    node temp = megaData->head->first;
    int i;
    for (i=0; i!=n; i++) {
      temp = temp->next;
    }
    return temp->caption;
  } else {
    return NULL;
  }  
}
//______________________________________________________________________________
void load(){
  char *url = (char*) malloc(size);
  scanf("%s", url);
  FILE *file;
  if (file = fopen(url, "r")) {
    megaData = new_mainList();
    char *data = (char*) malloc(size);
    char *caption = (char*) malloc(size);
    int value = 0;
    do {
      fscanf(file, "%s", data);
      int i;
      int j = 0;
      for (i=0; i<=strlen(data); i++) {
        if ((data[i] == ',') || (data[i] == '\0')) {
          caption[j] = '\0';
          megaData = addNode(megaData, new_node(getValue(value), caption));
          caption = (char*) malloc(size);
          j = 0;
          value++;
        } else {
          caption[j] = data[i];
          j++;
        }
      }
      value = 0;
      megaData = addList(megaData, new_list());
    } while (!feof(file));
    fclose(file);
    printf("> Successful! <\n");
  } else {
    printf("> Bad Command <\n");
  }    
}
//______________________________________________________________________________
void showList(list l) {
  node temp = l->first;
  while (temp != NULL) {
    printf("%s, ", temp->caption);
    temp = temp->next;
  }
  printf("\n");
}
//______________________________________________________________________________
void showMainList(mainList ml) {
  if (ml->head->first == NULL) {
    printf("> Void <\n");
  } else {  
    printf(">\n");
    list temp = ml->head;
    while (temp->first != NULL) {
      showList(temp);
      temp = temp->next;
    }
    printf("<\n");
  }
  printf("> Successful! <\n");
}
//______________________________________________________________________________
void showJoin(list l, char *arg) {
  node temp;
  char *col = (char*) malloc(size);
  int i;
  int j = 0;
  for(i=0; i<=strlen(arg); i++) {
    if ((arg[i] != ',') && !(i == strlen(arg))) {
      col[j] = arg[i];
      j++;
    } else {
      col[j] = '\0';
      temp = l->first;
      while (temp != NULL) {
        if (!strcmp(temp->value, col)) {
          printf("%s, ", temp->caption);
        }
        temp = temp->next;
      }
      col = (char*) malloc(size);
      j = 0;
    }
  }
}
//______________________________________________________________________________
void select() {
  int success = 0;
  char *cmd = (char*) malloc(size);
  char *arg = (char*) malloc(size);
  char *col = (char*) malloc(size);
  char *val = (char*) malloc(size);
  char *ord = (char*) malloc(size);
  arg[0] = '\0';
  col[0] = '\0';
  while (strcmp(col, "Where")) {
    strcat(arg, col);
    scanf("%s", col);
  }
  scanf("%s", col);
  scanf("%s", cmd);
  if (!strcmp(cmd, "=")) {
    scanf("%s", val);
    scanf("%s", cmd);
    if (!strcmp(cmd, "Order")) {
      scanf("%s", cmd);
      if (!strcmp(cmd, "By")) {
        scanf("%s", ord);
        list tempList;
        node tempNode;
        if (!strcmp(ord, "Asc")) {
          tempList = megaData->head->next;
          printf(">\n");
          while (tempList != NULL) {
            tempNode = tempList->first;
            while (tempNode != NULL) {
              if (!strcmp(tempNode->value, col) && !strcmp(tempNode->caption, val)) {
                showJoin(tempList, arg);
                printf("\n");
                break;
              }
              tempNode = tempNode->next;
            }
            tempList = tempList->next;
          }
          printf("<\n");
          success++;
        } else if (!strcmp(ord, "Des")) {
          tempList = megaData->head;
          int i = 0;
          int j;
          while (tempList->next->first != NULL) {
            tempList = tempList->next;
            i++;
          }
          printf(">\n");
          while (i != 0) {
            tempList = megaData->head;
            for (j=i; j!=0; j--) {
              tempList = tempList->next;
            }
            tempNode = tempList->first;
            while (tempNode != NULL) {
              if (!strcmp(tempNode->value, col) && !strcmp(tempNode->caption, val)) {
                showJoin(tempList, arg);
                printf("\n");
                break;
              }
              tempNode = tempNode->next;
            }
            i--;
          }
          printf("<\n");
          success++;
        }
      }
    }
  }
  if (success) {
    printf("> Successful! <\n");
  } else {
    printf("> Bad Command <\n");
  }
}
//______________________________________________________________________________
void count() {
  int val = 0;
  char *col = (char*) malloc(size);
  scanf("%s", col);
  list tempList = megaData->head->next;
  node tempNode;
  printf("%s", "> ");
  while (tempList != NULL) {
    tempNode = tempList->first;
    while (tempNode != NULL) {
      if (!strcmp(tempNode->value, col)) {
        printf("%s, ", tempNode->caption);
      }
      tempNode = tempNode->next;
    }
    tempList = tempList->next;
  }
  printf("<\n> Successful! <\n");
}
//______________________________________________________________________________
void sum() {
  int val = 0;
  char *col = (char*) malloc(size);
  scanf("%s", col);
  list tempList = megaData->head->next;
  node tempNode;
  while (tempList != NULL) {
    tempNode = tempList->first;
    while (tempNode != NULL) {
      if (!strcmp(tempNode->value, col)) {
        val += atoi(tempNode->caption);
      }
      tempNode = tempNode->next;
    }
    tempList = tempList->next;
  }
  printf("> %i <\n> Successful! <\n", val);
}
//______________________________________________________________________________
void max() {
  int val = 0;
  char *col = (char*) malloc(size);
  scanf("%s", col);
  list tempList = megaData->head->next;
  node tempNode;
  while (tempList != NULL) {
    tempNode = tempList->first;
    while (tempNode != NULL) {
      if (!strcmp(tempNode->value, col)) {
        if (val < atoi(tempNode->caption)) {
          val = atoi(tempNode->caption);
        }
      }
      tempNode = tempNode->next;
    }
    tempList = tempList->next;
  }
  printf("> %i <\n> Successful! <\n", val);
}
//______________________________________________________________________________
main() {
  init();
  char *cmd = (char*) malloc(size);
  do {
    scanf("%s", cmd);
    if (!strcmp(cmd, "Load")) {
      load();
    } else if (!strcmp(cmd, "Show")) {
      showMainList(megaData);
    } else if (!strcmp(cmd, "Select")) {
      select();
    } else if (!strcmp(cmd, "Count")) {
      count();
    } else if (!strcmp(cmd, "Sum")) {
      sum();
    } else if (!strcmp(cmd, "Max")) {
      max();
    } else if (strcmp(cmd, "Exit")){
      printf("> Bad Command <\n");
    }
    printf("\n");
  } while (strcmp(cmd, "Exit"));
  return 0;
}

