import matplotlib.pyplot as plt

with open("./test_cases.txt", "r") as f:
    lines = f.readlines()
    x = []
    y = []
    for line in lines:
        x.append(float(line.split(" ")[0]))
        y.append(float(line.split(" ")[1]))
    plt.scatter(x, y)
    plt.show()