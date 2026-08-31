#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char codigo[14]; // 13 digits + null terminator
    char nome[31];   // 30 characters + null terminator
} Produto;

int validar_formato(const char *codigo);
int calcular_dv(const char *codigo);
int cadastrar(Produto **lista, int *n, const char *codigo, const char *nome);
int buscar_por_codigo(const Produto *lista, int n, const char *codigo);
void liberar(Produto **lista, int *n);

int validar_formato(const char *codigo) {
    if (strlen(codigo) != 13) return 0;
    int i = 0;
    while (codigo[i] != '\0') {
        if (!isdigit((unsigned char)codigo[i])) {
            return 0;
        }
        i++;
    }
    return 1;
}

int main() {
    Produto *lista = NULL;
    char codigo[14] = "7891000100103";
    if (!validar_formato(&codigo)) {
        printf("Formato de código inválido\n");
    }
    
    return 0;
}