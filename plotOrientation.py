import numpy as np
from scipy.spatial.transform import Rotation as R
import matplotlib.pyplot as plt
import pandas as pd
from mpl_toolkits.mplot3d import Axes3D

dataTrue = pd.read_csv("cmake-build-debug/trueStatePPC.csv", sep=";")
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
# Configurações adicionais do gráfico
ax.set_xlim([-1, 1])
ax.set_ylim([-1, 1])
ax.set_zlim([-1, 1])
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

for i in range(len(dataTrue)):
    w = dataTrue['q1'][i]
    x = dataTrue['q2'][i]
    y = dataTrue['q3'][i]
    z = dataTrue['q4'][i]

    # Defina o quaternion (w, x, y, z)
    quaternion = [w, x, y, z]  # Substitua pelos valores do seu quaternion

    # Converta o quaternion em uma matriz de rotação
    rotation = R.from_quat(quaternion)

    # Aplica a rotação ao vetor de base [1, 0, 0] para obter a direção
    direction = rotation.apply([1, 0, 0])

    # Define o ponto inicial e final do vetor
    origin = np.array([0, 0, 0])  # Origem
    ax.quiver(origin[0], origin[1], origin[2], direction[0], direction[1], direction[2], color='r', length=1.0)

plt.show()