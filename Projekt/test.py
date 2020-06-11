import secrets

print('Projekt OiAK - Szybkie potegowanie wielkich liczb.\nMaciej Ciura 248879\n\nProgram do testowania poprawnosci algorytmu'
     +'generuje plik "data_input" z k parami liczb w notacji heksadecymalnej:\n'
     +'liczbe dlugosci n-bajtow, oraz potege kolejne liczby calkowite z zakresu <0,k>\n'
     +'Podaj n w notacji dziesietnej (np. 512+ bajty):')

n=int(input())
print('Podaj k w notacji dziesietnej (przy wartości >255 czas wykonywania kilka min.):')
k=int(input())

result_file = open('./result_python' , 'w' )
data_file = open('./data_input' , 'w' )
print('...')

data_file.write("%d\n%d\n"%(k,n))

for i in range(0,k):

    string = (secrets.token_hex(n))

    if(len(string)>0):
        number = int(string,16)
        data_file.write(string+'\n'+hex(i)+'\n')
        result_file.write("%x\n" %number**i)

    else:
        number = 0
        data_file.write('0\n'+hex(i)+'\n')
        result_file.write("%x\n" %number**i)


print('Plik wygenerowany poprawnie!\n\nAby kontynuowac test na wygenerowanych danych nalezy podac w terminalu komende:\n'
     +'./OiAK_Potegowanie_TEST\n\nZostanie wygenerowany plik z wynikami dzialan "result_cpp" ktory nastepnie należy porownac\n'
     +'w celu sprawdzenia poprawnosci, z plikiem wynikowym "result_python" uzywajac komendy:')
print('\ndiff result_python result_cpp\nPomiar czasu zostanie wypisany do pliku "times_n_k"')
#python test.py; ./OiAK_Potegowanie_TEST < data_input > result_cpp.txt; diff result_python.txt result_cpp.txt
