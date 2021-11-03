# Leitor-de-Arvore
Programa com intuito de ler arvores binárias escrito em C

A árvore que deve ser lida, deve ser armazenada num arquivo .txt, na mesma pasta do programa, e com a estrutura correta:

## Estrutura da Arvore: (raiz(esquerda)(direita))
Esquerda refere-se ao nó à esquerda da raiz
Direita refere-se ao nó à direita da raiz

Essa estrutura pode ser encadeada desta forma: (raiz(esquerda(esquerda2)(direita2))(direita(esquerda3)(direita3)))

Para representar NULL na arvore basta usar (-1), desta forma (30(-1)(-1)) pode-se construir, neste exemplo, uma arvore unicamente com uma raiz (30) e ambos nós nulos

*Obs:Esta arvore comporta valores inteiros apenas, podendo ser facilmente alterar, mexendo no arquivo BiblioArv.c*