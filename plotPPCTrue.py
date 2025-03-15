import matplotlib.pyplot as plt
import matplotlib as mpl
import pandas as pd
import numpy as np
pd.options.display.float_format = '{:.6f}'.format
mpl.rcParams.update({'font.size': 10})
column_width = 3.5

def set_axes_equal(ax):
    # Obtém os limites de cada eixo
    x_limits = ax.get_xlim3d()
    y_limits = ax.get_ylim3d()

    # Calcula o intervalo máximo em cada direção
    x_range = abs(x_limits[1] - x_limits[0])
    y_range = abs(y_limits[1] - y_limits[0])
    max_range = max(x_range, y_range)

    # Calcula os centros de cada eixo
    x_middle = np.mean(x_limits)
    y_middle = np.mean(y_limits)

    # Define os novos limites para os eixos com base no intervalo máximo
    ax.set_xlim3d([x_middle - max_range/2, x_middle + max_range/2])
    ax.set_ylim3d([y_middle - max_range/2, y_middle + max_range/2])

dataTrue = pd.read_csv("cmake-build-debug/trueStatePPC.csv", sep=";")

# Plot True States
############################################################
plt.figure()
plt.subplot(3,1,1)
plt.title("Position x Time")
plt.plot(dataTrue['t'],dataTrue['p1'],label='True')
plt.legend()
plt.xlabel("Time [s]")
plt.grid()

plt.subplot(3,1,2)
plt.plot(dataTrue['t'],dataTrue['p2'],label='True')
plt.legend()
plt.xlabel("Time [s]")
plt.grid()

plt.subplot(3,1,3)
plt.plot(dataTrue['t'],dataTrue['p3'],label='True')
plt.legend()
plt.xlabel("Time [s]")
plt.grid()
plt.show(block=False)
###############################################################
plt.figure()
plt.subplot(3,1,1)
plt.title("Linear Velocity x Time")
plt.plot(dataTrue['t'],dataTrue['v1'],label='True')
plt.legend()
plt.xlabel("Time [s]")
plt.grid()

plt.subplot(3,1,2)
plt.plot(dataTrue['t'],dataTrue['v2'],label='True')
plt.legend()
plt.xlabel("Time [s]")
plt.grid()

plt.subplot(3,1,3)
plt.plot(dataTrue['t'],dataTrue['v3'],label='True')
plt.legend()
plt.xlabel("Time [s]")
plt.grid()
plt.show(block=False)
################################################################
plt.figure()
plt.subplot(4,1,1)
plt.title("Quaternion x Time")
plt.plot(dataTrue['t'],dataTrue['q1'],label='True')
plt.legend()
plt.xlabel("Time [s]")
plt.grid()

plt.subplot(4,1,2)
plt.plot(dataTrue['t'],dataTrue['q2'],label='True')
plt.legend()
plt.xlabel("Time [s]")
plt.grid()

plt.subplot(4,1,3)
plt.plot(dataTrue['t'],dataTrue['q3'],label='True')
plt.legend()
plt.xlabel("Time [s]")
plt.grid()
plt.show(block=False)

plt.subplot(4,1,4)
plt.plot(dataTrue['t'],dataTrue['q4'],label='True')
plt.legend()
plt.xlabel("Time [s]")
plt.grid()
plt.show(block=False)
##################################################################
plt.figure()
plt.subplot(3,1,1)
plt.title("Acceleration Bias x Time")
plt.plot(dataTrue['t'],dataTrue['ab1'],label='True')
plt.legend()
plt.xlabel("Time [s]")
plt.grid()

plt.subplot(3,1,2)
plt.plot(dataTrue['t'],dataTrue['ab2'],label='True')
plt.legend()
plt.xlabel("Time [s]")
plt.grid()

plt.subplot(3,1,3)
plt.plot(dataTrue['t'],dataTrue['ab3'],label='True')
plt.legend()
plt.xlabel("Time [s]")
plt.grid()
plt.show(block=False)
##################################################################
plt.figure()
plt.subplot(3,1,1)
plt.title("Acceleration Bias x Time")
plt.plot(dataTrue['t'],dataTrue['wb1'],label='True')
plt.legend()
plt.xlabel("Time [s]")
plt.grid()

plt.subplot(3,1,2)
plt.plot(dataTrue['t'],dataTrue['wb2'],label='True')
plt.legend()
plt.xlabel("Time [s]")
plt.grid()

plt.subplot(3,1,3)
plt.plot(dataTrue['t'],dataTrue['wb3'],label='True')
plt.legend()
plt.xlabel("Time [s]")
plt.grid()
plt.show(block=False)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot(dataTrue['p1'],dataTrue['p2'],dataTrue['p3'])
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
plt.title("Trajetory")
set_axes_equal(ax)
plt.show()
input("Pressione Enter para fechar os plots e encerrar...")

