import numpy as np

print("The different norms of vectors: ")
a = np.arange(9) - 6
print(a)

L1norm = np.linalg.norm(a, ord=1)
print("The L1 norm is ", L1norm)

L2norm = np.linalg.norm(a, ord=2)
print("The L2 norm is ", L2norm)

L4norm = np.linalg.norm(a, ord=4)
print("The L4 norm is ", L4norm)

Linfnorm = np.linalg.norm(a, ord=np.inf)
print("The L(infinity) norm is ", Linfnorm)

# ------ matrix operations
print("-----------------------------")
print("Some matrix operations:")
a = np.array([
   [0, 1],
   [2, 3]
])
b = np.array([
    [2, 3],
    [3, 4]
])
print("matrix a:\n", a)
print("matrix b:\n", b)
ab = np.matmul(a, b) # a@b
print("matrix product of a and b:")
print(ab)
hadamard = a*b
print("Hadamard product of a and b:")
print(hadamard)

# ------ vector operations
print("-----------------------------")
print("Some operations with vectors")
x = np.array([1, 2, 3])
y = np.array([0, 1, 1])
print("vector x: ", x)
print("vector y: ", y)
xy_inner_product = np.inner(x, y)
print("inner product:", xy_inner_product)
xy_outer_product = np.outer(x, y)
print("outer product:\n", xy_outer_product)
xy_hadamard = x*y
print("hadamard product:\n", xy_hadamard)

# eigenvalue of a matrix
print("-----------------------------")
print("eigenvalues of a matrix")

a = np.array([
    [1, 3, 1],
    [3, 2, 2],
    [1, 2, 1]
])
print(a)
eig = np.linalg.eigvals(a)
print("eigenvalues:", eig)
