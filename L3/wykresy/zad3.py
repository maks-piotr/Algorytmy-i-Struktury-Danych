import matplotlib.pyplot as plt
import statistics as stat

x = [i for i in range(100, 10001, 100)]
select3C = [[] for i in range(100)]
select3S = [[] for i in range(100)]
select5C = [[] for i in range(100)]
select5S = [[] for i in range(100)]
select7C = [[] for i in range(100)]
select7S = [[] for i in range(100)]
select9C = [[] for i in range(100)]
select9S = [[] for i in range(100)]

m = 0
with open('output/zad3/select3_100.out') as file:
    for line in file:
        if ('Liczba porownan miedzy kluczami' in line):
            m = m + 1


for i in x:
    with open('output/zad3/select3_' + str(i) + '.out') as file:
        for line in file:
            if ('Liczba porownan miedzy kluczami' in line):
                select3C[(i)//100 -1].append(int((line.split('kluczami: ')[1]).split()[0]))
            if ('Liczba przypisan wartosci' in line):
                select3S[(i)//100 -1].append(int((line.split('wartosci: ')[1]).split()[0]))
    with open('output/zad3/select5_' + str(i) + '.out') as file:
        for line in file:
            if ('Liczba porownan miedzy kluczami' in line):
                select5C[(i)//100 -1].append(int((line.split('kluczami: ')[1]).split()[0]))
            if ('Liczba przypisan wartosci' in line):
                select5S[(i)//100 -1].append(int((line.split('wartosci: ')[1]).split()[0]))
    with open('output/zad3/select7_' + str(i) + '.out') as file:
        for line in file:
            if ('Liczba porownan miedzy kluczami' in line):
                select7C[(i)//100 -1].append(int((line.split('kluczami: ')[1]).split()[0]))
            if ('Liczba przypisan wartosci' in line):
                select7S[(i)//100 -1].append(int((line.split('wartosci: ')[1]).split()[0]))
    with open('output/zad3/select9_' + str(i) + '.out') as file:
        for line in file:
            if ('Liczba porownan miedzy kluczami' in line):
                select9C[(i)//100 -1].append(int((line.split('kluczami: ')[1]).split()[0]))
            if ('Liczba przypisan wartosci' in line):
                select9S[(i)//100 -1].append(int((line.split('wartosci: ')[1]).split()[0]))


fig, ((c, cn),(s, sn)) = plt.subplots(2,2)
c.plot(x,[stat.mean(select3C[i]) for i in range(100)],'r',label='Liczba porównań select_3')
c.plot(x,[stat.mean(select5C[i]) for i in range(100)],'g',label='Liczba porównań select_5')
c.plot(x,[stat.mean(select7C[i]) for i in range(100)],'b',label='Liczba porównań select_7')
c.plot(x,[stat.mean(select9C[i]) for i in range(100)],'m',label='Liczba porównań select_9')
c.legend(loc="upper left")
c.set(xlabel='Wielkość tablicy', ylabel='Liczba porównań')
c.set_title('Liczba porównań dla losowej tablicy w zależności od wielkości (m = ' + str(m) + ', k losowe)')
c.grid()

cn.plot(x,[stat.mean(select3C[i])/((i+1)*100) for i in range(100)],'r',label='Liczba porównań / n select_3')
cn.plot(x,[stat.mean(select5C[i])/((i+1)*100) for i in range(100)],'g',label='Liczba porównań / n select_5')
cn.plot(x,[stat.mean(select7C[i])/((i+1)*100) for i in range(100)],'b',label='Liczba porównań / n select_7')
cn.plot(x,[stat.mean(select9C[i])/((i+1)*100) for i in range(100)],'m',label='Liczba porównań / n select_9')
cn.legend(loc="upper left")
cn.set(xlabel='Wielkość tablicy', ylabel='Liczba porównań')
cn.set_title('Liczba porównań dla losowej tablicy / n w zależności od wielkości (m = ' + str(m) + ', k losowe)')
cn.grid()

s.plot(x,[stat.mean(select3S[i]) for i in range(100)],'r',label='Liczba przypisań select_3')
s.plot(x,[stat.mean(select5S[i]) for i in range(100)],'g',label='Liczba przypisań select_5')
s.plot(x,[stat.mean(select7S[i]) for i in range(100)],'b',label='Liczba przypisań select_7')
s.plot(x,[stat.mean(select9S[i]) for i in range(100)],'m',label='Liczba przypisań select_9')
s.legend(loc="upper left")
s.set(xlabel='Wielkość tablicy', ylabel='Liczba przypisań')
s.set_title('Liczba przypisań dla losowej tablicy w zależności od wielkości (m = ' + str(m) + ', k losowe)')
s.grid()

sn.plot(x,[stat.mean(select3S[i])/((i+1)*100) for i in range(100)],'r',label='Liczba przypisań / n select_3')
sn.plot(x,[stat.mean(select5S[i])/((i+1)*100) for i in range(100)],'g',label='Liczba przypisań / n select_5')
sn.plot(x,[stat.mean(select7S[i])/((i+1)*100) for i in range(100)],'b',label='Liczba przypisań / n select_7')
sn.plot(x,[stat.mean(select9S[i])/((i+1)*100) for i in range(100)],'m',label='Liczba przypisań / n select_9')
sn.legend(loc="upper left")
sn.set(xlabel='Wielkość tablicy', ylabel='Liczba przypisań')
sn.set_title('Liczba przypisań dla losowej tablicy / n w zależności od wielkości (m = ' + str(m) + ', k losowe)')
sn.grid()


plt.show()