import matplotlib.pyplot as plt
import numpy as np

with open("test_cases.txt", "r") as f:
    lines = f.readlines()
    n = []
    runtime = []
    l2 = []
    l3 = []

    for line in lines:
        n.append(int(line.split()[0]))
        runtime.append(int(line.split()[1]))
        l2.append(float(line.split()[2]))
        l3.append(float(line.split()[3]))

fig, ax = plt.subplots(3)

runtime = np.array(runtime)
n = np.array(n)

ax[0].scatter(n, runtime, color='green', label='Runtime', s=2)
ax[1].scatter(n, l2, color='blue', label='L2', s=2)
ax[2].scatter(n, l3, color='black', label='L3', s=2)
plt.show()