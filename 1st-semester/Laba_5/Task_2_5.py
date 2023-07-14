file = open('graph.csv', 'r')
n = 0
for line in file:
    n += 1
file = open('graph.csv', 'r')
G = file.read()
file.close()


# Формируем таблицу из csv файла, а затем эту таблицу в матрицу
def read_graph(graph):
    pole = str()
    table = [[0 for _ in range(n)] for _ in range(n)]
    i, j = 0, 0
    for p in graph:
        if (p != '+') and (p != '\n'):
            pole = pole + p
        else:
            table[i][j] = pole
            pole = str()
            j += 1
            if j == n:
                j = 0
                i += 1
    def_matrix = [[0 for _ in range(n-1)] for _ in range(n-1)]
    for i in range(n-1):
        for j in range(n-1):
            def_matrix[i][j] = float(table[i+1][j+1])
            if def_matrix[i][j] == 0:
                def_matrix[i][j] = float('Inf')
    return def_matrix, table


s_matrix, summon_matrix = read_graph(G)
inf = float('Inf')
print('''\t Ваш список городов:\n 0 - Казань\n 1 - Санкт-Петербург\n 2 - Москва\n 3 - Нижний Новгород\n 4 - Владимир 
 5 - Тула\n 6 - Рязань\n 7 - Липецк\n 8 - Воронеж\n 9 - Белгород\n 10 - Смоленск\n 11 - Тверь\n 12 - Брянск
 13 - Ярославль\n 14 - Кастрома\n''')
print('Матрица смежности графа, моделирующего дорожную сеть: ')
print('%6s' % '', end='')
for x in range(n-1):
    print('%6s' % x, end='')
print()
for x in range(1, n):
    for y in range(n):
        if y > 0:
            print('%6s' % summon_matrix[x][y], end='')
        else:
            print('%6s' % (x-1), end='')
    print()

start, end = (int(i) for i in input('Задайте начальную и конечную точку маршрута между городами: ').split())


# Применяю алгоритм Дейкстры на поиск кратчайших путей из заданной точки
def dijkstra(g, s):
    k = len(g)
    q = [(0, s)]
    d = [inf for _ in range(k)]
    d[s] = 0
    while len(q) != 0:
        (cost, u) = q.pop(0)
        for v in range(k):
            if d[v] > d[u] + g[u][v]:
                d[v] = d[u] + g[u][v]
                q.append((d[v], v))
    return d


# Выполняю обратную задачу верхней, перебирая все варианты из конечной точки в другие, пока не найду нужное расстояние
def getpath(f):
    global short_lines
    k = len(s_matrix)
    path = [f]
    while f != start:
        for v in range(k):
            if short_lines[v] == round(short_lines[f] - s_matrix[f][v], 10):
                path.append(v)
                f = v
    return path[::-1]


short_lines = dijkstra(s_matrix, start)
print('Кратчайшее расстояние между выбранными вами городами = ', short_lines[end], 'км')
road = getpath(end)
print('Ваш маршрут:', end=' ')
for x in range(len(road)):
    print(summon_matrix[0][road[x]+1], end=' ')
    if x != len(road)-1:
        print('->', end=' ')
