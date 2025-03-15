import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import seaborn as sns

sns.set_context("notebook", font_scale=1)  # Aumenta o tamanho da fonte
sns.set_theme(style="darkgrid")
sns.color_palette("rocket")
plt.rcParams["lines.linewidth"] = 0.4
plt.rcParams["figure.subplot.left"] = 0.15
plt.rcParams["figure.subplot.right"] = 0.98
plt.rcParams["figure.subplot.hspace"] = 0.27
plt.rcParams["font.family"] = "Times New Roman"
plt.rcParams["font.size"] = 12

pd.options.display.float_format = '{:.6f}'.format

dataPred = pd.read_csv("cmake-build-debug/DelayTest_Delay_Comp/timePredPPC.csv", sep=";")

dataUp = pd.read_csv("cmake-build-debug/DelayTest_Delay_Comp/timeUpPPC.csv", sep=";")

#plt.figure()
media = (dataPred['Fx']*1e6).mean()
desvio_padrao = (dataPred['Fx']*1e6).std()
print(f"Media de Fx: {media:.15f}")
print(f"Desvio padrao de Fx: {desvio_padrao:.15f}")

sns.histplot(dataPred['Fx']*1e6,kde=False,binwidth=0.5)
plt.title("Histogram: Processing Time for Fx computation")
plt.xlabel("Processing Time [µs]")
plt.ylabel("Count")
plt.xlim(0, media + 2*desvio_padrao)

plt.figure()
sns.lineplot(x=dataPred['t'],y=(dataPred['Fx']*1e6))
plt.title("Processing Time for Fx")
plt.ylabel("Processing Time [µs]")
plt.xlabel("Simulation Time [s]")

media = (dataPred['predX']*1e6).mean()
desvio_padrao = (dataPred['predX']*1e6).std()
print(f"Media de PredX: {media:.15f}")
print(f"Desvio padrao de PredX: {desvio_padrao:.15f}")

plt.figure()
sns.histplot(dataPred['predX']*1e6,kde=False)
plt.title("Histogram: Processing Time for Nominal Propagation")
plt.xlabel("Processing Time [µs]")
plt.ylabel("Count")
plt.xlim(0, media + 2*desvio_padrao)

plt.figure()
sns.lineplot(x=dataPred['t'],y=(dataPred['predX']*1e6))
plt.title("Processing Time for Nominal Propagation")
plt.ylabel("Processing Time [µs]")
plt.xlabel("Simulation Time [s]")

media = (dataPred['predP']*1e6).mean()
desvio_padrao = (dataPred['predP']*1e6).std()
print(f"Media de PredP: {media:.15f}")
print(f"Desvio padrao de PredP: {desvio_padrao:.15f}")

plt.figure()
sns.histplot(dataPred['predP']*1e6,kde=False)
plt.title("Histogram: Processing Time for Covariance Propagation")
plt.xlabel("Processing Time [µs]")
plt.ylabel("Count")
plt.xlim(0, media + 2*desvio_padrao)

plt.figure()
sns.lineplot(x=dataPred['t'],y=(dataPred['predP']*1e6))
plt.title("Processing Time for Covariance Propagation")
plt.ylabel("Processing Time [µs]")
plt.xlabel("Simulation Time [s]")

### Update Step

media = (dataUp['H']*1e6).mean()
desvio_padrao = (dataUp['H']*1e6).std()
print(f"Media de H: {media:.15f}")
print(f"Desvio padrao de H: {desvio_padrao:.15f}")

plt.figure()
sns.histplot(dataUp['H']*1e6,kde=False)
plt.title("Histogram: Processing Time for H matrix computation")
plt.xlabel("Processing Time [µs]")
plt.ylabel("Count")
plt.xlim(0, media + 2*desvio_padrao)

plt.figure()
sns.lineplot(x=dataUp['t'],y=(dataUp['H']*1e6))
plt.title("Processing Time for H matrix computation")
plt.ylabel("Processing Time [µs]")
plt.xlabel("Simulation Time [s]")

media = (dataUp['up']*1e6).mean()
desvio_padrao = (dataUp['up']*1e6).std()
print(f"Media de up: {media:.15f}")
print(f"Desvio padrao de up: {desvio_padrao:.15f}")

