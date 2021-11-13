#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



/*
--------------------------------------------------------------------------------
Biblioteca feita pra compilar as Funções referentes a leitura da Árvore Binária
--------------------------------------------------------------------------------
*/



// Tipo de dado avl com valor armazenado em info, e dois ponteiros para seus respectivos nós
typedef struct avl
{
        int info;
        int FB;
        struct avl *esq;
        struct avl *dir;
} avl;

//Recebe o ponteiro de um arquivo obtido na main lê a armazena os dados da avl numa avl
avl *LerArvore(FILE *arq){ 
    char c; 
    int num; 
 
    fscanf(arq,"%c",&c); 
    fscanf(arq,"%d",&num); 

    if(num==-1){ 
        fscanf(arq,"%c",&c); 
        return NULL; 
    } 
    else{ 
        avl *a = (avl*)malloc(sizeof(avl)); 
        a->info = num; 
        a->esq = LerArvore(arq); 
        a->dir = LerArvore(arq); 
        fscanf(arq,"%c",&c); 
        return a; 
    } 
}

//Verificando se um valor (int num) existe dentro da avl binária (avl *arv)
int Existe(avl *arv, int num){
        if(arv==NULL) return 0;
        if(arv->info == num) return 1;
        //if(arv->info > num) return Existe(arv->esq, num);
        //else return Existe(arv->esq,num);
        printf("\n%d\n",arv->info);
        return arv->info > num? Existe(arv->esq, num): Existe(arv->dir,num);
}

//Impressão dos dados da avl binária em Pre Ordem
void ImprimirPreOrd(avl *arv){
        if(arv==NULL) return;
        printf("%d ",arv->info);
        ImprimirPreOrd(arv->esq);
        ImprimirPreOrd(arv->dir);
}
//Impressão dos dados da avl binária em Ordem
void ImprimirEmOrd(avl *arv){
        if(arv==NULL) return;
        ImprimirEmOrd(arv->esq);
        printf("%d ",arv->info);
        ImprimirEmOrd(arv->dir);
}
//Impressão dos dados da avl binária em Pos Ordem
void ImprimirPosOrd(avl *arv){
        if(arv==NULL) return;
        ImprimirPosOrd(arv->esq);
        ImprimirPosOrd(arv->dir);
        printf("%d ",arv->info);
}

