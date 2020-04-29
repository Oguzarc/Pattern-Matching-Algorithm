#include <stdio.h>
#include <stdlib.h>
#define d 256
#include <time.h>
void search(char **pat, char **txt, long int q,int K,int row,int column)
{
    int textColumn =  column;
    int textRow =  row;
    int patColumn =  K;
    int patRow =  K;
    int p = 0;
    int t = 0;
	int k,z;
	for(int j=0;j<patRow;j++){
		for (int i = 0; i < patColumn; i++) {
        	p = ((d * p + pat[j][i]) & q);
    	}
    }
    //display pattern and text
    printf("\n");
    for(int j=0;j<textRow;j++){
		for (int i = 0; i < textColumn; i++) {
      		printf("%c ",txt[j][i]);
	  	}
	  	printf("\n");
    }
    printf("----------------------------\n");
    	for(int j=0;j<patRow;j++){
		for (int i = 0; i < patColumn; i++) {
      		printf("%c ",pat[j][i]);
	  	}
	  	printf("\n");
    }
    //Hash calculate and Brute-Force character Control
    for (int i = 0; i <=textRow - patRow; i++) {
    	for(int j=0;j<=textColumn-patColumn;j++){
        	t=0;
        	//hash Calculate
            	for(int m=i;m<i+patRow;m++){
					for (int n = j; n <j+patColumn; n++) {
        				t = ((d * t + txt[m][n]) & q);
    				}
    			}
    			//Brute-Force
    		if (p == t) {
                for ( k = 0; k<patRow ; k++){
                    for( z=0; z<patColumn;z++){
                        if (txt[i + z][j + k] != pat[z][k]){
                            goto label;
                            }
                    }
                }
                label:
                if (k == patRow && z == patColumn)
                    printf("Pattern found at index (%d,%d) \n", i,j);
        	}
        }
    }
}
int main(){
    srand(time(NULL));
    int K,row,column;
    char *randomletter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    printf("Please choose text row: ");
    scanf("%d",&row);
    printf("Please choose text column: ");
    scanf("%d",&column);
    printf("Please choose pattern dimension: ");
    scanf("%d",&K);

    char **twoDarray = (char **)malloc(row * sizeof(char *));
    for (int i=0; i<row; i++)
         twoDarray[i] = (char *)malloc(column * sizeof(char));
    char **pattern = (char **)malloc(K * sizeof(char *));
    for (int i=0; i<K; i++)
         pattern[i] = (char *)malloc(K * sizeof(char));
    //creating text values randomly
    for(int i=0; i<row; i++){
        for(int j=0; j<column; j++){
            twoDarray[i][j] =randomletter[rand()%26];
        }
    }
    //chosing k*k from top-right from text
	if(K>row ||K> column){
        printf("k can not be bigger than indexes of matrix");
	}
	else{
       for(int i=0,m=0; i<K; i++,m++) {
        for(int j=column-K,n=0; j<column; j++,n++){
            pattern[m][n]=twoDarray[i][j];
       }
	}
	long long int q=2521008887;
	search(pattern,twoDarray,q,K,row,column);
	return 0;
} }
