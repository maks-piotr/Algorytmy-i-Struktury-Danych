import matplotlib.pyplot as plt
import statistics as stat
import math

x = [i for i in range(100, 10001, 100)]
quick_wC = [[] for i in range(100)]
quick_wS = [[] for i in range(100)]
quick_select_wC = [[] for i in range(100)]
quick_select_wS = [[] for i in range(100)]

m = 0
with open('output/zad5/quick_w100.out') as file:
    for line in file:
        if ('Liczba porownan miedzy kluczami' in line):
            m = m + 1


for i in x:
    with open('output/zad5/quick_select_w' + str(i) + '.out') as file:
        for line in file:
            #print(line)
            if ('Liczba porownan miedzy kluczami' in line):
                quick_select_wC[(i)//100 -1].append(int((line.split('kluczami: ')[1]).split()[0]))
            if ('Czas w mikrosekundach:' in line):
                #print("xd")
                quick_select_wS[(i)//100 -1].append(int((line.split('mikrosekundach: ')[1]).split()[0]))
    with open('output/zad5/quick_w' + str(i) + '.out') as file:
        for line in file:
            if ('Liczba porownan miedzy kluczami' in line):
                quick_wC[(i)//100 -1].append(int((line.split('kluczami: ')[1]).split()[0]))
            if ('Czas w mikrosekundach:' in line):
                quick_wS[(i)//100 -1].append(int((line.split('mikrosekundach: ')[1]).split()[0]))


fig, ((c, cn),(s, sn)) = plt.subplots(2,2)
c.plot(x,[stat.mean(quick_select_wC[i]) for i in range(100)],'r',label='Liczba porównań quick select')
#c.plot(x,[stat.mean(quick_wC[i]) for i in range(100)],'g',label='Liczba porównań quick')
c.legend(loc="upper left")
c.set(xlabel='Wielkość tablicy', ylabel='Liczba porównań')
c.set_title('Liczba porównań dla złośliwej tablicy w zależności od wielkości (m = ' + str(m) + ', k losowe)')
c.grid()

cn.plot(x,[stat.mean(quick_select_wC[i])/(((i+1)*100)) for i in range(100)],'r',label='Liczba porównań / n quick select')
#cn.plot(x,[stat.mean(quick_wC[i])/(((i+1)*100)) for i in range(100)],'g',label='Liczba porównań / n quick')
cn.legend(loc="upper left")
cn.set(xlabel='Wielkość tablicy', ylabel='Liczba porównań')
cn.set_title('Liczba porównań dla złośliwej tablicy / n w zależności od wielkości (m = ' + str(m) + ', k losowe)')
cn.grid()

s.plot(x,[stat.mean(quick_select_wS[i]) for i in range(100)],'r',label='Czas wykonywania quick select')
#s.plot(x,[stat.mean(quick_wS[i]) for i in range(100)],'g',label='Czas wykonywania quick')
s.legend(loc="upper left")
s.set(xlabel='Wielkość tablicy', ylabel='Czas wykonywania')
s.set_title('Czas wykonywania dla złośliwej tablicy w zależności od wielkości (m = ' + str(m) + ', k losowe)')
s.grid()

sn.plot(x,[stat.mean(quick_select_wS[i])/(((i+1)*100)) for i in range(100)],'r',label='Czas wykonywania / n quick select')
#sn.plot(x,[stat.mean(quick_wS[i])/(((i+1)*100)) for i in range(100)],'g',label='Czas wykonywania / n quick')
sn.legend(loc="upper left")
sn.set(xlabel='Wielkość tablicy', ylabel='Czas wykonywania')
sn.set_title('Czas wykonywania dla złośliwej tablicy / n w zależności od wielkości (m = ' + str(m) + ', k losowe)')
sn.grid()


plt.show()