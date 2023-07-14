print('Введите строку, заканчивающуюся точкой')
s = str(input())
print('Введите символ, который необходимо удалить из строки')
star = str(input())
count, space, k, max = 0, 0, 0, 0
min = len(s)
for i in s:
    k += 1
    if i == '.':
        count += 1
    if i == ' ':
        space += 1
        if (k-1) >= max:
            max = k-1
        if (k-1) <= min:
            min = k-1
        k = 0
if count > 0:
    print('а. Длина строки =', len(s))
    print('b. Количество слов в строке =', space+1)
    print('c. Длина самого короткого и самого длинного слова соответственно:', min, max)
    news = str()
    for i in s:
        if i != star:
            news = news + i*2
    print('d. Преобразованная строка: ', news)
else:
    print('Введите строку, удовлетворяющую условиям задачи')
