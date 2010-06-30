/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.c
 * Copyright (C) Francesco Brundu 2008 <francesco.brundu@gmail.com>
 * 
 * main.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * main.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h> 
#include <string.h>
#include <errno.h>
#include "ffuncts.h"
#include "bst.h"
#include "dato.h"
	 
#define LUNG_PATH   50
#define LUNG_DATE		20    
#define DEBUG	1
 
int main() {
	FILE* fdata = NULL;
	char r;
	char datapath [LUNG_PATH+1];
	char currentdate [LUNG_DATE+1];
	BST_t dbase_t = bst_alloc();
	
	//open file dbase.txt, stream linked by fdata
	if((fdata = gorg_init(fdata,"dbase.txt",datapath)) == NULL) {
		printf("Could not open file dbase.txt\n");
		exit(1);
	}

	//find current date
	if(gorg_cdate(currentdate,datapath) != 0) {
		printf("Could not read current date\n");
		exit(1);
	}

	//read database and store it in the tree
	if(gorg_read_db(fdata, currentdate, dbase_t) != 0) {
		printf("Could not read dbase.txt\n");
		exit(1);
	}
	fclose(fdata);
	printf("\n*** GORG - Gnu Organizer\n");
	printf("*** Francesco Brundu - francesco.brundu@gmail.com\n");
	printf("*** v 0.1\n\n");
	
	while(1){
		printf("Press h<enter> to learn how to use me.\n");
		printf("gorg.textbased :P ");
		scanf("%c",&r);
		switch(r){
			case 'p':
			case 'P':
				//print dbase to stdout
				gorg_print_dbase(dbase_t,stdout);
			break;
			
			case 'e':
			case 'E':
				//exit the program
				getc(stdin);
				printf("Do you want to save the database? [y,n]: ");
				r = getc(stdin);
				if((r == 'y') || (r == 'Y')) gorg_save_dbase(dbase_t,datapath);
				exit(0);
			break;
			
			case 'w':
			case 'W':
				//save a new date
				getc(stdin);
				gorg_new_date(dbase_t);
			break;
			
			case 'd':
			case 'D':
				//delete a date
				getc(stdin);
				gorg_delete_date(dbase_t);
			break;
						
			case 's':
			case 'S':
				//save dbase file
				gorg_save_dbase(dbase_t,datapath);
			break;
						
			case 'h':
			case 'H':
				//print help text
				gorg_print_help();
			break;
			
			default: 
				printf("Yet not implemented. Try later..\n");
				while(getc(stdin)!='\n');
				printf("Press a key to continue...\n");
			break;
		}
		getc(stdin);
	}
	return 0;
}

