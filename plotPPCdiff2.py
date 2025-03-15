import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import seaborn as sns
pd.options.display.float_format = '{:.6f}'.format
sns.set_context("notebook", font_scale=1)  # Aumenta o tamanho da fonte
sns.set_theme(style="darkgrid")
sns.color_palette("rocket")
plt.rcParams["lines.linewidth"] = 0.4
plt.rcParams["figure.subplot.left"] = 0.15
plt.rcParams["figure.subplot.right"] = 0.98
plt.rcParams["figure.subplot.hspace"] = 0.27
plt.rcParams["font.family"] = "Times New Roman"
plt.rcParams["font.size"] = 12
# Config plots

trueDecimation = 10;

legFreeDelay = "No delay"
legDelay = "50 ms delay"
legDelayComp = "Delay comp."

# Import PPC data

dataTrue = pd.read_csv("cmake-build-debug/DelayTest_FreeDelay_NoComp/trueStatePPC.csv", sep=";")
dataState = pd.read_csv("cmake-build-debug/DelayTest_FreeDelay_NoComp/statePPC.csv", sep=";")
dataTrueD = pd.read_csv("cmake-build-debug/DelayTest_Delay_NoComp/trueStatePPC.csv", sep=";")
dataStateD = pd.read_csv("cmake-build-debug/DelayTest_Delay_NoComp/statePPC.csv", sep=";")
dataTrueDC = pd.read_csv("cmake-build-debug/DelayTest_Delay_Comp/trueStatePPC.csv", sep=";")
dataStateDC = pd.read_csv("cmake-build-debug/DelayTest_Delay_Comp/statePPC.csv", sep=";")

#dataCAMDelay = pd.read_csv("cmake-build-debug/CAMmeasDelayPPC.csv", sep=";")

# Plot EKF Comparatives
# Plot positions

plt.figure()
plt.subplot(3,1,1)
plt.title("Position Error x Time")
#plt.plot(dataError['t'],dataError['p1'],label='Error-state')
plt.plot(dataTrueDC['t'],dataTrueDC['p1']-dataStateDC['p1'],"g--",label=legDelayComp)
plt.plot(dataTrue['t'],dataTrue['p1']-dataState['p1'],label=legFreeDelay)
plt.plot(dataTrueD['t'],dataTrueD['p1']-dataStateD['p1'],label=legDelay)
#plt.step(dataCAMDelay['t'],dataCAMDelay["p1"],linestyle='--',label="Meas.",where="post")
plt.legend(loc="upper right")
plt.xlabel("Time [s]")
plt.ylabel(r"$\delta p_x$ [m]")
#plt.grid()

plt.subplot(3,1,2)
#plt.plot(dataError['t'],dataError['p2'],label='Error-state')
plt.plot(dataTrueDC['t'],dataTrueDC['p2']-dataStateDC['p2'],"g--",label=legDelayComp)
plt.plot(dataTrue['t'],dataTrue['p2']-dataState['p2'],label=legFreeDelay)
plt.plot(dataTrueD['t'],dataTrueD['p2']-dataStateD['p2'],label=legDelay)
plt.legend(loc="upper right")
plt.xlabel("Time [s]")
plt.ylabel(r"$\delta  p_y$ [m]")
#plt.grid()

plt.subplot(3,1,3)
#plt.plot(dataError['t'],dataError['p3'],label='Error-state')
plt.plot(dataTrueDC['t'],dataTrueDC['p3']-dataStateDC['p3'],"g--",label=legDelayComp)
plt.plot(dataTrue['t'],dataTrue['p3']-dataState['p3'],label=legFreeDelay)
plt.plot(dataTrueD['t'],dataTrueD['p3']-dataStateD['p3'],label=legDelay)
plt.legend(loc="upper right")
plt.xlabel("Time [s]")
plt.ylabel(r"$\delta p_z$ [m]")
#plt.grid()
plt.show(block=False)

mse_total = np.sqrt(np.mean((dataTrue['p1']-dataState['p1'])**2 + (dataTrue['p2']-dataState['p2'])**2 + (dataTrue['p3']-dataState['p3'])**2))
print("Erro Quadrático Médio Total (Position):", mse_total)

