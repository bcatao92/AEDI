/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2021                           **/
/**   <turma> - Prof. Luciano Antonio Digiampietri                  **/
/**                                                                 **/
/**   EP 2 - Fila Preferencial                                      **/
/**                                                                 **/
/**   <Bruno Alves Catão Silva>                   <7553278>         **/
/**                                                                 **/
/*********************************************************************/

#include "filapreferencial.h"

PFILA criarFila(){
    PFILA res = (PFILA) malloc(sizeof(FILAPREFERENCIAL));
    res->cabeca = (PONT) malloc(sizeof(ELEMENTO));
    res->inicioNaoPref = res->cabeca;
    res->cabeca->id = -1;
    res->cabeca->ehPreferencial = false;
    res->cabeca->ant = res->cabeca;
    res->cabeca->prox = res->cabeca;
    return res;
}

int tamanho(PFILA f){
	PONT atual = f->cabeca->prox;
	int tam = 0;
	while (atual != f->cabeca) {
		atual = atual->prox;
		tam++;
	}
	return tam;
}

PONT buscarID(PFILA f, int id){
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		if (atual->id == id) return atual;
		atual = atual->prox;
	}
	return NULL;
}

void exibirLog(PFILA f){
	int numElementos = tamanho(f);
	printf("\nLog fila [elementos: %i]\t- Inicio:", numElementos);
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		printf(" [%i;%i]", atual->id, atual->ehPreferencial);
		atual = atual->prox;
	}
	printf("\n                       \t-    Fim:");
	atual = f->cabeca->ant;
	while (atual != f->cabeca) {
		printf(" [%i;%i]", atual->id, atual->ehPreferencial);
		atual = atual->ant;
	}
	printf("\n\n");
}

void circulo1(PFILA f, PONT a){
  f->cabeca->prox = f->cabeca->ant = a;
}

void circulo2(PFILA f, PONT a){
  a->prox = a->ant = f->cabeca;
}

bool substituir(PFILA f){
  f->cabeca->prox = f->cabeca->prox->prox;
  f->cabeca->prox->ant = f->cabeca;
  if(f->cabeca->prox->ehPreferencial == false){
    f->inicioNaoPref = f->inicioNaoPref->prox;
 }

}

bool desistir(PFILA f, PONT a){
  a->ant->prox = a->prox;
  a->prox->ant = a->ant;
  free(a);
	return true;
}

bool consultarPreferencial(PFILA f, int id){
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		if (atual->id == id) return atual->ehPreferencial;
		atual = atual->prox;
	}
	return -1;
}

bool inserirPessoaNaFila(PFILA f, int id, bool ehPreferencial){

//teste de entrada
  if((id < 0) ||(buscarID(f, id) != NULL)) return false;

  PONT insert = (PONT) malloc(sizeof(ELEMENTO));
  insert->id = id;
  insert->ehPreferencial = ehPreferencial;

  //inserir o primeiro elemento

  if (tamanho(f) == 0)
    {
    if(ehPreferencial==1) 
    {
  	circulo1(f, insert);
  	circulo2(f, insert);
  	return true;
  	}
  	else{
  	f->inicioNaoPref = insert;
  	circulo1(f,insert);
  	circulo2(f,insert);
  	return true;
  	}
  }
  //inserir os proximos elementos
  else if (tamanho(f)>0){ 
  	if(ehPreferencial==1)
  {
  	if(f->inicioNaoPref->id == -1) //a fila nao tem nao-preferencial
  	{
  	circulo2(f,insert);
  	f->cabeca->ant = insert;
  	return true;
  	}
  	else { //inserindo um preferencial qualqer
  	insert->prox = f->inicioNaoPref;
  	insert->ant = f->inicioNaoPref->ant;
  	f->inicioNaoPref->ant->prox = f->inicioNaoPref->ant = insert;
  	return true;
  }
}
  	else if(ehPreferencial == 0){

  	if(f->inicioNaoPref->id == -1)//primeiro nÃ£o preferencial numa fila com preferenciais
  	{
  	    	f->inicioNaoPref = insert;
			f->cabeca->prox->prox = insert;
			f->cabeca->ant = insert;
			insert->ant = f->cabeca->prox;
			insert->prox = f->cabeca;
			return true;
  	}
  	else //enÃ©simo nÃ£o preferencial
  	{
  		insert->prox = f->cabeca;
    	insert->ant = f->cabeca->ant;
    	f->cabeca->ant->prox = insert;
    	f->cabeca->ant = insert;
    	return true;
	}
  								}
					  }			
  
return false;
}

bool atenderPrimeiraDaFila(PFILA f, int* id){

  if((tamanho(f) == 0) || id == -1) return false;

  *id = f->cabeca->prox->id;

  substituir(f);

  PONT deletar = (PONT)malloc(sizeof(ELEMENTO));
  deletar = buscarID(f, id);

  free(deletar);

  return true;
}

bool desistirDaFila(PFILA f, int id){

  if((buscarID(f, id) == false || id == -1)) return false;

  PONT deletar = (PONT)malloc(sizeof(ELEMENTO));
  deletar = buscarID(f, id);

  if(deletar->ehPreferencial)
  {
    desistir(f,deletar);
  }else{
    f->inicioNaoPref = deletar->prox;
    desistir(f,deletar);
    }

}
