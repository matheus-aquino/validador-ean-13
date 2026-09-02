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

int cadastrar(Produto **lista, int *n, const char *codigo, const char *nome) {
    if (!validar_formato(codigo)) return 0;
    if ((*n) < 0) return 0;

    
    Produto *tmp = realloc(*lista, (*n + 1) * sizeof(*tmp));
    if (tmp == NULL) return 0;

    (*lista) = tmp;

    for (int i = 0; i < (*n); i++) {
        if (strcmp((*lista)[i].codigo, codigo) == 0) return -2;
    }

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
    return -1;
}

void liberar(Produto **lista, int *n) {
    free(*lista);
    *lista = NULL;
    *n = 0;
}

int main() {
    Produto *lista = NULL;
    int tamanho = 0;
    //char codigo[14] = "7891000100103";
    /*
    if (!validar_formato(&codigo)) {
        printf("Formato de código inválido\n");
    }
    */

    //int dv = calcular_dv(&codigo);
    //printf("O DV é %d\n", dv);

    if (cadastrar(&lista, &tamanho, "7891000100103", "ARROZ 5KG") == -2) printf("Produto já existe\n");
    if (cadastrar(&lista, &tamanho, "7891000200209", "FEIJAO 1KG") == -2) printf("Produto já existe\n");
    if (cadastrar(&lista, &tamanho, "7891000200209", "FEIJAO 1KG") == -2) printf("Produto já existe\n");
    printf("Produto %s | Nome: %s \n", lista[0].codigo, lista[0].nome);
    printf("Produto %s | Nome: %s \n", lista[1].codigo, lista[1].nome);

    int index_codigo = buscar_por_codigo(lista, tamanho, "7891000100103");
    printf("O codigo 7891000100103 está no index %d\n", index_codigo);

    index_codigo = buscar_por_codigo(lista, tamanho, "78910002002091");
    printf("O codigo 78910002002091 está no index %d\n", index_codigo);

    liberar(&lista, &tamanho);
    return 0;
}