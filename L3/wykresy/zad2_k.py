import matplotlib.pyplot as plt
import statistics as stat

x = [i for i in range(100, 10001, 100)]
selectC = [[] for i in range(100)]
rand_selectC = [[] for i in range(100)]
selectS = [[] for i in range(100)]
rand_selectS = [[] for i in range(100)]

m = 0
with open('output/select100.out') as file:
    for line in file:
        if ('Liczba porownan miedzy kluczami' in line):
            m = m + 1


for i in x:
    with open('output/select' + str(i) + '.out') as file:
        for line in file:
            if ('Liczba porownan miedzy kluczami' in line):
                selectC[(i)//100 -1].append(int((line.split('kluczami: ')[1]).split()[0]))
            if ('Liczba przypisan wartosci' in line):
                selectS[(i)//100 -1].append(int((line.split('wartosci: ')[1]).split()[0]))
    with open('output/random_select' + str(i) + '.out') as file:
        for line in file:
            if ('Liczba porownan miedzy kluczami' in line):
                rand_selectC[(i)//100 -1].append(int((line.split('kluczami: ')[1]).split()[0]))
            if ('Liczba przypisan wartosci' in line):
                rand_selectS[(i)//100 -1].append(int((line.split('wartosci: ')[1]).split()[0]))


fig, ((c, cn),(s, sn)) = plt.subplots(2,2)
c.plot(x,[stat.mean(selectC[i]) for i in range(100)],'b',label='Liczba porównań select')
c.plot(x,[stat.mean(rand_selectC[i]) for i in range(100)],'m',label='Liczba porównań random selecta')
c.legend(loc="upper left")
c.set(xlabel='Wielkość tablicy', ylabel='Liczba porównań')
c.set_title('Liczba porównań dla losowej tablicy w zależności od wielkości (m = ' + str(m) + ', k = wielkość tablicy / 2)')
c.grid()

cn.plot(x,[stat.mean(selectC[i])/((i+1)*100) for i in range(100)],'b',label='Liczba porównań / n select')
cn.plot(x,[stat.mean(rand_selectC[i])/((i+1)*100) for i in range(100)],'m',label='Liczba porównań / n random selecta')
cn.legend(loc="upper left")
cn.set(xlabel='Wielkość tablicy', ylabel='Liczba porównań')
cn.set_title('Liczba porównań dla losowej tablicy / n w zależności od wielkości (m = ' + str(m) + ', k = wielkość tablicy / 2)')
cn.grid()

s.plot(x,[stat.mean(selectS[i]) for i in range(100)],'b',label='Liczba przypisań select')
s.plot(x,[stat.mean(rand_selectS[i]) for i in range(100)],'m',label='Liczba przypisań random selecta')
s.legend(loc="upper left")
s.set(xlabel='Wielkość tablicy', ylabel='Liczba przypisań')
s.set_title('Liczba przypisań dla losowej tablicy w zależności od wielkości (m = ' + str(m) + ', k = wielkość tablicy / 2)')
s.grid()

sn.plot(x,[stat.mean(selectS[i])/((i+1)*100) for i in range(100)],'b',label='Liczba przypisań / n select')
sn.plot(x,[stat.mean(rand_selectS[i])/((i+1)*100) for i in range(100)],'m',label='Liczba przypisań / n random selecta')
sn.legend(loc="upper left")
sn.set(xlabel='Wielkość tablicy', ylabel='Liczba przypisań')
sn.set_title('Liczba przypisań dla losowej tablicy / n w zależności od wielkości (m = ' + str(m) + ', k = wielkość tablicy / 2)')
sn.grid()


plt.show()