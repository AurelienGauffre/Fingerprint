import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from pylab import meshgrid


l= np.loadtxt('results/data_affich_opti_x.txt')
x = l[:,0]
y = l[:,1]
plt.plot(x,y)
plt.savefig('opti_tx')

fig = plt.figure()
ax = fig.gca(projection='3d')
l= np.loadtxt('results/data_affich_opti_xy.txt')
x = l[:,0]
y = l[:,1]
z = l[:,2]
ax.plot(x,y,z)
plt.show()
