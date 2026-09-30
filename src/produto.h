#ifndef PRODUTO_H
#define PRODUTO_H

/* Registro de um produto do catalogo. Interface combinada no Dia 1
   (arquivo da Pessoa A; struct definida junto com a Pessoa B). */
typedef struct {
    int   id;
    char  nome[100];
    float preco;
    float avaliacao;
    int   vendas;
} Produto;

#endif /* PRODUTO_H */
