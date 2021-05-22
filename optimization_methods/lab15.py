import numpy as np
from sklearn.datasets import make_blobs
import matplotlib.pylab as plt
from sklearn.tree import DecisionTreeClassifier

RNDST = np.random.seed(52)
CMAP = 'bwr'
fig = plt.figure(1, figsize=(9, 6))

X, y = make_blobs(n_samples=200, centers=2, random_state=RNDST, cluster_std=5.)
plt.scatter(X[:, 0], X[:, 1], s=80, c=y, cmap=CMAP)

plt.xlabel('x')
plt.ylabel('y')
plt.show()

tree = DecisionTreeClassifier()
tree.fit(X, y)
print("DecisionTree - score: ", tree.score(X, y))

# exit()
# -----------

fig = plt.figure(1, figsize=(9, 6))
ax = plt.gca()

ax.scatter(X[:, 0], X[:, 1], c=y, s=80, cmap=CMAP, clim=(y.min(), y.max()), zorder=3)
ax.axis('tight')
xlim = ax.get_xlim()
ylim = ax.get_ylim()

xx, yy = np.meshgrid(np.linspace(*xlim, num=200), np.linspace(*ylim, num=200))
Z = tree.predict(np.c_[xx.ravel(), yy.ravel()]).reshape(xx.shape)
n_classes = len(np.unique(y))
contours = ax.contourf(xx, yy, Z, alpha=0.7,
                       levels=np.arange(n_classes + 1) - 0.5,
                       cmap=CMAP, clim=(y.min(), y.max()),
                       zorder=1)

ax.set(xlim=xlim, ylim=ylim)
plt.xlabel('x')
plt.ylabel('y')
plt.show()

# exit()
# ----------------------
# construct the tree

fig = plt.figure(1, figsize=(9, 6))
ax = plt.gca()

def textbox(ax, x, y, t, size=10, fc='w',ec='k', bstyle='round4', **kwargs):
    ax.text(x, y, t, ha='center', va='center', size=size,
            bbox=dict(boxstyle=bstyle, pad=0.5, ec=ec, fc=fc), **kwargs)

slev0 = 12
slev1 = 10
slev2 = 8
slev3 = 6

textbox(ax, 1.2, 0.9, "Level 1", slev1, alpha=0.99,color='k',fc='orange',bstyle='larrow')
textbox(ax, 1.2, 0.6, "Level 2", slev1, alpha=0.99,color='k',fc='orange',bstyle='larrow')
textbox(ax, 1.2, 0.3, "Level 3", slev1, alpha=0.99,color='k',fc='orange',bstyle='larrow')

textbox(ax, 0.5, 0.9, "x > 2 ?", slev0)

textbox(ax, 0.3, 0.6, "y > 0 ?", slev1)
textbox(ax, 0.7, 0.6, "y > -8 ?", slev1)

textbox(ax, 0.12, 0.3, "x > 4 ?", slev2)
#textbox(ax, 0.38, 0.3, "x > 4 ?", slev2)
textbox(ax, 0.62, 0.3, "y > -6 ?", slev2)
textbox(ax, 0.88, 0.3, "y > -6 ?", slev2)

textbox(ax, 0.4, 0.75, "true", slev0, alpha=0.99,color='g')
textbox(ax, 0.6, 0.75, "false", slev0, alpha=0.99,color='m')

textbox(ax, 0.21, 0.45, "true", slev1, alpha=0.99,color='g')
textbox(ax, 0.34, 0.45, "false", slev1, alpha=0.99,color='m')
textbox(ax, 0.66, 0.45, "true", slev1, alpha=0.99,color='g')
textbox(ax, 0.79, 0.45, "false", slev1, alpha=0.99,color='m')

textbox(ax, 0.06, 0.15, "true", slev2, alpha=0.99,color='g')
textbox(ax, 0.16, 0.15, "false", slev2, alpha=0.99,color='m')
#textbox(ax, 0.34, 0.15, "true", slev2, alpha=0.99,color='g')
#textbox(ax, 0.43, 0.15, "false", slev2, alpha=0.99,color='m')
textbox(ax, 0.57, 0.15, "true", slev2, alpha=0.99,color='g')
textbox(ax, 0.66, 0.15, "false", slev2, alpha=0.99,color='m')
textbox(ax, 0.84, 0.15, "true", slev2, alpha=0.99,color='g')
textbox(ax, 0.94, 0.15, "false", slev2, alpha=0.99,color='m')

ax.plot([0.3, 0.5, 0.7], [0.6, 0.9, 0.6], '-k')
ax.plot([0.12, 0.3, 0.38], [0.3, 0.6, 0.3], '-k')
ax.plot([0.62, 0.7, 0.88], [0.3, 0.6, 0.3], '-k')
ax.plot([0.0, 0.12, 0.20], [0.0, 0.3, 0.0], '-k')
#ax.plot([0.32, 0.38, 0.44], [0.0, 0.3, 0.0], '-k')
ax.plot([0.56, 0.62, 0.68], [0.0, 0.3, 0.0], '-k')
ax.plot([0.8, 0.88, 1.0], [0.0, 0.3, 0.0], '-k')
ax.axis([0, 1, 0, 1])

textbox(ax, .0, 0., "class1", slev2, alpha=0.99,color='w',fc='b',bstyle='square')
textbox(ax, .20, 0., "class2", slev2, alpha=0.99,color='w',fc='r',bstyle='square')
#textbox(ax, .32, 0., "class2", slev2, alpha=0.99,color='w',fc='r',bstyle='square')
#textbox(ax, .44, 0., "class1", slev2, alpha=0.99,color='w',fc='b',bstyle='square')
textbox(ax, 0.38, 0.3, "class1", slev2, alpha=0.99,color='w',fc='b',bstyle='square')
textbox(ax, .56, 0., "class1", slev2, alpha=0.99,color='w',fc='b',bstyle='square')
textbox(ax, .68, 0., "class2", slev2, alpha=0.99,color='w',fc='r',bstyle='square')
textbox(ax, .8, 0., "class2", slev2, alpha=0.99,color='w',fc='r',bstyle='square')
textbox(ax, 1., 0., "class1", slev2, alpha=0.99,color='w',fc='b',bstyle='square')

ax.axis('off')
plt.show()

# exit()
# --------------------------------
