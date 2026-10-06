/*
 * Gerador de catálogos aleatórios para testes e benchmark.
 *
 * Uso: ./gerador <quantidade> <arquivo_saida> [semente]
 *
 * Sem semente, usa o horário atual (cada execução gera dados diferentes).
 * Com semente, gera sempre o mesmo catálogo, útil para repetir o benchmark.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const char *TIPOS[] = {
    "Fone", "Mouse", "Teclado", "Monitor", "Notebook", "SSD", "Pendrive",
    "Webcam", "Headset", "Smartphone", "Carregador", "Cabo USB", "Smartwatch",
    "Caixa de Som", "Roteador", "HD Externo", "Tablet", "Microfone"
};
static const char *MARCAS[] = {
    "Samsung", "Logitech", "JBL", "Xiaomi", "Lenovo", "Kingston", "Multilaser",
    "Philips", "Sony", "Positivo", "Redragon", "TP-Link", "Dell", "Acer"
};

#define NUM_TIPOS  (int)(sizeof TIPOS / sizeof TIPOS[0])
#define NUM_MARCAS (int)(sizeof MARCAS / sizeof MARCAS[0])

/*
 * Número inteiro aleatório no intervalo [min, max].
 * Combina duas chamadas de rand() porque no Windows RAND_MAX vale só 32767,
 * o que limitaria os preços a cerca de R$ 330.
 */
static int aleatorio(int min, int max) {
    unsigned long r = (unsigned long)rand() * ((unsigned long)RAND_MAX + 1) + (unsigned long)rand();
    return min + (int)(r % (unsigned long)(max - min + 1));
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Uso: %s <quantidade> <arquivo_saida> [semente]\n", argv[0]);
        return 1;
    }

    long quantidade = strtol(argv[1], NULL, 10);
    if (quantidade <= 0) {
        fprintf(stderr, "Erro: quantidade deve ser um inteiro positivo\n");
        return 1;
    }

    unsigned semente = (argc >= 4) ? (unsigned)strtoul(argv[3], NULL, 10)
                                   : (unsigned)time(NULL);
    srand(semente);

    FILE *arq = fopen(argv[2], "w");
    if (arq == NULL) {
        fprintf(stderr, "Erro: nao foi possivel criar '%s'\n", argv[2]);
        return 1;
    }

    fprintf(arq, "id,nome,preco,avaliacao,vendas\n");
    for (long i = 1; i <= quantidade; i++) {
        const char *tipo  = TIPOS[rand() % NUM_TIPOS];
        const char *marca = MARCAS[rand() % NUM_MARCAS];
        int modelo        = aleatorio(100, 9999);

        /* Preço entre R$ 10,00 e R$ 5.000,00, gerado em centavos. */
        double preco     = aleatorio(1000, 500000) / 100.0;
        double avaliacao = aleatorio(10, 50) / 10.0;   /* 1.0 a 5.0 */
        int vendas       = aleatorio(0, 10000);

        fprintf(arq, "%ld,%s %s %d,%.2f,%.1f,%d\n",
                i, tipo, marca, modelo, preco, avaliacao, vendas);
    }

    fclose(arq);
    printf("%ld produtos gravados em '%s' (semente %u)\n", quantidade, argv[2], semente);
    return 0;
}