#include <stdio.h>
#include <stdlib.h>
typedef struct no{
	int valor;
	struct no *proximo;	
	struct no *anterior;
}No;

void inserir_no_inicio(No **topo, int num);
void inserir_no_meio(No **topo, int num, int valor, int antesOUdepois);
void inserir_no_final(No **topo, int num);
void remover_inicio(No **topo);
void remover_meio(No **topo);
void remover_final(No **topo);
void imprimir(No *topo);
void ordenar_crescente(No **topo);
void ordenar_decrescente(No **topo);
void copiar_Lista(No **destino, No **origem);
void par_ou_impar(No **topo, No **par, No **impar);
No* buscar(No **topo, int num);	
No* ultimo(No *topo);
void ImprimirContrario(No *topo);
void troca_De_No(No **topo, int num, int num2);
void troca_a_posicao(No* trocar, No* trocar2);

int main(){
	No* topo = NULL;
	No* par = NULL;
	No* impar = NULL;
	int opcao, valor, qualnum, aoud;
	do{
		printf("\n\t0 - Sair\n\t1 - InserirInicio\n\t2 - InserirFim\n\t3 - InserirMeio\n\t4 - Imprimir\n\t5 - RemoverInicio\n\t6 - RemoverFim\n\t7 - RemoverValor\n\t8 - OrdenarCresente\n\t9 - OrdenarDecresente\n\t10 - Lista_Par_ou_Impar\n");
		scanf("%d", &opcao);
		switch(opcao){
			case 1:
				printf("Digite um valor: ");
				scanf("%d", &valor);
				inserir_no_inicio(&topo, valor);
				/*// SEGUNDA
				printf("Digite um valor: ");
				scanf("%d", &valor);
				inserir_no_inicio(&topo2, valor);*/
				break;
			case 2:
				printf("Digite um valor: ");
				scanf("%d", &valor);
				inserir_no_final(&topo, valor);
				break;
			case 3:	{
				printf("Digite um valor: ");
				scanf("%d", &valor);
				printf("Qual eh o elemento de referencia: ");
				scanf("%d", &qualnum);
				do{
					printf("\nDigite\n[1] para ANTES DE %d\n[2] para DEPOIS DE %d\n", qualnum, qualnum);
					scanf("%d", &aoud);	
				} while(aoud != 1 && aoud != 2);
				inserir_no_meio(&topo, valor, qualnum, aoud);
				break;
			}
			case 4:
				//printf("\tA: ");
				imprimir(topo);
				/*printf("\tB: ");
				imprimir(topo2);
				printf("\tC: ");
				imprimir(c);*/
				break;
			case 5:
				remover_inicio(&topo);
				break;
			case 6:
				remover_final(&topo);
				break;
			case 7:
				remover_meio(&topo);
				break;
			case 8:
				ordenar_crescente(&topo);
				break;
			case 9:
				ordenar_decrescente(&topo);
				break;
			/*case 10:
				copiar_Lista(&c, &topo);
				copiar_Lista(&c, &topo2);
				break;*/
			case 10:
				par_ou_impar(&topo, &par, &impar);
				break;
			case 11:
				ImprimirContrario(topo);
				break;
			case 12:
				scanf("%d", &valor);
				scanf("%d", &aoud);
				troca_De_No(&topo, valor, aoud);
				break;
			default:
				if(opcao != 0){
					printf("Opcao Invalida\n");
				}
		}
	}while(opcao != 0);
	return 0;
}
void inserir_no_inicio(No **topo, int num){
	No* novo = malloc(sizeof(No));
	if(novo){
		novo->valor = num;
		novo->proximo = (*topo);
		novo->anterior = NULL;
		if((*topo))
			(*topo)->anterior = novo;
		(*topo) = novo;	
	}
	else{
		printf("Erro ao alocar memoria...");
	}
}
void inserir_no_final(No **topo, int num){
	No *aux, *novo = malloc(sizeof(No));
	if(novo){
		novo->valor = num;
		novo->proximo = NULL;
		if((*topo) == NULL){
			(*topo) = novo;
			novo->anterior = NULL;
		}
		else{
			aux = (*topo);
			while(aux->proximo){
				aux = aux->proximo;
			}
			aux->proximo = novo;
			novo->anterior = aux;
		}
	}
	else{
		printf("Erro ao alocar memoria...");
	}
}
void inserir_no_meio(No **topo, int num, int valor, int antesOUdepois){
	No *aux, *novo = malloc(sizeof(No));
	if(novo){
		novo->valor = num;
		novo->proximo = NULL;
		novo->anterior = NULL;
		if((*topo) == NULL){
			(*topo) = novo;
		}
		else{
			aux = (*topo);
			if(antesOUdepois == 1){
				if (aux->valor == valor){
					novo->proximo = (*topo);
					(*topo)->anterior = novo;
					(*topo) = novo;
				} 
				else{
					while(aux->proximo && aux->proximo->valor != valor){
						aux = aux->proximo;	
					}
					if(aux->proximo == NULL){
						printf("Elemento nao encontrado\n");
						free(novo);
					}
					else{
						novo->proximo = aux->proximo;
						novo->anterior = aux;
						aux->proximo->anterior = novo;
						aux->proximo = novo;
					}
				}
			}
			else if(antesOUdepois == 2){
				while(aux && aux->valor != valor){ 
					aux = aux->proximo;
				}
				if(aux == NULL){ 
					printf("Elemento nao encontrado");
					free(novo);
				} 
				else{
					novo->proximo = aux->proximo;
					novo->anterior = aux;
					if(aux->proximo)
						aux->proximo->anterior = novo;
					aux->proximo = novo;
				}
			}
		}
	}
	else{
		printf("Erro ao alocar memoria...");
	}	
}
void imprimir(No *topo){
	printf("\n\tLista: ");
	while(topo){
		printf("%d ", topo->valor);
		topo = topo->proximo;
	}
	printf("\n\n");
}
void ImprimirContrario(No *topo){
	No *aux = NULL;
	if(topo != NULL)
		aux = ultimo(topo);
	printf("\n\tLista: ");
	while(aux){
		printf("%d ", aux->valor);
		aux = aux->anterior;
	}
	printf("\n\n");
}

