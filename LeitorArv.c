#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Biblioarv.c"



int main()
{
        arvore *arv=NULL;
        int num;
        int opc = 0;
        char localarv[30];
        FILE *arq;
        fila *f;

        // Menu
        while (opc != 9){
                printf("Escolha uma das opcoes a seguir: \n");
                printf("[1]- Ler uma Arvore de um arquivo\n");
                printf("[2]- Imprimir a Arvore\n");
                printf("[3]- Verificar se um elemento existe na Arvore\n");
                printf("[4]- Contar o numero de elementos na arvore\n");
                printf("[5]- Imprimir os nos folhas da arvore\n");
                printf("[6]- Verificar se a arvore esta balanceada\n");
                printf("[7]- Verificar se a arvore e cheia\n");
                printf("[8]- Informar um nivel de um determinado no\n");
                printf("[9]- Sair\n");

                scanf("%d", &opc);

                switch (opc){
                case 1: printf("Digite o nome do arquivo txt que contem a arvore: ");
                        fflush(stdin);

                        fgets(localarv,30,stdin);
                        fflush(stdin);          
                        if(localarv[strlen(localarv)-1]=='\n') localarv[strlen(localarv)-1]='\0';

                        arq=fopen(localarv,"rt");
                        arv=LerArvore(arq);
                        fclose(arq);
                        printf("\nArvore Lida com sucesso!\n");
                        fflush(stdin);
                        break;
                case 2:
                        while (opc < 5 && opc > 1)
                        { // Submenu
                                system("cls");
                                if(arv==NULL){
                                        printf("Nenhuma arvore foi lida, por favor leia uma arvore antes de tentar imprimir!\n");
                                }else{
                                        printf("Como deseja imprimir a arvore: \n");
                                        printf("[1]- Pre-Ordem\n");
                                        printf("[2]- Em-Ordem\n");
                                        printf("[3]- Pos-Ordem\n");
                                        printf("[4]- Em Largura\n");
                                        printf("[5]- Sair\n");
                                        scanf("%d", &opc);
                                        switch (opc)
                                        {
                                                case 1: ImprimirPreOrd(arv);
                                                        printf("\n");
                                                        break;
                                                case 2: ImprimirEmOrd(arv);
                                                        printf("\n");
                                                        break;
                                                case 3:ImprimirPosOrd(arv);
                                                        printf("\n");
                                                        break;
                                                case 4: f=CriaFila();
                                                        ImprimirEmLarg(arv,f);
                                                        break;
                                        }
                                        opc=0;
                                }
                        }
                        break;
                        
                case 3: printf("Digite o numero que deseja procurar na arvore: ");
                        scanf("%d",&num);
                        num=Existe(arv, num);
                        if(num!=0) printf("\nO numero esta contido na arvore!\n");
                        else printf("O numero nao esta contido na arvore!\n");
                        break;

                case 4: printf("A arvore tem %d elementos",ContaArvore(arv));
                        break;

                case 5: printf("Os nos folhas da arvore sao: \n");
                        ImprimirFolhas(arv);
                        break;

                case 6: if(balanceada(arv)==1) printf("A arvore esta balanceada!");
                        else printf("A arvore nao esta balanceada!");
                        break;

                case 7: //A verificação de arvore cheia é baseada na definição de arvore cheia pegando a altura da arvore e quantidade de nós
                        if(ContaArvore(arv)==(pow(2,altura(arv))-1)) printf("A arvore esta cheia");
                        else printf("A arvore nao esta cheia");
                        break;

                case 8: printf("Digite o valor do no a ser buscado: ");
                        scanf("%d",&num);
                        if(BuscaNivel(arv,num,0)==-1) printf("\nO numero %d nao esta contido na arvore",num);
                        else printf("\nO no %d esta no nivel %d",num,BuscaNivel(arv,num,0));
                        break;
                }
                printf("\n");
                
                system("pause");

                if(opc!=9){
                        opc=0;
                        system("cls");
                }
                
                
        }
        DestroiArvore(arv);
        return 0;
}