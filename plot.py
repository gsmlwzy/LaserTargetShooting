import numpy as np
import matplotlib.pyplot as plt

data = list()
path = r'data.txt'
with open(path) as f:
	# data = f.readlines()
	for line in f:
		cache = float(line[:-1])
		# print(cache)
		data.append(cache)

x = range(len(data))
plt.plot(x, data)
plt.title("Motor rotates between -45and 45 degrees")
plt.axhline(45, c = 'r', ls = ':')
plt.axhline(-45, c='r', ls = ':')
plt.show()
