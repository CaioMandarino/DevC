#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main(){
	int valor[1000];
	int i, j, aux, digito, esquerda = 0, direita = 999;
	srand(time(NULL));
	for( i = 0 ; i < 1000 ; i++){
		valor[i] = rand() % 1100 + 1;	
	}	
	for( i = 0 ; i < 999 ; i++){
		for ( j = i + 1 ; j < 1000 ; j++){
			if (valor[i] > valor[j]){
				aux = valor[i];
				valor[i] = valor[j];
				valor[j] = aux;
			}
		}
	}
	printf("Digite um valor entre 1 e 1100: ");
	scanf("%d", &digito);
	while (esquerda <= direita){
	 		i = esquerda + (direita - esquerda) / 2;
		if	(valor[i] > digito){
			direita = i - 1;
		}
		else if (valor[i] < digito){
			esquerda = i + 1;
 		} 
		else {
			printf("Valor encontrado na posicao: %d\n", i);
			break;
		}
	}
	if(esquerda>direita){
		printf("Valor nao encontrado\n");
	}
	return 0;
}