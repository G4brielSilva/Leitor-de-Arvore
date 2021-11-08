# Leitor-de-Arvore
Programa com intuito de ler arvores binárias escrito em C

A árvore que deve ser lida, deve ser armazenada num arquivo .txt, na mesma pasta do programa, e com a estrutura correta:

# Estrutura da Arvore: (raiz(esquerda)(direita))
Esquerda refere-se ao nó à esquerda da raiz
Direita refere-se ao nó à direita da raiz

Essa estrutura pode ser encadeada desta forma: (raiz(esquerda(esquerda2)(direita2))(direita(esquerda3)(direita3)))

Para representar NULL na arvore basta usar (-1), desta forma (30(-1)(-1)) pode-se construir, neste exemplo, uma arvore unicamente com uma raiz (30) e ambos nós nulos

*Obs:Esta arvore comporta valores inteiros apenas, podendo ser facilmente alterar, mexendo no arquivo BiblioArv.c*

# Adicionados tratamentos para Árvore Binária de Busca(ABB)
Na respectiva pasta ABB, tem arquivos, similares aos de Árvore Binária "Simples", contendo funções novas, baseadas em ABB.


## Futuras Melhorias
A função referente a Impressão em Largura/ Por Nível, deveria utilizar os ponteiros da árvore, pra desta forma poder fazer a devida apresentação.

Por erros, decidi utilizar este formato que armazena apenas os valores dos nós da árvore, estou estudando pra em breve implementar a fila com ponteiros.

