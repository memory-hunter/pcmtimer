import matplotlib.pyplot as plt
import numpy as np
import sys

if len(sys.argv) < 4:
    print("""Usage: plot_data_points.py <runtime> <limit> <ar> 
          <runtime> - algorithm runtime function : 'logn' | 'n' | 'nlogn' | 'n2'
          <limit> - maximum n : int
          <ar> - 1:1 aspect ratio or free : y/n""")
    exit()

eq = sys.argv[3]
rt = sys.argv[1]
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
print("Runtime function type: " + rt)

test_case_max_limit = int(sys.argv[2])
x = np.linspace(1, test_case_max_limit, test_case_max_limit)
y_logn, y_n, y_nlogn, y_n2 = np.log(x), x, x*np.log2(x), x*x
k = 1

with open("test_cases.txt", "r") as f:
    lines = f.readlines()

    n = []
    runtime = []
    l2 = []
    l3 = []

    for line in lines:
        data = line.split()
        n.append(int(data[0]))
        runtime.append(int(data[1]))
        l2.append(float(data[2]))
        l3.append(float(data[3]))
    
    n = np.array(n)
    runtime = np.array(runtime)
    l2 = np.array(l2)
    l3 = np.array(l3)

if eq == "y":
    plt.gca().set_aspect('equal', adjustable='box')
plt.grid()

if p_logn:
    print("Adjusting k, where runtime = k * " + rt + ". k = k/100")
    k = 100
    plt.plot(x, y_logn, color='red', label='log(n)')
if p_n:
    plt.plot(x, y_n, color='green', label='n')
if p_nlogn:
    print("Adjusting k, where runtime = k * " + rt + ". k = k/100")
    k = 100
    plt.plot(x, y_nlogn, color='blue', label='nlog(n)')
if p_n2:
    print("Adjusting k, where runtime = k * " + rt + ". k = k/10")
    k= 10
    plt.plot(x, y_n2, color="magenta", label="n^2")
plt.scatter(n, runtime//k, color='black', label='Runtime', s=3)
plt.legend()
plt.show()

plt.scatter(n, l2, color='red', label='L2', s=1)
plt.scatter(n, l3, color='cyan', label='L3', s=1)
plt.legend()
plt.show()