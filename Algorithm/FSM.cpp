#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <windows.h>
#define NO_OF_CHARS 256
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
int getNextState(char *pat, int M, int state, int x)
{

    if (state < M && x == pat[state])
        return state+1;
    int ns, i;
    for (ns = state; ns > 0; ns--)
    {
        if (pat[ns-1] == x)
        {
            for (i = 0; i < ns-1; i++)
                if (pat[i] != pat[state-ns+1+i])
                    break;
            if (i == ns-1)
                return ns;
        }
    }

    return 0;
}
void computeTF(char *pat, int M, int** TF)
{
    int state, x;
    for (state = 0; state <= M; ++state)
        for (x = 0; x < NO_OF_CHARS; ++x)
            TF[state][x] = getNextState(pat, M, state, x);
}
void search(char *pat, char *txt)
{
    int M = strlen(pat);
    int N = strlen(txt);

    int** TF= new int*[M+1];
    for (int i = 0; i < M+1; ++i)
    TF[i] = new int[NO_OF_CHARS];


    computeTF(pat, M, TF);
    int i, state=0;
    for (i = 0; i < N; i++)
    {
        state = TF[state][txt[i]];
        if (state == M)
            ;
    }
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
    char pat[] = "morning";
    char *txt=FileToString(infile);
    StartCounter();
    search(pat,txt);
    printf("%0.11f \n",GetCounter());
    return 0;
}
