#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_CINTA 100

// Estructura para la máquina de Turing
struct Turing {
    char cinta[TAM_CINTA];
    int pos;
};

// Inicializa la máquina de Turing con '0's y coloca el puntero en el medio
void iniciar(struct Turing* t) {
    for (int i = 0; i < TAM_CINTA; i++) {
        t->cinta[i] = '0';
    }
    t->pos = TAM_CINTA / 2;
}

// Desplaza el puntero según la dirección: 'D' derecha, 'I' izquierda
void desplazar(struct Turing* t, char dir) {
    if (dir == 'D') {
        t->pos = (t->pos + 1) % TAM_CINTA;
    } else if (dir == 'I') {
        t->pos = (t->pos - 1 + TAM_CINTA) % TAM_CINTA;
    }
}

// Lee el valor actual en la cinta
char leer(struct Turing* t) {
    return t->cinta[t->pos];
}

// Escribe en la cinta en la posición del puntero
void escribir(struct Turing* t, char valor) {
    t->cinta[t->pos] = valor;
}

// Imprime la cinta, destacando la posición del puntero
void mostrar_cinta(struct Turing* t) {
    for (int i = 0; i < TAM_CINTA; i++) {
        if (i == t->pos) {
            printf("[%c]", t->cinta[i]);
        } else {
            printf("%c", t->cinta[i]);
        }
    }
    printf("\n");
}

// Convierte binario a decimal
int binario_a_dec(const char* binario) {
    return (int)strtol(binario, NULL, 2);
}

// Convierte un número decimal a binario
void dec_a_binario(int num, char* bin) {
    int i = 0;
    if (num == 0) {
        strcpy(bin, "0");
    } else {
        while (num > 0) {
            bin[i++] = (num % 2) + '0';
            num /= 2;
        }
        bin[i] = '\0';
        for (int j = 0; j < i / 2; j++) {
            char tmp = bin[j];
            bin[j] = bin[i - j - 1];
            bin[i - j - 1] = tmp;
        }
    }
}

// Suma dos binarios
void sumar_bin(char* a, char* b, char* resultado) {
    int n1 = binario_a_dec(a);
    int n2 = binario_a_dec(b);
    int suma = n1 + n2;
    dec_a_binario(suma, resultado);
}

// Resta dos binarios
void restar_bin(char* a, char* b, char* resultado) {
    int n1 = binario_a_dec(a);
    int n2 = binario_a_dec(b);
    int resta = n1 - n2;
    dec_a_binario(resta, resultado);
}

// Muestra el movimiento del puntero
void mostrar_desplazamiento(struct Turing* t, char dir) {
    printf("Moviendo a la %s\n", (dir == 'D') ? "derecha" : "izquierda");
    desplazar(t, dir);
    mostrar_cinta(t);
}

int main() {
    struct Turing turing;
    iniciar(&turing);

    char bin1[50], bin2[50];

    // Entrada de números binarios
    printf("Ingresa el primer número binario: ");
    scanf("%s", bin1);
    printf("Ingresa el segundo número binario: ");
    scanf("%s", bin2);

    // Coloca el primer binario en la cinta
    for (int i = 0; i < strlen(bin1); i++) {
        escribir(&turing, bin1[i]);
        mostrar_desplazamiento(&turing, 'D');
    }

    printf("Cinta tras primer número binario:\n");
    mostrar_cinta(&turing);

    // Coloca separador
    escribir(&turing, ' ');
    mostrar_desplazamiento(&turing, 'D');

    // Coloca el segundo binario
    for (int i = 0; i < strlen(bin2); i++) {
        escribir(&turing, bin2[i]);
        mostrar_desplazamiento(&turing, 'D');
    }

    printf("Cinta tras segundo número binario:\n");
    mostrar_cinta(&turing);

    // Operaciones: suma
    char suma_res[50];
    sumar_bin(bin1, bin2, suma_res);
    printf("Suma en binario: %s\n", suma_res);
    printf("Suma en decimal: %d\n", binario_a_dec(suma_res));

    // Operaciones: resta
    char resta_res[50];
    restar_bin(bin1, bin2, resta_res);
    printf("Resta en binario: %s\n", resta_res);
    printf("Resta en decimal: %d\n", binario_a_dec(resta_res));

    return 0;
}
