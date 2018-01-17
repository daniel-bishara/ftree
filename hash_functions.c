#include <stdio.h>
#include <stdlib.h>
/*
 * Compute an xor-based hash of the data provided on STDIN. The result
 * should be placed in the array of length block_size pointed to by
 * hash_val.
 */

char* hash(FILE *f) {
	char * hash_val=malloc(sizeof(char)*8);
	for(int x = 0; x<8; x++){
	hash_val[x]='\0';
	}
char x=0;
int index=0;
while ((x=fgetc(f))!= EOF){
	hash_val[index]=(char)x^hash_val[index];
	if (index == 7){
		index=0;
	}
	else{
		index++;
	}
}
return hash_val;
}
/* 
 * Print the message "Hashes match" if the two hashes of size 
 * block_size contain the same value. Print "Hash mismatch" otherwise.
 */
 
void check_hash(const char *hash1, const char *hash2, long block_size) {
	for (int x=0;x<block_size;x++){
	if (hash1[x]!=hash2[x]){
		printf("Hash mismatch\n");
		return;
	}
}
printf("Hashes match\n");
}

