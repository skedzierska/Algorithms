import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression

# we create some random data
# generate some random numbers between 0 and 2
X = 2 * np.random.rand(1000, 1)
# calculate y-values and add some random noise
y = 4 + 3 * X + np.random.randn(1000, 1)

plt.scatter(X, y, color='black')
plt.show()

# Let's see the shape of this data
print("X.shape: ", X.shape)

# We need to include a columns with a bias to the data.
# This can be done with these lines.
X_b = np.c_[np.ones((1000, 1)), X]  # add x0 = 1 to each instance

# The shape of X_b: we see we have now one column more
print("X_b.shape: ", X_b.shape)
# Print X_b: we see that we have one column with values 1
print("X_b: \n", X_b)

# Let's do the fitting of the data using the "Normal equation"
theta_best = np.linalg.inv(X_b.T.dot(X_b)).dot(X_b.T).dot(y)
# Let's see the results:
# We see that we get two parameters for the fitting
# with the bias.
print("Results using the Normal Equation:")
print("theta_best: ", theta_best)
print("The ideal values would be: theta_0 = 4 and theta_1 = 3")

# Let's do the fitting, this time without the bias.
# This is just to show that we need the bias!
theta_best_nobias = np.linalg.inv(X.T.dot(X)).dot(X.T).dot(y)
# Without the bias we get only one parameter.
print("Warning: here are results without bias:")
print("theta_best without bias: ", theta_best_nobias)

# Now we are doing predictions with our fitted model
# step 1: define the X_new values
X_new = np.array([[0], [2]])
# step 2: include a column for the bias
X_new_b = np.c_[np.ones((2, 1)), X_new]
# step 3: calculate the prediction using the "Normal Equation"s
y_predict = X_new_b.dot(theta_best)
# print the predition
print("y_predict: ", y_predict)

# make a plot
# use the predicted points to draw a line
plt.plot(X_new, y_predict, "r-")
plt.plot(X, y, "b.")
plt.axis([0, 2, 0, 15])
plt.show()

# Do the fitting again - this time with
# sklearn using the LinearRegression model
lin_reg = LinearRegression()
# Please note: we do not need to add a bias!
lin_reg.fit(X, y)
# Show the results with the linear regression
print("Results with sklearn - LinearRegression:")
print("theta_0: ", lin_reg.intercept_)
print("other theta values: ", lin_reg.coef_)
print(lin_reg.predict(X_new))
