import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import seaborn as sns
pd.options.display.float_format = '{:.6f}'.format
sns.set_theme(style="darkgrid")
sns.color_palette("rocket")
# Config plots

trueDecimation = 10;

# Import PPC data

dataTrue = pd.read_csv("cmake-build-debug/trueStatePPC.csv", sep=";")
dataError = pd.read_csv("cmake-build-debug/errorStatePPC.csv", sep=";")
dataState = pd.read_csv("cmake-build-debug/statePPC.csv", sep=";")
dataIMU = pd.read_csv("cmake-build-debug/IMUmeasPPC.csv", sep=";")
dataCAM = pd.read_csv("cmake-build-debug/CAMmeasPPC.csv", sep=";")
dataCov = pd.read_csv("cmake-build-debug/covariancePPC.csv",sep=';')

# Plot EKF Comparatives
# Plot positions

plt.figure()
plt.subplot(3,1,1)
plt.title("Position Error [m] x Time")
#plt.plot(dataError['t'],dataError['p1'],label='Error-state')
plt.plot(dataTrue['t'],dataTrue['p1']-dataState['p1'],label='True Error')
plt.legend()
plt.xlabel("Time [s]")
plt.ylabel(r"$p_x$")
#plt.grid()

plt.subplot(3,1,2)
#plt.plot(dataError['t'],dataError['p2'],label='Error-state')
plt.plot(dataTrue['t'],dataTrue['p2']-dataState['p2'],label='True Error')
plt.legend()
plt.xlabel("Time [s]")
plt.ylabel(r"$p_y$")
#plt.grid()

plt.subplot(3,1,3)
#plt.plot(dataError['t'],dataError['p3'],label='Error-state')
plt.plot(dataTrue['t'],dataTrue['p3']-dataState['p3'],label='True Error')
plt.legend()
plt.xlabel("Time [s]")
plt.ylabel(r"$p_z$")
#plt.grid()
plt.show(block=False)

mse_total = np.mean((dataTrue['p1']-dataState['p1'])**2 + (dataTrue['p2']-dataState['p2'])**2 + (dataTrue['p3']-dataState['p3'])**2)
print("Erro Quadrático Médio Total (Position):", mse_total)

#Plot Velocity
plt.figure()
plt.subplot(3,1,1)
plt.title("Linear Velocity Error [m/s] x Time")
#plt.plot(dataError['t'],dataError['v1'],label='Error-state')
plt.plot(dataTrue['t'],dataTrue['v1']-dataState['v1'],label='True Error')
plt.legend()
plt.xlabel("Time [s]")
plt.ylabel(r"$v_x$")
#plt.grid()

plt.subplot(3,1,2)
#plt.plot(dataError['t'],dataError['v2'],label='Error-state')
plt.plot(dataTrue['t'],dataTrue['v2']-dataState['v2'],label='True Error')
plt.legend()
plt.xlabel("Time [s]")
plt.ylabel(r"$v_y$")
#plt.grid()

plt.subplot(3,1,3)
#plt.plot(dataError['t'],dataError['v3'],label='Error-state')
plt.plot(dataTrue['t'],dataTrue['v3']-dataState['v3'],label='True Error')
plt.legend()
plt.xlabel("Time [s]")
plt.ylabel(r"$v_z$")
#plt.grid()
plt.show(block=False)

mse_total = np.mean((dataTrue['v1']-dataState['v1'])**2 + (dataTrue['v2']-dataState['v2'])**2 + (dataTrue['v3']-dataState['v3'])**2)
print("Erro Quadrático Médio Total (Velocity):", mse_total)

# Plot Orientation
plt.figure()
plt.subplot(4,1,1)
plt.title("CAM quaternion x Time")
plt.plot(dataCAM['t'],dataCAM['q1'],linestyle=':',label="Meas")
plt.plot(dataState['t'],dataState['q1'],label='State')
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['q1'][::trueDecimation],linestyle='--',label='True')
#plt.fill_between(dataCov['t'], dataState['q1'] - np.sqrt(dataCov['P6']), dataState['q1'] + np.sqrt(dataCov['P6']), color='b', alpha=0.2, label="STD")
plt.legend()
plt.xlabel("Time [s]")
plt.ylabel(r"$q_\omega$")
#plt.grid()