mse_total = np.sqrt(np.mean((dataTrueD['p1']-dataStateD['p1'])**2 + (dataTrueD['p2']-dataStateD['p2'])**2 + (dataTrueD['p3']-dataStateD['p3'])**2))
print("Erro Quadrático Médio Total (Position D):", mse_total)

mse_total = np.sqrt(np.mean((dataTrueDC['p1']-dataStateDC['p1'])**2 + (dataTrueDC['p2']-dataStateDC['p2'])**2 + (dataTrueDC['p3']-dataStateDC['p3'])**2))
print("Erro Quadrático Médio Total (Position DC):", mse_total)

#Plot Velocity
plt.figure()
plt.subplot(3,1,1)
plt.title("Linear Velocity Error x Time")
#plt.plot(dataError['t'],dataError['v1'],label='Error-state')
plt.plot(dataTrueDC['t'],dataTrueDC['v1']-dataStateDC['v1'],"g--",label=legDelayComp)
plt.plot(dataTrue['t'],dataTrue['v1']-dataState['v1'],label=legFreeDelay)
plt.plot(dataTrueD['t'],dataTrueD['v1']-dataStateD['v1'],label=legDelay)
plt.legend(loc="upper right")
plt.xlabel("Time [s]")
plt.ylabel(r"$\delta v_x$ [m/s]")
#plt.grid()

plt.subplot(3,1,2)
#plt.plot(dataError['t'],dataError['v2'],label='Error-state')
plt.plot(dataTrueDC['t'],dataTrueDC['v2']-dataStateDC['v2'],"g--",label=legDelayComp)
plt.plot(dataTrue['t'],dataTrue['v2']-dataState['v2'],label=legFreeDelay)
plt.plot(dataTrueD['t'],dataTrueD['v2']-dataStateD['v2'],label=legDelay)
plt.legend(loc="upper right")
plt.xlabel("Time [s]")
plt.ylabel(r"$\delta v_y$ [m/s]")
#plt.grid()

plt.subplot(3,1,3)
#plt.plot(dataError['t'],dataError['v3'],label='Error-state')
plt.plot(dataTrueDC['t'],dataTrueDC['v3']-dataStateDC['v3'],"g--",label=legDelayComp)
plt.plot(dataTrue['t'],dataTrue['v3']-dataState['v3'],label=legFreeDelay)
plt.plot(dataTrueD['t'],dataTrueD['v3']-dataStateD['v3'],label=legDelay)
plt.legend(loc="upper right")
plt.xlabel("Time [s]")
plt.ylabel(r"$\delta v_z$ [m/s]")
#plt.grid()
plt.show(block=False)

mse_total = np.sqrt(np.mean((dataTrue['v1']-dataState['v1'])**2 + (dataTrue['v2']-dataState['v2'])**2 + (dataTrue['v3']-dataState['v3'])**2))
print("Erro Quadrático Médio Total (Velocity):", mse_total)

mse_total = np.sqrt(np.mean((dataTrueD['v1']-dataStateD['v1'])**2 + (dataTrueD['v2']-dataStateD['v2'])**2 + (dataTrueD['v3']-dataStateD['v3'])**2))
print("Erro Quadrático Médio Total (Velocity D):", mse_total)

mse_total = np.sqrt(np.mean((dataTrueDC['v1']-dataStateDC['v1'])**2 + (dataTrueDC['v2']-dataStateDC['v2'])**2 + (dataTrueDC['v3']-dataStateDC['v3'])**2))
print("Erro Quadrático Médio Total (Velocity DC):", mse_total)

# Plot Orientation
plt.figure()
plt.subplot(4,1,1)
plt.title("CAM quaternion x Time")
plt.plot(dataState['t'],dataState['q1'],label='State')
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['q1'][::trueDecimation],linestyle='--',label='True')
#plt.fill_between(dataCov['t'], dataState['q1'] - np.sqrt(dataCov['P6']), dataState['q1'] + np.sqrt(dataCov['P6']), color='b', alpha=0.2, label="STD")
plt.legend(loc="upper right")
plt.xlabel("Time [s]")
plt.ylabel(r"$q_\omega$")
#plt.grid()

