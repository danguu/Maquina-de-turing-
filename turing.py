# Definimos el tamaño de la cinta
TAPE_SIZE = 100

class MaquinaDeTuring:
    def __init__(self):
        # Inicializa la cinta con ceros y coloca el puntero en el centro de la cinta
        self.cinta = ['0'] * TAPE_SIZE
        self.puntero = TAPE_SIZE // 2
    
    def mover_puntero(self, direccion):
        # Mueve el puntero en la dirección especificada
        # 'D' para derecha, 'I' para izquierda
        if direccion == 'D':
            self.puntero = min(self.puntero + 1, TAPE_SIZE - 1)  # Mueve a la derecha, sin exceder el tamaño de la cinta
        elif direccion == 'I':
            self.puntero = max(self.puntero - 1, 0)  # Mueve a la izquierda, sin ir por debajo del índice 0
    
    def leer_cinta(self):
        # Lee el valor actual en la posición del puntero
        return self.cinta[self.puntero]
    
    def escribir_cinta(self, valor):
        # Escribe un valor en la posición actual del puntero
        self.cinta[self.puntero] = valor
    
    def imprimir_cinta(self):
        # Imprime la cinta con el puntero resaltado
        cinta_mostrada = ''.join(self.cinta)
        print(cinta_mostrada[:self.puntero] + '[' + self.cinta[self.puntero] + ']' + cinta_mostrada[self.puntero + 1:])
    
    def mostrar_movimiento(self, direccion):
        # Muestra la dirección del movimiento y actualiza la posición del puntero
        print(f"Moviendo el puntero hacia la {'derecha' if direccion == 'D' else 'izquierda'}")
        self.mover_puntero(direccion)
        self.imprimir_cinta()

def binario_a_decimal(binario):
    # Convierte un número binario (como cadena) a decimal
    return int(binario, 2)

def decimal_a_binario(decimal):
    # Convierte un número decimal a binario (como cadena)
    return bin(decimal)[2:]

def sumar_binario(a, b):
    # Suma dos números binarios (como cadenas)
    max_len = max(len(a), len(b))
    a = a.zfill(max_len)  # Rellena con ceros a la izquierda para igualar longitudes
    b = b.zfill(max_len)
    carry = 0
    resultado = []
    # Suma bit a bit desde el final de las cadenas
    for i in range(max_len - 1, -1, -1):
        suma = int(a[i]) + int(b[i]) + carry
        resultado.append(str(suma % 2))
        carry = suma // 2
    if carry:
        resultado.append('1')
    return ''.join(resultado[::-1])  # Invierte el resultado para obtener el binario correcto

def restar_binario(a, b):
    # Resta dos números binarios (como cadenas)
    max_len = max(len(a), len(b))
    a = a.zfill(max_len)  # Rellena con ceros a la izquierda para igualar longitudes
    b = b.zfill(max_len)
    borrow = 0
    resultado = []
    # Resta bit a bit desde el final de las cadenas
    for i in range(max_len - 1, -1, -1):
        resta = int(a[i]) - int(b[i]) - borrow
        if resta < 0:
            resta += 2
            borrow = 1
        else:
            borrow = 0
        resultado.append(str(resta))
    return ''.join(resultado[::-1]).lstrip('0') or '0'  # Invierte el resultado y elimina ceros a la izquierda

def main():
    turing = MaquinaDeTuring()  # Crea una instancia de la máquina de Turing
    
    def leer_binario(prompt):
        # Lee una entrada binaria del usuario y valida que sea correcta
        binario = input(prompt)
        if not all(bit in '01' for bit in binario):
            print("Error: Entrada no válida, solo se permiten números binarios.")
            exit()
        return binario
    
    # Lee dos números binarios del usuario
    binary1 = leer_binario("Ingresa el primer número binario: ")
    binary2 = leer_binario("Ingresa el segundo número binario: ")
    
    # Coloca el primer número binario en la cinta y mueve el puntero
    for bit in binary1:
        turing.escribir_cinta(bit)
        turing.mostrar_movimiento('D')  # Mueve el puntero a la derecha
    turing.mover_puntero('I' * len(binary1))  # Mueve el puntero de vuelta al inicio
    print("Cinta después de colocar el primer número binario:")
    turing.imprimir_cinta()
    
    # Coloca un separador en la cinta y mueve el puntero
    turing.escribir_cinta(' ')
    turing.mostrar_movimiento('D')
    # Coloca el segundo número binario en la cinta y mueve el puntero
    for bit in binary2:
        turing.escribir_cinta(bit)
        turing.mostrar_movimiento('D')  # Mueve el puntero a la derecha
    turing.mover_puntero('I' * (len(binary2) + 1))  # Mueve el puntero de vuelta al inicio
    print("Cinta después de colocar el segundo número binario:")
    turing.imprimir_cinta()
    
    # Calcula y muestra el resultado de la suma
    suma_binaria = sumar_binario(binary1, binary2)
    print(f"Resultado de la suma en binario: {suma_binaria}")
    print(f"Resultado de la suma en decimal: {binario_a_decimal(suma_binaria)}")
    
    # Mueve el puntero a la derecha y calcula el resultado de la resta
    turing.mover_puntero('D')
    resta_binaria = restar_binario(binary1, binary2)
    print(f"Resultado de la resta en binario: {resta_binaria}")
    print(f"Resultado de la resta en decimal: {binario_a_decimal(resta_binaria)}")

if __name__ == "__main__":
    main()  # Ejecuta la función principal

