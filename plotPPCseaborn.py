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
dataErrorDelay = pd.read_csv("cmake-build-debug/errorStateDelayPPC.csv", sep=";")
dataStateDelay = pd.read_csv("cmake-build-debug/stateDelayPPC.csv", sep=";")
dataIMU = pd.read_csv("cmake-build-debug/IMUmeasPPC.csv", sep=";")
dataCAM = pd.read_csv("cmake-build-debug/CAMmeasPPC.csv", sep=";")
dataCAMDelay = pd.read_csv("cmake-build-debug/CAMmeasDelayPPC.csv", sep=";")
dataCov = pd.read_csv("cmake-build-debug/covariancePPC.csv",sep=';')
dataCovDelay = pd.read_csv("cmake-build-debug/covarianceDelayPPC.csv",sep=';')

# Plot EKF Comparatives
# Plot positions

plt.figure()
plt.subplot(3,1,1)
plt.title("Position x Time")
plt.step(dataState['t'],dataState['p1'],label='State')
plt.step(dataStateDelay['t'],dataStateDelay['p1'],linestyle='--',label='State during update')
plt.step(dataCAM['t'],dataCAM['p1'],linestyle=':',label="Meas delayed")
plt.step(dataCAMDelay['t'],dataCAMDelay['p1'],linestyle=':',label="Meas")
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['p1'][::trueDecimation],linestyle='--',label='True')
plt.legend()
plt.xlabel("Time [s]")
plt.grid()

plt.subplot(3,1,2)
plt.step(dataCAM['t'],dataCAM['p2'],linestyle=':',label="Meas delayed")
plt.step(dataState['t'],dataState['p2'],label='State')
plt.step(dataCAMDelay['t'],dataCAMDelay['p2'],linestyle=':',label="Meas")
plt.step(dataStateDelay['t'],dataStateDelay['p2'],label='State during update')
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['p2'][::trueDecimation],linestyle='--',label='True')
plt.legend()
plt.xlabel("Time [s]")
plt.grid()

plt.subplot(3,1,3)
plt.step(dataCAM['t'],dataCAM['p3'],linestyle=':',label="Meas delayed")
plt.step(dataState['t'],dataState['p3'],label='State')
plt.step(dataCAMDelay['t'],dataCAMDelay['p3'],linestyle=':',label="Meas")
plt.step(dataStateDelay['t'],dataStateDelay['p3'],label='State during update')
plt.plot(dataTrue['t'][::trueDecimation],dataTrue['p3'][::trueDecimation],linestyle='--',label='True')
plt.legend()
plt.xlabel("Time [s]")
plt.grid()
plt.show(block=False)