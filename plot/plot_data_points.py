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

fig, (ax1, ax2) = plt.subplots(1, 2)

if eq == "y":
    # plt.gca().set_aspect('equal', adjustable='box') 
    ax1.set_aspect('equal', adjustable='box')
ax1.grid()

if p_logn:
    print("Adjusting k, where runtime = k * " + rt + ". k = k/100")
    k = 100
    ax1.plot(x, y_logn, color='magenta', label='log(n)')
if p_n:
    ax1.plot(x, y_n, color='magenta', label='n')
if p_nlogn:
    print("Adjusting k, where runtime = k * " + rt + ". k = k/100")
    k = 100
    ax1.plot(x, y_nlogn, color='magenta', label='nlog(n)')
if p_n2:
    print("Adjusting k, where runtime = k * " + rt + ". k = k/10")
    k = 10
    ax1.plot(x, y_n2, color="magenta", label="n^2")

combined_data = [(n[i], runtime[i] // k // n[i], l2[i], l3[i]) for i in range(len(n))]
sorted_data = sorted(combined_data, key=lambda x: x[1], reverse=True)
top_10_elements = sorted_data[:10]
bottom_10_elements = sorted_data[-10:]
a_list = np.array([item[0] for item in top_10_elements])
b_list = np.array([item[1] * item[0] for item in top_10_elements])
c_list = np.array([item[2] for item in top_10_elements])
d_list = np.array([item[3] for item in top_10_elements])
e_list = np.array([item[0] for item in bottom_10_elements])
f_list = np.array([item[1] * item[0] for item in bottom_10_elements])
g_list = np.array([item[2] for item in bottom_10_elements])
h_list = np.array([item[3] for item in bottom_10_elements])

ax1.scatter(n, runtime // k, color='grey', label='Runtime', s=1)
ax1.scatter(a_list, b_list, color='red', label="Worst constant", s=10)
ax1.scatter(e_list, f_list, color="green", label="Best constant", s=10)
ax1.legend()

ax2.scatter(n, l2, color='cyan', label='L2', s=1)
ax2.scatter(n, l3, color='pink', label='L3', s=1)
ax2.scatter(a_list, c_list, color="red", label="L2 of Worst", s=10)
ax2.scatter(a_list, d_list, color="orange", label="L3 of Worst", s=10)
ax2.scatter(e_list, g_list, color="blue", label="L2 of Best", s=10)
ax2.scatter(e_list, h_list, color="green", label="L3 of Best", s=10)
ax2.legend()
plt.show()