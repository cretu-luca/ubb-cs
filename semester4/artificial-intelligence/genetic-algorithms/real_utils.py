import numpy as np
import random
from typing import List, Tuple
import json

with open('config.json', 'r') as f:
    config = json.load(f)

def generate_real_individual():
    x1 = np.random.uniform(-10, 10)
    x2 = np.random.uniform(-10, 10)
    return [x1, x2]

def real_mutation(individual):
    mutation_rate = config["mutation_rate"]
    mutated = individual.copy()

    for i in range(len(mutated)):
        if random.random() < mutation_rate:
            noise = np.random.normal(0, 0.1)
            mutated[i] += noise
            mutated[i] = np.clip(mutated[i], -10, 10)
            
    return mutated

def arithmetic_crossover(parent1, parent2):
    alpha = 0.5

    child1 = [alpha * p1 + (1 - alpha) * p2 for p1, p2 in zip(parent1, parent2)]
    child2 = [(1 - alpha) * p1 + alpha * p2 for p1, p2 in zip(parent1, parent2)]
    
    return child1, child2

def blx_alpha_crossover(parent1, parent2, alpha=0.5):
    child1 = []
    child2 = []
    
    for p1, p2 in zip(parent1, parent2):
        min_val = min(p1, p2)
        max_val = max(p1, p2)
        range_val = max_val - min_val
        
        lower_bound = min_val - alpha * range_val
        upper_bound = max_val + alpha * range_val
        
        lower_bound = max(lower_bound, -10)
        upper_bound = min(upper_bound, 10)
        
        child1.append(np.random.uniform(lower_bound, upper_bound))
        child2.append(np.random.uniform(lower_bound, upper_bound))
    
    return child1, child2