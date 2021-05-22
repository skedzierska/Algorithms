import numpy as np
import matplotlib.pylab as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import sklearn.linear_model as lm
from numpy.linalg import norm


def line(a, b, x):
    return a*x+b


def sign_(x,y,a,b):
    if y > a*x+b:
        return 1
    else:
        return -1


def logf(t):
    return 1./(1 + np.exp( -t ))


def get_label_bin_p(d0,d1,a,b,x_class,y_class0,y_class1):
    pref1 = np.array([-10,a*(-10)+b])
    pref2 = np.array([10,a*10 + b])
    count_0 = 0
    count_1 = 0
    for ic,xc in enumerate(x_class):
        p3_0 = np.array([xc,y_class0[ic]])
        p3_1 = np.array([xc,y_class1[ic]])
        dc0 = norm(np.cross(pref2-pref1, pref1-p3_0))/norm(pref2-pref1)
        dc1 = norm(np.cross(pref2-pref1, pref1-p3_1))/norm(pref2-pref1)
        dc0_s = sign_(xc,y_class0[ic],a,b)
        dc1_s = sign_(xc,y_class1[ic],a,b)
        dc0 = dc0 * dc0_s
        dc1 = dc1 * dc1_s
        if dc0<d1 and dc0>d0:
            count_0 += 1
        if dc1<d1 and dc1>d0:
            #print(p3_1,dc1,dc1_s)
            count_1 += 1
    return count_0,count_1



x = np.linspace(0, 10)
a = 2
b = 3
y = line(a, b, x)

size = 333
x_sample = np.linspace(0, 10, size)
y_sample = a * x_sample + b + np.random.normal(loc=0, scale=2, size=size)

plt.scatter(x_sample, y_sample, marker='o', alpha=0.6, c='r')
plt.plot(x, y, c='k', lw=2.)
plt.xlim(0, 10); plt.ylim(0, 30)
plt.xlabel('x'); plt.ylabel('y')
#plt.show()

#exit()
# -------------------------------


size = 1000
x_sample = np.linspace(0, 10, size)
x_class = np.linspace(0, 10, size)
y_class0 = np.array([r if r <= line(a, b, x) + 3 else -1 for x,r in zip(x_sample, 30 * np.random.uniform(size=size))])
y_class1 = np.array([r if r >= line(a, b, x) - 3 else -1 for x,r in zip(x_sample, 30 * np.random.uniform(size=size))])

plt.scatter(x_class[:len(y_class0)], y_class0, 	marker='o',alpha=0.6, c='r')
plt.scatter(x_class[:len(y_class1)], y_class1, 	marker='o',alpha=0.6, c='b')
plt.plot(x, y, c='k', lw=2.)
plt.xlim(0, 10); plt.ylim(0, 30)
plt.xlabel('x'); plt.ylabel('y')
#plt.show()


#exit()
# -------------------------------

fig = plt.figure(1, figsize=(9, 6))

plt.scatter(x_class,y_class0, marker='o',alpha=0.6, c='r')
plt.scatter(x_class,y_class1, marker='o',alpha=0.6, c='b')
plt.plot(x,y, c='k',lw=50.,alpha=0.3) # fat transparent line over opaque regression line
plt.plot(x,y, c='k',lw=2.,alpha=0.9) # regression line
plt.xlim(0,10)
plt.ylim(0,30)
plt.xlabel('x')
plt.ylabel('y')
plt.show()


#exit()
# -------------------------------



tsize = 40
t_sample = np.linspace(-10,9,tsize)
t_sample2 = t_sample + 1

p_0 = []
p_1 = []
for it,ts in enumerate(t_sample):
    c0,c1 = get_label_bin_p(ts,t_sample2[it],a,b,x_class,y_class0,y_class1)
    p_0.append(c0)
    p_1.append(c1)
p_0 = np.array(p_0)
p_1 = np.array(p_1)
p_1[:14] = 0
print(p_0)
print(p_1)

fig = plt.figure(1, figsize=(9, 6))

plt.plot(t_sample,p_0/(p_0+p_1), c='b',lw=2.)
plt.plot(t_sample,p_1/(p_0+p_1), c='r',lw=2.)
plt.xlabel('t')
plt.ylabel('p(t|x)')
plt.xlim(-9,9)
plt.ylim(0,1.01)
plt.show()

#exit()
# -------------------------------


fig = plt.figure(1, figsize=(9, 6))

t = np.linspace(-10,10,200)
plt.plot(t, logf(t), lw=3., c='r')
plt.plot(t, 1-logf(t), lw=3., c='b')
plt.xlabel('t')
plt.ylabel('p(t|x)')
#plt.show()

#exit()

fig = plt.figure(1, figsize=(9, 6))

t = np.linspace(-10, 10, 200)
plt.plot(t, logf(t), lw=3., c='g')
plt.xlabel('t')
plt.ylabel('logistic function(t)')
#plt.show()

#exit()
# -------------------------------


fig = plt.figure()
ax = fig.gca(projection='3d')


def logf_z(p, q, X, Y):
    return (1. / (1. + np.exp(-(p * X + q) + Y)))


X = np.arange(0, 10., 0.1)
Y = np.arange(0., 30., 0.1)
X, Y = np.meshgrid(X, Y)

# Z = 1-logf_z(2,3,X,Y)
Z = logf_z(2, 3, X, Y)

surf = ax.plot_surface(X, Y, Z, cmap=cm.coolwarm, rstride=16, cstride=3, alpha=0.5,
                       linewidth=0, antialiased=False)

ax.set_zlim(0., 1.0)
ax.zaxis.set_major_locator(LinearLocator(5))
ax.zaxis.set_major_formatter(FormatStrFormatter('%.02f'))

ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('logistic function(x,y)')

ax.xaxis.set_major_locator(LinearLocator(5))
ax.xaxis.set_major_formatter(FormatStrFormatter('%.00f'))
ax.yaxis.set_major_locator(LinearLocator(4))
ax.yaxis.set_major_formatter(FormatStrFormatter('%.00f'))

# Add a color bar which maps values to colors.
fig.colorbar(surf, shrink=0.64, aspect=20)
cset = ax.contourf(X, Y, Z, zdir='z', offset=0.001, cmap=cm.coolwarm)
ax.view_init(25, -151)
plt.show()

#exit()
# -------------------------------

logr = lm.LogisticRegression()
# unfortunately a bit complex to construct X
x1 = np.append(x_class[y_class0>=0], x_class[y_class1>=0])
x2 = np.append(y_class0[y_class0>=0], y_class1[y_class1>=0])
X = np.array([x1, x2]).T

# 0 is for class0, 1 for class1
y = np.append(np.zeros(len(y_class0[y_class0>=0])), np.ones(len(y_class1[y_class1>=0])))

# now do the logistic regression
logr.fit(X, y)

print("score from logistic regression: ", logr.score(X, y))

