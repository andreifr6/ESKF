import numpy as np
import pandas as pd
from scipy.spatial.transform import Rotation as R
import matplotlib.pyplot as plt
import seaborn as sns
pd.options.display.float_format = '{:.6f}'.format
sns.set_theme(style="darkgrid")
sns.color_palette("rocket")
# Config plots

# Carrega os dados
dataTrue = pd.read_csv("cmake-build-debug/trueStatePPC.csv", sep=";")
dataState = pd.read_csv("cmake-build-debug/statePPC.csv", sep=";")

# Função para obter o conjugado do quaternion
def conjugado_quaternion(q):
    return np.array([q[0], -q[1], -q[2], -q[3]])

# Função para multiplicação de dois quaternions (assumindo scalar first)
def multiplica_quaternion(q1, q2):
    w1, x1, y1, z1 = q1
    w2, x2, y2, z2 = q2
    return np.array([
        w1*w2 - x1*x2 - y1*y2 - z1*z2,
        w1*x2 + x1*w2 + y1*z2 - z1*y2,
        w1*y2 - x1*z2 + y1*w2 + z1*x2,
        w1*z2 + x1*y2 - y1*x2 + z1*w2
    ])

# Função para calcular o erro angular em graus
def erro_angular(q_true, q_est):
    # Calcula qt * conjugado(qe)
    qt_qe_conj = multiplica_quaternion(q_true, conjugado_quaternion(q_est))

    # Converte o resultado para ângulos de Euler
    rot = R.from_quat([qt_qe_conj[1], qt_qe_conj[2], qt_qe_conj[3], qt_qe_conj[0]])  # scipy usa x, y, z, w
    euler = rot.as_euler('xyz',degrees=True)  # Converte para ângulos de Euler em rad

    # Calcula o erro angular como a magnitude do vetor de rotação em Euler
    angular_error = np.linalg.norm(euler)
    return euler

# Calcula o erro angular para cada linha
erros_angulares_x = []
erros_angulares_y = []
erros_angulares_z = []
for i in range(len(dataTrue)):
    q_true = dataTrue.loc[i, ['q1', 'q2', 'q3', 'q4']].values
    q_est = dataState.loc[i, ['q1', 'q2', 'q3', 'q4']].values
    erro = erro_angular(q_true, q_est)
    erros_angulares_x.append(erro[0])
    erros_angulares_y.append(erro[1])
    erros_angulares_z.append(erro[2])

plt.figure()
plt.subplot(3,1,1)
plt.title("Angle True Error [deg] x Time")
plt.plot(dataTrue['t'],erros_angulares_x,label='50 ms delay')
plt.legend()
plt.xlabel("Time [s]")
plt.ylabel(r"$\delta \theta_x$")

plt.subplot(3,1,2)
plt.plot(dataTrue['t'],erros_angulares_y,label='50 ms delay')
plt.legend()
plt.xlabel("Time [s]")
plt.ylabel(r"$\delta  \theta_y$")

plt.subplot(3,1,3)
plt.plot(dataTrue['t'],erros_angulares_z,label='50 ms delay',)
plt.legend()
plt.xlabel("Time [s]")
plt.ylabel(r"$\delta \theta_z$")
plt.show(block=False)

mse_total = np.sqrt(np.mean((np.array(erros_angulares_x))**2 + (np.array(erros_angulares_y))**2 + (np.array(erros_angulares_z))**2))
print("Erro Quadrático Médio Total (Angular Velocity Bias):", mse_total)

input("Pressione Enter para fechar os plots e encerrar...")