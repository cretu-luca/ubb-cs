from graph import Graph


def get_graph():
    print("1. Read graph from file")
    print("2. Generate random graph")
    print("> ")

    option = int(input())
    if option == 1:
        file_path = str(input("File path:"))
        graph = Graph.read_from_file(file_path)
        return graph

    if option == 2:
        numberOfNodes = int(input("Number of nodes:"))
        numberOfEdges = int(input("Number of edges:"))
        graph = Graph.generate_random_graph(numberOfNodes, numberOfEdges)
        return graph


class UserInterface:
    def __init__(self):
        self.graph = get_graph()
        self.main_menu()

    @staticmethod
    def print_main_menu():
        print("1. Print number of nodes")
        print("2. Print number of edges")
        print("3. Check existence of certain edge")
        print("4. Get in degree of certain node")
        print("5. Get out degree of certain node")
        print("6. Get cost of given edge")
        print("7. Write graph to file")
        print("8. Add edge")
        print("9. Remove edge")
        print("10. Add node")
        print("11. Remove node")
        print("12. Print all edges")
        print("0. Exit")

    def write_to_file_UI(self):
        file_path = str(input("File path:"))
        self.graph.write_to_file(file_path)

    def check_existenceUI(self):
        source = int(input("Source:"))
        target = int(input("Target:"))

        if self.graph.is_edge(source, target):
            return True
        else:
            return False

    def get_inbound_degree(self):
        node = int(input("Node:"))
        return len(self.graph.get_inbound_edges_number(node))

    def get_outbound_degree(self):
        node = int(input("Node:"))
        return len(self.graph.get_outbound_edges_number(node))

    def get_costUI(self):
        source = int(input("Source:"))
        target = int(input("Target:"))

        if not self.graph.is_edge(source, target):
            return None
        else:
            return self.graph.get_cost(source, target)

    def add_edgeUI(self):
        source = int(input("Source:"))
        target = int(input("Target:"))
        cost = int(input("Cost:"))

        if self.graph.is_edge(source, target):
            print("No such edge.")
        else:
            self.graph.add_edge(source, target, cost)
            print("Edge was added.")

    def remove_edgeUI(self):
        source = int(input("Source:"))
        target = int(input("Target:"))

        if not self.graph.is_edge(source, target):
            print("No such edge in.")

        self.graph.remove_edge(source, target)

    def remove_nodeUI(self):
        node = int(input("Node:"))
        self.graph.remove_node(node)

    def add_noteUI(self):
        node = int(input("Node:"))
        self.graph.add_node(node)

    def main_menu(self):
        while True:
            self.print_main_menu()
            option = int(input())

            if option == 0:
                exit(0)
            if option == 1:
                print(f"Number of nodes: {self.graph.numberOfNodes}")
            if option == 2:
                print(f"Number of edges: {self.graph.numberOfEdges}")
            if option == 3:
                if self.check_existenceUI():
                    print(f"There is an edge between given nodes.")
                else:
                    print(f"There is no edge between given nodes.")
            if option == 4:
                print(f"The inner degree is {self.get_inbound_degree()}.")
            if option == 5:
                print(f"The outer degree is {self.get_outbound_degree()}.")
            if option == 6:
                if self.get_costUI() is not None:
                    print(f"The cost of given edge is {self.get_costUI()}")
                else:
                    print("There is no such edge.")
            if option == 7:
                self.write_to_file_UI()
            if option == 8:
                self.add_edgeUI()
            if option == 9:
                self.remove_edgeUI()
            if option == 10:
                self.add_noteUI()
            if option == 11:
                self.remove_nodeUI()
            if option == 12:
                self.graph.print_graph()


ui = UserInterface()

