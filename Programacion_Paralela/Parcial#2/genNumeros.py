import numpy as np

def aleatorio(r, c, a):
    print(f'{r}, {c}')
    matrix = np.random.randint(a, size=(r, c))  # Generar la matriz aleatoria directamente
    for row in matrix:
        row_str = ', '.join(map(str, row))  # Convertir cada fila en una cadena
        print(row_str)
    
    # Imprimir una fila adicional
    last_row_str = ', '.join(map(str, np.random.randint(a, size=c)))
    print()
    print(last_row_str)

r, c, a = map(int, input().split())
aleatorio(r, c, a)

