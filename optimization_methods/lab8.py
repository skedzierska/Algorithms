import numpy as np
import matplotlib.pyplot as plt

from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error
from sklearn.model_selection import train_test_split
from sklearn.pipeline import Pipeline

def plot_learning_curves(model, X, y):
    X_train, X_val, y_train, y_val = train_test_split(X, y, test_size=0.2)
    train_errors = []
    val_errors = []
    for mm in range(1, len(X_train)):
        model.fit(X_train[:mm], y_train[:mm])
        y_train_predict = model.predict(X_train[:mm])
        y_val_predict = model.predict(X_val)
        train_errors.append(mean_squared_error(y_train[:mm], y_train_predict))
        val_errors.append(mean_squared_error(y_val, y_val_predict))
    plt.plot(np.sqrt(train_errors), "r-+", linewidth=2, label='train')
    plt.plot(np.sqrt(val_errors), "b-", linewidth=3, label='val')
    plt.legend()
    plt.xlim(0, 80)
    plt.ylim(0, 5)
    plt.xlabel("Size of the training set")
    plt.ylabel("RMSE")
    plt.show()


m = 100
X = 6 * np.random.rand(m, 1) - 3
y = 2 + 1.0 * X + 6 * X**2 + 2 * np.random.randn(m, 1)


poly_features = PolynomialFeatures(degree=2, include_bias=False)
X_poly = poly_features.fit_transform(X)
print('X[0]: ', X[0])
print('X_poly[0]: ', X_poly[0])

lin_reg = LinearRegression()
lin_reg.fit(X_poly, y)
print("polynomial of degree 2: ", lin_reg.intercept_, lin_reg.coef_)
#plot_learning_curves(lin_reg, X_poly, y)

poly_features = PolynomialFeatures(degree=2, include_bias=False)
X_poly = poly_features.fit_transform(X)
lin_reg.fit(X_poly, y)
print("polynomial of degree 10: ", lin_reg.intercept_, lin_reg.coef_)
plot_learning_curves(lin_reg, X_poly, y)

polynomial_regression = Pipeline([
    ("poly_features", PolynomialFeatures(degree=10, include_bias=False)),
    ("lin_reg", LinearRegression())
])
#plot_learning_curves(polynomial_regression, X, y)
