#include <stdio.h>

int somma(int N);

int main() {
    int n;
    printf("Inserisci un numero intero non negativo\n");
    scanf("%d",&n);

    if(n>0)
        printf("Somma delle cifre:%d\n",somma(n));
    else
        printf("numero negativo!\n");

    return 0;
}

int somma(int N){
/*ad ogni iterazione ricorsiva calcolo il resto della divisione intera
  N/10 e lo sommo alla sommatoria
  Cond. di terminazione: se N=0 ritorno il valore di N */
  
    int res=0,som=0;
    if(N==0)
        return N;
    res=N%10;
    som=res+somma(N/10);
    return som;
}

