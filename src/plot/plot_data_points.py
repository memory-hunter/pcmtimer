import matplotlib.pyplot as plt
import math

with open("./test_cases.txt", "r") as f:
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
    
    ratios = []
    for i in range(len(n)):
        ratios.append(runtime[i])
    
    mean = sum(ratios)/len(ratios)
    mult = 1.3
    thresh = mean*mult

    bad_n, bad_runtime, bad_l2, bad_l3 = [], [], [], []
    for i in range(len(n)):
        if runtime[i] > thresh:
            bad_n.append(n[i])
            bad_runtime.append(runtime[i])
            bad_l2.append(l2[i])
            bad_l3.append(l3[i])
    
    
    plt.scatter(n, runtime, color='green', label='runtime', s=5)
    plt.hlines(y=thresh, xmin=0, xmax=1000000, color='cyan', label='Threshhold')
    plt.scatter(bad_n, bad_runtime, color='red', label='bad runtime', s=5)
    plt.xlabel("Number of nodes")
    plt.ylabel("Runtime (ms)")
    plt.legend()
    plt.show()
    plt.scatter(n, l2, color='blue', label='L2', s=5)
    plt.scatter(bad_n, bad_l2, color='red', label='bad L2', s=5)
    plt.xlabel("Number of nodes")
    plt.ylabel("L2 ratio")
    plt.legend()
    plt.show()
    plt.scatter(n, l3, color='black', label='L3', s=5)
    plt.scatter(bad_n, bad_l3, color='red', label='bad L3', s=5)
    plt.xlabel("Number of nodes")
    plt.ylabel("L3 ratio")
    plt.legend()
    plt.show()