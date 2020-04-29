#include <string.h>
#include <stdio.h>
#include<stdlib.h>
char *FileToString(FILE *infile){
    char *buffer;
    long numbytes;
    fseek(infile, 0L, SEEK_END);
    numbytes = ftell(infile);
    fseek(infile, 0L, SEEK_SET);
    buffer = (char*)calloc(numbytes, sizeof(char));
    fread(buffer, sizeof(char), numbytes, infile);
    fclose(infile);
    return buffer;
}
int main(){
FILE *infile = fopen("dosya2.txt", "r");
char word[] = "strenuous c";
char *text = FileToString(infile);

int m=strlen(word);
int n=strlen(text);
int i= 0;
for(i=0; i< n-m+1; i++){
	int j=0;
	while(j<m && text[i+j]==word[j]){
		j++;
	}
	if(j==m){
		printf("There is a match!! %d \n",i);
	}
}
return 0;
}
