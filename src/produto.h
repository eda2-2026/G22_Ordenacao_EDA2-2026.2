#ifndef PRODUTO_H
#define PRODUTO_H

#define TAM_NOME 100

typedef struct {
    int   id;
    char  nome[TAM_NOME];
    float preco;
    float avaliacao;
    int   vendas;
} Produto;

void imprimir_produto(const Produto *p);

void imprimir_lista(const Produto *v, int n, int quantidade);

#endif
