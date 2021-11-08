#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



/*
--------------------------------------------------------------------------------
Biblioteca feita pra compilar as Funções referentes a leitura da Árvore Binária
--------------------------------------------------------------------------------
*/



// Tipo de dado arvore com valor armazenado em info, e dois ponteiros para seus respectivos nós
typedef struct arvore
{
        int info;
        struct arvore *esq;
        struct arvore *dir;
} arvore;


//Recebe o ponteiro de um arquivo obtido na main lê a armazena os dados da arvore numa arvore
arvore *LerArvore(FILE *arq){ 
    char c; 
    int num; 
 
    fscanf(arq,"%c",&c); 
    fscanf(arq,"%d",&num); 

    if(num==-1){ 
        fscanf(arq,"%c",&c); 
        return NULL; 
    } 
    else{ 
        arvore *a = (arvore*)malloc(sizeof(arvore)); 
        a->info = num; 
        a->esq = LerArvore(arq); 
        a->dir = LerArvore(arq); 
        fscanf(arq,"%c",&c); 
        return a; 
    } 
}

//Verificando se um valor (int num) existe dentro da arvore binária (arvore *arv)
int Existe(arvore *arv, int num){
        if(arv==NULL) return 0;
        if(arv->info == num) return 1;
        //if(arv->info > num) return Existe(arv->esq, num);
        //else return Existe(arv->esq,num);
        printf("\n%d\n",arv->info);
        return arv->info > num? Existe(arv->esq, num): Existe(arv->dir,num);
}

//Impressão dos dados da arvore binária em Pre Ordem
void ImprimirPreOrd(arvore *arv){
        if(arv==NULL) return;
        printf("%d ",arv->info);
        ImprimirPreOrd(arv->esq);
        ImprimirPreOrd(arv->dir);
}
//Impressão dos dados da arvore binária em Ordem
void ImprimirEmOrd(arvore *arv){
        if(arv==NULL) return;
        ImprimirEmOrd(arv->esq);
        printf("%d ",arv->info);
        ImprimirEmOrd(arv->dir);
}
//Impressão dos dados da arvore binária em Pos Ordem
void ImprimirPosOrd(arvore *arv){
        if(arv==NULL) return;
        ImprimirPosOrd(arv->esq);
        ImprimirPosOrd(arv->dir);
        printf("%d ",arv->info);
}

//Impressão dos nós folhas da arvore(nós em que tanto ->dir quanto ->esq são NULL)
void ImprimirFolhas(arvore *arv, int num){
        if(arv==NULL) return;

        if((arv->dir == NULL) && (arv->esq == NULL) && arv->info < num){
            printf("%d ",arv->info);
            return;
        }
        
        if(arv->info < num){
            ImprimirFolhas(arv->dir, num);
        }
        ImprimirFolhas(arv->esq,num);
        
        
}

//Busca em que nível da arvore(arvore *arv) se encontra um determinado valor(int num)
int BuscaNivel(arvore *arv, int num,int nivel){
        if(arv==NULL) return -1;
        if(arv->info==num) return nivel;
        
        int esq=BuscaNivel(arv->esq, num, nivel+1);
        int dir=BuscaNivel(arv->dir, num, nivel+1);

        if(esq!=-1) return esq;
        return dir;

}

arvore *CriaNo(int no){
	arvore *arv=(arvore *) malloc(sizeof(arvore));
	arv->info=no;
	arv->dir=NULL;
    arv->esq==NULL;
	
	return arv;
}

arvore *InsereNo(arvore *arv, int num){
    if(arv==NULL){
        arv=(arvore *) malloc(sizeof(arvore));
        arv->info= num;
        arv->dir=NULL;
        arv->esq=NULL;
    }else if(arv->info > num) arv->esq = InsereNo(arv->esq, num); 
    else arv->dir = InsereNo(arv->dir, num); 

    return arv;
}

arvore *RemoveNo(arvore *arv,int num){
    if(arv == NULL) return;

    if(arv->info == num){
        if(arv->dir == NULL && arv->esq == NULL){ 
            free(arv);
            return NULL;
        }else if(arv->esq == NULL){
            arvore *aux=arv->dir;
            free(arv);
            return aux;
        }else if(arv->dir==NULL){
            arvore *aux=arv->esq;   
            free(arv);
            return aux;
        }else{
            arvore *aux=arv->esq;

            while(aux->dir!=NULL){
                aux=aux->dir;
            }
            arv->info=aux->info;
            arv->esq=RemoveNo(arv->esq, aux->info);
        }
        
    }else if(arv->info > num) arv->esq = RemoveNo(arv->esq, num); 
    else arv->dir = RemoveNo(arv->dir, num);
    return arv;

}

/*
--------------------------------------
FILA E IMPRESSÃO DE ARVORE EM LARGURA  
--------------------------------------
*/

//Tipo de dado elemento que será usado pra constituir a fila
typedef struct elemento{
        int no;
        struct elemento *prox;
}elemento;

//tipo de dado fila
typedef struct fila{
	elemento *inicio, *fim;
	int qtd;
}fila;

//Criando Fila
fila *CriaFila(){
	fila *f=(fila *)malloc(sizeof(fila));

	f->qtd=0;
	f->inicio=NULL;
	f->fim=NULL;

	return f;
}

//Criando elemento a partir de um valor de nó(int no) da arvore
elemento *CriaElemento(int no){
	elemento *arv=(elemento *) malloc(sizeof(elemento));
	arv->no=no;
	arv->prox=NULL;
	
	return arv;
}

//Enfileirando o valor do nó(int no) da arvore na fila(fila *f)
void Enfileira(fila *f, int no){
    elemento *new=CriaElemento(no);

	if(f->qtd==0){
		f->inicio=new;
	}else{
		f->fim->prox=new;
	}
	f->fim=new;
	f->qtd++;
}

//Desenfileirando(retirando o primeiro elemento da fila e "passando os outros para frente")
void Desenfileira(fila *f){
	if(f->qtd==0) return;

	elemento *arv=f->inicio;

	f->inicio = f->inicio->prox;
	f->qtd--;
	free(arv);

	if(f->qtd==0) f->fim=NULL;
}

/**FUNÇÃO IMPRIMIR EM LARGURA // IMPRIMIR POR NÍVEL
* Primeiro enfileira os valores na fila      
* Imprime o Valor do inicio da fila e o Desenfileira
* Chama a função recursivamente de modo a ir pro próximo nível
*/
void ImprimirEmLarg(arvore *arv, fila *f){
        if(arv==NULL) return;
        

        if(f->qtd==0) Enfileira(f,arv->info);

        if(arv->esq!=NULL) Enfileira(f,arv->esq->info);     
        if(arv->dir!=NULL) Enfileira(f,arv->dir->info);

        printf("%d ",f->inicio->no);
        Desenfileira(f);

        ImprimirEmLarg(arv->esq,f);
        ImprimirEmLarg(arv->dir,f);
        
        return;
}

//Dando free na memória alocada dinâmicamente usada na arvore durante o processo
void DestroiArvore(arvore *arv){
        if(arv==NULL) return;
        DestroiArvore(arv->esq);
        DestroiArvore(arv->dir);
        free(arv);
}