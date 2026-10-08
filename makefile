# Makefile do projeto Ranking de Produtos
# Funciona no Linux/WSL (make) e no Windows com MinGW (mingw32-make).
#
#   make          compila o programa principal (ranking)
#   make gerador  compila o gerador de catalogos (gerador)
#   make test     compila e roda todos os testes de tests/
#   make clean    apaga os executaveis gerados

CC     = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2

# No Windows os executaveis terminam em .exe e o comando de apagar e "del".
ifeq ($(OS),Windows_NT)
    EXE = .exe
    RM  = del /Q /F
else
    EXE =
    RM  = rm -f
endif

SRCS     = $(wildcard src/*.c)
HDRS     = $(wildcard src/*.h)
LIB_SRCS = $(filter-out src/main.c,$(SRCS))

TESTS     = $(wildcard tests/test_*.c)
TEST_BINS = $(patsubst tests/%.c,%$(EXE),$(TESTS))
TEST_RUNS = $(patsubst tests/test_%.c,rodar_%,$(TESTS))

BIN = ranking$(EXE)

.PHONY: all gerador test clean

all: $(BIN)

# Compila todos os .c de src/ de uma vez (o projeto e pequeno).
$(BIN): $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -o $@ $(SRCS)

GERADOR = gerador$(EXE)

$(GERADOR): tools/gerador.c
	$(CC) $(CFLAGS) -o $@ $<

# No Windows, "make gerador" precisa apontar para gerador.exe.
ifneq ($(EXE),)
gerador: $(GERADOR)
endif

# Cada teste tem seu proprio main e e ligado com o codigo de src/ (sem o main.c).
test_%$(EXE): tests/test_%.c $(LIB_SRCS) $(HDRS)
	$(CC) $(CFLAGS) -Isrc -o $@ $< $(LIB_SRCS)

rodar_%: test_%$(EXE)
	./$<

test: $(TEST_RUNS)

# Mantem os executaveis de teste depois de rodar (senao o make tentaria apaga-los).
.SECONDARY: $(TEST_BINS)

clean:
	-$(RM) $(BIN) $(GERADOR) $(TEST_BINS)