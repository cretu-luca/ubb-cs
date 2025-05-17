import numpy as np

def one_point_crossover(parent1, parent2):
    length = len(parent1)
    crossover_point = np.random.randint(1, length - 1)

    child1 = parent1[:crossover_point] + parent2[crossover_point:]
    child2 = parent2[:crossover_point] + parent1[crossover_point:]

    return child1, child2

def two_point_crossover(parent1, parent2):
    length = len(parent1)
    
    crossover_point_1 = np.random.randint(1, length - 2)
    crossover_point_2 = np.random.randint(crossover_point_1, length - 1)

    child1 = parent1[:crossover_point_1] + parent2[crossover_point_1:crossover_point_2] + parent1[crossover_point_2:]
    child2 = parent2[:crossover_point_1] + parent1[crossover_point_1:crossover_point_2] + parent2[crossover_point_2:]

    return child1, child2