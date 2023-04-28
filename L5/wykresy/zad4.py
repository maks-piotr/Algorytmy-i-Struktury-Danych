import matplotlib.pyplot as plt
import statistics as stat
import math

x = [i for i in range(1000, 5001, 1000)]
porM = [[] for i in range(5)]
porS = [[] for i in range(5)]
k = 20


for i in x:
    with open('output/LCS' + str(i) + '.out') as file:
        for line in file:
            if ('Liczba porownan miedzy kluczami: ' in line):
                #print(line)
                porM[(i)//1000 -1].append(float((line.split('kluczami: ')[1]).split()[0]))
            if ('Liczba przypisan wartosci: ' in line):
                #print(line)
                porS[(i)//1000 -1].append(float((line.split('wartosci: ')[1]).split()[0]))            
          
fig, (m, s) = plt.subplots(1,2)


m.plot(x,[stat.mean(porM[i]) for i in range(5)],'r')
#m.plot(x,[stat.mean(splayM[i]) for i in range(10)],'g',label='Splay-BST')

m.ticklabel_format(useOffset=False, style='plain')
#m.legend(loc="upper left")
m.set(xlabel='Wielkość danych wejściowych', ylabel='Liczba porównań')
m.set_title('Liczba porównań LCS w zależności od wielkośći danych (próba statystyczna 20)\n input losowy')
m.grid()


s.plot(x,[stat.mean(porS[i]) for i in range(5)],'b')
#s.plot(x,[stat.mean(splayS[i]) for i in range(10)],'g',label='Splay-BST')

s.ticklabel_format(useOffset=False, style='plain')
#s.legend(loc="upper left")
s.set(xlabel='Wielkość danych wejściowych', ylabel='Liczba przypisań ')
s.set_title('Liczba przypisań wartości LCS w zależności od wielkośći danych (próba statystyczna 20)\n input losowy')
s.grid()


plt.show()