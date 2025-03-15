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
legNom = 'Nom. State'
legTrue = 'True'

# Import PPC data

dataTrue = pd.read_csv("cmake-build-debug/DelayTest_Delay_NoComp/trueStatePPC.csv", sep=";")
dataError = pd.read_csv("cmake-build-debug/DelayTest_Delay_NoComp/errorStatePPC.csv", sep=";")
dataState = pd.read_csv("cmake-build-debug/DelayTest_Delay_NoComp/statePPC.csv", sep=";")
dataErrorDelay = pd.read_csv("cmake-build-debug/DelayTest_Delay_NoComp/errorStateDelayPPC.csv", sep=";")
dataStateDelay = pd.read_csv("cmake-build-debug/DelayTest_Delay_NoComp/stateDelayPPC.csv", sep=";")
dataIMU = pd.read_csv("cmake-build-debug/DelayTest_Delay_NoComp/IMUmeasPPC.csv", sep=";")
dataCAM = pd.read_csv("cmake-build-debug/DelayTest_Delay_NoComp/CAMmeasPPC.csv", sep=";")
dataCAMDelay = pd.read_csv("cmake-build-debug/DelayTest_Delay_NoComp/CAMmeasDelayPPC.csv", sep=";")
dataCov = pd.read_csv("cmake-build-debug/DelayTest_Delay_NoComp/covariancePPC.csv",sep=';')
dataCovDelay = pd.read_csv("cmake-build-debug/DelayTest_Delay_NoComp/covarianceDelayPPC.csv",sep=';')

# Plot EKF Comparatives
# Plot positions

plt.figure()
plt.subplot(3,1,1)
plt.title("Position x Time")
plt.step(dataState['t'],dataState['p1'],label=legNom)
plt.step(dataStateDelay['t'],dataStateDelay['p1'],linestyle='--',label='State during update')
plt.step(dataCAM['t'],dataCAM['p1'],linestyle=':',label="Meas. delayed")
plt.step(dataCAMDelay['t'],dataCAMDelay['p1'],linestyle=':',label="Meas.")
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['p1'][::trueDecimation],linestyle='--',label=legTrue)
plt.legend()
plt.xlabel("Time [s]")
plt.ylabel(r"$p_x$ [m]")
#plt.grid()

plt.subplot(3,1,2)
plt.step(dataCAM['t'],dataCAM['p2'],linestyle=':',label="Meas. delayed")
plt.step(dataState['t'],dataState['p2'],label=legNom)
plt.step(dataCAMDelay['t'],dataCAMDelay['p2'],linestyle=':',label="Meas.")
plt.step(dataStateDelay['t'],dataStateDelay['p2'],label='State during update')
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['p2'][::trueDecimation],linestyle='--',label=legTrue)
plt.legend()
plt.xlabel("Time [s]")
plt.ylabel(r"$p_y$ [m]")
#plt.grid()

plt.subplot(3,1,3)
plt.step(dataCAM['t'],dataCAM['p3'],linestyle=':',label="Meas. delayed")
plt.step(dataState['t'],dataState['p3'],label=legNom)
plt.step(dataCAMDelay['t'],dataCAMDelay['p3'],linestyle=':',label="Meas.")
plt.step(dataStateDelay['t'],dataStateDelay['p3'],label='State during update')
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['p3'][::trueDecimation],linestyle='--',label=legTrue)
plt.legend()
plt.xlabel("Time [s]")
plt.ylabel(r"$p_z$ [m]")
#plt.grid()
plt.show(block=False)

plt.figure()
plt.subplot(3,1,1)
plt.title("Position x Time")
plt.step(dataState['t'],dataState['p1'],label=legNom)
#plt.step(dataCAM['t'],dataCAM['p1'],linestyle=':',label="Meas delayed")
#plt.step(dataCAMDelay['t'],dataCAMDelay['p1'],linestyle=':',label="Meas")
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['p1'][::trueDecimation],linestyle='--',label=legTrue)
plt.legend()
plt.xlabel("Time [s]")
plt.ylabel(r"$p_x$ [m]")
#plt.grid()

