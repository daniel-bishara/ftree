#include <stdio.h>
// Add your system includes here.
#include <unistd.h>
#include "ftree.h"
#include "hash.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>



/*
 * Returns the FTree rooted at the path fname.
 */
struct TreeNode *generate_ftree(const char *fname) {
    // Your implementation here.
	int oct = 0777;
	struct stat information;
	lstat(fname,&information);
    struct TreeNode *tree=malloc(sizeof(struct TreeNode));
	(*tree).fname=fname;
	(*tree).permissions = information.st_mode & oct;
    tree->next = tree->contents = NULL;
	tree->hash=0;

	if (S_ISDIR(information.st_mode)){
		
		DIR *dir = opendir(fname);
		struct dirent * new;
		while((new = readdir(dir))){
		
		if((*new).d_name[0]!='.'){
		

		char *newpaths=malloc(sizeof(fname)+sizeof((*new).d_name)+1);
		
		strcpy(newpaths,fname);
		strcat(newpaths,"/");
		strcat(newpaths,(*new).d_name);
		
		
		struct TreeNode *child = malloc(sizeof(struct TreeNode));
		child = generate_ftree(newpaths);
		(*child).fname=(*new).d_name;
		(*tree).contents=child;

		struct TreeNode *lastChild = malloc(sizeof(struct TreeNode));
		
		lastChild=child;
		
		while ((new=readdir(dir))){
			
			if((*new).d_name[0]!='.'){
			printf("%s\n",((*new).d_name));
			char * newpath=malloc(sizeof(fname)+sizeof((*new).d_name)+1);
			strcpy(newpath,fname);
			strcat(newpath,"/");
			strcat(newpath,(*new).d_name);
			(child)=generate_ftree(newpath);
			(*child).fname=(*new).d_name;
			(*lastChild).next=(child);
			lastChild=child;
			}
		}
		}
	}
	}
	
	else if (S_ISLNK(information.st_mode) || S_ISREG(information.st_mode)) {
		(*tree).next=NULL;
		(*tree).contents=NULL;
		FILE * flink;
		flink=fopen(fname,"r");
		if (flink!=NULL){
		(*tree).hash=hash(flink);
		fclose(flink);
		}
	}
	return tree;
}



void print_help(struct TreeNode *root,int depth){

	if (!((*root).hash)){
		printf("%*s", depth * 2, "");
		printf("===== ");
		printf("%s (%d)",(*root).fname,(*root).permissions);
		printf(" =====\n");
		if((*root).contents){
		print_help((*root).contents,depth+1);
		}
	}
	else{
		printf("%*s", depth * 2, "");
		printf("%s (%d)\n",(*root).fname,(*root).permissions);
	}
	if ((*root).next){
		print_help((*root).next,depth);
	}
	
}

/*
 * Prints the TreeNodes encountered on a preorder traversal of an FTree.
 */
void print_ftree(struct TreeNode *root) {
    int depth = 0;
    printf("%*s", depth * 2, "");
	print_help(root,0);

}
