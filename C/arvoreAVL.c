#include <stdio.h>
#include <stdlib.h>
typedef struct no{
	int valor;
	int altura;
	struct no *left, *right;
}NoArv;

NoArv* remover_elemento(NoArv** raiz, int valor);
int contar_quantos_no(NoArv *raiz);
int altura(NoArv *raiz);
NoArv* buscar(NoArv *raiz, int valor);
void imprimir_v2(NoArv *raiz);
void imprimir_v1(NoArv *raiz);
void inserir_v2(NoArv **raiz, int valor);
void inserir_v1(NoArv **raiz, int valor);
int fatorBalanceamento(NoArv *no);
int calc_altura(NoArv* no);
int maior(int a, int b);
NoArv* alocar_memoria_novo_no(int valor);
NoArv* rotacaoHorario_Anti_Horario(NoArv* root);
NoArv* rotacaoAnti_Horario_Horario(NoArv* root);
NoArv* rotacaoAnti_Horario(NoArv* root);
NoArv* rotacaoHorario(NoArv* root);
NoArv* balancear(NoArv* root);
void atualizar_altura(NoArv* root);
void imprimir_arv(NoArv* root, int nivel);

int main(){
	NoArv *remover, *raiz = NULL;
	int opcao, valor;
	do{
		printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Imprimir\n\t3 - Remover\n");
		scanf("%d", &opcao);
		switch(opcao){
			case 1:
				printf("Digite um valor: ");
				scanf("%d", &valor);
				remover = buscar(raiz, valor);
				if(remover)
					printf("A arvore ja possui o valor %d", valor);
				else
					inserir_v1(&raiz, valor);
				break;
			case 2:
				printf("\nArvore: \n");
				imprimir_arv(raiz, 1);
				//printf("\nAltura: %d", altura(raiz));
				//printf("\nQuantidade: %d", contar_quantos_no(raiz));
				//printf("\nQuantidade de Folha: %d", contar_folha(raiz));
				/*printf("\t\nOrdenado: ");
				imprimir_v2(raiz);*/
				printf("\n\n");
				
				break;
			case 3:
				printf("Digite o valor a ser removido: ");
				scanf("%d", &valor);
				remover = remover_elemento(&raiz, valor);
				if(remover){
					printf("Valor removido: %d\n", remover->valor);
					free(remover);
				}
				else{
					printf("Valor nao encontrado!\n");
				}
				break;
			default:
				if(opcao != 0)
				printf("Valor Invalido!\n");
		}	
	}while(opcao!= 0);
	printf("\nFechando Programa...\n");
	return 0;
}
void imprimir_arv(NoArv* root, int nivel){
	int i;
	if(root){
		imprimir_arv(root->left, nivel + 1);
		printf("\n\n");
		for ( i = 0 ; i < nivel ; i++)
			printf("\t");
		printf("%d", root->valor);
		imprimir_arv(root->right, nivel + 1);	
	}
}

NoArv* balancear(NoArv* root){
	int fb = fatorBalanceamento(root);
	if(fb > 1 && fatorBalanceamento(root->left) >= 0){
		root = rotacaoHorario(root);
	}
	else if(fb > 1 && fatorBalanceamento(root->left) < 0){
		root = rotacaoAnti_Horario_Horario(root);
	}
	else if(fb < -1 && fatorBalanceamento(root->right) <= 0){
		root = rotacaoAnti_Horario(root);
	}
	else if(fb < -1 && fatorBalanceamento(root->right) > 0){
		root = rotacaoHorario_Anti_Horario(root);
	}
	return root;
}
NoArv* rotacaoHorario(NoArv* root){
	NoArv *y, *fi;
	y = root->left;
	fi = y->right;
	
	y->right = root;
	root->left = fi;
	
	root->altura = maior(calc_altura(root->left), calc_altura(root->right)) + 1;
	y->altura = maior(calc_altura(y->left), calc_altura(y->right) + 1);
	
	return y;
}
NoArv* rotacaoAnti_Horario(NoArv* root){
	NoArv* y, *fi;
	y = root->right;
	fi = y->left;
	
	y->left = root;
	root->right = fi;
	
	root->altura = maior(calc_altura(root->left), calc_altura(root->right)) + 1;
	y->altura = maior(calc_altura(y->left), calc_altura(y->right) + 1);
	
	return y;	
}
NoArv* rotacaoAnti_Horario_Horario(NoArv* root){
	root->left = rotacaoAnti_Horario(root->left);
	return rotacaoHorario(root);
}

NoArv* rotacaoHorario_Anti_Horario(NoArv* root){
	root->right = rotacaoHorario(root->right);
	return rotacaoAnti_Horario(root);
}

NoArv* alocar_memoria_novo_no(int valor){
	NoArv *novo = malloc(sizeof(NoArv));
	if(novo){
		novo->altura = 0;
		novo->valor = valor;
		novo->left = NULL;
		novo->right = NULL;
		return novo;
	}	
	else{
		printf("Erro ao alocar memoria...\n");
		return NULL;
	}	
		
}

