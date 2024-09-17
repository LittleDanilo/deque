#include <stdio.h>
#include <stdlib.h>

typedef struct deque {
    char vet[8];
    int front, rear;
} TDeque;

// define o valor inicial do front e do rear
void created(TDeque *d) {
    d->front = 0;
    d->rear = -1;
}

// define o valor do lado que foi pedido, para o valor inicial
void destroyd(TDeque *d, int lado) {
    switch(lado) {
        case 0:
            d->front = 0;
            break;
        default:
            d->rear = -1;
            break;
    }
}

// compara se o rear é menor que o front, porque se o deque está vazio, o rear deve ser igual a -1 e o front igual a 0
int isemptyd(TDeque *d) {
    return d->rear < d->front;
}

// se o rear tiver o valor 7, o deque está cheio pq ele estará no ultimo indice do vetor
int isfulld(TDeque *d) {
    return d->rear == 7;
}

// armazena um char no deque, pelo lado escolhido
void stored(TDeque *d, int lado, char elem) {
    // primeiro confere se o deque não está cheio
    if (isfulld(d)) {
        puts("Deque Cheio!");
        abort();
    }

    // compara se o lado escolhido é o começo do deque ou não
    switch (lado) {
        case 0:// se for o começo
            // joga todos os elementos pra esquerda
            for (int i = d->rear + 1; i > d->front; i--) { // o for começa no rear + 1 e vai diminuindo até ficar igual o front
                // como o rear + 1 é um espaço vazio
                // se atribui a ele o valor do anterior
                d->vet[i] = d->vet[i - 1];
            }

            // agora que o front está com um espaço livre
            // atribuimos o elem ao indice do front
            d->vet[d->front] = elem;
            // e ajustamos a diferença do rear porque após o for, ele ficou no penultimo numero e não no ultimo
            d->rear++;
            break;
        default: // se for no fim
        // apenas aumentamos o rear, atribuimos ao vetor o elem
            d->rear++;
            d->vet[d->rear] = elem;
            break;
    }
}

// remove um char do deque, pelo lado escolhido
char retrieved(TDeque *d, int lado) {
    // verifica se o deque não está vazio
    if (isemptyd(d)) {
        puts("Deque vazio!");
        abort();
    }

    // verifica qual foi o lado escolhido
    switch (lado) {
        case 0: // se foi o inicio
        { // esse bloco serve pra você poder definir a variavel elem dentro do switch mais de umas vez. Bloco igual = {}

            // armazena o elem numa variavel
            char elem = d->vet[d->front];
            // joga todos os elementos para o começo
            for (int i; i < d->rear; i++) {
                // pega o elemento do indice i, e substitui pelo proximo
                d->vet[i] = d->vet[i + 1];
            }

            // agora ele reposiciona o rear que está um elemento a mais do que o fim
            d->rear--;

            // retorna o elem
            return elem;
        } break;
        default: // se for pelo fim do deque
        {
            // armazena o char numa variavel
            char elem = d->vet[d->rear];

            // diminui o valor do rear
            d->rear--;

            // retorna o elem
            return elem;
        } break;
    }
}

// Testes
int main(void) {
    // criar o deque
    TDeque d;
    created(&d);

    // colocar items pelo inicio do deque
    stored(&d, 0, 'A');//                         front |       
    stored(&d, 0, 'B');//      O deque vai ficar assim [C,B,A, , , , , ]
    stored(&d, 0, 'C');//                                   | rear

    // remover um do front e um do rear;                    front |       
    printf("%c \n", retrieved(&d, 0));// O deque vai ficar assim [B, , , , , , , ]
    printf("%c \n", retrieved(&d, 1));//                          | rear
    
    // colocar items pelo final do deque
    stored(&d, 1, 'C');//                         front |       
    stored(&d, 1, 'D');//      O deque vai ficar assim [B,C,D,E, , , , ]
    stored(&d, 1, 'E');//                                     | rear
    
    // remover um do front e um do rear;
    printf("%c \n", retrieved(&d, 1));//                    front |       
    printf("%c \n", retrieved(&d, 1));// O deque vai ficar assim [ , , , , , , , ]
    printf("%c \n", retrieved(&d, 1));//                        | rear
    printf("%c \n", retrieved(&d, 1));
}