plt.subplot(4,1,2)
plt.plot(dataState['t'],dataState['q2'],label='State')
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['q2'][::trueDecimation],linestyle='--',label='True')
#plt.fill_between(dataCov['t'], dataState['q2'] - np.sqrt(dataCov['P7']), dataState['q2'] + np.sqrt(dataCov['P7']), color='b', alpha=0.2, label="STD")
plt.legend(loc="upper right")
plt.xlabel("Time [s]")
plt.ylabel(r"$q_x$")
#plt.grid()

plt.subplot(4,1,3)
plt.plot(dataState['t'],dataState['q3'],label='State')
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['q3'][::trueDecimation],linestyle='--',label='True')
#plt.fill_between(dataCov['t'], dataState['q3'] - np.sqrt(dataCov['P8']), dataState['q3'] + np.sqrt(dataCov['P8']), color='b', alpha=0.2, label="STD")
plt.legend(loc="upper right")
plt.xlabel("Time [s]")
plt.ylabel(r"$q_y$")
#plt.grid()

plt.subplot(4,1,4)
plt.plot(dataState['t'],dataState['q4'],label='State')
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['q4'][::trueDecimation],linestyle='--',label='True')
#plt.fill_between(dataCov['t'], dataState['q4'] - np.sqrt(dataCov['P9']), dataState['q4'] + np.sqrt(dataCov['P9']), color='b', alpha=0.2, label="STD")
plt.xlabel("Time [s]")
plt.ylabel(r"$q_z$")
plt.legend(loc="upper right")
#plt.grid()
plt.show(block=False)

# Plot Bias
plt.figure()
plt.subplot(3,1,1)
plt.title("Linear Acceleration Bias Error x Time")
#plt.plot(dataError['t'],dataError['ab1'],label='Error-state')
plt.plot(dataTrueDC['t'],dataTrueDC['ab1']-dataStateDC['ab1'],"g--",label=legDelayComp)
plt.plot(dataTrue['t'],dataTrue['ab1']-dataState['ab1'],label=legFreeDelay)
plt.plot(dataTrueD['t'],dataTrueD['ab1']-dataStateD['ab1'],label=legDelay)
plt.legend(loc="upper right")
plt.ylim(-0.5,0.5)
plt.xlabel("Time [s]")
plt.ylabel(r"$\delta a_{b,x} [m/s^2]$")
#plt.grid()

plt.subplot(3,1,2)
#plt.plot(dataError['t'],dataError['ab2'],label='Error-state')
plt.plot(dataTrueDC['t'],dataTrueDC['ab2']-dataStateDC['ab2'],"g--",label=legDelayComp)
plt.plot(dataTrue['t'],dataTrue['ab2']-dataState['ab2'],label=legFreeDelay)
plt.plot(dataTrueD['t'],dataTrueD['ab2']-dataStateD['ab2'],label=legDelay)
plt.legend(loc="upper right")
plt.ylim(-0.5,0.5)
plt.xlabel("Time [s]")
plt.ylabel(r"$\delta a_{b,y} [m/s^2]$")
#plt.grid()

plt.subplot(3,1,3)
#plt.plot(dataError['t'],dataError['ab3'],label='Error-state')
plt.plot(dataTrueDC['t'],dataTrueDC['ab3']-dataStateDC['ab3'],"g--",label=legDelayComp)
plt.plot(dataTrue['t'],dataTrue['ab3']-dataState['ab3'],label=legFreeDelay)
plt.plot(dataTrueD['t'],dataTrueD['ab3']-dataStateD['ab3'],label=legDelay)
plt.legend(loc="upper right")
plt.ylim(-0.5,0.5)
plt.xlabel("Time [s]")
plt.ylabel(r"$\delta a_{b,z} [m/s^2]$")
#plt.grid()
plt.show(block=False)

mse_total = np.sqrt(np.mean((dataTrue['ab1']-dataState['ab1'])**2 + (dataTrue['ab2']-dataState['ab2'])**2 + (dataTrue['ab3']-dataState['ab3'])**2))
print("Erro Quadrático Médio Total (Linear Acc Bias):", mse_total)

