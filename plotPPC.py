import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

data = pd.read_csv("cmake-build-debug/results.csv", sep=";")

plt.figure()
plt.subplot(3,1,1)
plt.title("Position x Time")
plt.plot(data['t'],data['p1'])
plt.xlabel("Time [s]")
plt.grid()

plt.subplot(3,1,2)
plt.plot(data['t'],data['p2'])
plt.xlabel("Time [s]")
plt.grid()

plt.subplot(3,1,3)
plt.plot(data['t'],data['p3'])
plt.xlabel("Time [s]")
plt.grid()
plt.show()

plt.figure()
plt.subplot(3,1,1)
plt.title("Linear Velocity x Time")
plt.plot(data['t'],data['v1'])
plt.xlabel("Time [s]")
plt.grid()

plt.subplot(3,1,2)
plt.plot(data['t'],data['v2'])
plt.xlabel("Time [s]")
plt.grid()

plt.subplot(3,1,3)
plt.plot(data['t'],data['v3'])
plt.xlabel("Time [s]")
plt.grid()
plt.show()