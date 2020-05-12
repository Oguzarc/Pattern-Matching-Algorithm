#include <stdio.h>
#include<string.h>
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
int main()
{
    FILE *infile = fopen("dosya2.txt", "r");
    char P[] = "morning";
    char *T = FileToString(infile);
    StartCounter();
    int m = strlen(P);
    int n = strlen(T);

    int lastoccoff[127];
    for(int j=0; j<127; j++)
    {
        lastoccoff[j]=-1;
    }
    for(int j=0; j<m; j++)
    {
        lastoccoff[P[j]]=j;
    }
    int i;
    for(i=0; i<n-m; i+=m-lastoccoff[T[i+m]])
    {
        int j=0;
        while (j<m && T[i+j]==P[j])
        {
            j++;
        }
        if(j==m){
            ;
        }
    }
    if(i==n-m){
        int j=0;
        while (j<m && T[i+j]==P[j])
        {
            j++;
        }
        if(j==m){
            ;
        }
    }
    printf("%0.11f \n",GetCounter());
}
