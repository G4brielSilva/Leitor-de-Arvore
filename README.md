# Leitor-de-Arvore
Programa com intuito de ler arvores binárias escrito em C
A ideia é acompanhar os algoritmos e conteúdos referentes a disciplina Estrutura de Dados.

A árvore que deve ser lida, deve ser armazenada num arquivo .txt, na mesma pasta do programa, e com a estrutura correta:

## Estrutura da Arvore: (raiz(esquerda)(direita))
Esquerda refere-se ao nó à esquerda da raiz
Direita refere-se ao nó à direita da raiz

Essa estrutura pode ser encadeada desta forma: (raiz(esquerda(esquerda2)(direita2))(direita(esquerda3)(direita3)))

Para representar NULL na arvore basta usar (-1), desta forma (30(-1)(-1)) pode-se construir, neste exemplo, uma arvore unicamente com uma raiz (30) e ambos nós nulos

*Obs:Esta arvore comporta valores inteiros apenas, podendo ser facilmente alterar, mexendo no arquivo BiblioArv.c*

## Adicionados tratamentos para Árvore AVL V 0.2
Na respectiva pasta AVL, tem arquivos, com funções similares da Árvore Binária de Busca, porém carregando algumas propriedades de AVL, como manter o balanceamento por quando adiciona, ou remove um elemento da árvore.

Esse balanceamento torna-se interessante em árvores muito grandes, permitindo assim, percorrer ela de forma mais rápida

## Adicionados tratamentos para Árvore Binária de Busca(ABB) V 0.1
Na respectiva pasta ABB, tem arquivos, similares aos de Árvore Binária "Simples", contendo funções novas, baseadas em ABB.


## Futuras Melhorias
A função referente a Impressão em Largura/ Por Nível, deveria utilizar os ponteiros da árvore, pra desta forma poder fazer a devida apresentação.

Por erros, decidi utilizar este formato que armazena apenas os valores dos nós da árvore, estou estudando pra em breve implementar a fila com ponteiros.

