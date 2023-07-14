file = open('in.txt', 'r')
s = file.read()
file.close()
count = 0
num = str()
for i in s:
    if ('0' <= i <= '9') or (i == '.') or (i == ','):  # Так как число может быть нецелым, то проверяем все знаки
        num = num + i
    else:
        if len(num) >= 1:  # Так как строка может остаться пустой, а также состоять только из "." или ","
            if (num[0] == '.') or (num[0] == ','):  # Если после точки или запятой пропущен пробел
                new = num[1:]
                num = new
            if (len(num) >= 1) and ((num[len(num)-1] == '.') or (num[len(num)-1] == ',')):  # Ан-но в конце
                new = num[:len(num)-1]
                num = new
            k = 0  # Для проверки целости числа
            for j in num:
                if (j == '.') or (j == ','):
                    k += 1
            if (k == 0) and (len(num) >= 1):  # Так как строка может остаться пустой, если она была "." или ","
                count += 1
            num = str()
file = open('out.txt', 'w')
file.write(str(count))
file = open('out.txt', 'r')
print('Количество целых чисел в файле =', file.read())
file.close()
