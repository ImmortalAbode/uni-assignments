import random

print('Введи размерности матрицы m*n, где m-число строк и n-число столбцов')
m, n = (int(i) for i in input().split())
a = [[random.randint(-1000, 1000) for i in range(0, n)] for j in range(0, m)]
print('Ваша  полученная матрица A:')
for i in range(0, m):
    for j in range(0, n):
        print('%4d' % a[i][j], end=' ')
    print()
print('Ваш полученный двумерный список: ', a)
print('Соответствующие средние арифметические столбцов матрицы:')
for j in range(0, n):
    s = 0
    for i in range(0, m):
        s = s + a[i][j]
    print(s/m, end=' ')
