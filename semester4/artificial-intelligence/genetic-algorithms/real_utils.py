import numpy as np
import random
from typing import List, Tuple
import json

with open('config.json', 'r') as f:
    config = json.load(f)

def arithmetic_crossover(parent1, parent2):
    child = (parent1 + parent2) / 2

    return child