//Impressão dos nós folhas da avl(nós em que tanto ->dir quanto ->esq são NULL)
void ImprimirFolhas(avl *arv, int num){
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

//Busca em que nível da avl(avl *arv) se encontra um determinado valor(int num)
int BuscaNivel(avl *arv, int num,int nivel){
        if(arv==NULL) return -1;
        if(arv->info==num) return nivel;
        
        int esq=BuscaNivel(arv->esq, num, nivel+1);
        int dir=BuscaNivel(arv->dir, num, nivel+1);

        if(esq!=-1) return esq;
        return dir;

}

avl *CriaNo(int no){
	avl *arv=(avl *) malloc(sizeof(avl));
	arv->info=no;
	arv->dir=NULL;
    arv->esq=NULL;
	
	return arv;
}

int Altura(avl *arv){
        if(arv==NULL) return 0;

        int he=Altura(arv->esq);
        int hd=Altura(arv->dir);
        if(he>hd) return he+1;
        else return hd+1;
}


/*
--------------------------------------
   FUNÇÕES ESPECÍFICAS À ARVORE AVL    
--------------------------------------
*/

void AjustaFB(avl *arv){
    if(arv!=NULL){
        int he=Altura(arv->esq);
        int hd=Altura(arv->dir);
        arv->FB = hd- he;

        AjustaFB(arv->esq);
        AjustaFB(arv->dir);
    }
}

avl *LerAVL(FILE *arq){
    avl *arv=LerArvore(arq);
    AjustaFB(arv);
    return arv;
}

avl *RotacaoEsqSimples(avl *no){
    avl *a=no;
    avl *b=a->dir;

    a->dir=b->esq;
    b->esq=a;

    if(b->FB == 1){
        a->FB=0;
        b->FB=0;
    }else{
        a->FB=1;
        b->FB=-1;
    }
    no=b;
    return no;
}

avl *RotacaoEsqDupla(avl *no){
    avl *a=no;
    avl *c=a->dir;
    avl *b=c->esq;

    c->esq=b->dir;
    a->dir=b->esq;
    b->esq=a;
    b->dir=c;

    switch(b->FB){
        case -1: a->FB=0;
                 c->FB=1;
                 break;

        case 0: a->FB=0;
                c->FB=0;
                break;

        case +1: a->FB=-1;
                 c->FB=0;
                 break;
    }
    b->FB=0;
    no=b;
    return no;
}

avl *RotacaoEsq(avl *no){
    if(no->dir->FB == -1) no=RotacaoEsqDupla(no);
    else no=RotacaoEsqSimples(no);

    return no;
}

avl *RotacaoDirSimples(avl *no){
    avl *a=no->esq;
    avl *b=no;

    b->esq=a->dir;
    a->dir=b;

    if(a->FB == -1){
        a->FB=0;
        b->FB=0;
    }else{
        a->FB=1;
        b->FB=-1;
    }
    no=a;
    return no;
}

avl *RotacaoDirDupla(avl *no){
    avl *c=no;
    avl *a=c->esq;
    avl *b=a->dir;

    c->esq=b->dir;
    a->dir=b->esq;
    b->esq=a;
    b->dir=c;

    switch(b->FB){
        case -1: a->FB=0;
                 c->FB=1;
                 break;

        case 0: a->FB=0;
                c->FB=0;
                break;

        case +1: a->FB=-1;
                 c->FB=0;
                 break;
    }
    b->FB=0;
    no=b;
    return no;
}

avl *RotacaoDir(avl *no){
    if(no->esq->FB == 1) no=RotacaoDirDupla(no);
    else no=RotacaoDirSimples(no);

    return no;
}

avl *InsereNo(avl *arv, int num, int *hMudou){
    if(arv==NULL){
        arv=(avl *) malloc(sizeof(avl));
        arv->info= num;
        arv->dir=NULL;
        arv->esq=NULL;
        arv->FB=0;
        *hMudou=1;
    }else{
        if(arv->info >= num){
            arv->esq = InsereNo(arv->esq, num, hMudou); 

            if(*hMudou == 1){
                switch(arv->FB){
                    case -1:
                            arv=RotacaoDir(arv);
                            *hMudou=0;
                            break;
                    case 0:
                            arv->FB = -1;
                            *hMudou = 1;
                            break;
                    case +1:
                            arv->FB=0;
                            *hMudou =0;
                            break;
                }
            }
        }
        else{
            arv->dir = InsereNo(arv->dir, num, hMudou);

            if(*hMudou == 1){
                switch(arv->FB){
                    case -1:
                            arv->FB=0;
                            *hMudou=0;
                            break;
                    case 0:
                            arv->FB = +1;
                            *hMudou = 1;
                            break;
                    case +1:
                            arv=RotacaoEsq(arv);
                            *hMudou =0;
                            break;
                }
            }
        }
    }

    return arv;
}

avl *RemoveNo(avl *arv,int num, int *hMudou){
    if(arv == NULL) return NULL;

    if(arv->info == num){
        //Verifica se é folha
        if(arv->dir == NULL && arv->esq == NULL){ 
            free(arv);
            *hMudou=1;
            return NULL;
        }//Verifica se tem apenas o filho esquerdo é NULL
        else if(arv->esq == NULL){
            avl *aux=arv->dir;
            free(arv);
            *hMudou=1;
            return aux;
        }//Verifica se tem apenas o filho direito é NULL
        else if(arv->dir==NULL){
            avl *aux=arv->esq;   
            free(arv);
            *hMudou=1;
            return aux;
        }//Sem filhos NULL
        else{
            avl *maiorEsq=arv->esq;

            while(maiorEsq->dir!=NULL)
                maiorEsq=maiorEsq->dir;
            
            arv->info=maiorEsq->info;
            arv->esq=RemoveNo(arv->esq, maiorEsq->info, hMudou);

            if(*hMudou == 1){
                int aux;
                switch(arv->FB){
                    case -1:
                            arv->FB =0;
                            *hMudou=1;
                            break;
                    case 0:
                            arv->FB=1;
                            *hMudou=0;
                            break;
                    case +1:
                            aux=arv->dir->FB;
                            arv=RotacaoEsq(arv);
                            
                            if(aux == 0)*hMudou=0;
                            else *hMudou =1;
                            break;
                            
                }
            }
        }
        
    }else if(arv->info > num){
        arv->esq = RemoveNo(arv->esq, num, hMudou); 

        if(*hMudou == 1){
            int aux;
            switch(arv->FB){
                case -1:
                        arv->FB =0;
                        *hMudou=1;
                        break;
                case 0:
                        arv->FB=1;
                        *hMudou=0;
                        break;
                case +1:
                        aux=arv->dir->FB;
                        arv=RotacaoEsq(arv);
                        
                        if(aux == 0)*hMudou=0;
                        else *hMudou =1;
                        break;
                        
            }
        }
    }
    else{
        arv->dir = RemoveNo(arv->dir, num, hMudou);

        if(*hMudou == 1){
            int aux;
            switch(arv->FB){
                case -1:
                        arv->FB =0;
                        *hMudou=1;
                        break;
                case 0:
                        arv->FB=-1;
                        *hMudou=0;
                        break;
                case +1:
                        aux=arv->esq->FB;
                        arv=RotacaoDir(arv);
                        
                        if(aux == 0)*hMudou=0;
                        else *hMudou =1;
                        break;
                        
            }
        }
    }
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

//Criando elemento a partir de um valor de nó(int no) da avl
elemento *CriaElemento(int no){
	elemento *arv=(elemento *) malloc(sizeof(elemento));
	arv->no=no;
	arv->prox=NULL;
	
	return arv;
}

//Enfileirando o valor do nó(int no) da avl na fila(fila *f)
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
void ImprimirEmLarg(avl *arv, fila *f){
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
void DestroiArvore(avl *arv){
        if(arv==NULL) return;
        DestroiArvore(arv->esq);
        DestroiArvore(arv->dir);
        free(arv);
}