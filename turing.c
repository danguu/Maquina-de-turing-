#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAPE_SIZE 100 // Define el tamaño de la cinta de la máquina de Turing

// Estructura para la máquina de Turing
struct MaquinaDeTuring {
    char cinta[TAPE_SIZE]; // Cinta de la máquina de Turing
    int puntero;           // Posición actual del puntero en la cinta
};

// Inicializa la máquina de Turing
void inicializar_maquina(struct MaquinaDeTuring* maquina) {
    memset(maquina->cinta, '0', TAPE_SIZE); // Llena la cinta con ceros
    maquina->puntero = TAPE_SIZE / 2;        // Coloca el puntero en el centro de la cinta
}

// Mueve el puntero de la máquina de Turing
void mover_puntero(struct MaquinaDeTuring* maquina, char direccion) {
    if (direccion == 'D') { // Si la dirección es 'D' (derecha)
        maquina->puntero = (maquina->puntero + 1) % TAPE_SIZE; // Mueve el puntero a la derecha, con envolvimiento circular
    } else if (direccion == 'I') { // Si la dirección es 'I' (izquierda)
        maquina->puntero = (maquina->puntero - 1 + TAPE_SIZE) % TAPE_SIZE; // Mueve el puntero a la izquierda, con envolvimiento circular
    }
}

// Lee el valor en la posición actual del puntero
char leer_cinta(struct MaquinaDeTuring* maquina) {
    return maquina->cinta[maquina->puntero]; // Devuelve el valor en la posición actual del puntero
}

// Escribe un valor en la cinta en la posición actual del puntero
void escribir_cinta(struct MaquinaDeTuring* maquina, char valor) {
    maquina->cinta[maquina->puntero] = valor; // Establece el valor en la posición actual del puntero
}

// Imprime la cinta con el puntero resaltado
void imprimir_cinta(struct MaquinaDeTuring* maquina) {
    for (int i = 0; i < TAPE_SIZE; i++) {
        if (i == maquina->puntero) {
            printf("[%c]", maquina->cinta[i]); // Resalta la posición del puntero con corchetes
        } else {
            printf("%c", maquina->cinta[i]); // Imprime el contenido de la cinta
        }
    }
    printf("\n"); // Nueva línea al final de la impresión de la cinta
}

// Convierte una cadena binaria a un número decimal
int binario_a_decimal(char* binario) {
    return (int)strtol(binario, NULL, 2); // Usa strtol para convertir de binario a decimal
}

// Convierte un número decimal a una cadena binaria
void decimal_a_binario(int decimal, char* resultado) {
    int index = 0;
    if (decimal == 0) {
        strcpy(resultado, "0"); // Caso especial para el valor 0
        return;
    }
    while (decimal > 0) { // Convierte el número decimal a binario
        resultado[index++] = (decimal % 2) + '0'; // Añade el bit menos significativo
        decimal /= 2; // Divide el número decimal por 2
    }
    resultado[index] = '\0'; // Termina la cadena binaria
    // Invierte la cadena binaria
    for (int i = 0; i < index / 2; i++) {
        char temp = resultado[i];
        resultado[i] = resultado[index - i - 1];
        resultado[index - i - 1] = temp;
    }
}

// Suma dos números binarios (como cadenas)
void sumar_binario(char* a, char* b, char* resultado) {
    int num_a = binario_a_decimal(a); // Convierte el primer número binario a decimal
    int num_b = binario_a_decimal(b); // Convierte el segundo número binario a decimal
    int suma = num_a + num_b; // Suma los dos números decimales
    decimal_a_binario(suma, resultado); // Convierte el resultado de la suma a binario
}

// Resta dos números binarios (como cadenas)
void restar_binario(char* a, char* b, char* resultado) {
    int num_a = binario_a_decimal(a); // Convierte el primer número binario a decimal
    int num_b = binario_a_decimal(b); // Convierte el segundo número binario a decimal
    int resta = num_a - num_b; // Resta el segundo número del primero
    decimal_a_binario(resta, resultado); // Convierte el resultado de la resta a binario
}

// Función para mostrar el movimiento del puntero
void mostrar_movimiento(struct MaquinaDeTuring* maquina, char direccion) {
    printf("Moviendo el puntero hacia la %s\n", direccion == 'D' ? "derecha" : "izquierda"); // Muestra la dirección del movimiento
    mover_puntero(maquina, direccion); // Mueve el puntero
    imprimir_cinta(maquina); // Imprime la cinta después del movimiento
}

// Función principal
int main() {
    struct MaquinaDeTuring turing; // Declara una instancia de la máquina de Turing
    inicializar_maquina(&turing); // Inicializa la máquina de Turing

    char binary1[50], binary2[50]; // Arrays para almacenar los números binarios

    // Leer dos números binarios del usuario
    printf("Ingresa el primer número binario: ");
    scanf("%s", binary1);
    printf("Ingresa el segundo número binario: ");
    scanf("%s", binary2);

    // Coloca el primer número binario en la cinta
    for (int i = 0; i < strlen(binary1); i++) {
        escribir_cinta(&turing, binary1[i]); // Escribe cada bit del primer número en la cinta
        mostrar_movimiento(&turing, 'D'); // Mueve el puntero a la derecha
    }

    printf("Cinta después de colocar el primer número binario:\n");
    imprimir_cinta(&turing); // Imprime la cinta después de colocar el primer número binario

    // Coloca un separador en la cinta
    escribir_cinta(&turing, ' '); // Escribe un espacio como separador
    mostrar_movimiento(&turing, 'D'); // Mueve el puntero a la derecha

    // Coloca el segundo número binario en la cinta
    for (int i = 0; i < strlen(binary2); i++) {
        escribir_cinta(&turing, binary2[i]); // Escribe cada bit del segundo número en la cinta
        mostrar_movimiento(&turing, 'D'); // Mueve el puntero a la derecha
    }

    printf("Cinta después de colocar el segundo número binario:\n");
    imprimir_cinta(&turing); // Imprime la cinta después de colocar el segundo número binario

    // Realiza la suma
    char resultado_suma[50];
    sumar_binario(binary1, binary2, resultado_suma); // Suma los dos números binarios
    printf("Resultado de la suma en binario: %s\n", resultado_suma);
    printf("Resultado de la suma en decimal: %d\n", binario_a_decimal(resultado_suma)); // Muestra el resultado de la suma en decimal

    // Realiza la resta
    char resultado_resta[50];
    restar_binario(binary1, binary2, resultado_resta); // Resta el segundo número del primero
    printf("Resultado de la resta en binario: %s\n", resultado_resta);
    printf("Resultado de la resta en decimal: %d\n", binario_a_decimal(resultado_resta)); // Muestra el resultado de la resta en decimal

    printf("Cinta final después de la suma y resta:\n");
    imprimir_cinta(&turing); // Imprime la cinta final después de realizar la suma y la resta

    return 0; // Fin del programa
}
