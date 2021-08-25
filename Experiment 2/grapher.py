from matplotlib import pyplot as plt

x = []
y1 = []
y2 = []
file = open('data.txt', 'r')
for line in file:
    coor = line.split()
    x.append(float(coor[0]))
    y1.append(float(coor[1]))
    y2.append(float(coor[2]))

plt.plot(x, y1)
plt.plot(x, y2)
plt.xlabel('Freq (Hz)')
plt.ylabel('Vr (mV)')
plt.title("Vr vs Freq")
plt.show()
