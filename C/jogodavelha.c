#include <stdio.h>
#include <stdlib.h>
int ganhou(char y[3][3], int *empate);
void cabeca(char x[3][3]);
void placar(int px, int po, int pe);
int continuar(int conti, char vetor[3][3]);
void jogadorxouo(char vetor[3][3]);
int repitir(char vetor[3][3]);
int pox = 0, poo = 0, poe = 0, jogador = 0;
int main (void){
	int gan = 0, empate = 0;
	char xeo[3][3] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
	placar(pox, poo, poe);
	cabeca(xeo);
	for ( ; ; ){
		jogadorxouo(xeo);
		system("cls");
		placar(pox, poo, poe);
		cabeca(xeo);
		gan = ganhou(xeo, &empate);
		continuar (gan , xeo);
		if (gan == 1){
			pox++;
			repitir(xeo);
			empate = 0;
			continue;	
		}
		if ( gan == 3){
			poe++;
			repitir(xeo);
			empate = 0;
			continue;	
		}
		jogadorxouo(xeo);
		jogador = 0;
		system("cls");
		placar(pox, poo, poe);
		cabeca(xeo);
		gan = ganhou(xeo, &empate);
		continuar (gan, xeo);
		if (gan == 2){
			poo++;
			repitir(xeo);
			empate = 0;
			continue;				
		}		
	}
	return 0;
}
void cabeca(char x[3][3]){
	printf("+---+---+---+\n");
	printf("| %c | %c | %c |\n", x[0][0], x[0][1], x[0][2]);
	printf("+---+---+---+\n");
	printf("| %c | %c | %c |\n", x[1][0], x[1][1], x[1][2]);
	printf("+---+---+---+\n");
	printf("| %c | %c | %c |\n", x[2][0], x[2][1], x[2][2]);	
	printf("+---+---+---+\n");	
}
int ganhou(char y[3][3], int *empate){
	int var, var1, ganhou = 0, ganhouo = 0;
	//Para as Linhas
	for (var1 = 0 ; var1 < 3 ; var1++){
		for (var = 0 ; var < 3 ; var++){
			if ( y[var1][var] == 'X' )
				ganhou++;
			if ( y[var1][var] == 'O')
				ganhouo++;
			}
		if (ganhou == 3){
			return 1;
		}
		else if (ganhouo == 3){
			return 2;
		}
		ganhou = 0;
		ganhouo = 0;
	}
	//Para as colunas
	for (var1 = 0 ; var1 < 3 ; var1++){
		for (var = 0 ; var < 3 ; var++){
			if ( y[var][var1] == 'X') 
			ganhou++;
			if ( y[var][var1] == 'O')
			ganhouo++;
			}
		if (ganhou == 3){
			return 1;
		}
		else if (ganhouo == 3){
			return 2;
		}
		ganhou = 0;
		ganhouo = 0;
	}
	//Para diagonal
	for (var1 = 0 ; var1 < 3 ; var1++){
		if ( y[var1][var1] == 'X')
			ganhou++;
		if ( y[var1][var1] == 'O')
			ganhouo++;
	}
		if (ganhou == 3){
			return 1;
		}
		else if (ganhouo == 3){
			return 2;
		}	
	ganhou = 0;
	ganhouo = 0;
	//Para diagonal oposta
	for (var1 = 0 ; var1 < 3 ; var1++){
		if ( y[var1][3-var1-1] == 'X') // (N - i - 1) em uma matriz N por N para saber a diagonal oposta usar essa formula
			ganhou++;	
		if ( y[var1][3-var1-1] == 'O')
			ganhouo++;	
	}
		if (ganhou == 3){
			return 1;
		}
		else if (ganhouo == 3){
			return 2;
		}
	ganhou = 0;
	ganhouo = 0;
	++(*empate);
	if (*empate == 9){
		return 3;
	}
	return 0;
	}
void placar(int px, int po, int pe){
	printf("        Placar\n");
	printf("   [X]    [O]    [E]\n");
	printf("+------+------+------+\n");
	printf("|  %2d  |  %2d  |  %2d  |\n", px, po, pe);
	printf("+------+------+------+\n\n\n");
}
int continuar(int conti, char vetor[3][3]){
	char sair = 'N', valor = '1';
	int cont, cont1;
	
	if ( conti == 0){
		return 0;		
	}
	else if ( conti == 1) {
		printf("[X] Ganhou!");	
	}
		else if (conti == 2){
			printf("[O] Ganhou!");
		}
		else {
			printf("O Jogo Empatou!");
		}
	printf("\nQuer fechar o programa? [S] para SIM e [N] para NAO:\n");
			scanf(" %c", &sair);
			if ( sair == 'S' || sair == 's'){
				exit(0);
			}
			while(getchar() != '\n');
			for ( cont = 0 ; cont < 3 ; cont++){
				for ( cont1 = 0 ; cont1 < 3 ; cont1++){
					vetor[cont][cont1] = valor;
					valor++;
				}
			}
	return 0;
}
void jogadorxouo(char vetor[3][3]){
	int aux, r, i = -1, cont, cont1;
			do{ 
			aux = 0;
			if (jogador == 0)
				printf("Quer Jogar Onde [X]: ");
			else 
				printf("Quer Jogar Onde [O]: ");
			r = scanf("%d", &i); // 0 == False, ou seja, nao conseguiu ler, 1 conseguiu ler um valor
			if (r != 1){ 
				system("cls");
				placar(pox, poo, poe);
				cabeca(vetor);
				printf("Digite um valor inteiro disponivel!\n");
				while(getchar() != '\n'); // usar para limpar o buffer
				continue; // voltar para o começo do lupe
			}
			for ( cont = 0 ; cont < 3 ; cont++){
				for ( cont1 = 0 ; cont1 < 3 ; cont1++){
					if (vetor[cont][cont1] == i + 48){
						if (jogador == 0){
							vetor[cont][cont1] = 'X';		
						}
						else
							vetor[cont][cont1] = 'O';		
						aux = 1;
					}
				}
			}
			if ( aux == 0 ){
				system("cls");
				placar(pox, poo, poe);
				cabeca(vetor);
				printf("Jogada Invalida!\n");				
			}
		}while (aux == 0);
		jogador++;
}
int repitir(char vetor[3][3]){
	system("cls");
	placar(pox, poo, poe);		
	cabeca(vetor);
	system("pause");
}