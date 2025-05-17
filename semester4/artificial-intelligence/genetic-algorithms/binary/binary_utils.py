import numpy as np
import random
from typing import List, Tuple
import json

with open('config.json', 'r') as f:
    config = json.load(f)

def binary_to_float(binary: str, min_value: int, max_value: int) -> float:
    decimal = int(binary, 2)
    max_decimal = 2 ** len(binary) - 1
    
    return min_value + (max_value - min_value) * decimal / max_decimal

def float_to_binary(real: str, min_value: int, max_value: int, interval_size: int = 20) -> str:
    decimal = int((real - min_value) * (2 ** interval_size - 1)) / (max_value - min_value)
    binary = format(decimal, f'0{interval_size}b')

    return binary

def decode(individual: str, bits_per_input: int = None) -> Tuple[float, float]: 
    if bits_per_input is None:
        bits_per_input = config["bits_per_input"]
    
    x1_binary = individual[bits_per_input:]
    x2_binary = individual[:bits_per_input]

    x1 = binary_to_float(x1_binary, -10, 10)
    x2 = binary_to_float(x2_binary, -10, 10)

    return x1, x2

def generate_binary_individual(bits_per_input: int = None):
    if bits_per_input is None:
        bits_per_input = config["bits_per_input"]
    
    individual = ''.join(np.random.choice(['0', '1']) for _ in range(bits_per_input * 2))
    return individual

def binary_mutation(individual, mutation_rate = None):
    if mutation_rate is None:
        mutation_rate = config["mutation_rate"]
    
    mutated = ""

    for bit in individual:
        if random.random() < mutation_rate:
            mutated += '1' if bit == '0' else '0'
        else:
            mutated += bit

    return mutated