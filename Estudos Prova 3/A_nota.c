#include <stdio.h> 

int main(){
    int n = 0, k = 0, tmp = 0, maior = 0; 

    while (scanf("%d %d", &n, &k) == 2){
        int notas[n];
        for(int i = 0; i < n; i++){
            scanf("%d", &notas[i]);
        }

        for(int i = 0; i < n-1; i++){
            for(int j = 0; j < n-1 -i; j++){
                if(notas[j]< notas[j+1]){
                    tmp = notas[j];
                    notas[j]= notas[j+1];
                    notas[j+1] = tmp;
                    
                }
            }
        }

        int soma = 0;
        for(int i = 0; i < k; i++){
            soma = soma + notas[i];
        }
        printf("%d\n", soma);

    }
}