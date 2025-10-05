// George Toshiaki Shinohara - 187210
// EP1 - Estatística Básica
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Funções
double media(double *numero, int n);
double desvio_padrao(double *numero, int n, double media);
void insertion_sort(double *numero, int n);
double mediana(double *numero, int n);
void min_max(double *numero, int n, double *min, double *max);

int main() {
    int n;
    printf("Digite quantidade de números: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("QUANTIDADE INVÁLIDA\n");
        return 1;
    }

    // Alocação dinãmica
    double *numero = malloc(n * sizeof(double));
    if (numero == NULL) {
        printf("ERRO DE ALOCAÇÃO DE MEMÓRIA\n");
        return 1;
    }

    // Introdução de números
    printf("Digite os %d números: \n", n);
    for (int i=0; i<n; i++) {
        printf("> ");
        scanf("%lf", &numero[i]);
    }

     // Cálculos
    double valor_m = media(numero, n);
    double valor_dp = desvio_padrao(numero, n, valor_m);
    double valor_mdn = mediana(numero, n);
    double valor_min, valor_max;
    min_max(numero, n, &valor_min, &valor_max);
    
    // Resultados
    printf("\nResultados:\n");
    printf("Valor mínimo: %.1lf\n", valor_min);
    printf("Valor máximo: %.1lf\n", valor_max);
    printf("Mediana: %.2lf\n", valor_mdn);
    printf("Média: %.2lf\n", valor_m);
    printf("Desvio-padrão: %.13lf\n", valor_dp);

    // Liberação de memória
    free(numero);
    return 0;
}

// Ordenar com Insertion Sort
void insertion_sort(double *numero, int n) {
    for (int i=1; i<n; i++) {
        double key = numero[i];
        int j = i-1;
        while (j >= 0 && numero[j] > key) {
            numero[j+1] = numero[j];
            j--;
        }
        numero[j+1] = key;
    }
}
    
// Mediana
double mediana(double *numero, int n) {
insertion_sort(numero, n);
if (n%2 == 0) {
    return (numero[n/2 - 1] + numero[n/2]) / 2.0;
 } else {
    return numero[n/2];
 }
}

// Média
double media(double *numero, int n) {
    double soma = 0;
    for (int i=0; i<n; i++) {
        soma += numero[i];
    }
    return soma / n;
}

// Desvio-padrão
double desvio_padrao(double *numero, int n, double media) {
    double soma_nsquared = 0;
    for (int i=0; i<n; i++) {
        soma_nsquared += (numero[i] - media) * (numero[i] - media);
    }
    return sqrt(soma_nsquared / (n - 1));
}  

// Mínimo e máximo
void min_max(double *numero, int n, double *min, double *max) {
    *min = *max = numero[0];
    for (int i = 1; i < n; i++) {
        if (numero[i] < *min) *min = numero[i];
        if (numero[i] > *max) *max = numero[i];
    }
}