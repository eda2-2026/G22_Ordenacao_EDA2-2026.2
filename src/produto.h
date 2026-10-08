#ifndef PRODUTO_H
#define PRODUTO_H

#define TAM_NOME 100

/* Registro de um produto do catalogo. Interface combinada no Dia 1
   (arquivo da Pessoa A; struct definida junto com a Pessoa B). */
typedef struct {
    int   id;              /* identificador unico, usado no desempate */
    char  nome[TAM_NOME];  /* nome exibido na loja */
    float preco;           /* preco em reais */
    float avaliacao;       /* nota media de 0.0 a 5.0 */
    int   vendas;          /* unidades vendidas */
} Produto;

/* Imprime um produto em uma linha formatada. */
void imprimir_produto(const Produto *p);

/* Imprime os `quantidade` primeiros produtos do vetor
   (todos, se quantidade for 0 ou maior que n). */
void imprimir_lista(const Produto *v, int n, int quantidade);

#endif /* PRODUTO_H */