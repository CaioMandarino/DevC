#include <stdio.h>
int calc_existencia(int razao, int a1, int valor){
	int cont = 1;
	if (razao == 0)
		return (valor == a1 ) ? 1 : -1;
	while((razao > 0 && valor > a1) || (razao < 0 && valor < a1)){
		a1 = a1 + razao;
		cont++;
	}
	return (valor == a1) ? cont : -1;
}
int main(){
	int a1, r, valorProcurado, existe;
	printf("Qual primeiro termo da PA: ");
	scanf("%d", &a1);
	printf("Qual a razao da PA: ");
	scanf("%d", &r);
	printf("Qual valor a ser procurado: ");
	scanf("%d", &valorProcurado);
	existe = calc_existencia(r, a1, valorProcurado);
	if(existe == -1){
		printf("Valor nao encontrado!\n");
	}
	else{
		printf("Valor encontrado no indice %d\n", existe);
	}
	return 0;
}