import matplotlib.pyplot as plt
import statistics as stat
import math

x = [i for i in range(100, 10001, 100)]
dual_quickC = [[] for i in range(100)]
dual_quickS = [[] for i in range(100)]
quickC = [[] for i in range(100)]
quickS = [[] for i in range(100)]
quick_selectC = [[] for i in range(100)]
quick_selectS = [[] for i in range(100)]
dual_quick_selectC = [[] for i in range(100)]
dual_quick_selectS = [[] for i in range(100)]

m = 0
with open('output/zad5/dual_quick100.out') as file:
    for line in file:
        if ('Liczba porownan miedzy kluczami' in line):
            m = m + 1


for i in x:
    with open('output/zad5/dual_quick' + str(i) + '.out') as file:
        for line in file:
            #print(line)
            if ('Liczba porownan miedzy kluczami' in line):
                dual_quickC[(i)//100 -1].append(int((line.split('kluczami: ')[1]).split()[0]))
            if ('Czas w mikrosekundach:' in line):
                #print("xd")
                dual_quickS[(i)//100 -1].append(int((line.split('mikrosekundach: ')[1]).split()[0]))
    with open('output/zad5/quick' + str(i) + '.out') as file:
        for line in file:
            if ('Liczba porownan miedzy kluczami' in line):
                quickC[(i)//100 -1].append(int((line.split('kluczami: ')[1]).split()[0]))
            if ('Czas w mikrosekundach:' in line):
                quickS[(i)//100 -1].append(int((line.split('mikrosekundach: ')[1]).split()[0]))
    with open('output/zad5/quick_select' + str(i) + '.out') as file:
        for line in file:
            if ('Liczba porownan miedzy kluczami' in line):
                quick_selectC[(i)//100 -1].append(int((line.split('kluczami: ')[1]).split()[0]))
            if ('Czas w mikrosekundach:' in line):
                quick_selectS[(i)//100 -1].append(int((line.split('mikrosekundach: ')[1]).split()[0]))
    with open('output/zad5/dual_quick_select' + str(i) + '.out') as file:
        for line in file:
            if ('Liczba porownan miedzy kluczami' in line):
                dual_quick_selectC[(i)//100 -1].append(int((line.split('kluczami: ')[1]).split()[0]))
            if ('Czas w mikrosekudnach:' in line):
                dual_quick_selectS[(i)//100 -1].append(int((line.split('mikrosekudnach: ')[1]).split()[0]))


fig, ((c, cn),(s, sn)) = plt.subplots(2,2)
c.plot(x,[stat.mean(dual_quickC[i]) for i in range(100)],'r',label='Liczba porównań dual quick')
c.plot(x,[stat.mean(quickC[i]) for i in range(100)],'g',label='Liczba porównań quick')
c.plot(x,[stat.mean(quick_selectC[i]) for i in range(100)],'b',label='Liczba porównań quick (select)')
c.plot(x,[stat.mean(dual_quick_selectC[i]) for i in range(100)],'m',label='Liczba porównań dual quick (select)')
c.legend(loc="upper left")
c.set(xlabel='Wielkość tablicy', ylabel='Liczba porównań')
c.set_title('Liczba porównań dla losowej tablicy w zależności od wielkości (m = ' + str(m) + ', k losowe)')
c.grid()

cn.plot(x,[stat.mean(dual_quickC[i])/(((i+1)*100)*math.log2((i+1)*100)) for i in range(100)],'r',label='Liczba porównań / n log n dual quick')
cn.plot(x,[stat.mean(quickC[i])/(((i+1)*100)*math.log2((i+1)*100)) for i in range(100)],'g',label='Liczba porównań / n log n quick')
cn.plot(x,[stat.mean(quick_selectC[i])/(((i+1)*100)*math.log2((i+1)*100)) for i in range(100)],'b',label='Liczba porównań / n log n quick (select)')
cn.plot(x,[stat.mean(dual_quick_selectC[i])/(((i+1)*100)*math.log2((i+1)*100)) for i in range(100)],'m',label='Liczba porównań / n log n dual quick (select)')
cn.legend(loc="upper left")
cn.set(xlabel='Wielkość tablicy', ylabel='Liczba porównań')
cn.set_title('Liczba porównań dla losowej tablicy / n log n w zależności od wielkości (m = ' + str(m) + ', k losowe)')
cn.grid()

s.plot(x,[stat.mean(dual_quickS[i]) for i in range(100)],'r',label='Czas wykonywania dual quick')
s.plot(x,[stat.mean(quickS[i]) for i in range(100)],'g',label='Czas wykonywania quick')
s.plot(x,[stat.mean(quick_selectS[i]) for i in range(100)],'b',label='Czas wykonywania quick (select)')
s.plot(x,[stat.mean(dual_quick_selectS[i]) for i in range(100)],'m',label='Czas wykonywania dual quick (select)')
s.legend(loc="upper left")
s.set(xlabel='Wielkość tablicy', ylabel='Czas wykonywania')
s.set_title('Czas wykonywania dla losowej tablicy w zależności od wielkości (m = ' + str(m) + ', k losowe)')
s.grid()

sn.plot(x,[stat.mean(dual_quickS[i])/(((i+1)*100)*math.log2((i+1)*100)) for i in range(100)],'r',label='Czas wykonywania / n log n dual quick')
sn.plot(x,[stat.mean(quickS[i])/(((i+1)*100)*math.log2((i+1)*100)) for i in range(100)],'g',label='Czas wykonywania / n log n quick')
sn.plot(x,[stat.mean(quick_selectS[i])/(((i+1)*100)*math.log2((i+1)*100)) for i in range(100)],'b',label='Czas wykonywania / n log n quick (select)')
sn.plot(x,[stat.mean(dual_quick_selectS[i])/(((i+1)*100)*math.log2((i+1)*100)) for i in range(100)],'m',label='Czas wykonywania / n log n dual quick (select)')
sn.legend(loc="upper left")
sn.set(xlabel='Wielkość tablicy', ylabel='Czas wykonywania')
sn.set_title('Czas wykonywania dla losowej tablicy / n log n w zależności od wielkości (m = ' + str(m) + ', k losowe)')
sn.grid()


plt.show()