mse_total = np.sqrt(np.mean((dataTrueD['ab1']-dataStateD['ab1'])**2 + (dataTrueD['ab2']-dataStateD['ab2'])**2 + (dataTrueD['ab3']-dataStateD['ab3'])**2))
print("Erro Quadrático Médio Total (Linear Acc Bias D):", mse_total)

mse_total = np.sqrt(np.mean((dataTrueDC['ab1']-dataStateDC['ab1'])**2 + (dataTrueDC['ab2']-dataStateDC['ab2'])**2 + (dataTrueDC['ab3']-dataStateDC['ab3'])**2))
print("Erro Quadrático Médio Total (Linear Acc Bias DC):", mse_total)

plt.figure()
plt.subplot(3,1,1)
plt.title("Angular Velocity Bias True Error [rad/s] x Time")
#plt.plot(dataError['t'],dataError['wb1'],label='Error-state')
plt.plot(dataTrue['t'],dataTrue['wb1']-dataState['wb1'],label=legFreeDelay)
plt.plot(dataTrueD['t'],dataTrueD['wb1']-dataStateD['wb1'],label=legDelay)
plt.plot(dataTrueDC['t'],dataTrueDC['wb1']-dataStateDC['wb1'],"g--",label=legDelayComp)
plt.legend(loc="upper right")
plt.ylim(-10.0e-3,10.0e-3)
plt.xlabel("Time [s]")
plt.ylabel(r"$\delta \omega_{b,x}$")
#plt.grid()

plt.subplot(3,1,2)
#plt.plot(dataError['t'],dataError['wb2'],label='Error-state')
plt.plot(dataTrue['t'],dataTrue['wb2']-dataState['wb2'],label=legFreeDelay)
plt.plot(dataTrueD['t'],dataTrueD['wb2']-dataStateD['wb2'],label=legDelay)
plt.plot(dataTrueDC['t'],dataTrueDC['wb2']-dataStateDC['wb2'],"g--",label=legDelayComp)
plt.legend(loc="upper right")
plt.ylim(-10.0e-3,10.0e-3)
plt.xlabel("Time [s]")
plt.ylabel(r"$\delta \omega_{b,y}$")
#plt.grid()

plt.subplot(3,1,3)
#plt.plot(dataError['t'],dataError['wb3'],label='Error-state')
plt.plot(dataTrue['t'],dataTrue['wb3']-dataState['wb3'],label=legFreeDelay)
plt.plot(dataTrueD['t'],dataTrueD['wb3']-dataStateD['wb3'],label=legDelay)
plt.plot(dataTrueDC['t'],dataTrueDC['wb3']-dataStateDC['wb3'],"g--",label=legDelayComp)
plt.legend(loc="upper right")
plt.ylim(-10.0e-3,10.0e-3)
plt.xlabel("Time [s]")
plt.ylabel(r"$\delta \omega_{b,z}$")
#plt.grid()
plt.show(block=False)

mse_total = np.sqrt(np.mean((dataTrue['wb1']-dataState['wb1'])**2 + (dataTrue['wb2']-dataState['wb2'])**2 + (dataTrue['wb3']-dataState['wb3'])**2))
print("Erro Quadrático Médio Total (Angular Velocity Bias):", mse_total)

mse_total = np.mean((dataTrueD['wb1']-dataStateD['wb1'])**2 + (dataTrueD['wb2']-dataStateD['wb2'])**2 + (dataTrueD['wb3']-dataStateD['wb3'])**2)
print("Erro Quadrático Médio Total (Angular Velocity Bias D):", mse_total)

mse_total = np.mean((dataTrueDC['wb1']-dataStateDC['wb1'])**2 + (dataTrueDC['wb2']-dataStateDC['wb2'])**2 + (dataTrueDC['wb3']-dataStateDC['wb3'])**2)
print("Erro Quadrático Médio Total (Angular Velocity Bias DC):", mse_total)

input("Pressione Enter para fechar os plots e encerrar...")

