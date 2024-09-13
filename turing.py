# Definir tamaño de la cinta
TAPE_SIZE = 100

# Función para verificar si una cadena es un número binario válido
def es_binario_valido(binario):
    for char in binario:
        if char != '0' and char != '1':
            return False  # No es un número binario válido
    return True

# Función para convertir binario a decimal
def binario_a_decimal(binario):
    decimal = 0
    base = 1  # 2^0
    for bit in reversed(binario):
        if bit == '1':
            decimal += base
        base *= 2  # Incrementar la base
    return decimal

# Función para convertir decimal a binario
def decimal_a_binario(decimal):
    if decimal == 0:
        return '0'
    binario = ''
    while decimal > 0:
        binario = str(decimal % 2) + binario
        decimal //= 2
    return binario

# Función para sumar dos números binarios
def sumar_binario(a, b):
    resultado = ''
    carry = 0
    i, j = len(a) - 1, len(b) - 1
    while i >= 0 or j >= 0 or carry:
        suma = carry
        if i >= 0:
            suma += int(a[i])
            i -= 1
        if j >= 0:
            suma += int(b[j])
            j -= 1
        resultado = str(suma % 2) + resultado  # Guardar el bit menos significativo
        carry = suma // 2  # Calcular el nuevo carry
    return resultado

# Función para restar dos números binarios
def restar_binario(a, b):
    resultado = ''
    borrow = 0
    i, j = len(a) - 1, len(b) - 1
    while i >= 0 or j >= 0:
        resta = int(a[i]) - borrow if i >= 0 else -borrow
        if j >= 0:
            resta -= int(b[j])
        if resta < 0:
            resta += 2
            borrow = 1
        else:
            borrow = 0
        resultado = str(resta) + resultado
        i -= 1
        j -= 1

    # Eliminar ceros a la izquierda
    return resultado.lstrip('0') or '0'

# Función principal
def main():
    binary1 = input("Ingresa el primer número binario: ")
    if not es_binario_valido(binary1):
        print("Error: Entrada no válida, solo se permiten números binarios.")
        return

    binary2 = input("Ingresa el segundo número binario: ")
    if not es_binario_valido(binary2):
        print("Error: Entrada no válida, solo se permiten números binarios.")
        return

    # Sumar
    suma_binaria = sumar_binario(binary1, binary2)
    print(f"Resultado de la suma en binario: {suma_binaria}")
    suma_decimal = binario_a_decimal(suma_binaria)
    print(f"Resultado de la suma en decimal: {suma_decimal}")

    # Restar
    resta_binaria = restar_binario(binary1, binary2)
    print(f"Resultado de la resta en binario: {resta_binaria}")
    resta_decimal = binario_a_decimal(resta_binaria)
    print(f"Resultado de la resta en decimal: {resta_decimal}")

if __name__ == "__main__":
    main()
