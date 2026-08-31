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

int calcular_dv(const char *codigo){
    if (!validar_formato((codigo))) return 0;
    int tamanho = strlen(codigo) - 1;
    int soma = 0;
    int dv = 0;
    for (int i = 0; i < tamanho; i++) {
        int digito = codigo[i] - '0';
        if (i % 2 == 0) {
            soma += digito * 1;
        } else {
            soma += digito * 3;
        }
    }
    dv = ((10 - soma %10) % 10);
    if ((soma + dv) %10 != 0) {
        return -1;
    } else {
        return dv;
    }
}

int main() {
    Produto *lista = NULL;
    char codigo[14] = "7891000100103";
    if (!validar_formato(&codigo)) {
        printf("Formato de código inválido\n");
    }
    
    int dv = calcular_dv(&codigo);
    printf("O DV é %d\n", dv);

    return 0;
}