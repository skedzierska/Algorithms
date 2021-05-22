import numpy as np

A = np.array([
    [1, 2, 0],
    [2, 0, 2]
])

print(A.T)
print("A.T @ A:")
print(A.T @ A)

print("A @ A.T:")
B = A.dot(A.T)
print(B)

eigenvalues = np.linalg.eigvals(B)
print("eigenvalues: ", eigenvalues)

singular_values = np.sqrt(eigenvalues)
print("singular values: ", singular_values)

eigenvalues, eigenvectors = np.linalg.eig(B)
print("eigenvalues: ", eigenvalues)
print("eigenvectors:")
print(np.sqrt(5)*eigenvectors)
u1 = eigenvectors[:, 0]
zerovector = B.dot(u1) - eigenvalues[0] * u1
print("vector with zeros: ", zerovector)
u2 = eigenvectors[:, 1]
zerovector = B.dot(u2) - eigenvalues[1] * u2
print("vector with zeros: ", zerovector)

sigma1 = singular_values[0]
v1 = 1.0/sigma1 * A.T.dot(u1)
print("v1: ", np.sqrt(45) * v1)

sigma2 = singular_values[1]
v2 = 1.0/sigma2 * A.T.dot(u2)
print("v2: ", np.sqrt(45) * v2)

Apinv = np.linalg.pinv(A)
print("pseudo-inverse of A:")
print(90*Apinv)

print("check")
print("A @ Apinv: \n", A @ Apinv)
print("Apinv @ A: \n", Apinv @ A)

print("Using singular value decomposition")
u, s, vh = np.linalg.svd(A)
print("np.sqrt(5) * u:\n", np.sqrt(5) * u)
print("s:\n", s)
print("np.sqrt(45) * vh:\n", np.sqrt(45)*vh)
