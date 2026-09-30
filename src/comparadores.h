#ifndef COMPARADORES_H
#define COMPARADORES_H

#include "produto.h"

/* Os 8 comparadores do ranking: 4 criterios x (crescente/decrescente).
   Todos desempatam por id (crescente) e sao compativeis com o tipo
   Comparador (quicksort.h) e com a qsort da libc. */

int cmp_preco_asc(const Produto *a, const Produto *b);
int cmp_preco_desc(const Produto *a, const Produto *b);

int cmp_avaliacao_asc(const Produto *a, const Produto *b);
int cmp_avaliacao_desc(const Produto *a, const Produto *b);

int cmp_vendas_asc(const Produto *a, const Produto *b);
int cmp_vendas_desc(const Produto *a, const Produto *b);

int cmp_nome_asc(const Produto *a, const Produto *b);
int cmp_nome_desc(const Produto *a, const Produto *b);

#endif /* COMPARADORES_H */
