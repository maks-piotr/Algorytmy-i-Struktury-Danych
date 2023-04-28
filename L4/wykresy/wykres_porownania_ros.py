import matplotlib.pyplot as plt
import statistics as stat
import math

x = [i for i in range(10000, 100001, 10000)]
bstM = [[] for i in range(10)]
bstS = [[] for i in range(10)]
rbM = [[] for i in range(10)]
rbS = [[] for i in range(10)]
splayM = [[] for i in range(10)]
splayS = [[] for i in range(10)]
k = 20


for i in x:
    with open('output/bst_ros' + str(i) + '.out') as file:
        for line in file:
            if ('Srednia porowania:' in line):
                #print(line)
                bstS[(i)//10000 -1].append(float((line.split('porowania: ')[1]).split()[0]))
            if ('Max porownan:' in line):
                #print(line)
                bstM[(i)//10000 -1].append(float((line.split('porownan: ')[1]).split()[0]))              
for i in x:
    with open('output/rb_ros' + str(i) + '.out') as file:
        for line in file:
            if ('Srednia porowania:' in line):
                #print(line)
                rbS[(i)//10000 -1].append(float((line.split('porowania: ')[1]).split()[0]))
            if ('Max porownan:' in line):
                #print(line)
                rbM[(i)//10000 -1].append(float((line.split('porownan: ')[1]).split()[0]))              
for i in x:
    with open('output/splay_ros' + str(i) + '.out') as file:
        for line in file:
            if ('Srednia porowania:' in line):
                #print(line)
                splayS[(i)//10000 -1].append(float((line.split('porowania: ')[1]).split()[0]))
            if ('Max porownan:' in line):
                #print(line)
                splayM[(i)//10000 -1].append(float((line.split('porownan: ')[1]).split()[0]))             
fig, (m, s) = plt.subplots(1,2)


m.plot(x,[stat.mean(bstM[i]) for i in range(10)],'r',label='BST')
m.plot(x,[stat.mean(rbM[i]) for i in range(10)],'b',label='RBT')
m.plot(x,[stat.mean(splayM[i]) for i in range(10)],'g',label='Splay-BST')

m.legend(loc="upper left")
m.set(xlabel='Wielkość danych wejściowych', ylabel='Maksymalna liczba porównań kluczy')
m.set_title('Maksymalna liczba porównań kluczy w operacji\n w zależności od wielkośći danych (próba statystyczna 20)\n input rosnący')
m.grid()


s.plot(x,[stat.mean(bstS[i]) for i in range(10)],'r',label='BST')
s.plot(x,[stat.mean(rbS[i]) for i in range(10)],'b',label='RBT')
s.plot(x,[stat.mean(splayS[i]) for i in range(10)],'g',label='Splay-BST')

s.legend(loc="upper left")
s.set(xlabel='Wielkość danych wejściowych', ylabel='Średnia liczba porównań kluczy')
s.set_title('Średnia liczba porównań kluczy w operacji\n w zależności od wielkośći danych (próba statystyczna 20)\n input rosnący')
s.grid()


plt.show()