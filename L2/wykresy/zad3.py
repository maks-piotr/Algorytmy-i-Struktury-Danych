import matplotlib.pyplot as plt
import statistics as stat
import math

x = [i for i in range(100, 1001, 100)]
insertC = [[] for i in range(10)]
mergeC = [[] for i in range(10)]
quickC = [[] for i in range(10)]
dual_quickC = [[] for i in range(10)]
hybridC = [[] for i in range(10)]
insertS = [[] for i in range(10)]
mergeS = [[] for i in range(10)]
quickS = [[] for i in range(10)]
dual_quickS = [[] for i in range(10)]
hybridS = [[] for i in range(10)]

k = 0
with open('output/insert100.out') as file:
    for line in file:
        if ('Liczba porownan miedzy kluczami' in line):
            k = k + 1


for i in x:
    with open('output/insert' + str(i) + '.out') as file:
        for line in file:
            if ('Liczba porownan miedzy kluczami' in line):
                insertC[(i)//100 -1].append(int((line.split('kluczami: ')[1]).split()[0]))
            if ('Liczba przypisan wartosci' in line):
                insertS[(i)//100 -1].append(int((line.split('wartosci: ')[1]).split()[0]))
    with open('output/merge' + str(i) + '.out') as file:
        for line in file:
            if ('Liczba porownan miedzy kluczami' in line):
                mergeC[(i)//100 -1].append(int((line.split('kluczami: ')[1]).split()[0]))
            if ('Liczba przypisan wartosci' in line):
                mergeS[(i)//100 -1].append(int((line.split('wartosci: ')[1]).split()[0]))
    with open('output/quick' + str(i) + '.out') as file:
        for line in file:
            if ('Liczba porownan miedzy kluczami' in line):
                quickC[(i)//100 -1].append(int((line.split('kluczami: ')[1]).split()[0]))
            if ('Liczba przypisan wartosci' in line):
                quickS[(i)//100 -1].append(int((line.split('wartosci: ')[1]).split()[0]))
    with open('output/dual_quick' + str(i) + '.out') as file:
        for line in file:
            if ('Liczba porownan miedzy kluczami' in line):
                dual_quickC[(i)//100 -1].append(int((line.split('kluczami: ')[1]).split()[0]))
            if ('Liczba przypisan wartosci' in line):
                dual_quickS[(i)//100 -1].append(int((line.split('wartosci: ')[1]).split()[0]))
    with open('output/hybrid' + str(i) + '.out') as file:
        for line in file:
            if ('Liczba porownan miedzy kluczami' in line):
                hybridC[(i)//100 -1].append(int((line.split('kluczami: ')[1]).split()[0]))
            if ('Liczba przypisan wartosci' in line):
                hybridS[(i)//100 -1].append(int((line.split('wartosci: ')[1]).split()[0]))               
            
fig, (c, cn) = plt.subplots(1,2)
#c.plot(x,[stat.mean(insertC[i]) for i in range(10)],'r',label='Liczba porównań insert sort')
c.plot(x,[stat.mean(quickC[i]) for i in range(10)],'b',label='Liczba porównań quick sort')
c.plot(x,[stat.mean(dual_quickC[i]) for i in range(10)],'m',label='Liczba porównań dual quick sort')
#c.plot(x,[stat.mean(hybridC[i]) for i in range(10)],'orange',label='Liczba porównań hybrid sort')
#c.plot(x,[stat.mean(mergeC[i]) for i in range(10)],'g',label='Liczba porównań merge sort')
c.legend(loc="upper left")
c.set(xlabel='Wielkość tablicy', ylabel='Liczba porównań')
c.set_title('Liczba porównań dla losowej tablicy w zależności od wielkości (k = ' + str(k) +')')
c.grid()

#cn.plot(x,[stat.mean(insertC[i])//((i+1)*100) for i in range(10)],'r',label='Liczba porównań / n insert sort')
cn.plot(x,[stat.mean(quickC[i])/((i+1)*100*math.log2((i+1)*100)) for i in range(10)],'b',label='Liczba porównań / nlogn quick sort')
cn.plot(x,[stat.mean(dual_quickC[i])/((i+1)*100*math.log2((i+1)*100)) for i in range(10)],'m',label='Liczba porównań / nlogn dual quick sort')
#cn.plot(x,[stat.mean(hybridC[i])/((i+1)*100) for i in range(10)],'orange',label='Liczba porównań / n hybrid sort')
#cn.plot(x,[stat.mean(mergeC[i])/((i+1)*100) for i in range(10)],'g',label='Liczba porównań / n merge sort')
cn.legend(loc="upper left")
cn.set(xlabel='Wielkość tablicy = n', ylabel='Liczba porównań / n')
cn.set_title('Liczba porównań / n dla losowej tablicy w zależności od wielkości (k = ' + str(k) +')')
cn.grid()


plt.show()