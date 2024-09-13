#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAPE_SIZE 100  
// Define el tamaño de la cinta

// Estructura para la máquina de Turing
typedef struct {
    char cinta[TAPE_SIZE]; // La cinta de la máquina de Turing
    int puntero;           // La posición actual del puntero en la cinta
} MaquinaDeTuring;

// Inicializa la máquina de Turing
void inicializar_maquina(MaquinaDeTuring *maquina) {
    memset(maquina->cinta, '0', TAPE_SIZE); // Inicializa la cinta con ceros
    maquina->puntero = TAPE_SIZE / 2;        // Coloca el puntero en el centro de la cinta
}

// Mueve el puntero de la máquina de Turing en la dirección indicada
void mover_puntero(MaquinaDeTuring *maquina, char direccion) {
    if (direccion == 'D') { // Mover hacia la derecha
        if (maquina->puntero < TAPE_SIZE - 1) { // Asegúrate de no salir del límite derecho
            maquina->puntero++;
            printf("Moviendo puntero a la derecha. Nueva posición: %d\n", maquina->puntero);
        }
    } else if (direccion == 'I') { // Mover hacia la izquierda
        if (maquina->puntero > 0) { // Asegúrate de no salir del límite izquierdo
            maquina->puntero--;
            printf("Moviendo puntero a la izquierda. Nueva posición: %d\n", maquina->puntero);
        }
    }
    imprimir_cinta(maquina); // Imprime el estado actual de la cinta
}

// Lee el valor en la posición actual del puntero en la cinta
char leer_cinta(MaquinaDeTuring *maquina) {
    return maquina->cinta[maquina->puntero];
}

// Escribe un valor en la posición actual del puntero en la cinta
void escribir_cinta(MaquinaDeTuring *maquina, char valor) {
    maquina->cinta[maquina->puntero] = valor;
}

// Imprime el estado de la cinta con el puntero indicado
void imprimir_cinta(MaquinaDeTuring *maquina) {
    for (int i = 0; i < TAPE_SIZE; i++) {
        if (i == maquina->puntero) { // Imprime una barra vertical en la posición del puntero
            printf("|");
        }
        printf("%c", maquina->cinta[i]); // Imprime el contenido de la cinta
    }
    printf("\n");
}

// Convierte una cadena binaria a un número decimal
int binario_a_decimal(const char *binario) {
    int decimal = 0;
    int base = 1;
    int longitud = strlen(binario);
    for (int i = longitud - 1; i >= 0; i--) {
        if (binario[i] == '1') { // Si el bit es 1, suma la base al decimal
            decimal += base;
        }
        base *= 2; // Incrementa la base (potencia de 2)
    }
    return decimal;
}

// Convierte un número decimal a una cadena binaria
void decimal_a_binario(int decimal, char *binario) {
    int index = 0;
    if (decimal == 0) { // Caso especial para 0
        binario[index++] = '0';
    } else {
        while (decimal > 0) { // Convierte el número decimal a binario
            binario[index++] = (decimal % 2) + '0'; // Añade el bit menos significativo
            decimal /= 2; // Divide el número decimal por 2
        }
    }
    binario[index] = '\0'; // Finaliza la cadena binaria
    // Invierte la cadena binaria
    for (int i = 0; i < index / 2; i++) {
        char temp = binario[i];
        binario[i] = binario[index - 1 - i];
        binario[index - 1 - i] = temp;
    }
}

// Suma dos cadenas binarias y guarda el resultado
void sumar_binario(const char *a, const char *b, char *resultado) {
    int carry = 0;
    int i = strlen(a) - 1;
    int j = strlen(b) - 1;
    int k = 0;

    while (i >= 0 || j >= 0 || carry) { // Mientras haya bits o acarreo
        int suma = carry;
        if (i >= 0) suma += a[i--] - '0'; // Suma el bit de a y el acarreo
        if (j >= 0) suma += b[j--] - '0'; // Suma el bit de b
        resultado[k++] = (suma % 2) + '0'; // Guarda el bit resultante
        carry = suma / 2; // Calcula el nuevo acarreo
    }
    resultado[k] = '\0'; // Finaliza la cadena de resultado
    // Invierte el resultado
    for (int m = 0; m < k / 2; m++) {
        char temp = resultado[m];
        resultado[m] = resultado[k - 1 - m];
        resultado[k - 1 - m] = temp;
    }
}

// Resta dos cadenas binarias y guarda el resultado
void restar_binario(const char *a, const char *b, char *resultado) {
    int borrow = 0;
    int i = strlen(a) - 1;
    int j = strlen(b) - 1;
    int k = 0;

    while (i >= 0 || j >= 0) { // Mientras haya bits en a o b
        int resta = (a[i] - '0') - borrow;
        if (j >= 0) resta -= (b[j] - '0'); // Resta el bit de b
        if (resta < 0) { // Maneja el préstamo
            resta += 2;
            borrow = 1;
        } else {
            borrow = 0;
        }
        resultado[k++] = resta + '0'; // Guarda el bit resultante
        i--;
        j--;
    }
    resultado[k] = '\0'; // Finaliza la cadena de resultado
    // Invierte el resultado
    for (int m = 0; m < k / 2; m++) {
        char temp = resultado[m];
        resultado[m] = resultado[k - 1 - m];
        resultado[k - 1 - m] = temp;
    }
    // Elimina los ceros a la izquierda
    int start = 0;
    while (resultado[start] == '0' && start < k - 1) {
        start++;
    }
    memmove(resultado, resultado + start, k - start + 1);
}

int main() {
    MaquinaDeTuring maquina; // Declara una instancia de MaquinaDeTuring
    inicializar_maquina(&maquina); // Inicializa la máquina de Turing

    char binary1[TAPE_SIZE], binary2[TAPE_SIZE];
    char resultado[TAPE_SIZE];
    int decimalResult;

    // Leer el primer número binario
    printf("Ingresa el primer número binario: ");
    scanf("%s", binary1);

    // Leer el segundo número binario
    printf("Ingresa el segundo número binario: ");
    scanf("%s", binary2);

    // Colocar el primer número binario en la cinta
    for (int i = 0; i < strlen(binary1); i++) {
        escribir_cinta(&maquina, binary1[i]);
        mover_puntero(&maquina, 'D'); // Mueve el puntero a la derecha
    }
    mover_puntero(&maquina, 'I' * strlen(binary1));  // Mueve el puntero de vuelta al inicio

    // Separador para el segundo número
    escribir_cinta(&maquina, ' ');
    mover_puntero(&maquina, 'D'); // Mueve el puntero a la derecha

    // Colocar el segundo número binario en la cinta
    for (int i = 0; i < strlen(binary2); i++) {
        escribir_cinta(&maquina, binary2[i]);
        mover_puntero(&maquina, 'D'); // Mueve el puntero a la derecha
    }
    mover_puntero(&maquina, 'I' * (strlen(binary2) + 1));  // Mueve el puntero de vuelta al inicio

    // Realizar suma
    sumar_binario(binary1, binary2, resultado);
    printf("Resultado de la suma en binario: %s\n", resultado);
    decimalResult = binario_a_decimal(resultado);
    printf("Resultado de la suma en decimal: %d\n", decimalResult);

    // Realizar resta
    restar_binario(binary1, binary2, resultado);
    printf("Resultado de la resta en binario: %s\n", resultado);
    decimalResult = binario_a_decimal(resultado);
    printf("Resultado de la resta en decimal: %d\n", decimalResult);

    return 0;
}
