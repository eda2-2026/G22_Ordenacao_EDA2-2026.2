#include "quicksort.h"
#include "comparadores.h"
#include <stdio.h>
#include <string.h>

static int total = 0, falhas = 0;

static Produto novo(int id, const char *nome, float preco, float aval, int vendas) {
    Produto p;
    p.id = id;
    strncpy(p.nome, nome, sizeof p.nome - 1);
    p.nome[sizeof p.nome - 1] = '\0';
    p.preco = preco;
    p.avaliacao = aval;
    p.vendas = vendas;
    return p;
}

/* Ordena com cmp e confere que o resultado respeita o proprio cmp. */
static void checa(const char *rotulo, const Produto *base, int n, Comparador cmp) {
    total++;
    Produto v[16];
    memcpy(v, base, (size_t)n * sizeof *v);
    quicksort(v, n, cmp);
    for (int i = 1; i < n; i++) {
        if (cmp(&v[i - 1], &v[i]) > 0) {
            falhas++;
            printf("  [FALHOU] %s\n", rotulo);
            return;
        }
    }
    printf("  [ok]     %s\n", rotulo);
}

int main(void) {
    printf("== quicksort generico + 8 comparadores ==\n\n");

    Produto base[] = {
        novo(1, "Teclado", 120.0f, 4.5f, 300),
        novo(2, "Mouse",    80.0f, 4.5f, 500),
        novo(3, "Monitor", 900.0f, 4.8f, 150),
        novo(4, "Cabo",     25.0f, 4.0f, 500),
        novo(5, "Webcam",  200.0f, 4.2f,  90),
        novo(6, "Headset", 150.0f, 4.5f, 300),
    };
    int n = 6;

    checa("preco asc",      base, n, cmp_preco_asc);
    checa("preco desc",     base, n, cmp_preco_desc);
    checa("avaliacao asc",  base, n, cmp_avaliacao_asc);
    checa("avaliacao desc", base, n, cmp_avaliacao_desc);
    checa("vendas asc",     base, n, cmp_vendas_asc);
    checa("vendas desc",    base, n, cmp_vendas_desc);
    checa("nome asc",       base, n, cmp_nome_asc);
    checa("nome desc",      base, n, cmp_nome_desc);

    /* desempate por id: ids 1,2,6 tem avaliacao 4.5 -> devem sair 1,2,6 */
    total++;
    Produto v[6];
    memcpy(v, base, sizeof base);
    quicksort(v, n, cmp_avaliacao_asc);
    int ok = 1, ultimo = -1;
    for (int i = 0; i < n; i++)
        if (v[i].avaliacao == 4.5f) {
            if (v[i].id < ultimo) ok = 0;
            ultimo = v[i].id;
        }
    if (ok) printf("  [ok]     desempate por id (avaliacao 4.5)\n");
    else { falhas++; printf("  [FALHOU] desempate por id\n"); }

    printf("\n== Resumo: %d/%d passaram ==\n", total - falhas, total);
    if (falhas > 0) { printf("RESULTADO: FALHOU (%d com erro)\n", falhas); return 1; }
    printf("RESULTADO: SUCESSO\n");
    return 0;
}