plt.figure()
sns.histplot(dataUp['up']*1e6,kde=False)
plt.title("Histogram: Processing Time for Update Step")
plt.xlabel("Processing Time [µs]")
plt.ylabel("Count")
plt.xlim(0, media + 2*desvio_padrao)

plt.figure()
sns.lineplot(x=dataUp['t'],y=(dataUp['up']*1e6))
plt.title("Processing Time for Update Step")
plt.ylabel("Processing Time [µs]")
plt.xlabel("Simulation Time [s]")

media = (dataUp['inj']*1e6).mean()
desvio_padrao = (dataUp['inj']*1e6).std()
print(f"Media de inj: {media:.15f}")
print(f"Desvio padrao de inj: {desvio_padrao:.15f}")

plt.figure()
sns.histplot(dataUp['inj']*1e6,kde=False)
plt.title("Histogram: Processing Time for Error Injection")
plt.xlabel("Processing Time [µs]")
plt.ylabel("Count")
plt.xlim(0, media + 2*desvio_padrao)

plt.figure()
sns.lineplot(x=dataUp['t'],y=(dataUp['inj']*1e6))
plt.title("Processing Time for Error Injection")
plt.ylabel("Processing Time [µs]")
plt.xlabel("Simulation Time [s]")

media = (dataUp['reset']*1e6).mean()
desvio_padrao = (dataUp['reset']*1e6).std()
print(f"Media de reset: {media:.15f}")
print(f"Desvio padrao de reset: {desvio_padrao:.15f}")

plt.figure()
sns.histplot(dataUp['reset']*1e6,kde=False)
plt.title("Histogram: Processing Time for Reset")
plt.xlabel("Processing Time [µs]")
plt.ylabel("Count")
plt.xlim(0, media + 2*desvio_padrao)

plt.figure()
sns.lineplot(x=dataUp['t'],y=(dataUp['reset']*1e6))
plt.title("Processing Time for Reset")
plt.ylabel("Processing Time [µs]")
plt.xlabel("Simulation Time [s]")

media = (dataUp['recov']*1e6).mean()
desvio_padrao = (dataUp['recov']*1e6).std()
print(f"Media de recov: {media:.15f}")
print(f"Desvio padrao de recov: {desvio_padrao:.15f}")

plt.figure()
sns.histplot(dataUp['recov']*1e6,kde=False)
plt.title("Histogram: Processing Time for State Recovery")
plt.xlabel("Processing Time [µs]")
plt.ylabel("Count")
plt.xlim(0, media + 2*desvio_padrao)

plt.figure()
sns.lineplot(x=dataUp['t'],y=(dataUp['recov']*1e6))
plt.title("Processing Time for State Recovery")
plt.ylabel("Processing Time [µs]")
plt.xlabel("Simulation Time [s]")

media = (dataUp['reprop']*1e6).mean()
desvio_padrao = (dataUp['reprop']*1e6).std()
print(f"Media de reprop: {media:.15f}")
print(f"Desvio padrao de reprop: {desvio_padrao:.15f}")

plt.figure()
sns.histplot(dataUp['reprop']*1e6,kde=False)
plt.title("Histogram: Processing Time for Re-propagation")
plt.xlabel("Processing Time [µs]")
plt.ylabel("Count")
plt.xlim(0, media + 2*desvio_padrao)

plt.figure()
sns.lineplot(x=dataUp['t'],y=(dataUp['reprop']*1e6))
plt.title("Processing Time for Re-propagation")
plt.ylabel("Processing Time [µs]")
plt.xlabel("Simulation Time [s]")
plt.show()

media = (dataUp['erase']*1e6).mean()
desvio_padrao = (dataUp['erase']*1e6).std()
print(f"Media de erase: {media:.15f}")
print(f"Desvio padrao de erase: {desvio_padrao:.15f}")

plt.figure()
sns.histplot(dataUp['erase']*1e6,kde=False)
plt.title("Histogram: Processing Time for Erasing")
plt.xlabel("Processing Time [µs]")
plt.ylabel("Count")
plt.xlim(0, media + 2*desvio_padrao)

plt.figure()
sns.lineplot(x=dataUp['t'],y=(dataUp['erase']*1e6))
plt.title("Processing Time for Erasing")
plt.ylabel("Processing Time [µs]")
plt.xlabel("Simulation Time [s]")
plt.show()