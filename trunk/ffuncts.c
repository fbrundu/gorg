 /***************************************************************************
 *            ffuncts.c
 *
 *  Fri Jun  6 19:01:05 2008
 *  Francesco Brundu
 *  francesco.brundu@studenti.polito.it
 ****************************************************************************/

#include "ffuncts.h"
#define LUNG_PATH 50

//init program
FILE* gorg_init(FILE* fdata, char* filename, char* datapath) {
	FILE* fhome = NULL;
	 
	//find user's home
	if((datapath = getenv("HOME")) == NULL){ 
        return NULL;
    }
	//home found successfully, now it's dir creation time
	strcat(datapath,"/.gorg");
	if((mkdir(datapath,S_IRWXU)) == -1) { 
		if(errno != EEXIST) {
			printf("Cannot initialize datapath. Exiting..");
			return NULL;
		}
	}
	
	//open program dir
	if(chdir(datapath) == -1) { 
		printf("Cannot open program dir. Exiting..");
		return NULL;
	}
	
	//open dbase file
	if((fdata = fopen(filename,"r")) == NULL) {
		if((fdata = fopen(filename,"w")) == NULL)
		  printf("Could not open (W) dbase.txt\n");
	}
	
	return fdata;
}

//save database
void gorg_save_dbase(BST_t dbase_t,char* datapath) {
  FILE* fhome = NULL;
	 
	//find user's home
	system("echo ~ > h.txt");
	if((fhome = fopen("h.txt","r")) == NULL) return;
	if(fscanf(fhome,"%s",datapath) == -1) return;
	fclose(fhome);
    fhome = NULL;
    system("rm h.txt");
	  
	//home found successfully
	strcat(datapath,"/.gorg");
	
	//open program dir
	if(chdir(datapath) == -1) { 
		printf("Cannot open program dir. Exiting..");
		return;
	}
	
	//open dbase file
	if((fhome = fopen("dbase.txt","w")) == NULL)
		  printf("Could not open (W) dbase.txt\n");
	else {
	  gorg_print_dbase(dbase_t,fhome);
	}
	
  return;
}

//find current date
int gorg_cdate(char* currentdate,char* datapath) {
    FILE* fgetdata = NULL;
  
    system("date +%y%m%d%H%M > d.txt");
	if((fgetdata = fopen("d.txt","r")) == NULL) return(-1);
	if(fscanf(fgetdata,"%s",currentdate) == -1) return(-1);
	fclose(fgetdata);
    gorg_remove("d.txt", "/",datapath);
  
    return 0;
}

//remove file "name" in "dir"
void gorg_remove(char* name, char* dir, char* mainpath) {
    char pathname [LUNG_PATH+1];
  
    strcpy(pathname,mainpath);
    strcat(pathname,dir);
    strcat(pathname,name);
    //printf("Removing %s...\n",pathname);
    remove(pathname);
      
    return;
}

//read database
int gorg_read_db(FILE* fp, char* currdate, BST_t dbase_t) {
  dato_t cdate = data_create(currdate,"\0");
  dato_t dp = NULL;
  if(fp == NULL) {
    printf("dbase.txt pointer has NULL value\n");
    return (-1);
  }
  if(cdate == NULL) {
    printf("cdate date is not allocated\n");
    return (-1);
  }
  if(dbase_t == NULL) {
    printf("Database tree structure doesn't exist\n");
    return (-1);
  }
  #if 0
  printf("Current date is\n");
  data_print(stdout,cdate);
  putchar('\n');
  #endif
  while(data_read(fp, &dp) != DATA_ERROR) {
    if(data_compare(cdate,dp,0)<0) {
      bst_insert(dbase_t, dp);
      #if 0
      printf("Dato inserito\n");
      data_print(stdout,dp);
      #endif
    }
    else {
      #if 0
      printf("Dato non inserito\n");
      data_print(stdout,dp);
      #endif
    }
  }
  return 0;
}

//print error stored in errno
void gorg_print_error(int global_errno) {
  switch(global_errno) {
		case EACCES: printf("Permission Denied\n");break;
		case EEXIST: printf("File Exists\n"); break;
		case EMLINK: printf("Too Many Link\n"); break;
		case ENOSPC: printf("No Space\n"); break;
		case EROFS: printf("Could Not Write On Readonly FS\n"); break;
		case EFAULT: printf("Segfault \n"); break;
		case ELOOP: printf("Too Many Symbolic Links In Path\n"); break;
		case ENAMETOOLONG: printf("Path Too Long\n"); break;
		case ENOENT: printf("File Doesn't Exist\n"); break;
		case ENOMEM: printf("Insufficient Kernel Memory\n"); break;
		case ENOTDIR: printf("A Component Of Path Is Not A Dir\n"); break;
		case EPERM: printf("Permission Denied - You Are Not The Owner\n"); break;
		default: break;
	}
	return;
}

//print content of dbase.txt
void gorg_print_dbase(BST_t dbase_t,FILE* fp) {
  if(dbase_t == NULL) return;
  putchar('\n');
  bst_print(dbase_t, fp, INORDER);
  return;
}

//print help informations
void gorg_print_help(void) {
  printf("\n*** HELP ***\n");
  printf("h - print this help\n");
  printf("p - print database content\n");
  printf("d - delete a date\n");
  printf("r - read a new database file (yet not implemented)\n");
  printf("w - save a new date\n");
  printf("s - save database content\n");
  printf("e - exit the program\n");
  printf("************\n\n");
}

//insert new date
void gorg_new_date(BST_t dbase_t) {
  dato_t dp = NULL;
  
  if(data_new(&dp)==DATA_ERROR) { 
    printf("\nUnable to insert new date..\n\n");
    data_free(dp);
    return;
  }
  bst_insert(dbase_t, dp);
  putchar('\n');      
  return;
}

//delete a date
void gorg_delete_date(BST_t dbase_t) {
  dato_t dp = NULL;
  
  if(data_new(&dp)==DATA_ERROR) { 
    printf("\nUnable to delete the date..\n\n");
    data_free(dp);
    return;
  }
  bst_remove(dbase_t, dp);
  putchar('\n');      
  return;
}

