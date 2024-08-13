#include<stdio.h>
int main (void){
	int x, y; 
	int aux, aux1 = 0;
	char resp = 'N', resp1 = 'N';	
	do {
		while(resp1 == 'N'){
			printf("Digite um valor: ");
			scanf("%d", &x);
			resp1 = 'S';
		}
		do {
			printf("[1] Digite para somar\n");
			printf("[2] Digite para subtrair\n");
			printf("[3] Digite para multiplicar\n");
			printf("[4] Digite para divisao\n");
			printf("[5] Digite para sair\n");
			scanf("%d", &aux);
			system("cls");
			switch (aux) {
				case 1 :
					printf("Digite um o valor para ser somado: ");
					scanf("%d", &y);
					x += y;
					printf("O valor somado eh: %d\n", x);
					aux1 = 0;
				break;		
				case 2 :
					printf("Digite um o valor para ser subtraido: ");
					scanf("%d", &y);
					x -= y;
					printf("O valor subtraido eh: %d\n", x);
					aux1 = 0;
				break;
				case 3 :
					printf("Digite um o valor para ser multiplicado: ");
					scanf("%d", &y);
					x *= y;
					printf("O valor da multiplicacao eh: %d\n", x);
					aux1 = 0;
				break;
				case 4 :
					printf("Digite um o valor para ser dividido: ");
					scanf("%d", &y);
					x /= y;
					printf("O valor da divisao eh: %d\n", x);	
					aux1 = 0;
				break;
				case 5 :
					printf("Saindo do Programa...");
					aux1 = 0;
					resp = 'S';
				break;
				default	:
					printf("Digite um dos valores presentes: (1, 2, 3, 4, 5)");
					aux1 = 1;				
			}
			if( aux1 == 0 && resp == 'N'){
				printf("Quer sair do programa: [S] para SIM e [N] para NAO: ");
				scanf(" %c", &resp);
				if (resp == 'N'){
					printf("Quer manter o valor %d na memoria? [S] para SIM e [N] para NAO\n", x);
					scanf(" %c", &resp1);
				}
				else{
					printf("Saindo do Programa...");	
				}				 	
			}
		} while( aux1 == 1 );
	} while( resp == 'N');
	
	return 0;
}