plt.subplot(3,1,2)
#plt.step(dataCAM['t'],dataCAM['p2'],linestyle=':',label="Meas delayed")
plt.step(dataState['t'],dataState['p2'],label=legNom)
#plt.step(dataCAMDelay['t'],dataCAMDelay['p2'],linestyle=':',label="Meas")
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['p2'][::trueDecimation],linestyle='--',label=legTrue)
plt.legend()
plt.xlabel("Time [s]")
plt.ylabel(r"$p_y$ [m]")
#plt.grid()

plt.subplot(3,1,3)
#plt.step(dataCAM['t'],dataCAM['p3'],linestyle=':',label="Meas delayed")
plt.step(dataState['t'],dataState['p3'],label=legNom)
#plt.step(dataCAMDelay['t'],dataCAMDelay['p3'],linestyle=':',label="Meas")
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['p3'][::trueDecimation],linestyle='--',label=legTrue)
plt.legend()
plt.xlabel("Time [s]")
plt.ylabel(r"$p_z$ [m]")
#plt.grid()
plt.show(block=False)

# Plot Trajectory
fig = plt.figure()
vehicleX = np.array([1,0,0])
vehicleY = np.array([0,1,0])
vehicleZ = np.array([0,0,1])
ax = fig.add_subplot(111, projection='3d')
ax.plot(dataState['p1'],dataState['p2'],dataState['p3'])
ax.plot(dataTrue['p1'][::trueDecimation],dataTrue['p2'][::trueDecimation],dataTrue['p3'][::trueDecimation])
ax.set_xlabel(r"$p_x$ [m]")
ax.set_ylabel(r"$p_y$ [m]")
ax.set_zlabel(r"$p_z$ [m]")
axis_limitX =[min(dataState['p1']-20),max(dataState['p1']+20)]
axis_limitY =[min(dataState['p2']-20),max(dataState['p2']+20)]
axis_limitZ =[min(dataState['p3']-20),max(dataState['p3']+20)]
ax.set_xlim(axis_limitX)
ax.set_ylim(axis_limitY)
ax.set_zlim(axis_limitZ)
plt.title("Trajetory")

#Plot Velocity
plt.figure()
plt.subplot(3,1,1)
plt.title("Linear Velocity x Time")
plt.plot(dataState['t'],dataState['v1'],label=legNom)
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['v1'][::trueDecimation],linestyle='--',label=legTrue)
plt.legend()
plt.xlabel("Time [s]")
plt.ylabel(r"$v_x$ [m/s]")
#plt.grid()

plt.subplot(3,1,2)
plt.plot(dataState['t'],dataState['v2'],label=legNom)
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['v2'][::trueDecimation],linestyle='--',label=legTrue)
plt.legend()
plt.xlabel("Time [s]")
plt.ylabel(r"$v_y$ [m/s]")
#plt.grid()

plt.subplot(3,1,3)
plt.plot(dataState['t'],dataState['v3'],label=legNom)
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['v3'][::trueDecimation],linestyle='--',label=legTrue)
plt.legend()
plt.xlabel("Time [s]")
plt.ylabel(r"$v_z$ [m/s]")
#plt.grid()
plt.show(block=False)

# Plot Orientation
plt.figure()
plt.subplot(4,1,1)
plt.title("CAM quaternion x Time")
plt.plot(dataCAM['t'],dataCAM['q1'],linestyle=':',label="Meas")
plt.plot(dataState['t'],dataState['q1'],label=legNom)
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['q1'][::trueDecimation],linestyle='--',label=legTrue)
plt.legend()
plt.xlabel("Time [s]")
#plt.grid()

plt.subplot(4,1,2)
plt.plot(dataCAM['t'],dataCAM['q2'],linestyle=':',label="Meas")
plt.plot(dataState['t'],dataState['q2'],label=legNom)
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['q2'][::trueDecimation],linestyle='--',label=legTrue)
plt.legend()
plt.xlabel("Time [s]")
#plt.grid()

plt.subplot(4,1,3)
plt.plot(dataCAM['t'],dataCAM['q3'],linestyle=':',label="Meas")
plt.plot(dataState['t'],dataState['q3'],label=legNom)
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['q3'][::trueDecimation],linestyle='--',label=legTrue)
plt.legend()
plt.xlabel("Time [s]")
#plt.grid()

