# Функция для создания матрицы смежности на основе данных вершин графа
def read_graph():
    if 0 < n <= 10:
        def_matrix = [[0 for _ in range(n)] for _ in range(n)]
        print('Введите матрицу смежности орграфа: ')
        for i in range(n):
            s_matrix_in_str = str(input())
            k = 0
            for j in range(n):
                def_matrix[i][j] = int(s_matrix_in_str[k])
                k += 2
        print('Матрица смежности: ')  # По вертикали предшественники, по горизонтали преемники
        return def_matrix
    else:
        return print('Число вершин орграфа не удовлетворяют условию')


n = int(input('Введите число n вершин орграфа, где 0<n<=10: '))
s_matrix = read_graph()
if 0 < n <= 10:
    print('\n'.join([str(s_matrix[i]) for i in range(len(s_matrix))]))
print()


# Функция нахождения вершин, имеющих предшественников и преемников
def neighbors_search(def_matrix):
    print('a) Вершины под номерами:', end=' ')
    for i in range(n):
        k1, k2 = 0, 0  # критерий наличия предшественника и преемника ссоответственно
        for j in range(n):
            if def_matrix[j][i] == 1:
                k1 += 1
            if def_matrix[i][j] == 1:
                k2 += 1
        if (k1 > 0) and (k2 > 0):
            print(i, end=' ')
    return print('\n')


neighbors_search(s_matrix)


# Функция, выписывающая дуги орграфа
def arc_graph(def_matrix):
    print('б) Список дуг орграфа: ')
    for i in range(n):
        for j in range(n):
            if def_matrix[i][j] == 1:
                print(i, '->', j)
    return print()


arc_graph(s_matrix)


# Функция нахождения числа преемников вершины, имеющей наибольшие число преемников
def max_graph_of_k1(def_matrix):
    k1max = 0
    for i in range(n):
        k1 = 0  # аналогичное обозначение предшественника, как выше
        for j in range(n):
            if def_matrix[i][j] == 1:
                k1 += 1
        if k1 >= k1max:
            k1max = k1
    return k1max


a = max_graph_of_k1(s_matrix)


# Функция нахождения вершины или вершин с максимальным числом преемников
def k1max_graph(def_matrix):
    print('в) Максимальное число преемников =', a, '. Искомые вершины:', end=' ')
    for i in range(n):
        k1 = 0  # аналогичное обозначение предшественника, как выше
        for j in range(n):
            if def_matrix[i][j] == 1:
                k1 += 1
        if k1 == a:
            print(i, end=' ')
    return print('\n')


k1max_graph(s_matrix)


# Функция, определяющая число вершин, соединённых дугами в обоих направлениях
def both_arc_count(def_matrix):
    both_arc_mass = []
    for i in range(n):
        for j in range(n):
            if (def_matrix[i][j] == def_matrix[j][i] == 1) and (i not in both_arc_mass):
                both_arc_mass.append(i)
    print('г) Число вершин, соединённых дугами в обоих направлениях:', len(both_arc_mass))
    return print('Это вершины:', both_arc_mass)


both_arc_count(s_matrix)
