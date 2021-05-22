import numpy as np
import matplotlib.pylab as plt
from sklearn.datasets._samples_generator import make_moons
from sklearn.svm import SVC

np.random.seed(7429)

x = np.linspace(0, 10)
xlim = [0, 10]
ylim = [0, 30]

X, y = make_moons(100, noise=0.08, shuffle=True)

plt.scatter(X[y==1][:,0],X[y==1][:,1], s=150, marker='o',alpha=0.6, c='r')
plt.scatter(X[y==0][:,0],X[y==0][:,1], s=150, marker='o',alpha=0.6, c='b')

plt.show()

#exit()
# ------------------------------------------------------

model4 = SVC(kernel='rbf', C=1E6, gamma=1.)
model4.fit(X, y)
print(model4.score(X,y))

fig = plt.figure(1, figsize=(9, 6))

plt.scatter(X[y==1][:,0],X[y==1][:,1], s=150, marker='o',alpha=0.6, c='r')
plt.scatter(X[y==0][:,0],X[y==0][:,1], s=150, marker='o',alpha=0.6, c='b')

plt.xlabel('x'); plt.ylabel('y')

# model
model1 = SVC(kernel='rbf', C=1E6, gamma=1.)
model1.fit(X, y)

NBINS = 25
xg = np.linspace(-1, 2, NBINS)
yg = np.linspace(-1, 2, NBINS)
Yg, Xg = np.meshgrid(yg, xg)
xy = np.vstack([Xg.ravel(), Yg.ravel()]).T
P1 = model1.decision_function(xy).reshape(Xg.shape)

# decision boundary and margins
cont = plt.contour(Xg, Yg, P1, colors='k',
                   levels=[-1, 0, 1], alpha=0.7,
                   linestyles=['--', '-', '--'])
plt.setp(cont.collections,lw=2)
# support vectors
plt.scatter(model1.support_vectors_[:, 0],
            model1.support_vectors_[:, 1],
            s=400,
            facecolors='grey',
            alpha=0.39)
plt.show()

# exit()
# ------------------------------------------------------
# over-fitting

fig = plt.figure(1, figsize=(9, 6))

plt.scatter(X[y==1][:,0],X[y==1][:,1], s=150, marker='o',alpha=0.6, c='r')
plt.scatter(X[y==0][:,0],X[y==0][:,1], s=150, marker='o',alpha=0.6, c='b')

plt.xlabel('x')
plt.ylabel('y')

# model
model1 = SVC(kernel='rbf', C=1E6, gamma=100)
model1.fit(X, y)

NBINS = 25
xg = np.linspace(-1, 2, NBINS)
yg = np.linspace(-1, 2, NBINS)
Yg, Xg = np.meshgrid(yg, xg)
xy = np.vstack([Xg.ravel(), Yg.ravel()]).T
P1 = model1.decision_function(xy).reshape(Xg.shape)

# decision boundary and margins
cont = plt.contour(Xg, Yg, P1, colors='k',
                   levels=[-1,0,1], alpha=0.7,
                   linestyles=['--','-','--'])
plt.setp(cont.collections,lw=2)
# support vectors
plt.scatter(model1.support_vectors_[:, 0],
            model1.support_vectors_[:, 1],
            s=400,
            facecolors='grey',
            alpha=0.39)
plt.show()

# exit()
# ------------------------------------------------------
# under-fitting

fig = plt.figure(1, figsize=(9, 6))

plt.scatter(X[y==1][:,0],X[y==1][:,1],
            s=150, marker='o',alpha=0.6, c='r')
plt.scatter(X[y==0][:,0],X[y==0][:,1],
            s=150, marker='o',alpha=0.6, c='b')

# model

model1 = SVC(kernel='rbf', C=1E6, gamma=0.001)
model1.fit(X, y)

NBINS = 25
xg = np.linspace(-1, 2, NBINS)
yg = np.linspace(-1, 2, NBINS)
Yg, Xg = np.meshgrid(yg, xg)
xy = np.vstack([Xg.ravel(), Yg.ravel()]).T
P1 = model1.decision_function(xy).reshape(Xg.shape)

# plot decision boundary and margins
cont = plt.contour(Xg, Yg, P1, colors='k',
                   levels=[-1, 0, 1], alpha=0.7,
                   linestyles =['--', '-', '--'])
plt.setp(cont.collections,lw=2)
# support vectors
plt.scatter(model1.support_vectors_[:, 0],
            model1.support_vectors_[:, 1],
            s=400, facecolors='grey',alpha=0.39);

plt.xlabel('x')
plt.ylabel('y')
plt.show()

exit()
# ------------------------------------------------------
