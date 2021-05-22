from timeit import default_timer as timer
from numpy.random import randint


class Node:
    def __init__(self, data = None):
        self.data = data
        self.left = None
        self.right = None


def generate(node, N):
    if N == 0:
        return
    else:
        node = Node()
        data = randint(0, 100000)
        node.data = int(data)
        if node.left:
            node.left = generate(node.left, N//2)
            return node
        if node.right:
            node.right = generate(node.right, N - N//2 - 1)
            return node


COUNT = [1]


def printtree(root, h):
    if root == None:
        return

    h += COUNT[0]

    printtree(root.right, h)
    for i in range(COUNT[0], h):
        print(end="...")
    print(root.data)
    printtree(root.left, h)

def printbin(root):
    printtree(root, 0)

def insert(node, data):
    if node is None:
        return Node(data)
    else:
        if data < node.data:
            node.left = insert(node.left, data)
            return node
        else:
            if data > node.data:
                node.right = insert(node.right, data)
                return node
            else:
                pass

def szukaj(node, liczba): 
  
    if (node == None):  
        
        return False
  
    if (node.data == liczba):  
        return True
  
    res1 = szukaj(node.left, liczba)  
    if res1: 
        return True 
  
    res2 = szukaj(node.right, liczba)  
    return res2 


root = None
for i in range(100):
    x = randint(0, 1000000)
    root = insert(root, x)
printbin(root)

print("napisz jaka liczbe chcesz znalezc: ")
start = timer()

liczba = int(input())
if szukaj(root, liczba):
    print("znaleziono")
else:
    print("nie znaleziono liczby w tym drzewie")
    
end = timer()
czas = end - start
print()
print("czas szukania dla 100 losowych elementów wyniósł: ", czas)
print()
