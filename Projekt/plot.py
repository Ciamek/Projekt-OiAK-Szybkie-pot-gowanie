import matplotlib.pyplot as plt
print ('Podaj nazwe pliku (domyslnie "times_n_k"):')
file_name = input()
f = open('./Dane pomiarowe/' + file_name)
data = [float(i) for i in f]
x = range(0, len(data))
plt.plot(x, data)
plt.title('Wykres zaleznosci czasu obliczen od potegi')
plt.ylabel('Czas w sekundach')
plt.xlabel('Potega')
plt.show()