void remover_inicio(No **topo){
	if(*topo){
		No *remover = *topo;
		*topo = (*topo)->proximo;
		printf("\nO Elemento %d foi removido!\n", remover->valor);
		free(remover);	
	}
	else{
		printf("Sem elementos para remover!\n");
	}
}
void remover_final(No **topo){
	if((*topo)){
		if((*topo)->proximo == NULL){
			printf("\nO Elemento %d foi removido!\n", (*topo)->valor);
			free((*topo));
			(*topo) = NULL;
			return;
		}
		No *ultimo = (*topo);
		while(ultimo->proximo){	
			ultimo = ultimo->proximo;
		}
		printf("\nO Elemento %d foi removido!\n", ultimo->valor);
		ultimo->anterior->proximo = NULL;
		free(ultimo);
	}
	else{
		printf("Sem elementos para remover!\n");	
	}
}
void remover_meio(No **topo){
	if((*topo)){
		int valor;
		printf("Qual eh o elemento a ser removido: ");
		scanf("%d", &valor);
		No *remover = (*topo);
		if((*topo)->valor == valor){
			printf("\nO Elemento %d foi removido!\n", remover->valor);
			(*topo) = remover->proximo;
			if((*topo))
				(*topo)->anterior = NULL;
			free(remover);
			return;
		}
		while(remover->proximo && remover->proximo->valor != valor){
			remover = remover->proximo;
		}
		if(remover->proximo == NULL){
			printf("Elemento nao encontrado!\n");
		}
		else{
			No *excluir = remover->proximo;
			remover->proximo = excluir->proximo;
			if(excluir->proximo)
				excluir->proximo->anterior = remover; // NAO FAZ SENTIDO O REMOVER->PROXIMO->ANTERIOR FUNCIONAR!!! PQ???
			printf("\nO Elemento %d foi removido!\n", excluir->valor);
			free(excluir);
		}
	}
	else{
		printf("Sem elementos para remover!\n");	
	}
}
void ordenar_crescente(No **topo){
	if( (*topo)  && ( (*topo)->proximo) ){
		No *anterior, *aux = (*topo);
		int salvar;
		anterior = (*topo);
		while(anterior->proximo){
			aux = anterior->proximo;
			while(aux){
				if(anterior->valor > aux->valor){
					salvar = anterior->valor;
					anterior->valor = aux->valor;
					aux->valor = salvar;
				}
				aux = aux->proximo;
			}
			anterior = anterior->proximo;
		}
		imprimir(*topo);

	}
	else{
		printf("Sem elementos para ordenar!\n");	
	}
}
void ordenar_decrescente(No **topo){
	if( (*topo)  && ( (*topo)->proximo) ){
		No *anterior, *aux = (*topo);
		int salvar;
		anterior = (*topo);
		while(anterior->proximo){
			aux = anterior->proximo;
			while(aux){
				if(anterior->valor < aux->valor){
					salvar = anterior->valor;
					anterior->valor = aux->valor;
					aux->valor = salvar;
				}
				aux = aux->proximo;
			}
			anterior = anterior->proximo;
		}	
		imprimir(*topo);
	}
	else{
		printf("Sem elementos para ordenar!\n");	
	}
}
No* buscar(No **topo, int num){
	No *aux = (*topo);
	while(aux && aux->valor != num){
		aux = aux->proximo;
	}
	return aux;
}
void copiar_Lista(No **destino, No **origem){
	No *aux = (*origem);
	while(aux){
		inserir_no_final(&(*destino), aux->valor);
		aux = aux->proximo;
	}
}
void par_ou_impar(No **topo, No **par, No **impar){
	No *aux = (*topo);
	while(aux){
		if(aux->valor > 0){
			if(aux->valor % 2 == 0){
				inserir_no_final(par, aux->valor);
			}
			else{
				inserir_no_final(impar, aux->valor);
			}
		}
		aux = aux->proximo;
	}
	printf("\tPAR:");
	imprimir(*par);
	printf("\tIMPAR:");
	imprimir(*impar);
}
No* ultimo(No *topo){
	No* aux = topo;
	while(aux->proximo){
		aux = aux->proximo;
	}	
	return aux;	
}

