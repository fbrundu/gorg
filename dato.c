/* 1 direttive
#define MAXC 60
*/
 /***************************************************************************
 *            dato_struct.c
 *
 *  Fri May 30 19:46:24 2008
 *  Francesco Brundu
 *  francesco.brundu@studenti.polito.it
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dato.h"

#define MAXC 60

/*** Declaration of struct dato ***/
struct dato {
  char string[MAXC];
  char date[11];
};

/*** Reads struct ***/
int data_read(FILE *fp, dato_t *dp) {
  dato_t dato;
  char riga[MAXC];

  if (fgets(riga, MAXC, fp) == NULL)
    return DATA_ERROR;

  dato = (dato_t)malloc(sizeof(*dato));
  if (dato == NULL) 
    return DATA_ERROR;

  sscanf(riga, "%s", dato->date);
  
  if (fgets(riga, MAXC, fp) == NULL)
    return DATA_ERROR;
  
  strcpy(dato->string,riga);
  
  *dp = dato;

  return !DATA_ERROR;
}

/*** Reads struct from stdin ***/
int data_new(dato_t *dp) {
  dato_t dato;
  char riga[MAXC];
  char d[3];
  char m[3];
  char y[5];
  
  printf("\nInsert subject: ");
  if (fgets(riga, MAXC,stdin) == NULL)
    return DATA_ERROR;
  
  dato = (dato_t)malloc(sizeof(*dato));
  if (dato == NULL) 
    return DATA_ERROR;

  strcpy(dato->string,riga);
  
  printf("Insert 'c' to cancel.\n");
  while(1) {
    printf("Insert day[dd]: ");
    scanf("%s",d);
    if(d[0]=='c') return DATA_ERROR;
    if(strlen(d) == 2) 
      if(strcmp(d,"32")<0) break;
  }
  while(1) {
    printf("Insert month[mm]: ");
    scanf("%s",m);
    if(m[0]=='c') return DATA_ERROR;
    if(strlen(m) == 2) 
      if(strcmp(m,"13")<0) break;
  }
  while(1) {
    printf("Insert year[yyyy]: ");
    scanf("%s",y);
    if(y[0]=='c') return DATA_ERROR;
    if(strlen(y) == 4) break;
  }
  strcpy(dato->date,&y[2]);
  strcat(dato->date,m);
  strcat(dato->date,d);
  while(1) {
    printf("Insert hour[hhmm]: ");
    scanf("%s",y);
    if(y[0]=='c') return DATA_ERROR;
    if(strlen(y) == 4) break;
  }
  strcat(dato->date,y);
      
  *dp = dato;

  return !DATA_ERROR;
}


/*** Prints struct ***/
void data_print(FILE *fp, dato_t dato) {
  if(fp != stdout)
    fprintf(fp, "%s\n%s\n", dato->date, dato->string);
  else {
    fprintf(fp, "Date: %c%c/%c%c/20%c%c\n", dato->date[4], dato->date[5], 
      dato->date[2], dato->date[3], dato->date[0], dato->date[1]);
    fprintf(fp, "Hour: %c%c:%c%c\n", dato->date[6], dato->date[7], 
      dato->date[8], dato->date[9]);
    fprintf(fp, "Subject: %s\n\n", dato->string);
  }
}

/*** Compares two structs ***/
int data_compare(dato_t d1, dato_t d2, int key)
{
  #if 0
  printf("Entro in data compare..");
  printf("data_1 = %s, data_2 = %s\n",d1->date,d2->date);
  #endif
  if (key) {
    #if 0
    printf("Confronto per subject\n");
    #endif
    return strcmp(d1->string, d2->string);
  }
  else {
    #if 0
    printf("Confronto per data\n");
    #endif
    return strcmp(d1->date, d2->date);
  }
}

/*** Frees the block of memory of the struct ***/
void data_free(dato_t dato) {
  free(dato);
}
/*** Creates data block ***/
dato_t data_create(char* date, char* string) {
  dato_t dato = (dato_t)malloc(sizeof(*dato));
  if (dato == NULL) 
    return DATA_ERROR;
  strcpy(dato->date,date);
  strcpy(dato->string,string);
  return dato;
}

