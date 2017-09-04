import matplotlib.pyplot as plt
x = []
y = []
file = open("output_naive.txt", "r")
for line in file.readlines():
	line = line.strip();
	a, b = line.split(' ', maxsplit=1);
	x.append(int(a))
	y.append(int(b))

x2 = []
y2 = []
file = open("output_backtracking.txt", "r")
for line in file.readlines():
	line = line.strip();
	a, b = line.split(' ', maxsplit=1);
	x2.append(int(a))
	y2.append(int(b))


plt.plot(x, y);
plt.plot(x2, y2);
plt.ylabel("time in microsseconds")
plt.xlabel("no. of vertices in graph")
plt.show()