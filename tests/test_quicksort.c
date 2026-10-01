/* tests/test_quicksort.c
 *
 * Testes formais de casos de borda do Quick Sort generico (Dia 4).
 *
 * Alem de verificar que o resultado fica ordenado segundo o comparador,
 * cobre explicitamente as entradas adversarias que o pivo mediana-de-tres
 * resolve: vetor JA ORDENADO e vetor INVERTIDO. Com o pivo fixo no ultimo
 * elemento esses casos degradariam para O(n^2) e, no vetor grande, a
 * recursao chegaria a ~N niveis de profundidade (risco de estouro de
 * pilha); com a mediana-de-tres as particoes ficam balanceadas.
 */
#include "quicksort.h"
#include "comparadores.h"
#include <stdio.h>
#include <stdlib.h>

static int total = 0, passaram = 0;

static void checa(const char *nome, int cond) {
    total++;
    if (cond) { passaram++; printf("  [ok]     %s\n", nome); }
    else      {             printf("  [FALHOU] %s\n", nome); }
}

/* Verifica que v esta em ordem nao-decrescente segundo cmp. */
static int esta_ordenado(const Produto *v, int n, Comparador cmp) {
    for (int i = 1; i < n; i++)
        if (cmp(&v[i - 1], &v[i]) > 0) return 0;
    return 1;
}

/* Soma dos ids: usada como "impressao digital" do conteudo para garantir
   que ordenar e uma permutacao (nao perde nem duplica elementos). */
static long soma_ids(const Produto *v, int n) {
    long s = 0;
    for (int i = 0; i < n; i++) s += v[i].id;
    return s;
}

static Produto prod(int id, float preco) {
    Produto p;
    p.id = id;
    p.preco = preco;
    p.avaliacao = 0.0f;
    p.vendas = 0;
    p.nome[0] = '\0';
    return p;
}

int main(void) {
    printf("== Testes de borda do Quick Sort generico (Dia 4) ==\n");

    /* 1. Ponteiro NULL nao deve quebrar (so retorna). */
    quicksort(NULL, 10, cmp_preco_asc);
    checa("ponteiro NULL nao quebra", 1);

    /* 2. Comparador NULL nao deve quebrar. */
    {
        Produto v[3] = { prod(1, 3.0f), prod(2, 1.0f), prod(3, 2.0f) };
        quicksort(v, 3, NULL);
        checa("comparador NULL nao quebra", 1);
    }

    /* 3. Vetor vazio (n = 0). */
    {
        Produto *v = NULL;
        quicksort(v, 0, cmp_preco_asc);
        checa("vetor vazio (n=0)", 1);
    }

    /* 4. Um unico elemento. */
    {
        Produto v[1] = { prod(1, 9.9f) };
        quicksort(v, 1, cmp_preco_asc);
        checa("um elemento", esta_ordenado(v, 1, cmp_preco_asc));
    }

    /* 5. Dois elementos fora de ordem. */
    {
        Produto v[2] = { prod(1, 5.0f), prod(2, 1.0f) };
        quicksort(v, 2, cmp_preco_asc);
        checa("dois elementos", esta_ordenado(v, 2, cmp_preco_asc)
                                && v[0].preco == 1.0f);
    }

    /* 6. Ja ordenado crescente (adversario do pivo fixo). */
    {
        int n = 1000;
        Produto *v = malloc(n * sizeof(Produto));
        for (int i = 0; i < n; i++) v[i] = prod(i, (float)i);
        long antes = soma_ids(v, n);
        quicksort(v, n, cmp_preco_asc);
        checa("ja ordenado crescente (1000)",
              esta_ordenado(v, n, cmp_preco_asc) && soma_ids(v, n) == antes);
        free(v);
    }

    /* 7. Ordem inversa / decrescente (adversario do pivo fixo). */
    {
        int n = 1000;
        Produto *v = malloc(n * sizeof(Produto));
        for (int i = 0; i < n; i++) v[i] = prod(i, (float)(n - i));
        long antes = soma_ids(v, n);
        quicksort(v, n, cmp_preco_asc);
        checa("ordem inversa (1000)",
              esta_ordenado(v, n, cmp_preco_asc) && soma_ids(v, n) == antes);
        free(v);
    }

    /* 8. Todos com o mesmo preco: desempate deve ordenar por id crescente. */
    {
        Produto v[5] = {
            prod(50, 7.0f), prod(10, 7.0f), prod(30, 7.0f),
            prod(20, 7.0f), prod(40, 7.0f)
        };
        quicksort(v, 5, cmp_preco_asc);
        int ids_ok = (v[0].id == 10 && v[1].id == 20 && v[2].id == 30
                      && v[3].id == 40 && v[4].id == 50);
        checa("precos iguais -> desempate por id crescente", ids_ok);
    }

    /* 9. Precos repetidos e negativos misturados. */
    {
        float precos[] = { -3.0f, 2.5f, -3.0f, 0.0f, 2.5f, -10.0f, 0.0f };
        int n = (int)(sizeof(precos) / sizeof(precos[0]));
        Produto *v = malloc(n * sizeof(Produto));
        for (int i = 0; i < n; i++) v[i] = prod(i + 1, precos[i]);
        quicksort(v, n, cmp_preco_asc);
        checa("precos repetidos e negativos",
              esta_ordenado(v, n, cmp_preco_asc));
        free(v);
    }

    /* 10. Vetor grande aleatorio: ordena e continua sendo permutacao. */
    {
        int n = 10000;
        Produto *v = malloc(n * sizeof(Produto));
        srand(42);
        for (int i = 0; i < n; i++) v[i] = prod(i, (float)(rand() % 1000));
        long antes = soma_ids(v, n);
        quicksort(v, n, cmp_preco_asc);
        checa("aleatorio grande (10000) ordenado",
              esta_ordenado(v, n, cmp_preco_asc));
        checa("aleatorio grande (10000) e permutacao",
              soma_ids(v, n) == antes);
        free(v);
    }

    printf("\n== Resumo: %d/%d passaram ==\n", passaram, total);
    if (passaram == total) {
        printf("RESULTADO: SUCESSO\n");
        return 0;
    }
    printf("RESULTADO: FALHA\n");
    return 1;
}
