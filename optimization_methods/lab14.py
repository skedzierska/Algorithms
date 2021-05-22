import numpy as np
import matplotlib.pylab as plt
from sklearn.datasets import load_iris
from sklearn.svm import SVC

iris = load_iris()
X = iris.data
y = iris.target

model_linear = SVC(kernel='linear', C=1, gamma=1)
model_linear.fit(X, y)
print("SVC - kernel = linear")
print("score: ", model_linear.score(X, y))

model_rbf_C1 = SVC(kernel='rbf', C=1, gamma=1)
model_rbf_C1.fit(X, y)
print("SVC - kernel = rbf, C=1")
print("score", model_rbf_C1.score(X, y))

model_rbf_C1000 = SVC(kernel='rbf', C=1000, gamma=1)
model_rbf_C1000.fit(X, y)
print("SVC - kernel = rbf, C=1000")
print("score", model_rbf_C1000.score(X, y))

#exit()
# --- do a few plots

svc = model_rbf_C1

n_classes = 3
colors = 'bwr' #['b','y','r']
CMAP = colors #plt.cm.rainbow
plot_step = 0.01

fig = plt.figure(1, figsize=(18, 9))

for pairidx, pair in enumerate([[0, 1], [0, 2], [0, 3],
                                [1, 2], [1, 3], [2, 3]]):
    X = iris.data[:, pair]
    y = iris.target

    clf = svc.fit(X, y)

    plt.subplot(2, 3, pairidx + 1)

    x_min, x_max = X[:, 0].min() - 1, X[:, 0].max() + 1
    y_min, y_max = X[:, 1].min() - 1, X[:, 1].max() + 1
    xx, yy = np.meshgrid(np.arange(x_min, x_max, plot_step),
                         np.arange(y_min, y_max, plot_step))

    Z = clf.predict(np.c_[xx.ravel(), yy.ravel()])
    Z = Z.reshape(xx.shape)
    cs = plt.contourf(xx, yy, Z, cmap=CMAP, alpha=0.5)

    plt.xlabel(iris.feature_names[pair[0]])
    plt.ylabel(iris.feature_names[pair[1]])
    plt.axis("tight")

    for i, color in zip(range(n_classes), colors):
        idx = np.where(y == i)
        plt.scatter(X[idx, 0], X[idx, 1], c=color, edgecolor='black', lw=2, label=iris.target_names[i],
                    cmap=CMAP)

    plt.axis("tight")

plt.legend(loc='upper left')
plt.show()
