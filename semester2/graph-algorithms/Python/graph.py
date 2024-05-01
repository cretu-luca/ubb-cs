from random import randint
from copy import deepcopy


class Graph:
    def __init__(self, numberOfNodes: int):
        self.numberOfNodes = numberOfNodes
        self.numberOfEdges = 0
        self.__inbound_edges = {}
        self.__outbound_edges = {}
        self.__edge_cost = {}

        for i in range(numberOfNodes):
            self.__inbound_edges[i] = []
            self.__outbound_edges[i] = []

    def add_node(self, nodeToAdd: int):
        if nodeToAdd in self.__inbound_edges:
            print("Node already in graph.")
        else:
            self.__inbound_edges[nodeToAdd] = []
            self.__outbound_edges[nodeToAdd] = []

    def copy(self):
        new_graph = Graph(self.numberOfNodes)
        new_graph.numberOfEdges = self.numberOfEdges
        new_graph.__inbound_edges = deepcopy(self.__inbound_edges)
        new_graph.__outbound_edges = deepcopy(self.__outbound_edges)
        new_graph.__edge_cost = deepcopy(self.__edge_cost)

        return new_graph

    def remove_node(self, nodeToRemove: int):
        if nodeToRemove not in self.__inbound_edges and nodeToRemove not in self.__outbound_edges:
            print("Node not found in graph.")
            return

        for source, cost in self.__inbound_edges[nodeToRemove]:
            if (source, nodeToRemove) in self.__edge_cost:
                self.remove_edge(source, nodeToRemove)

        for target, index in self.__outbound_edges[nodeToRemove]:
            if (nodeToRemove, target) in self.__edge_cost:
                self.remove_edge(nodeToRemove, target)

        del self.__inbound_edges[nodeToRemove]
        del self.__outbound_edges[nodeToRemove]

        self.numberOfNodes -= 1
        print("Node removed successfully.")

    def add_edge(self, source: int, target: int, cost: int):
        if source not in self.__outbound_edges:
            self.__outbound_edges[source] = []
        if target not in self.__inbound_edges:
            self.__inbound_edges[target] = []

        self.numberOfEdges += 1
        self.__edge_cost[(source, target)] = cost
        self.__outbound_edges[source].append((target, cost))
        self.__inbound_edges[target].append((source, cost))

    def remove_edge(self, source: int, target: int):
        del self.__edge_cost[(source, target)]

        self.__outbound_edges[source] = [pair for pair in self.__outbound_edges[source] if pair[0] != target]
        self.__inbound_edges[target] = [pair for pair in self.__inbound_edges[target] if pair[0] != source]

        self.numberOfEdges -= 1

    def is_edge(self, source: int, target: int):
        return (source, target) in self.__edge_cost

    def get_inbound_edges_number(self, node: int):
        return list(self.__inbound_edges[node])

    def get_outbound_edge_number(self, node: int):
        return list(self.__outbound_edges[node])

    def get_nodes(self):
        for node in self.__inbound_edges.keys():
            yield node

    def get_outbound_edges(self, node):
        if node in self.__outbound_edges:
            for target, cost in self.__outbound_edges[node]:
                yield target, cost

    def get_inbound_edges(self, node):
        if node in self.__inbound_edges:
            for source, cost in self.__inbound_edges[node]:
                yield source, cost

    def get_cost(self, source: int, target: int):
        return self.__edge_cost[(source, target)]

    def set_cost(self, source: int, target: int, cost: int):
        self.__edge_cost[(source, target)] = cost

    @staticmethod
    def read_from_file(file_path):
        with open(file_path, 'r') as file:
            first_line = file.readline().strip()

            numberOfNodes, numberOfEdges = map(int, first_line.split())

            graph = Graph(numberOfNodes)
            for line in file:
                source, target, cost = map(int, line.strip().split())
                graph.add_edge(source, target, cost)

        return graph

    def write_to_file(self, file_path):
        with open(file_path, 'w') as file:
            file.write(f"{self.numberOfNodes} {self.numberOfEdges}")
            file.write("\n")

            for source in self.__outbound_edges:
                for target, cost in self.__outbound_edges[source]:
                    file.write(f"{source} {target} {cost}")
                    file.write("\n")

    @staticmethod
    def generate_random_graph(numberOfNodes: int, numberOfEdges: int):
        graph = Graph(numberOfNodes)
        for i in range(numberOfEdges):
            cost = randint(1, 100)
            source = randint(1, numberOfNodes)
            target = randint(1, numberOfNodes)
            while graph.is_edge(source, target):
                source = randint(1, numberOfNodes)
                target = randint(1, numberOfNodes)

            graph.add_edge(source, target, cost)

        return graph

    def print_graph(self):
        print(self.numberOfNodes, self.numberOfEdges)
        for source in self.__outbound_edges:
            for pair in self.__outbound_edges[source]:
                print(f"{source} {pair[0]} {pair[1]}")

