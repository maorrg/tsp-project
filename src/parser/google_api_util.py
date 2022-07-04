import os
from dotenv import load_dotenv
import requests
import json
import numpy as np

# CONSTANTS
DATA_ROOT_PATH = '../../data/lima_matrix/'

load_dotenv()
GOOGLE_API_KEY = os.getenv("GOOGLE_API_KEY")
distance_matrix = [] #km
time_matrix = [] #minutes
gasoline_matrix = []
other_cost_matrix = []
total_cost_matrix = []

data = {}

def generate_distance_matrix():
    global data
    cities = ["Lima Centro", "Lince", "Miraflores", "Barranco", "Rimac",
              "Los Olivos", "La Molina", "La Victoria", "Magdalena", "San Borja"]
    cities_url = [city.replace(" ", "+") for city in cities]
    cities_url = [f"{city}+Lima+District+Peru" for city in cities_url]
    origins = "|".join(cities_url)
    url = f"https://maps.googleapis.com/maps/api/distancematrix/json?units=metric&origins={origins}&destinations={origins}&key={GOOGLE_API_KEY}"
    response = requests.get(url)
    data = json.loads(response.text)

def make_matrix_symetric(matrix):
    sym_matrix = matrix
    n = len(matrix)
    for i in range(0, n):
        for j in range(0, n):
            if i == j:
                matrix[i][j] = 999999999
            else:
                sym_matrix[i][j] = matrix[i][j]
                sym_matrix[j][i] = matrix[i][j]

    return sym_matrix

def parse_data_and_generate_matrix():
    global distance_matrix
    global time_matrix
    districts_origin = data["origin_addresses"]
    n = len(districts_origin)

    for row in data["rows"]:
        distance_row = []
        duration_row = []
        for values in row["elements"]:
            distance = int(values["distance"]["value"] / 1000)
            duration = int(values["duration"]["value"] / 60)
            distance_row.append(distance)
            duration_row.append(duration)
        distance_matrix.append(distance_row)
        time_matrix.append(duration_row)
    distance_matrix = make_matrix_symetric(distance_matrix)
    time_matrix = make_matrix_symetric(time_matrix)


def write_matrix(matrix, file_name):
    mat=np.matrix(matrix)
    np.savetxt(DATA_ROOT_PATH+file_name, mat, fmt='%.0f')


def fill_matrix(matrix, n):
    for i in range(0, n):
        row = []
        for j in range(0,n):
            row.append(1)
        matrix.append(row) 

def generate_total_cost_matrix():
    distance_weight, time_weight, gasoline_weight, other_cost_weight = ask_user_for_variables_weights()
    global total_cost_matrix
    n = len(distance_matrix)
    fill_matrix(total_cost_matrix, n)
    for i in range(0,n):
        for j in range(0,n):
            if i == j:
                total_cost_matrix[i][j] = 999999999
            else:
                total_cost_matrix[i][j] = int(distance_weight*distance_matrix[i][j]+time_weight*time_matrix[i][j]+gasoline_weight*gasoline_matrix[i][j]+other_cost_weight*other_cost_matrix[i][j])
                total_cost_matrix[j][i] = total_cost_matrix[i][j]
    write_matrix(total_cost_matrix, "total_cost_matrix.txt")


def read_matrix_from_file(file_name):
    with open(DATA_ROOT_PATH+file_name, 'r') as f:
        matrix = [[int(num) for num in line.split(' ')] for line in f]
    return matrix

def load_matrix():
    global gasoline_matrix
    global other_cost_matrix
    gasoline_matrix = read_matrix_from_file("gasoline_matrix.txt")
    other_cost_matrix = read_matrix_from_file("other_cost_matrix.txt")

def ask_user_for_variables_weights():
    print("Ingrese el factor / peso de:")
    distance_weight = float(input("-> Distancia: "))
    time_weight = float(input("-> Tiempo: "))
    gasoline_weight = float(input("-> Gasolina: "))
    other_cost_weight = float(input("-> Costos Adicionales: "))
    return distance_weight, time_weight, gasoline_weight, other_cost_weight

if __name__ == "__main__":
    generate_distance_matrix()
    parse_data_and_generate_matrix()
    write_matrix(distance_matrix, "distance_matrix.txt")
    write_matrix(time_matrix, "time_matrix.txt")
    load_matrix()
    generate_total_cost_matrix()
    print("[LOG] Matriz de costos totales generada correctamente.")