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
    if (!validar_formato((codigo))) return validar_formato(codigo);
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
    } else if (dv != (codigo[12] - '0')) {
        return -1;
    } else {
        return dv;
    }
}

int cadastrar(Produto **lista, int *n, const char *codigo, const char *nome) {
    if ((*n) < 0) return 0;
    if (validar_formato(codigo) == 0) return validar_formato(codigo);
    if (calcular_dv(codigo) != (codigo[12] - '0')) return calcular_dv(codigo);
    if (buscar_por_codigo(*lista, *n, codigo) != -2) return -2;

    Produto *tmp = realloc(*lista, (*n + 1) * sizeof(*tmp));
    if (tmp == NULL) return 0;

    (*lista) = tmp;

    strcpy((*lista)[(*n)].codigo, codigo);
    strcpy((*lista)[(*n)].nome, nome);
    
    (*n)++;
    return 1;
}

int buscar_por_codigo(const Produto *lista, int n, const char *codigo) {
    if ((n) < 0) return 0;
    int i;
    for (i = 0; i < n; i++) {
        if ((strcmp((lista)[i].codigo, codigo)) == 0) {
            return i;
        }
    }
    return -2;
}

void menu (const int cadastro_resultado, const char *codigo, const char *nome) {
    switch (cadastro_resultado)
    {
    case -2:
        printf("REJEITADO: %s (JA CADASTRADO)\n", codigo);
        break;
    case -1:
        printf("REJEITADO: %s (DV INVALIDO, ESPERADO %c)\n", codigo, codigo[12]);
        break;
    case 0:
        printf("REJEITADO: %s (FORMATO INVALIDO)\n", codigo);
        break;
    case 1:
        printf("CADASTRADO: %s %s\n", codigo, nome);
        break;
    default:
        break;
    }

}

void liberar(Produto **lista, int *n) {
    free(*lista);
    *lista = NULL;
    *n = 0;
}

int main() {
    Produto *lista = NULL;
    int tamanho = 0;

    printf("=== VALIDADOR EAN-13 ===\n");
    char codigo_parametro[14] = "7891000100103";
    char nome_parametro[31] = "ARROZ 5KG";
    int cadastro_resultado = cadastrar(&lista, &tamanho, codigo_parametro, nome_parametro);
    menu(cadastro_resultado, codigo_parametro, nome_parametro);

    strcpy(codigo_parametro, "7891000200209");
    strcpy(nome_parametro, "FEIJAO 1KG");
    cadastro_resultado = cadastrar(&lista, &tamanho, codigo_parametro, nome_parametro);
    menu(cadastro_resultado, codigo_parametro, nome_parametro);

    strcpy(codigo_parametro, "7898765432109");
    strcpy(nome_parametro, "CAFE 500G");
    cadastro_resultado = cadastrar(&lista, &tamanho, codigo_parametro, nome_parametro);
    menu(cadastro_resultado, codigo_parametro, nome_parametro);

    strcpy(codigo_parametro, "789100030030");
    strcpy(nome_parametro, "OLEO 900ML");
    cadastro_resultado = cadastrar(&lista, &tamanho, codigo_parametro, nome_parametro);
    menu(cadastro_resultado, codigo_parametro, nome_parametro);

    strcpy(codigo_parametro, "78910001A0103");
    strcpy(nome_parametro, "ACUCAR 1KG");
    cadastro_resultado = cadastrar(&lista, &tamanho, codigo_parametro, nome_parametro);
    menu(cadastro_resultado, codigo_parametro, nome_parametro);

    strcpy(codigo_parametro, "7891000100103");
    strcpy(nome_parametro, "ARROZ REPETIDO");
    cadastro_resultado = cadastrar(&lista, &tamanho, codigo_parametro, nome_parametro);
    menu(cadastro_resultado, codigo_parametro, nome_parametro);

    printf("PRODUTOS CADASTRADOS: %d\n", tamanho);
    
    int busca = buscar_por_codigo(lista, tamanho, "7891000200209");
    if (busca != -2) {
        printf("BUSCA %s: INDICE %d %s\n", lista[busca].codigo, busca, lista[busca].nome);
    } else {
        printf("BUSCA %s: NAO ENCONTRADO\n", codigo_parametro);
    }
    
    liberar(&lista, &tamanho);
    printf("LISTA LIBERADA: %d PRODUTOS\n", tamanho);
    printf("=== FIM ===\n");
    return 0;
}