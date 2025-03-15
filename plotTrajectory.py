import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
pd.options.display.float_format = '{:.6f}'.format

# Import PPC data

dataTrue = pd.read_csv("cmake-build-debug/trueStatePPC.csv", sep=";")
dataError = pd.read_csv("cmake-build-debug/errorStatePPC.csv", sep=";")
dataState = pd.read_csv("cmake-build-debug/statePPC.csv", sep=";")
dataIMU = pd.read_csv("cmake-build-debug/IMUmeasPPC.csv", sep=";")
dataCAM = pd.read_csv("cmake-build-debug/CAMmeasPPC.csv", sep=";")
dataCov = pd.read_csv("cmake-build-debug/covariancePPC.csv",sep=';')

fig = plt.figure()
vehicleX = np.array([1,0,0])
vehicleY = np.array([0,1,0])
vehicleZ = np.array([0,0,1])

ax = fig.add_subplot(111, projection='3d')
ax.plot(dataState['p1'],dataState['p2'],dataState['p3'])
ax.plot(dataTrue['p1'],dataTrue['p2'],dataTrue['p3'])
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
axis_limitX =[min(dataState['p1']-20),max(dataState['p1']+20)]
axis_limitY =[min(dataState['p2']-20),max(dataState['p2']+20)]
axis_limitZ =[min(dataState['p3']-20),max(dataState['p3']+20)]
ax.set_xlim(axis_limitX)
ax.set_ylim(axis_limitY)
ax.set_zlim(axis_limitZ)
plt.title("Trajetory")