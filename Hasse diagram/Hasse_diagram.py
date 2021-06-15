import itertools
import sys

def iter_paths(adj, min_length = 2, path = None): # Рекурсивный поиск всех путей в глубину
    if not path:
        for start_node in range(len(adj)):
            yield from iter_paths(adj, min_length, [start_node])
    else:
        # Генерируем пути, если находим их впервые
        if len(path) >= min_length:
            yield path
        # Если получается цикл (мы уже посещали эту вершину),
        # тогда останавливаем рекурсию
        if path[-1] in path[:-1]:  
            return
        # рекурсивно ищем все пути из текущей вершины
        current_node = path[-1]
        for next_node in range(len(adj[current_node])):
            if adj[current_node][next_node] == 1:
                yield from iter_paths(adj, min_length, path + [next_node])

tops = int(input("Введите количество вершин диаграммы Хассе: "))
edges = int(input("Введите количество рёбер диаграммы Хассе: "))
all_edges = [] # массив всех рёбер для проверки ввода 
first_tops = [] # массив минимальных элементов
check_for_first_tops = [0] * tops # массив для определения минимальных элементов
exit_status = 0 # флаг для остановки программы
graph = [[0] * tops for i in range(tops)] # матрица смежности графа


for i in range(edges):
    a, b = map(int,input("Введите через пробел начальную и конечную вершины ребра: ").split())
    all_edges.append([a, b])
    if a > tops or b > tops:
        sys.exit("Диаграмма задаётся матрицей смежности! Вы ломаете индексацию.")
    graph[a - 1][b - 1] = 1
    check_for_first_tops[b - 1] += 1
    for el in all_edges:
        if el == [b, a]:
            exit_status += 1
    if exit_status != 0:
        sys.exit("Вы ввели бред. Диаграмма Хассе - ориентированный граф!")
for i in range(len(check_for_first_tops)):
    if check_for_first_tops[i] == 0:
        first_tops.append(i + 1)

paths = list(iter_paths(graph)) # массив всех путей в графе
for row in range(len(paths)): # переводим в 1-индексацию
    for j in range(len(paths[row])):
        paths[row][j] += 1

matrix = []
basic_arr = list(x + 1 for x in range(tops))
matrix.append(first_tops) # Создаём матрицу для 
for i in range(tops - 1): # перебора всех комбинаций
    matrix.append(basic_arr) # исходных вершин

for row_comb in itertools.product(*matrix): # Используем модуль itertools для перебора
    # всех линейных порядков с помощью Декартова произведения. Используем оператор * для
    # получения каждой строки матрицы как одномерного массива.
    flag = 0 # Флаг для выбора правильных порядков
    for x in range(tops):
        if row_comb.count(x + 1) > 1: # Исключаем повторы элементов
            flag += 1
    if flag == 0: 
        for i in range(tops): # Исключаем варианты с неправильным
            for el in row_comb[:i]: # упорядовачением вершин
                for arr in paths:
                    if arr.count(row_comb[i]) != 0:
                        temp = arr[(arr.index(row_comb[i]) + 1):]
                        if temp.count(el) != 0:
                            flag += 1
                    if flag != 0:
                        break
    if flag == 0:
            print(row_comb)
                