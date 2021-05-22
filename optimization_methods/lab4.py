import matplotlib.pyplot as plt
import numpy as np


def func1(x):
    value = 2.0 * x**2 + 3.0 * x + 1
    return value


def exhaustive_search(functionToMinimize, a, b, n):
    x1 = a
    delta_x = (b - a) / n
    x2 = x1 + delta_x
    x3 = x2 + delta_x
    while x3 <= b:
        f1 = functionToMinimize(x1)
        f2 = functionToMinimize(x2)
        f3 = functionToMinimize(x3)
        if f1 >= f2 and f2 <= f3:
            return x2
        else:
            x1 = x2
            x2 = x3
            x3 = x2 + delta_x
    if b < a:
        return b
    else:
        return a



x = np.linspace(-10, 10, 101)
y = func1(x)
plt.plot(x, y)
plt.show()

a = -10
b = 10
n = 100

xmin = exhaustive_search(func1,a,b,n)
print("Minimum: xmin = {:.4f} f(min) = {:.4f}".format(xmin, func1(xmin)))


x0 = np.array([1.3, 0.7, 0.8, 1.9, 1.2])
print(x0)
print(x0[1:])
print(x0[:-1])
