#include <string.h>
#include <stdio.h>
#include<stdlib.h>
#include <windows.h>
double PCFreq = 0.0;
__int64 CounterStart = 0;
void StartCounter()
{
    LARGE_INTEGER li;
   if(!QueryPerformanceFrequency(&li))
    	printf("QueryPerformanceFrequency failed!\n");

    PCFreq = double(li.QuadPart)/1000000000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}
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
char word[] = "morning";
char *text = FileToString(infile);

StartCounter();
int m=strlen(word);
int n=strlen(text);
int i= 0;
for(i=0; i< n-m+1; i++){
	int j=0;
	while(j<m && text[i+j]==word[j]){
		j++;
	}
	if(j==m){
		;
	}
}
printf("%0.11f \n",GetCounter());
return 0;
}
