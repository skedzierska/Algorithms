import numpy as np
import matplotlib.pyplot as plt

N = 129         #wielkość automatu komórkowego
n_iter =N//2    #ilość iteracji

image = np.zeros ([n_iter, N], dtype = 'int') #inicjalizowanie kraty z pustymi komórkami
image[0, N//2] = 1      #centralny węzeł ustawiamy jako czarny

for i in range(1,n_iter):  #pętla iteracyjna
    for j in range(1,N-1):
        if image[i-1, j-1] == 1 and image [i-1,j] ==1 and image [i-1,j+1] ==0:
            image [i,j] = 1
        if image[i-1, j-1] == 1 and image [i-1,j] ==0 and image [i-1,j+1] ==0:
            image [i,j] = 1
        if image[i-1, j-1] == 0 and image [i-1,j] ==1 and image [i-1,j+1] ==1:
            image [i,j] = 1
        if image[i-1, j-1] == 0 and image [i-1,j] ==0 and image [i-1,j+1] ==1:
            image [i,j] = 1

plt.imshow(image, interpolation = "nearest")
plt.show()
