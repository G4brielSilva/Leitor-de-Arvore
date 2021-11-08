#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "BiblioArvABB.c"

int main()
{
        arvore *arv=NULL;
        int num;
        int opc = 0;
        char localarv[30];
        FILE *arq;
        fila *f;

        // Menu
        while (opc != 8){
                printf("Escolha uma das opcoes a seguir: \n");
                printf("[1]- Ler uma Arvore de um arquivo\n");
                printf("[2]- Imprimir a Arvore\n");
                printf("[3]- Verificar se um elemento existe na Arvore\n");
                printf("[4]- Informar um nivel de um determinado no\n");
                printf("[5]- Imprimir os nos folhas  menores que um numero\n");
                printf("[6]- Inserir um no na arvore\n");
                printf("[7]- Remover um no na arvore\n");
                printf("[8]- Sair\n");

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

                case 4: printf("Digite o numero para buscar o nivel: ");
                        scanf("%d",&num);
                        printf("O numero %d encontrase no nivel %d", num, BuscaNivel(arv,num,0));
                        break;

                case 5: printf("Digite o numero que deseja procurar na arvore: ");
                        scanf("%d",&num);
                        printf("Os nos folhas da arvore menores que %d sao: \n",num);
                        ImprimirFolhas(arv, num);
                        break;

                case 6: printf("Digite o numero que deseja adicionar na arvore: ");
                        scanf("%d",&num);
                        arv = InsereNo(arv,num);
                        break;

                case 7: printf("Digite o numero que deseja retirar da arvore: ");
                        scanf("%d",&num);
                        arv = RemoveNo(arv,num);
                        break;
                }
                printf("\n");
                
                system("pause");

                if(opc!=8){
                        opc=0;
                        system("cls");
                }
                
                
        }
        DestroiArvore(arv);
        return 0;
}