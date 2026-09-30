#include "comparadores.h"
#include <string.h>

/* Desempate padrao: id em ordem crescente, para uma ordenacao
   deterministica quando o criterio principal empata. */
static int desempate_id(const Produto *a, const Produto *b) {
    if (a->id < b->id) return -1;
    if (a->id > b->id) return 1;
    return 0;
}

int cmp_preco_asc(const Produto *a, const Produto *b) {
    if (a->preco < b->preco) return -1;
    if (a->preco > b->preco) return 1;
    return desempate_id(a, b);
}
int cmp_preco_desc(const Produto *a, const Produto *b) {
    if (a->preco > b->preco) return -1;
    if (a->preco < b->preco) return 1;
    return desempate_id(a, b);
}

int cmp_avaliacao_asc(const Produto *a, const Produto *b) {
    if (a->avaliacao < b->avaliacao) return -1;
    if (a->avaliacao > b->avaliacao) return 1;
    return desempate_id(a, b);
}
int cmp_avaliacao_desc(const Produto *a, const Produto *b) {
    if (a->avaliacao > b->avaliacao) return -1;
    if (a->avaliacao < b->avaliacao) return 1;
    return desempate_id(a, b);
}

int cmp_vendas_asc(const Produto *a, const Produto *b) {
    if (a->vendas < b->vendas) return -1;
    if (a->vendas > b->vendas) return 1;
    return desempate_id(a, b);
}
int cmp_vendas_desc(const Produto *a, const Produto *b) {
    if (a->vendas > b->vendas) return -1;
    if (a->vendas < b->vendas) return 1;
    return desempate_id(a, b);
}

int cmp_nome_asc(const Produto *a, const Produto *b) {
    int c = strcmp(a->nome, b->nome);
    return (c != 0) ? c : desempate_id(a, b);
}
int cmp_nome_desc(const Produto *a, const Produto *b) {
    int c = strcmp(a->nome, b->nome);
    return (c != 0) ? -c : desempate_id(a, b);
}
