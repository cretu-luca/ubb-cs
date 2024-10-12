class Nod:
    def __init__(self, e):
        self.e = e
        self.urm = None

class Lista:
    def __init__(self):
        self.prim = None


'''
crearea unei liste din valori citite pana la 0
'''
def creareLista():
    lista = Lista()
    lista.prim = creareLista_rec()
    return lista

def creareLista_rec():
    x = int(input("x="))
    if x == 0:
        return None
    else:
        nod = Nod(x)
        nod.urm = creareLista_rec()
        return nod

'''
tiparirea elementelor unei liste
'''
def tipar(lista):
    tipar_rec(lista.prim)

def tipar_rec(nod):
    if nod != None:
        print (nod.e)
        tipar_rec(nod.urm)


'''
program pentru test
'''

def checkIfSet(head):
    if head is None:
        return True

    if contains(head.e, head.urm):
        return False
    else:
        return checkIfSet(head.urm)


def contains(val, head):
    if head is None:
        return False

    if val == head.e:
        return True

    return contains(val, head.urm)


def numberOfDistinctElements(head):
    if head is None:
        return 0

    if not contains(head.e, head.urm):
        return 1 + numberOfDistinctElements(head.urm)
    else:
        return numberOfDistinctElements(head.urm)


def main():
    list = creareLista()
    tipar(list)
    print("List is set: ", checkIfSet(list.prim))
    print("Number of distinct elements: ", numberOfDistinctElements(list.prim))

main()
