#include <stdio.h> // Biblioteca Padrão
#include <stdlib.h> // Para função system("cls")
#include <string.h> // Para funções strcpy e strcmp
#include <unistd.h> // Para função sleep()
#include <locale.h> // Para função setlocale()

void cabeca(char *x1, char *x2, char *x3, char *x4); // Declaração de função, para poder ficar depois da função int main
void troca(char *t); // Declaração de função
void amarelo(char *v); // Declaração de função
void temp(int seg); // Declaração de função
int main(void) {
    char s1[10] = "Vermelho", s2[10] = "Verde", s3[10] = "Vermelho", s4[10] = "Vermelho"; // Declaração das variáveis que armazenam as cores de cada semáforo
    setlocale(LC_ALL, "portuguese"); // Para poder usar acentuação na função printf

    for (;;) { // Início de um loop infinito para o controle dos semáforos
        cabeca(s1, s2, s3, s4); // Função para exibir as cores dos semáforos na tela
        temp(17); // Temporizador de 17s para simular a passagem do tempo
        amarelo(s2); // Chama a função para trocar a cor do segundo semáforo para Amarelo
        system("cls"); // Limpar tela 
        cabeca(s1, s2, s3, s4); // Chama a função de novo para atualizar com as cores trocadas
        temp(3); // Temporizador de 3s para simular a passagem do tempo
        troca(s2); // Chama a função para trocar a cor do segundo semáforo 
        troca(s3); // Chama a função para trocar a cor do terceiro semáforo
        system("cls"); // Limpar tela 
        cabeca(s1, s2, s3, s4); // Chama a função de novo para atualizar com as cores trocadas
        temp(17); // Temporizador de 17s para simular a passagem do tempo
        amarelo(s3); // Chama a função para trocar a cor do terceiro semáforo para Amarelo
        system("cls"); // Limpar tela 
        cabeca(s1, s2, s3, s4); // Chama a função de novo para atualizar com as cores trocadas
        temp(3); // Temporizador de 3s para simular a passagem do tempo
        troca(s3); // Chama a função para trocar a cor do terceiro semáforo
        troca(s1); // Chama a função para trocar a cor do primeiro semáforo
        troca(s4); // Chama a função para trocar a cor do quarto semáforo
        system("cls"); // Limpar tela 
        cabeca(s1, s2, s3, s4); // Chama a função de novo para atualizar com as cores trocadas
        temp(37); // Temporizador de 37s para simular a passagem do tempo
        amarelo(s1); // Chama a função para trocar a cor do primeiro semáforo para Amarelo
        amarelo(s4); // Chama a função para trocar a cor do quarto semáforo para Amarelo
        system("cls"); // Limpar tela 
        cabeca(s1, s2, s3, s4); // Chama a função de novo para atualizar com as cores trocadas
        temp(3); // Temporizador de 3s para simular a passagem do tempo
        troca(s1); // Chama a função para trocar a cor do primeiro semáforo 
        troca(s4); // Chama a função para trocar a cor do quarto semáforo 
        troca(s2); // Chama a função para trocar a cor do segundo semáforo 
        system("cls"); // Limpar tela 
    }
}

void cabeca(char *x1, char *x2, char *x3, char *x4) { // Função para reduzir a quantidade de linhas
    printf("1º Semáforo:  %s\n", x1); 
    printf("2º Semáforo:  %s\n", x2);
    printf("3º Semáforo:  %s\n", x3);
    printf("4º Semáforo:  %s\n\n", x4);
}

void troca(char *t) { // Função para trocar a cor do semáforo: se a cor atual for 'Vermelho', altera para 'Verde'; caso contrário, altera para 'Vermelho'
    if (strcmp(t, "Vermelho") == 0) { // Verifica se o parâmetro enviado para função é igual a "Vermelho"
        strcpy(t, "Verde"); // Troca a cor para verde
    } else { // Senão
        strcpy(t, "Vermelho"); // Troca a cor para vermelho
    }
}

void amarelo(char *v) { // Função para trocar a cor do semáforo para Amarelo
    strcpy(v, "Amarelo"); // Troca a cor para amarelo
}
void temp(int seg){ // Função para o temporizador
	int i;
	if(seg == 17){ // Reconhece o tempo de 17s 
		for(i = 0; i < 18; i++){ // Contador
			sleep(1);
			if (i < 10){
				printf("\rTemporizador: 00:0%d",i);
			}
			else{
				printf("\rTemporizador: 00:%d",i);
			}
		}
		sleep(1);
		return ;
	}
	if (seg == 3){ // Reconhece o tempo de 3 segundos
		for (i = 0; i < 4; i++){ // Contador
			sleep(1);
			printf("\rTemporizador: 00:0%d",i);
		}
		sleep(1);
		return ;
	}
	if (seg == 37){ // Reconhece o tempo de 37 segundos
	for(i = 0; i < 38; i++){ // Contador
			sleep(1);
			if (i < 10){
				printf("\rTemporizador: 00:0%d",i);
			}
			else{
				printf("\rTemporizador: 00:%d",i);
			}
		}
		sleep(1);
		return ;
	}		
}


