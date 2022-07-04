from dis import dis
import random
import numpy as np
from python_tsp.exact import solve_tsp_dynamic_programming

ROOT_DATA_PATH = "../../data"

def create_matrix(n):
    matrix = np.array([[0 for x in range(n)] for y in range(n)])
    for i in range(n):
        for j in range(n):
            if i == j:
                matrix[i][j] = 999999999
            else:
                matrix[i][j] = random.randint(1, 100)
                matrix[j][i] = matrix[i][j]
    return matrix


def solve_tsp(matrix):
    trip, totalCost = solve_tsp_dynamic_programming(matrix)
    return trip, totalCost


def generate_all_inputs(min_value=5, max_value=20):
    values_of_n = [x for x in range(min_value, max_value+1)]
    for n in values_of_n:
        generate_single_input(n)

def list_to_string(list):
    ans = ""
    for e in list:
        ans += f'{str(e)} '
    ans += str(list[0])
    return ans

def generate_single_input(n):
    matrix = create_matrix(n)
    trip, totalCost = solve_tsp(matrix)

    with open(f"{ROOT_DATA_PATH}/matrix_{n}.txt", "w+") as f:
        header = f'{n} {list_to_string(trip)} {totalCost}'
        f.write(header)
        f.write("\n")
        for i in range(n):
            for j in range(n):
                f.write(str(matrix[i][j]) + " ")
            f.write("\n")
    print(f'[LOG] Matriz de {n} nodos creada correctamente.')

if __name__ == "__main__":
    min = input("Ingrese el valor mínimo de n: ")
    max = input("Ingrese el valor máximo de n: ")
    generate_all_inputs(int(min),int(max))
