#include <stdio.h>
int Hofstadter(int N);
int main() {
    int n,i;
    
    printf("Quanti valori della sequenza di Hofstadter vuoi stampare?\n ");
    scanf("%d",&n);
    
    for(i=0;i<n;i++){
	printf("\t%d",Hofstadter(i));
	}
	
    return 0;
}
int Hofstadter(int N){
    int res;
    if(N==0)
        return 0;
    else{
        res=N-Hofstadter(Hofstadter(Hofstadter(N-1)));
        return res;
    }


}
