// George Toshiaki Shinohara - 187210
// EP2 - Código Fila (FIFO)

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/////////////////////////////////////////////////////////////

typedef struct no {
    int numero;
    struct no *proximo;
} NoListaLigada;

typedef struct {
    NoListaLigada *inicio;
    NoListaLigada *fim;
} Fila;

/////////////////////////////////////////////////////////////
// Cria a fila (inicializa ponteiros)
void criaFila(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

/////////////////////////////////////////////////////////////
// ENFILEIRAR = insere no final da fila
void enfileirar(Fila *f, int valor) {
    NoListaLigada *novoNo = malloc(sizeof(NoListaLigada));
    if (!novoNo) {
        printf("\nERRO de alocação de memória\n");
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

/////////////////////////////////////////////////////////////
// DESINFILEIRAR = remove do início da fila
int desinfileirar(Fila *f, int *valor) {
    NoListaLigada *ptr = f->inicio;
    if (!ptr) { // Fila vazia
        return 0;
    }

    *valor = ptr->numero;
    f->inicio = ptr->proximo;
    if (f->inicio == NULL) // fila ficou vazia
        f->fim = NULL;
    free(ptr);
    return 1;
}

/////////////////////////////////////////////////////////////
// FRENTE (PEEK) = mostra o primeiro elemento sem remover
int frente(Fila *f, int *valor) {
    if (f->inicio == NULL) {
        return 0;
    }
    *valor = f->inicio->numero;
    return 1;
}

/////////////////////////////////////////////////////////////
// FILA VAZIA = verifica se fila está vazia
int filaVazia(Fila *f) {
    return (f->inicio == NULL);
}

/////////////////////////////////////////////////////////////
// Função para limpar buffer do teclado
void clear_stdin_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/////////////////////////////////////////////////////////////
// Programa principal
int main() {
    Fila fila;
    criaFila(&fila);

    int valor;
    char op = ' ';

    while (1) {
        printf("\nQual operação Enfileira (E), Desenfileira (D), Frente (F), FilaVazia (V) ou Sai (X): ");
        op = toupper(getchar());
        clear_stdin_buffer();  // limpar '\n' do buffer

        switch (op) {
            case 'E': // ENFILEIRAR
                printf("Entre com valor: ");
                scanf("%d", &valor);
                clear_stdin_buffer();
                enfileirar(&fila, valor);
                break;

            case 'D': // DESINFILEIRAR
                if (desinfileirar(&fila, &valor))
                    printf("Valor removido: %d\n", valor);
                else
                    printf("Fila vazia\n");
                break;

            case 'F': // FRENTE
                if (frente(&fila, &valor))
                    printf("Valor na frente da fila: %d\n", valor);
                else
                    printf("Fila vazia\n");
                break;

            case 'V': // FILA VAZIA
                if (filaVazia(&fila))
                    printf("Fila está vazia.\n");
                else
                    printf("Fila contém elementos.\n");
                break;

            case 'X':
                printf("Encerrando programa...\n");
                return 0;

            default:
                printf("Opção inválida: %c\n", op);
                break;
        }
    }
}
