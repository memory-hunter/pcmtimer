import matplotlib.pyplot as plt

with open("./test_cases.txt", "r") as f:
    lines = f.readlines()
    x = []
    y = []
    for line in lines:
        x.append(float(line.split(" ")[0]))
        y.append(float(line.split(" ")[1])/1e9)
    # label x and y
    plt.xlabel("Number of points")
    plt.ylabel("Time (ns)")
    plt.scatter(x, y)
    plt.show()