#include <stdio.h>
#include "produto.h"

void imprimir_produto(const Produto *p) {
    printf("%6d | %-35.35s | R$ %10.2f | %4.1f | %8d\n",
           p->id, p->nome, p->preco, p->avaliacao, p->vendas);
}

void imprimir_lista(const Produto *v, int n, int quantidade) {
    if (quantidade > n || quantidade <= 0) {
        quantidade = n;
    }

    printf("%6s | %-35s | %13s | %4s | %8s\n",
           "ID", "Nome", "Preco", "Nota", "Vendas");
    printf("-------+-------------------------------------+---------------+------+---------\n");

    for (int i = 0; i < quantidade; i++) {
        imprimir_produto(&v[i]);
    }

    printf("(%d de %d produtos)\n", quantidade, n);
}
