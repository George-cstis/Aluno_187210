// George Toshiaki Shinohara - 187210
// EP2 - Código Fila (FIFO)

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct no {
    int numero;
    struct no *proximo;
} NoListaLigada;

typedef struct {
    NoListaLigada *inicio;
    NoListaLigada *fim;
} Fila;

// CRIA A FILA (Inicializa ponteiros)
void criaFila(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

// ENFILEIRAR (Insere elemento no final da fila)
void enfileirar(Fila *f, int valor) {
    NoListaLigada *novoNo = malloc(sizeof(NoListaLigada));
    if (!novoNo) {
        printf("\n ERRO DE ALOCAÇÃO DE MEMÓRIA !! \n");
        exit(-1);
    }
    novoNo->numero = valor;
    novoNo->proximo = NULL;

    if (f->fim == NULL) { // fila vazia
        f->inicio = f->fim = novoNo;
    } else {
        f->fim->proximo = novoNo;
        f->fim = novoNo;
    }
}

// DESENFILEIRAR (Remove elemento do início da fila)
int desenfileirar(Fila *f, int *valor) {
    NoListaLigada *ptr = f->inicio;
    // Verifica se a fila está vazia
    if (!ptr) { 
        return 0;
    }

    *valor = ptr->numero;
    f-> inicio = ptr->proximo;
    // A fila ficou vazia
    if (f->inicio == NULL) 
        f->fim = NULL;
    free(ptr);
    return 1;
}

// PEEK (Mostra o primeiro elemento da fila sem remover)
int frente(Fila *f, int *valor) {
    if (f->inicio == NULL) {
        return 0;  // A fila está vazia
    }
    *valor = f->inicio->numero;  // Copia o primeiro elemento da fila
        return 1; 
}

// FILA VAZIA (Verifica se fila está vazia)
int filaVazia(Fila *f) {
    return (f->inicio == NULL);
}

// Limpa buffer do teclado
void clear_stdin_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Libera memória
void limparFila(Fila *f) {
    int valor;
    while (desenfileirar (f, &valor));
}

// Programa principal
int main() {
    Fila fila;
    criaFila(&fila);

    int valor;
    char op = ' ';

    while (op != 'X') {
        printf("\nQual operação Enfileira (E), Desenfileira (D), Peek (P), FilaVazia (V) ou Sai (X): ");
        op = toupper(getchar());
        clear_stdin_buffer();  // limpar '\n' do buffer

        switch (op) {
            case 'E': // Enfileirar
                printf("Entre com valor: ");
                scanf("%d", &valor);
                clear_stdin_buffer();
                enfileirar(&fila, valor);
                break;

            case 'D': // Desenfileirar
                if (desenfileirar(&fila, &valor))
                    printf("Valor removido: %d \n", valor);
                else
                    printf("A fila está vazia \n");
                break;

            case 'P': // Peek
                if (frente(&fila, &valor))
                    printf("Valor na frente da fila: %d \n", valor);
                else
                    printf("A fila está vazia. \n");
                break;

            case 'V': // Fila Vazia
                if (filaVazia(&fila))
                    printf("A fila está vazia. \n");
                else
                    printf("A fila têm elementos. \n");
                break;

            case 'X':
                limparFila(&fila);
                printf("Encerrando programa \n");
                return 0;

            default:
                printf("Opção inválida: %c\n", op);
                break;
        }
    }
}
