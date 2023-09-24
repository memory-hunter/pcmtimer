import matplotlib.pyplot as plt
import numpy as np
import sys

if len(sys.argv) < 3:
    print("""Usage: plot_data_points.py <ar> <runtime>
          <ar> : true or false
          <runtime> : 'logn' | 'n' | 'nlogn' | 'n2'""")
    exit()

eq = sys.argv[1]
rt = sys.argv[2]
p_logn, p_n, p_nlogn, p_n2 = False, False, False, False

match rt:
    case 'logn':
        p_logn = True
    case 'n':
        p_n = True
    case 'nlogn':
        p_nlogn = True
    case 'n2':
        p_n2 = True

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
y_logn, y_n, y_nlogn, y_n2 = np.log(x), x, x*np.log2(x), x*x

if p_logn:
    plt.plot(x, y_logn, color='red', label='log(n)')
if p_n:
    plt.plot(x, y_n, color='green', label='n')
if p_nlogn:
    plt.plot(x, y_nlogn, color='blue', label='nlog(n)')
if p_n2:
    plt.plot(x, y_n2, color="black", label="n^2")

if eq == "true":
    plt.gca().set_aspect('equal', adjustable='box')

plt.grid()
plt.scatter(n, runtime, color='black', label='Runtime', s=3)
plt.legend()
plt.show()

plt.scatter(n, l2, color='red', label='L2', s=1)
plt.scatter(n, l3, color='cyan', label='L3', s=1)
plt.legend()
plt.show()