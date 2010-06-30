 /***************************************************************************
 *            ffuncts.h
 *
 *  Fri Jun  6 19:01:13 2008
 *  Francesco Brundu
 *  francesco.brundu@studenti.polito.it
 ****************************************************************************/
#ifndef _FFUNCTS_INCLUDED
#define _FFUNCTS_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h> 
#include <errno.h>
#include "bst.h"
#include "dato.h"

//extern functions declaration
extern FILE* gorg_init(FILE* fdata, char* filename, char* datapath);	 
extern int gorg_cdate(char* currentdate,char* datapath);
extern void gorg_remove(char* name, char* dir, char* mainpath);
extern int gorg_read_db(FILE* fp, char* currdate, BST_t dbase_t);
extern void gorg_print_error(int global_errno);
extern void gorg_print_dbase(BST_t dbase_t,FILE* fp);
extern void gorg_print_help(void);
extern void gorg_new_date(BST_t dbase_t);
extern void gorg_delete_date(BST_t dbase_t);
extern void gorg_save_dbase(BST_t dbase_t,char* datapath);

#endif /* FFUNCTS_H */
