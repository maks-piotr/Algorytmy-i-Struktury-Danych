import matplotlib.pyplot as plt
import statistics as stat

x = [i for i in range(100, 10001, 100)]
select3C = [[] for i in range(100)]
select5C = [[] for i in range(100)]
select7C = [[] for i in range(100)]
select9C = [[] for i in range(100)]

m = 0
with open('output/zad3/select3_100.out') as file:
    for line in file:
        if ('Liczba porownan miedzy kluczami' in line):
            m = m + 1


for i in x:
    with open('output/zad3/select3_' + str(i) + '.out') as file:
        for line in file:
            if ('Czas w mikrosekundach' in line):
                select3C[(i)//100 -1].append(int((line.split('mikrosekundach: ')[1]).split()[0]))
    with open('output/zad3/select5_' + str(i) + '.out') as file:
        for line in file:
            if ('Czas w mikrosekundach' in line):
                select5C[(i)//100 -1].append(int((line.split('mikrosekundach: ')[1]).split()[0]))
    with open('output/zad3/select7_' + str(i) + '.out') as file:
        for line in file:
            if ('Czas w mikrosekundach' in line):
                select7C[(i)//100 -1].append(int((line.split('mikrosekundach: ')[1]).split()[0]))
    with open('output/zad3/select9_' + str(i) + '.out') as file:
        for line in file:
            if ('Czas w mikrosekundach' in line):
                select9C[(i)//100 -1].append(int((line.split('mikrosekundach: ')[1]).split()[0]))


fig, ((c, cn)) = plt.subplots(2,1)
c.plot(x,[stat.mean(select3C[i]) for i in range(100)],'r',label='Czas wykonania select_3')
c.plot(x,[stat.mean(select5C[i]) for i in range(100)],'g',label='Czas wykonania select_5')
c.plot(x,[stat.mean(select7C[i]) for i in range(100)],'b',label='Czas wykonania select_7')
c.plot(x,[stat.mean(select9C[i]) for i in range(100)],'m',label='Czas wykonania select_9')
c.legend(loc="upper left")
c.set(xlabel='Wielkość tablicy', ylabel='Czas wykonania')
c.set_title('Czas wykonania dla losowej tablicy w zależności od wielkości (m = ' + str(m) + ', k losowe)')
c.grid()

cn.plot(x,[stat.mean(select3C[i])/((i+1)*100) for i in range(100)],'r',label='Czas wykonania / n select_3')
cn.plot(x,[stat.mean(select5C[i])/((i+1)*100) for i in range(100)],'g',label='Czas wykonania / n select_5')
cn.plot(x,[stat.mean(select7C[i])/((i+1)*100) for i in range(100)],'b',label='Czas wykonania / n select_7')
cn.plot(x,[stat.mean(select9C[i])/((i+1)*100) for i in range(100)],'m',label='Czas wykonania / n select_9')
cn.legend(loc="upper left")
cn.set(xlabel='Wielkość tablicy', ylabel='Czas wykonania')
cn.set_title('Czas wykonania dla losowej tablicy / n w zależności od wielkości (m = ' + str(m) + ', k losowe)')
cn.grid()



plt.show()