plt.subplot(4,1,2)
plt.plot(dataCAM['t'],dataCAM['q2'],linestyle=':',label="Meas")
plt.plot(dataState['t'],dataState['q2'],label='State')
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['q2'][::trueDecimation],linestyle='--',label='True')
#plt.fill_between(dataCov['t'], dataState['q2'] - np.sqrt(dataCov['P7']), dataState['q2'] + np.sqrt(dataCov['P7']), color='b', alpha=0.2, label="STD")
plt.legend()
plt.xlabel("Time [s]")
plt.ylabel(r"$q_x$")
#plt.grid()

plt.subplot(4,1,3)
plt.plot(dataCAM['t'],dataCAM['q3'],linestyle=':',label="Meas")
plt.plot(dataState['t'],dataState['q3'],label='State')
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['q3'][::trueDecimation],linestyle='--',label='True')
#plt.fill_between(dataCov['t'], dataState['q3'] - np.sqrt(dataCov['P8']), dataState['q3'] + np.sqrt(dataCov['P8']), color='b', alpha=0.2, label="STD")
plt.legend()
plt.xlabel("Time [s]")
plt.ylabel(r"$q_y$")
#plt.grid()

plt.subplot(4,1,4)
plt.plot(dataCAM['t'],dataCAM['q4'],linestyle=':',label="Meas")
plt.plot(dataState['t'],dataState['q4'],label='State')
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['q4'][::trueDecimation],linestyle='--',label='True')
#plt.fill_between(dataCov['t'], dataState['q4'] - np.sqrt(dataCov['P9']), dataState['q4'] + np.sqrt(dataCov['P9']), color='b', alpha=0.2, label="STD")
plt.xlabel("Time [s]")
plt.ylabel(r"$q_z$")
plt.legend()
#plt.grid()
plt.show(block=False)

# Plot Bias
plt.figure()
plt.subplot(3,1,1)
plt.title("Acceleration Bias [$m/s^2$] x Time")
#plt.plot(dataError['t'],dataError['ab1'],label='Error-state')
plt.plot(dataTrue['t'],dataTrue['ab1']-dataState['ab1'],label='True Error')
plt.legend()
plt.xlabel("Time [s]")
plt.ylabel(r"$a_{b,x}$")
#plt.grid()

plt.subplot(3,1,2)
#plt.plot(dataError['t'],dataError['ab2'],label='Error-state')
plt.plot(dataTrue['t'],dataTrue['ab2']-dataState['ab2'],label='True Error')
plt.legend()
plt.xlabel("Time [s]")
plt.ylabel(r"$a_{b,y}$")
#plt.grid()

plt.subplot(3,1,3)
#plt.plot(dataError['t'],dataError['ab3'],label='Error-state')
plt.plot(dataTrue['t'],dataTrue['ab3']-dataState['ab3'],label='True Error')
plt.legend()
plt.xlabel("Time [s]")
plt.ylabel(r"$a_{b,z}$")
#plt.grid()
plt.show(block=False)

mse_total = np.mean((dataTrue['ab1']-dataState['ab1'])**2 + (dataTrue['ab2']-dataState['ab2'])**2 + (dataTrue['ab3']-dataState['ab3'])**2)
print("Erro Quadrático Médio Total (Linear Acc Bias):", mse_total)

plt.figure()
plt.subplot(3,1,1)
plt.title("Angular Velocity Bias [rad/s] x Time")
#plt.plot(dataError['t'],dataError['wb1'],label='Error-state')
plt.plot(dataTrue['t'],dataTrue['wb1']-dataState['wb1'],label='True Error')
plt.legend()
plt.xlabel("Time [s]")
plt.ylabel(r"$\omega_{b,x}$")
#plt.grid()

plt.subplot(3,1,2)
#plt.plot(dataError['t'],dataError['wb2'],label='Error-state')
plt.plot(dataTrue['t'],dataTrue['wb2']-dataState['wb2'],label='True Error')
plt.legend()
plt.xlabel("Time [s]")
plt.ylabel(r"$\omega_{b,y}$")
#plt.grid()

plt.subplot(3,1,3)
#plt.plot(dataError['t'],dataError['wb3'],label='Error-state')
plt.plot(dataTrue['t'],dataTrue['wb3']-dataState['wb3'],label='True Error')
plt.legend()
plt.xlabel("Time [s]")
plt.ylabel(r"$\omega_{b,z}$")
#plt.grid()
plt.show(block=False)

mse_total = np.mean((dataTrue['wb1']-dataState['wb1'])**2 + (dataTrue['wb2']-dataState['wb2'])**2 + (dataTrue['wb3']-dataState['wb3'])**2)
print("Erro Quadrático Médio Total (Angular Velocity Bias):", mse_total)

input("Pressione Enter para fechar os plots e encerrar...")