plt.subplot(4,1,4)
plt.plot(dataCAM['t'],dataCAM['q4'],linestyle=':',label="Meas")
plt.plot(dataState['t'],dataState['q4'],label=legNom)
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['q4'][::trueDecimation],linestyle='--',label=legTrue)
plt.xlabel("Time [s]")
plt.legend()
#plt.grid()
plt.show(block=False)

# Plot Bias
plt.figure()
plt.subplot(3,1,1)
plt.title("Acceleration Bias x Time")
plt.plot(dataState['t'],dataState['ab1'],label=legNom)
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['ab1'][::trueDecimation],linestyle='--',label=legTrue)
plt.legend()
plt.xlabel("Time [s]")
#plt.grid()

plt.subplot(3,1,2)
plt.plot(dataState['t'],dataState['ab2'],label=legNom)
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['ab2'][::trueDecimation],linestyle='--',label=legTrue)
plt.legend()
plt.xlabel("Time [s]")
#plt.grid()

plt.subplot(3,1,3)
plt.plot(dataState['t'],dataState['ab3'],label=legNom)
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['ab3'][::trueDecimation],linestyle='--',label=legTrue)
plt.legend()
plt.xlabel("Time [s]")
#plt.grid()
plt.show(block=False)

plt.figure()
plt.subplot(3,1,1)
plt.title("Angular Velocity Bias x Time")
plt.plot(dataState['t'],dataState['wb1'],label=legNom)
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['wb1'][::trueDecimation],linestyle='--',label=legTrue)
plt.legend()
plt.xlabel("Time [s]")
#plt.grid()

plt.subplot(3,1,2)
plt.plot(dataState['t'],dataState['wb2'],label=legNom)
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['wb2'][::trueDecimation],linestyle='--',label=legTrue)
plt.legend()
plt.xlabel("Time [s]")
#plt.grid()

plt.subplot(3,1,3)
plt.plot(dataState['t'],dataState['wb3'],label=legNom)
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['wb3'][::trueDecimation],linestyle='--',label=legTrue)
plt.legend()
plt.xlabel("Time [s]")
#plt.grid()
plt.show(block=False)

plt.figure()

# Primeiro subplot sem 'sharex'
ax = plt.subplot(15, 1, 1)
ax.plot(dataCov['t'], dataCov.iloc[:, 1])
ax.set_ylabel(f"P 1")

# Os demais subplots compartilhando o eixo x com o primeiro
for i in range(1, 15):
    ax = plt.subplot(15, 1, i+1, sharex=ax)
    ax.plot(dataCov['t'], dataCov.iloc[:, i+1])
    ax.set_ylabel(f"P {i+1}")

plt.show(block=False)
# Plot Error States

plt.figure()
plt.subplot(3,1,1)
plt.title("Error State: Position x Time")
plt.plot(dataError['t'],dataError['p1'])
plt.xlabel("Time [s]")
#plt.grid()

plt.subplot(3,1,2)
plt.plot(dataError['t'],dataError['p2'])
plt.xlabel("Time [s]")
#plt.grid()

plt.subplot(3,1,3)
plt.plot(dataError['t'],dataError['p3'])
plt.xlabel("Time [s]")
#plt.grid()
plt.show(block=False)

plt.figure()
plt.subplot(3,1,1)
plt.title("Error State:Linear Velocity x Time")
plt.plot(dataError['t'],dataError['v1'])
plt.xlabel("Time [s]")
#plt.grid()

plt.subplot(3,1,2)
plt.plot(dataError['t'],dataError['v2'])
plt.xlabel("Time [s]")
#plt.grid()

plt.subplot(3,1,3)
plt.plot(dataError['t'],dataError['v3'])
plt.xlabel("Time [s]")
#plt.grid()
plt.show(block=False)

# Plot IMU measurements

plt.figure()
plt.subplot(3,1,1)
plt.title("IMU: Angular Velocity x Time")
plt.plot(dataIMU['t'],dataIMU['w1'])
plt.xlabel("Time [s]")
#plt.grid()

