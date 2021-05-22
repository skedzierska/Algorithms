import pandas as pd
import seaborn as sns
import numpy as np
import matplotlib.pyplot as plt
from sklearn import datasets
import sklearn.linear_model as lm




iris = datasets.load_iris()
#print(iris)

df = pd.DataFrame(data=np.c_[iris['data'], iris['target']],
                  columns=iris['feature_names'] + ['target'])
df.columns = ['sepal length', 'sepal width',
              'petal length', 'petal width', 'class']
#print(df.head())
#print(df.tail())

print("count:")
print(df.count())
print("describe:")
print(df.describe())

print("group by / describe:")
print(df.groupby('class').describe())

df.hist(figsize=(15, 15))
plt.show()

#exit()

sns.jointplot(df['sepal length'], df['petal length'])
plt.show()

#exit()

# https://en.wikipedia.org/wiki/Pearson_correlation_coefficient
corrmat = df.corr()
sns.heatmap(corrmat, annot=True)
plt.show()

#exit()

df.boxplot()
plt.show


df.groupby('class').boxplot()
plt.show

df.groupby('class').hist()
plt.show()
