import matplotlib.pyplot as plt
import statistics as stat
import math
 
x = [i for i in range(1000, 100001, 1000)]
binC = [[] for i in range(100)]
binT = [[] for i in range(100)]

m = 0
with open('output/select100.out') as file:
    for line in file:
        if ('Liczba porownan miedzy kluczami' in line):
            m = m + 1


for i in x:
    with open('output/zad4/bin_search' + str(i) + '.out') as file:
        for line in file:
            if ('Liczba porownan' in line):
                binC[(i)//1000 -1].append(int((line.split('porownan: ')[1]).split()[0]))
            if ('Czas w nanosekundach' in line):
                binT[(i)//1000 -1].append(int((line.split('nanosekundach: ')[1]).split()[0]))


fig, ((c, cn),(t, tn)) = plt.subplots(2,2)
#c.plot(x,[math.log2((i+1)*100) for i in range (100)],'r',label='log n')
c.plot(x,[stat.mean(binC[i]) for i in range(100)],'b',label='Liczba porównań bin search')
c.legend(loc="upper left")
c.set(xlabel='Wielkość tablicy', ylabel='Liczba porównań')
c.set_title('Liczba porównań dla losowej tablicy w zależności od wielkości (m = ' + str(m) + ', element losowy)')
c.grid()

cn.plot(x,[stat.mean(binC[i])/(math.log2((i+1)*100)) for i in range(100)],'b',label='Liczba porównań / log n bin search')
#cn.plot(x,[1 for i in range(100)],'r',label='1')
cn.legend(loc="upper left")
cn.set(xlabel='Wielkość tablicy', ylabel='Liczba porównań')
cn.set_title('Liczba porównań dla losowej tablicy / log n w zależności od wielkości (m = ' + str(m) + ', element losowy)')
cn.grid()

t.plot(x,[stat.mean(binT[i]) for i in range(100)],'b',label='Czas wykonania bin search')
t.legend(loc="upper left")
t.set(xlabel='Wielkość tablicy', ylabel='Czas wykonania [ns]')
t.set_title('Czas wykonania dla losowej tablicy w zależności od wielkości (m = ' + str(m) + ', element losowy)')
t.grid()

tn.plot(x,[stat.mean(binT[i])/(math.log2((i+1)*100)) for i in range(100)],'b',label='Czas wykonania / log n bin search')
tn.legend(loc="upper left")
tn.set(xlabel='Wielkość tablicy', ylabel='Czas wykonania / log n [ns]')
tn.set_title('Czas wykonania dla losowej tablicy / log n w zależności od wielkości (m = ' + str(m) + ', element losowy)')
tn.grid()


plt.show()