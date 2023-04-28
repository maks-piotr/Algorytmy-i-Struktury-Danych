import matplotlib.pyplot as plt
import statistics as stat
import math

x = [i for i in range(10000, 100001, 10000)]
podsM = [[] for i in range(10)]
podsS = [[] for i in range(10)]
porM = [[] for i in range(10)]
porS = [[] for i in range(10)]
k = 20


for i in x:
    with open('output/queue' + str(i) + '.out') as file:
        for line in file:
            if ('Srednia podstawienia:' in line):
                #print(line)
                podsS[(i)//10000 -1].append(float((line.split('podstawienia: ')[1]).split()[0]))
            if ('Max podstwaienia:' in line):
                #print(line)
                podsM[(i)//10000 -1].append(float((line.split('podstwaienia: ')[1]).split()[0]))  
            if ('Srednia porowania:' in line):
                #print(line)
                porS[(i)//10000 -1].append(float((line.split('porowania: ')[1]).split()[0]))
            if ('Max porownan:' in line):
                #print(line)
                porM[(i)//10000 -1].append(float((line.split('porownan: ')[1]).split()[0]))            
          
fig, (m, s) = plt.subplots(1,2)


m.plot(x,[stat.mean(podsM[i]) for i in range(10)],'r',label='podstawienia')
m.plot(x,[stat.mean(porM[i]) for i in range(10)],'b',label='porównania')
#m.plot(x,[stat.mean(splayM[i]) for i in range(10)],'g',label='Splay-BST')

m.legend(loc="upper left")
m.set(xlabel='Wielkość danych wejściowych', ylabel='Maksymalna liczba operacji')
m.set_title('Maksymalna liczba porównań i podstawień węzłów w operacji\n w zależności od wielkośći danych (próba statystyczna 20)\n input losowy')
m.grid()


s.plot(x,[stat.mean(podsS[i]) for i in range(10)],'r',label='podstawienia')
s.plot(x,[stat.mean(porS[i]) for i in range(10)],'b',label='porównania')
#s.plot(x,[stat.mean(splayS[i]) for i in range(10)],'g',label='Splay-BST')

s.legend(loc="upper left")
s.set(xlabel='Wielkość danych wejściowych', ylabel='Średnia liczba operacji')
s.set_title('Średnia liczba porównań i podstawień węzłów w operacji\n w zależności od wielkośći danych (próba statystyczna 20)\n input losowy')
s.grid()


plt.show()