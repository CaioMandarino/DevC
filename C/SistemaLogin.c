#include <stdio.h>
#include <string.h>
int main (void){
	FILE *arq;
	char usuario[30], senha[30], conferir[30];
	char nomeParaArq[54];
	char resp;
	int registro, tamanho;
	do {		
		printf("Vc ja esta registrado? [1] para Sim e [2] para Nao: ");
		scanf("%d", &registro);
		switch(registro){
			case 1 :
				printf("Qual seu usuario: ");
				scanf("%s", usuario);
				getchar();
				printf("Qual sua senha: ");
				fgets(senha, 30, stdin);
				strcat(usuario, ".bin");
				arq = fopen(usuario, "rb");
				if (arq == NULL){
					printf("Erro ao abrir o arquivo");
					return 1;
				}
				fread(&conferir, sizeof(conferir), 30, arq);
				for ( ; ; ){
					if (strcmp(conferir, senha) == 0){
						printf("Login realizado com sucesso!\n");
						break;
					}
					else {
						printf("Erro, usuario ou senha incorreto\n");
						printf("Qual sua senha: ");
						fgets(senha, 30, stdin);
					}
					fclose(arq);	
				}
				break;	
			case 2 :
				printf("Escolha um nome de usuario: ");
				scanf("%s", usuario);
				getchar();
				printf("Escolha uma senha: ");
				fgets(senha, 30, stdin);
				strcat(usuario, ".bin");
				arq = fopen(usuario, "wb");
				if (arq == NULL){
					printf("Erro ao abrir o arquivo");
					return 1;
				}
				tamanho = strlen(senha);
				fwrite(senha, sizeof(char), tamanho, arq);
				fclose(arq);
				break;
			default :
				printf("Digite um valor que seja 1 ou 2\n");
		}
		printf("Quer fechar o programa? [S] / [N]");
		scanf(" %c", &resp);
	} while (resp == 'N');
	return 0;
}