int maior(int a, int b){
	return (a > b) ? a : b;
}
int calc_altura(NoArv* no){
	return (no) ? no->altura : -1;
}

int fatorBalanceamento(NoArv *no){
	if(no == NULL){
		return 0;
	}
	return calc_altura(no->left) - calc_altura(no->right);
}

void inserir_v1(NoArv **raiz, int valor){

	if((*raiz) == NULL){
		(*raiz) = alocar_memoria_novo_no(valor);
	}
	else{
		if(valor < (*raiz)->valor)
			inserir_v1(&((*raiz)->left), valor);
		else{
			inserir_v1(&((*raiz)->right), valor);
		}	
		(*raiz)->altura = maior( calc_altura( (*raiz)->left ) , calc_altura( (*raiz)->right ) ) + 1;
		(*raiz) = balancear((*raiz));
	}
	
		
}
void inserir_v2(NoArv **raiz, int valor){
	NoArv **aux = raiz;
	while((*aux)){
		if(valor < (*aux)->valor){
			aux = &((*aux)->left);
		}
		else{
			aux = &((*aux)->right);
		}
	}
	(*aux) = alocar_memoria_novo_no(valor);
	
}


void imprimir_v1(NoArv *raiz){
	if(raiz){
		printf("%d ", raiz->valor);	
		imprimir_v1(raiz->left);
		imprimir_v1(raiz->right);
	}
}
void imprimir_v2(NoArv *raiz){
	if(raiz){
		imprimir_v2(raiz->left);
		printf("%d ", raiz->valor);	
		imprimir_v2(raiz->right);
	}
}
NoArv* buscar(NoArv *raiz, int valor){
	if(raiz){
		while(raiz && raiz->valor != valor){
			if(valor < raiz->valor){
				raiz = raiz->left;
			}
			else{
				raiz = raiz->right;
			}
		}
		if(raiz == NULL){
			return NULL;
		}
		else{
			return raiz;
		}
	}
	return NULL;	
}
int altura(NoArv *raiz){ 
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

int contar_quantos_no(NoArv *raiz){ 
	return raiz ? contar_quantos_no(raiz->left) + contar_quantos_no(raiz->right) + 1 : 0 ;
}
int contar_folha(NoArv *raiz){ 
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

NoArv* remover_elemento(NoArv** raiz, int valor){
	if(*raiz){
		NoArv *aux = *raiz;
		NoArv *pai = NULL;
		while(aux && aux->valor != valor){
			pai = aux;
			if(valor < aux->valor){
				aux = aux->left;
			}
			else{
				aux = aux->right;
			}
		}
	
		if(aux && aux->valor == valor){
			if(aux->left == NULL && aux->right == NULL){ // folha
				if((*raiz) == aux){ 
					(*raiz) = NULL;	
				}
				else if(pai->left == aux){
					pai->left = NULL;
				}	
				else{
					pai->right = NULL;	
				}
				
			}
			else if(aux->left == NULL ^ aux->right == NULL){ // 1 filho
				NoArv *filho = (aux->left != NULL) ? aux->left : aux->right;
				if( pai == NULL){
					(*raiz)	= filho; 
				}
				else if(pai->left == aux){ 
					pai->left = filho;
				}	
				else{
					pai->right = filho;	
				}	
			}
			else{ // 2 filhos	
				NoArv *quem_mais_esquerda = aux->right;
				NoArv* anterior = aux;
				while(quem_mais_esquerda->left){
					anterior = quem_mais_esquerda;
					quem_mais_esquerda = quem_mais_esquerda->left;
				}
				if(aux != anterior){
					anterior->left = quem_mais_esquerda->right;
					quem_mais_esquerda->right = aux->right;
				}
				
				if(pai == NULL){
					(*raiz) = quem_mais_esquerda;
				}	
				else if(pai->left == aux){
					pai->left = quem_mais_esquerda;	
				}
				else{
					pai->right = quem_mais_esquerda;	
				}

				quem_mais_esquerda->left = aux->left;
				/*while(quem_mais_esquerda->left){
					anterior = quem_mais_esquerda;
					quem_mais_esquerda = quem_mais_esquerda->left;
				}
				int x = aux->valor;
				aux->valor = quem_mais_esquerda->valor;
				quem_mais_esquerda->valor = x;
				if(quem_mais_esquerda->right == NULL) // folha
					return remover_elemento(&quem_mais_esquerda, x);
				anterior->left = quem_mais_esquerda->right;
				quem_mais_esquerda->right = NULL;
				return remover_elemento(&quem_mais_esquerda, x);*/
			}
			atualizar_altura((*raiz));
			(*raiz) = balancear((*raiz));
			return aux;
		}
		else{
			return NULL;
		}
	}		
	else{
		return NULL;
	}
}

void atualizar_altura(NoArv* root){
	if(root == NULL) return;
	if(root->left){
		atualizar_altura(root->left);
	}
	if(root->right){
		atualizar_altura(root->right);
	}
	root->altura = maior( calc_altura( root->left ) , calc_altura( root->right ) ) + 1;
}