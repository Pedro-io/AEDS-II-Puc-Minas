#include <stdio.h> 
#include <stdlib.h>
//Definindo extrutura do Nó
typedef struct No{
    int elemento;
    struct No *esq, *dir;
} No; 
//Cria o nó
No* newNo(int elemento){
    No* no = (No*)malloc(sizeof(No)); //aloca dinamicamente 
    no -> elemento = elemento; // Insere o elemento
    no ->esq = no -> dir= NULL; 
    return no;
}
//Deleta o nó limpando ele da memória
void delNo(No* no){
    free(no);
}
//Criando extrutura dos elementos da árvore 
typedef struct{
    No* raiz;
} ABP;
//Cria a árvore 
ABP* newABP(){
    ABP* abp = (ABP*)malloc(sizeof(ABP));//Aloca dinamicamente
    abp->raiz = NULL;//Inicialmente a raiz é nula 
    return abp;
}

void delABP(ABP* arv){
    //desalocar todos os nós
    free(arv);
}
// Método auxiliar para pesquisar
int pesquisar(ABP* arv, int x){
    return pesquisarRec(x, arv->raiz); // chama o método pricipal
}

int pesquisarRec(int x, No* i){
    int resp;
    if(i==NULL){
        resp= 0;
    }
    else if(x==i->elemento){
        resp = 1;
    }
    else if(x < i->elemento){
        resp = pesquisarRec(x, i->esq);
    }
    else if(x > i->elemento){
        resp = pesquisarRec(x, i->dir);
    }
    return resp;
}

void inserir(ABP* arv, int x){
    inserirRec(x, & arv->raiz);
}

void inserirRec(int x, No** i){
     if(*i == NULL){
        *i = newNo(x);
    }
    else if(x == &((*i))){
        printf("erro ao inserir");
    }
    else if(x < &((*i))){
        (*i)->esq = x;  
    }
    else if(x > &((*i))){
        (*i)->dir =x; 
    }
}

int main()
{
    ABP* arv = newABP();
    inserir(arv, 5);
    inserir(arv, 3);
    printf("%d\n", pesquisar(arv,3));
    delABP(arv);
}