void troca_De_No(No **topo, int num, int num2){
	if(num == num2){
		return;
	}
	No *trocar, *trocar2, *aux;
	aux = buscar(topo, num);
	if(aux == NULL){
		return;
	}
	trocar = aux;
	aux = buscar(topo, num2);
	if(aux == NULL){
		return;
	}
	trocar2 = aux;
	if((*topo)->valor == num){
		troca_a_posicao(trocar, trocar2);
		(*topo) = trocar2;		
	} else if((*topo)->valor == num2) {
			troca_a_posicao(trocar, trocar2);
			(*topo) = trocar;		
	} else{	
		troca_a_posicao(trocar, trocar2);
	}
	
}

void troca_a_posicao(No* trocar, No* trocar2){
	
	if(trocar->proximo == trocar2){
		trocar->proximo = trocar2->proximo;
		if(trocar2->proximo)
			trocar2->proximo->anterior = trocar;
		trocar2->anterior = trocar->anterior;
		if(trocar->anterior)
			trocar->anterior->proximo = trocar2;
		trocar2->proximo = trocar;	
		trocar->anterior = trocar2;
	}
	else if(trocar2->proximo == trocar){
		trocar2->proximo = trocar->proximo;	
		if(trocar->proximo)
			trocar->proximo->anterior = trocar2;
		trocar->anterior = trocar2->anterior;
		if(trocar2->anterior)
			trocar2->anterior->proximo = trocar;
		trocar->proximo = trocar2;
		trocar2->anterior = trocar;
	}
	else{
		No* salvarP = trocar->proximo;
		No* salvarA = trocar->anterior;
		if(trocar->proximo)
				trocar->proximo->anterior = trocar2;
		trocar->proximo = trocar2->proximo;
		if(trocar->anterior)
			trocar->anterior->proximo = trocar2;
		trocar->anterior = trocar2->anterior;
		if(trocar2->proximo)	
			trocar2->proximo->anterior = trocar;
		trocar2->proximo = salvarP;
		if(trocar2->anterior)
			trocar2->anterior->proximo = trocar;
		trocar2->anterior = salvarA;
		}
	}