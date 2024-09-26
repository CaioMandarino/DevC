#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
typedef struct no{
	char caracter;
	int frequencia;
	struct no* next;
	struct no* left;
	struct no* right;	
}List;
char **dicionario;

void inserir_Lista(List** start, char letra);
void aumentar_Frequencia(List** start, char letra);
void imprimir(List **start);
void buscar(List** start, char letra);
void organizar(List **start);
void receber_Frase(List **start, char *vetor);
void criar_arvore(List **start);
List* criar_no_arvore(List *aux, List *aux_proximo);
void inserir_root(List **start, List *root);
void criar_dicionario(List *start);
void imprimir_codigo();
void decodificar(List *root, char* vetor);
char* codificar(List *root, char *vetor);
int altura(List *raiz);
int contar_folha(List *raiz);
void criar_matriz(List *start);
int calc_tamanho_string(List* root, char *vetor);
void compactar(char* codigo);
void descompactar(List *root);
int descobrir_tamanho();
void ler_texto(char *texto);

int main(){
	char *codigo;
	List *start = NULL;
  	char *texto = calloc(descobrir_tamanho() + 2, sizeof(char));
  	SetConsoleOutputCP(65001);
	//char frase[] = "Estou aprendendo a Programar! Funcionou PORRA";
  	ler_texto(texto);
	receber_Frase(&start, texto);
 	codigo = codificar(start, texto);
	compactar(codigo);
	descompactar(start);
	return 0;	
}
void ler_texto(char *texto){
	char letra;
	int i = 0;
	FILE *arq = fopen("comprimir.txt", "r");
	if(arq == NULL){
		printf("Erro ao abrir arquivo em ler_texto\n");
	}
 	else{
 		while(!(feof(arq)) ){ 			
		 	letra = fgetc(arq);
			texto[i] = letra;
			i++; 		
		}
		texto[i] = '\0';
	
	 }
 	fclose(arq);
}

int descobrir_tamanho(){
	int tam = 0;
	FILE *arq = fopen("comprimir.txt", "r");
	if(arq == NULL){
		printf("Erro ao abrir arquivo em descobrir_tamanho()\n");
	}
	else{
		while(fgetc(arq) != -1){
			tam++;
		}
		fclose(arq);
	}
	
	return tam;
}
unsigned int  eh_bit_um(unsigned char byte, int i){
	unsigned char mascara = (1 << i);
	return byte & mascara;
}
void descompactar(List *root){
	FILE *arq = fopen("compactar.bin", "rb");
	if(arq == NULL){
		printf("Erro ao abrir o arquivo");
		return;
	}
	else{
		List *aux = root;
		unsigned char byte;
		int i;
		while(fread(&byte, sizeof(unsigned char), 1, arq)){
			for( i = 7 ; i >= 0; i--){
				if(eh_bit_um(byte, i)){ // bit 1
					aux = aux->right;	
				}
				else{ // bit 0
					aux = aux->left;	
				}
				if(aux->left == NULL && aux->right == NULL){
					printf("%c", aux->caracter);
					aux = root;
				}
			}					
		}
	fclose(arq);
	}
}
void compactar(char* codigo){
	FILE *arq = fopen("compactar.bin", "wb");
	if(arq == NULL){
		printf("\nERRO, ao abrir o arquivo\n");
	}

	int  j = 7, i = 0;
	unsigned char byte = 0, mascara = 1;
	while(codigo[i] != '\0'){
		mascara = 1;
		if(codigo[i] == '1'){
			mascara = mascara << j;	
			byte = byte | mascara;
		
		}
		j--;
		if(j < 0){
			fwrite(&byte ,sizeof(unsigned char),1, arq);
			j = 7;
			byte = 0;
		}
		i++;
	}
	if (j != 7){
		fwrite(&byte ,sizeof(unsigned char),1, arq);	
	}
	
	fclose(arq);
	
}



void imprimir_codigo(List* start){
	int i = 0, j;
	for (  ; i < contar_folha(start) ; i++){
		printf("%c = ", dicionario[i][0]);
		for ( j = 1 ; j < (altura(start) + 1) ; j++){
			printf("%c", dicionario[i][j]);
		}
		printf("\n");
	}
}
void criar_matriz(List *start){
	int i, j;
	dicionario = (char**) (malloc(sizeof(char*) * contar_folha(start)));
	for( i = 0 ; i <= contar_folha(start) ; i++ ){
		dicionario[i] = (char*) (calloc( altura(start) + 2 , sizeof(char)));
	}
}
int contar_folha(List *raiz){ 
	if(raiz){
		if( (raiz->right == NULL) && (raiz->left == NULL) ){
			return 1;	
		}
		else{
			return contar_folha(raiz->left) + contar_folha(raiz->right);
		}	
	}
	return 0;
}
int altura(List *raiz){ 
	if(raiz == NULL){
		return -1;
	}
	else{
		int esq = altura(raiz->left);
		int dir = altura(raiz->right);
		if(esq > dir){
			return esq + 1;
		}  
		else{
			return dir + 1;
		}
	}
}
int calc_tamanho_string(List* root, char *vetor){
	return altura(root) * strlen(vetor) + 1;
}
char* codificar(List *root, char *vetor){
	int tam = calc_tamanho_string(root, vetor);
	char *codigo = (char*) calloc(tam, sizeof(char));
	char temp[2]; 
	int i, j, cont, verificar = 0;
	for ( i = 0 ; i < strlen(vetor) ; i++ ){
		for ( j = 0 ; j <= contar_folha(root) ; j++){
			if(vetor[i] == dicionario[j][0]){
				for( cont = 1 ; dicionario[j][cont] != '\0'; cont++ ){
					temp[0] = dicionario[j][cont];
					temp[1] = '\0';
					strcat(codigo, temp);
				}
				verificar = 1;	
			}
		}
		if(verificar == 0){
			printf("\nERRO, A frase chave nao possui esse caracter: %c\n", vetor[i]);
			return NULL;
		}
		verificar = 0;		
	}
	return codigo;
}

