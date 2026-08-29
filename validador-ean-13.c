#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char codigo[14]; // 13 digits + null terminator
    char nome[31];   // 30 characters + null terminator
} Produto;

int validar_formato(const char *codigo);
int calcular_dv(const char *codigo);
int cadastrar(Produto **lista, int *n, const char *codigo, const char *nome);
int buscar_por_codigo(const Produto *lista, int n, const char *codigo);
void liberar(Produto **lista, int *n);

int main() {
    return 0;
}