plt.subplot(3,1,2)
plt.plot(dataIMU['t'],dataIMU['w2'])
plt.xlabel("Time [s]")
#plt.grid()

plt.subplot(3,1,3)
plt.plot(dataIMU['t'],dataIMU['w3'])
plt.xlabel("Time [s]")
#plt.grid()
plt.show(block=False)

plt.figure()
plt.subplot(3,1,1)
plt.title("IMU: Acceleration x Time")
plt.plot(dataIMU['t'],dataIMU['a1'])
plt.xlabel("Time [s]")
#plt.grid()

plt.subplot(3,1,2)
plt.plot(dataIMU['t'],dataIMU['a2'])
plt.xlabel("Time [s]")
#plt.grid()

plt.subplot(3,1,3)
plt.plot(dataIMU['t'],dataIMU['a3'])
plt.xlabel("Time [s]")
#plt.grid()
plt.show(block=False)

# Plot CAM measurements

plt.figure()
plt.subplot(3,1,1)
plt.title("CAM: Position x Time")
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['p1'][::trueDecimation],label=legTrue)
plt.plot(dataCAM['t'],dataCAM['p1'],label="CAM")
plt.plot(dataCAMDelay['t'],dataCAMDelay['p1'],label="CAM Compensated")
plt.legend()
plt.xlabel("Time [s]")
#plt.grid()

plt.subplot(3,1,2)
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['p2'][::trueDecimation],label=legTrue)
plt.plot(dataCAM['t'],dataCAM['p2'],label="CAM")
plt.plot(dataCAMDelay['t'],dataCAMDelay['p2'],label="CAM Compensated")
plt.legend()
plt.xlabel("Time [s]")
#plt.grid()

plt.subplot(3,1,3)
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['p3'][::trueDecimation],label=legTrue)
plt.plot(dataCAM['t'],dataCAM['p3'],label="CAM")
plt.plot(dataCAMDelay['t'],dataCAMDelay['p3'],label="CAM Compensated")
plt.legend()
plt.xlabel("Time [s]")
#plt.grid()
plt.show(block=False)

plt.figure()
plt.subplot(4,1,1)
plt.title("CAM quaternion x Time")
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['q1'][::trueDecimation],label=legTrue)
plt.step(dataCAM['t'],dataCAM['q1'],label="CAM")
plt.step(dataCAMDelay['t'],dataCAMDelay['q1'],label="CAM Compensated")
plt.xlabel("Time [s]")
#plt.grid()

plt.subplot(4,1,2)
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['q2'][::trueDecimation],label=legTrue)
plt.step(dataCAM['t'],dataCAM['q2'],label="CAM")
plt.step(dataCAMDelay['t'],dataCAMDelay['q2'],label="CAM Compensated")
plt.xlabel("Time [s]")
#plt.grid()

plt.subplot(4,1,3)
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['q3'][::trueDecimation],label=legTrue)
plt.step(dataCAM['t'],dataCAM['q3'],label="CAM")
plt.step(dataCAMDelay['t'],dataCAMDelay['q3'],label="CAM Compensated")
plt.xlabel("Time [s]")
#plt.grid()

plt.subplot(4,1,4)
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['q4'][::trueDecimation],label=legTrue)
plt.step(dataCAM['t'],dataCAM['q4'],label="CAM")
plt.step(dataCAMDelay['t'],dataCAMDelay['q4'],label="CAM Compensated")
plt.xlabel("Time [s]")
#plt.grid()
plt.legend()
plt.show(block=False)

# Número de pontos de telemetria (N)
N_CAM = len(dataCAM['q4'])
N_CAMDelay = len(dataCAMDelay['q4'])

# Criando as contagens
count_CAM = np.linspace(0, N_CAM, N_CAM)
count_CAMDelay = np.linspace(0, N_CAMDelay, N_CAMDelay)

plt.figure()
plt.step(dataCAM['t'],count_CAM,label="CAM Delayed", color='blue')
plt.step(dataCAMDelay['t'],count_CAMDelay,label="CAM", color='orange')
plt.xlabel("CAM packege count")
plt.ylabel("Count")
plt.legend()
#plt.grid()
plt.show(block=False)
input("Pressione Enter para fechar os plots e encerrar...")