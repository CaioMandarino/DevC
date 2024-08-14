#include <stdio.h>
#include <stdlib.h>
void primo (int *v, int *s, int y);
int main (void){
	int x, *ptr, i, *salvar;
	printf("Quantos valores serao testados: ");
	scanf("%d", &x);
	ptr = (int *)(malloc( x * sizeof( int )));
	salvar = (int *)(malloc( x * sizeof( int )));
	if ( ptr == NULL)
		return 1;
	if ( salvar == NULL)
		return 2;
	for ( i = 0 ; i < x ; i++){
		salvar[i] = 0;
	}
	for ( i = 0 ; i < x ; i++){
		printf("Digite o %d.o valor: ", i + 1);
		scanf("%d", &ptr[i]);
	}
	primo(ptr, salvar, x);
	for ( i = 0 ; i < x ; i++){
		if ( salvar[i] != 0){
			printf("Valores Primos: %d\n", salvar[i]);
		}
	}
	system("pause");
	free(ptr);
	free(salvar);
	return 0;
}
void primo (int *v, int *s, int y){	// Para melhorar a eficiência, deve-se modificar a condição de verificação para iterar até a raiz quadrada (melhor opção) em vez de até a metade + 1.
	int cont, primo, testador, contf = 0; 
	for ( cont = 0 ; cont < y ; cont++ ){
		testador = 0;
		for ( primo = v[cont]; primo > 0 ; primo--){
			if ( v[cont] % primo == 0){
				testador++;
			}
		}
		if ( testador == 2){
			s[contf] = v[cont];
			contf++;
		}
	}	
}
