import numpy as np
import matplotlib.pyplot as plt
#from sklearn.linear_model import LinearRegression

# Gradient descent
# The purpose of this example to play with the algorithms
# shown during the lecture.
# Here we work with the "Gradient Descent" and
# check the influence of the learning rate eta
# on the values for theta.

X = 2 * np.random.rand(100, 1)
y = 4 + 3 * X + np.random.randn(100, 1)

X_b = np.c_[np.ones((100, 1)), X]  # add x0 = 1 to each instance

eta = 0.01  # learning rate
n_iterations = 100
m = 100

theta = np.random.randn(2, 1)

for iteration in range(n_iterations):
    gradients = 2/m * X_b.T.dot(X_b.dot(theta) - y)
    theta = theta - eta * gradients
    print("iteration: ", iteration, " theta: ", theta)

