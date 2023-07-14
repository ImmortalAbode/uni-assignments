import random

T = [[[random.randint(-1000, 1000) for i in range(0, 7)] for j in range(0, 5)] for k in range(0, 3)]
print('Ваш трёхмерный список T, выведенный в виде 3-х матриц 5х7:')
for k in range(0, 3):
    for i in range(0, 5):
        for j in range(0, 7):
            print('%5d' % T[k][i][j], end='')
        print()
    print()
m = T[0][0][0]
for k in range(0, 3):
    for i in range(0, 5):
        for j in range(0, 7):
            if T[k][i][j] > m:
                m = T[k][i][j]
                ind = '['+str(k)+']'+'['+str(i)+']'+'['+str(j)+']'
print('Максимальный элемент массива Т:', m, 'с индексами', ind)
