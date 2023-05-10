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
    
    n = np.array(n)
    runtime = np.array(runtime)
    l2 = np.array(l2)
    l3 = np.array(l3)

test_case_max_limit = 100000
x = np.linspace(1, test_case_max_limit, test_case_max_limit)
y_logn, y_n, y_nlogn = np.log(x), x, x*np.log(x)

plt.plot(x, y_logn, color='red', label='log(n)')
plt.plot(x, y_n, color='green', label='n')
plt.plot(x, y_nlogn, color='blue', label='nlog(n)')
plt.gca().set_aspect('equal', adjustable='box') # This line fixed the plotting beingd weirdly
plt.grid()
plt.scatter(n, runtime, color='black', label='Runtime', s=3)
plt.legend()
plt.show()
plt.scatter(n, l2, color='red', label='L2', s=1)
plt.scatter(n, l3, color='cyan', label='L3', s=1)
plt.legend()
plt.show()