void decodificar(List *root, char* vetor){
	int i;
	List *aux = root;
	for( i = 0 ; i < strlen(vetor) ; i++ ){
		if(vetor[i] == '0'){
			aux = aux->left;
		}
		else if ( vetor[i] == '1'){
			aux = aux->right;
		}
		else{
			printf("\nERRO! A mensagem so pode possuir 0 ou 1\n");
			return;
		}
		if(aux->left == NULL && aux->right == NULL){
			printf("%c", aux->caracter);
			aux = root;
		}
	}
}
void criar_dicionario(List *start){
	int static i = 0, j = 0;
	char static zeroou1[50];
	if(start){
		if(start->caracter != '\0' ){
			zeroou1[i] = '\0';
			dicionario[j][0] = start->caracter;
			strcat(dicionario[j], zeroou1);
			j++;
		}
		if(start->left){
			zeroou1[i] = '0';
			i++;
			criar_dicionario(start->left);
			i--;	
		}
		if(start->right){	
			zeroou1[i] = '1';
			i++;
			criar_dicionario(start->right);
			i--;
		}
	}

}
void criar_arvore(List **start){
	while((*start) && (*start)->next){
		List *aux = (*start);
		List *aux_proximo = aux->next;
		List *root = criar_no_arvore(aux, aux_proximo);	
		inserir_root(&(*start), root);
		(*start) = aux_proximo->next;
		aux->next = NULL;
		aux_proximo->next = NULL;
	}	
}
List* criar_no_arvore(List *aux, List *aux_proximo){
	List *root = malloc(sizeof(List));
	if(root == NULL){
		printf("Erro ao alocar memoria...\n");
		return NULL;
	}
	root->frequencia = aux->frequencia + aux_proximo->frequencia;
	root->caracter = '\0';
	root->left = aux;
	root->right = aux_proximo;
	root->next = NULL;
	return root;
}
void inserir_root(List **start, List *root){
	if((*start) && root){
		List *aux = (*start);
		List *anterior = NULL;
		while(aux && aux->frequencia < root->frequencia){
			anterior = aux;
			aux = aux->next;
		}
		if(anterior){
			anterior->next = root;
			root->next = aux;
		}
		else{ 
			(*start) = root;
			root->next = aux->next;
		}
	}
}
void inserir_Lista(List** start, char letra){
	List *novo = malloc(sizeof(List));
	if(novo == NULL){
		printf("Erro ao alocar memoria...\n");
		return;
	}
	novo->next = NULL;
	novo->left = NULL;
	novo->right = NULL;
	novo->caracter = letra;
	novo->frequencia = 1;
	if((*start) == NULL)
		(*start) = novo;
	else{
		List *aux = (*start);
		while(aux->next){
			aux = aux->next;
		}
		aux->next = novo;
	}	
}
void aumentar_Frequencia(List** start, char letra){
	if((*start) == NULL) return;
	List *aux = (*start);
	while(aux->caracter != letra){
		aux = aux->next;
	}
	aux->frequencia++;
}
void buscar(List** start, char letra){
	List *aux = (*start);
	while(aux && aux->next && aux->caracter != letra){
		aux = aux->next;
	}
	if(aux && aux->caracter == letra){
		aumentar_Frequencia(start, letra);		
	}	
	else{
		inserir_Lista(&(*start), letra);
	}
}
void organizar(List **start){
	if((*start)->next){
		List *aux = (*start);
		char salvarLe;
		int salvarFre;
		while(aux->next){
			List *proxima = aux->next;
			while(proxima){
				if(aux->frequencia > proxima->frequencia){
					salvarFre = aux->frequencia;
					salvarLe = aux->caracter;
					aux->frequencia = proxima->frequencia;
					aux->caracter = proxima->caracter;
					proxima->frequencia = salvarFre;
					proxima->caracter = salvarLe;
				}
				proxima = proxima->next;	
			}
			aux = aux->next;
		}
	}
}
void receber_Frase(List **start, char *vetor){
	int i;
	for ( i = 0 ; i < strlen(vetor) ; i++){
		buscar(start, vetor[i]);
	}
	organizar(&(*start));
	criar_arvore(&(*start));
	criar_matriz(*start);
	criar_dicionario(*start);	
}
void imprimir(List **start){
	List *aux = (*start);
	printf("Lista:\n");
	printf("-------------\n");
	while(aux){
		printf("Letra: %c\nFrequencia: %d\n", aux->caracter, aux->frequencia);
		printf("-------------\n");
		aux = aux->next;
	}
}