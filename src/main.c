#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto.h"
#include "comparadores.h"
#include "quicksort.h"
#include "csv.h"

#define QUANTIDADE_PADRAO 10

/* Associa o nome do critério digitado aos comparadores crescente e decrescente. */
typedef struct {
    const char *nome;
    Comparador  asc;
    Comparador  desc;
} Criterio;

static const Criterio CRITERIOS[] = {
    { "preco",     cmp_preco_asc,     cmp_preco_desc     },
    { "avaliacao", cmp_avaliacao_asc, cmp_avaliacao_desc },
    { "vendas",    cmp_vendas_asc,    cmp_vendas_desc    },
    { "nome",      cmp_nome_asc,      cmp_nome_desc      },
};
#define NUM_CRITERIOS (int)(sizeof CRITERIOS / sizeof CRITERIOS[0])

static void imprimir_uso(const char *programa) {
    printf("Uso: %s <arquivo.csv> <criterio> <ordem> [quantidade]\n\n", programa);
    printf("  criterio   : preco, avaliacao, vendas ou nome\n");
    printf("  ordem      : asc (crescente) ou desc (decrescente)\n");
    printf("  quantidade : produtos exibidos (padrao: %d, 0 = todos)\n\n", QUANTIDADE_PADRAO);
    printf("Exemplo: %s data/produtos.csv preco asc 5\n", programa);
}

/* Devolve o comparador para o critério e a ordem, ou NULL se forem inválidos. */
static Comparador escolher_comparador(const char *criterio, const char *ordem) {
    int crescente;
    if (strcmp(ordem, "asc") == 0) {
        crescente = 1;
    } else if (strcmp(ordem, "desc") == 0) {
        crescente = 0;
    } else {
        fprintf(stderr, "Erro: ordem '%s' invalida (use asc ou desc)\n", ordem);
        return NULL;
    }

    for (int i = 0; i < NUM_CRITERIOS; i++) {
        if (strcmp(criterio, CRITERIOS[i].nome) == 0) {
            return crescente ? CRITERIOS[i].asc : CRITERIOS[i].desc;
        }
    }

    fprintf(stderr, "Erro: criterio '%s' invalido (use preco, avaliacao, vendas ou nome)\n", criterio);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 4 || argc > 5) {
        imprimir_uso(argv[0]);
        return 1;
    }

    const char *arquivo  = argv[1];
    const char *criterio = argv[2];
    const char *ordem    = argv[3];
    int quantidade = (argc == 5) ? atoi(argv[4]) : QUANTIDADE_PADRAO;

    Comparador cmp = escolher_comparador(criterio, ordem);
    if (cmp == NULL) {
        return 1;
    }

    int n;
    Produto *produtos = ler_csv(arquivo, &n);
    if (produtos == NULL) {
        return 1;
    }
    if (n == 0) {
        printf("Nenhum produto encontrado em '%s'\n", arquivo);
        free(produtos);
        return 0;
    }

    quicksort(produtos, n, cmp);

    printf("Ordenado por %s (%s)\n\n", criterio,
           strcmp(ordem, "asc") == 0 ? "crescente" : "decrescente");
    imprimir_lista(produtos, n, quantidade);

    free(produtos);
    return 0;
}