import numpy as np
import matplotlib.pyplot as plt

############################################################
#                   РАСЧЕТНЫЕ ФУНКЦИИ                      #
############################################################
# ЭТАП I. Функция для вычисления необходимых сумм по исходным данным, а также квадратов величин.
def calculate_sums(xi, yi):
    xi_squared = xi ** 2
    yi_squared = yi ** 2
    xi_yi_product = xi * yi

    # Вычисление сумм
    sum_xi = np.sum(xi)
    sum_yi = np.sum(yi)
    sum_xi_squared = np.sum(xi_squared)
    sum_yi_squared = np.sum(yi_squared)
    sum_xi_yi = np.sum(xi_yi_product)

    return sum_xi, sum_yi, sum_xi_squared, sum_yi_squared, sum_xi_yi, xi_squared, yi_squared, xi_yi_product
# ЭТАП I. Функция для вычисления вспомогательных величин и коэффициентов регрессии.
def calculate_coeffs(sum_xi, sum_yi, sum_xi_squared, sum_yi_squared, sum_xi_yi, n):
    # Вычисление вспомогательных величин
    A = n * sum_xi_squared - sum_xi ** 2
    A0 = sum_yi * sum_xi_squared - sum_xi * sum_xi_yi
    A1 = n * sum_xi_yi - sum_xi * sum_yi
    B = n * sum_yi_squared - sum_yi ** 2
    B0 = sum_xi * sum_yi_squared - sum_yi * sum_xi_yi
    B1 = A1
    # Вычисление коэффициентов
    a0 = A0/A
    a1 = A1/A
    b0 = B0/B
    b1 = B1/B
    r1 = A1 / ((A * B) ** 0.5)
    r2 = B1 / ((A * B) ** 0.5)
    r = 0
    if r1!=r2:
        print("Ошибка! Линейные коэффициенты корреляции r1 = A1 / sqrt(A * B) и r2 = A2 / sqrt(A * B) должны быть равны.")
        return None
    else:
        r = r1
    # Вовзрат вычисленных величин и коэффициентов
    return A, A0, A1, B, B0, B1, a0, a1, b0, b1, r
# ЭТАП I. Интерпретация коэффициента корреляции.
def interpret_correlation(r):
    if r == 0:
        return "Отсутствует.", "Нет линейной зависимости между переменными."
    elif 0 < r < 1:
        return "Вероятностная, прямая.", "С увеличением X увеличивается Y."
    elif -1 < r < 0:
        return "Вероятностная, обратная.", "С увеличением X уменьшается Y, и наоборот."
    elif r == 1:
        return "Функциональная, прямая.", "Каждому значению X строго соответствует одно значение Y, с увеличением X увеличивается Y."
    elif r == -1:
        return "Функциональная, обратная.", "Каждому значению X строго соответствует одно значение Y, с увеличением X уменьшается Y, и наоборот."
# ЭТАП I. Вычисление несмещенной дисперсии и расчет среднего квадратического отклонения выборочного среднего.
def calculate_dispersions_errors(sum_xi, sum_yi, sum_xi_squared, sum_yi_squared, n):
    Sy_squared = 1/(n-1)*(sum_yi_squared-1/n * (sum_yi ** 2))
    Sx_squared = 1/(n-1)*(sum_xi_squared-1/n * (sum_xi ** 2))
    Sy_error = (Sy_squared ** 0.5) / (n ** 0.5)
    Sx_error = (Sx_squared ** 0.5) / (n ** 0.5)
    return Sx_squared, Sy_squared, Sx_error, Sy_error
# ЭТАП I. Оценка силы связи.
def evaluate_correlation_strength(r):
    if abs(r) <= 0.3:
        return "Практически отсутствует"
    elif 0.3 < abs(r) <= 0.5:
        return "Слабая"
    elif 0.5 < abs(r) <= 0.7:
        return "Умеренная"
    elif 0.7 < abs(r) <= 1.0:
        return "Сильная"

# ЭТАП II. Решение системы уравнений методом Гаусса.
def gauss(A, B):
    n = len(A)
    
    # Прямой ход (приводим к верхней треугольной матрице)
    for i in range(n):
        # Находим строку с максимальным элементом для стабильности
        max_row = max(range(i, n), key=lambda r: abs(A[r][i]))
        A[i], A[max_row] = A[max_row], A[i]
        B[i], B[max_row] = B[max_row], B[i]
        
        # Приводим элементы ниже главной диагонали к нулю
        for j in range(i + 1, n):
            ratio = A[j][i] / A[i][i]
            for k in range(i, n):
                A[j][k] -= ratio * A[i][k]
            B[j] -= ratio * B[i]
    
    # Обратный ход (вычисляем переменные)
    X = [0] * n
    for i in range(n - 1, -1, -1):
        X[i] = B[i] / A[i][i]
        for j in range(i - 1, -1, -1):
            B[j] -= A[j][i] * X[i]

    return X    
# ЭТАП II. Составление матрицы системы нормальных уравнений.
def create_normal_equations(x, y, degree=6):    
    # Составление матрицы A и вектора B
    A = np.zeros((degree + 1, degree + 1))
    B = np.zeros(degree + 1)
    
    for i in range(degree + 1):
        for j in range(degree + 1):
            A[i][j] = np.sum(x**(i + j))  # Сумма x^(i+j)
        B[i] = np.sum(y * (x**i))  # Сумма y * x^i

    return A, B

############################################################
#    ФУНКЦИИ ДЛЯ ОСНОВНЫХ РАСЧЕТОВ ПО РЕГРЕССИЯМ           #
############################################################
# ЭТАП II. Прямая линейная регрессия.
def direct_linear_regression(xi, yi, sum_yi, n, a0, a1):
    y_mean = sum_yi / n
    y_pred = a0 + a1 * xi
    numenator = (y_pred - y_mean) ** 2
    denominator = (yi - y_mean) ** 2
    R_squared = np.sum(numenator)/np.sum(denominator)
    return y_mean, y_pred, numenator, denominator, R_squared
# ЭТАП II. Обратная линейная регрессия.
def reverse_linear_regression(xi, yi, sum_xi, n, b0, b1):
    x_mean = sum_xi / n
    x_pred = b0 + b1 * yi
    numenator = (x_pred - x_mean) ** 2
    denominator = (xi - x_mean) ** 2
    R_squared = np.sum(numenator)/np.sum(denominator)
    return x_mean, x_pred, numenator, denominator, R_squared
# ЭТАП II. Экспоненциальная регрессия.
def exponential_regression(xi, yi, n):
    ln_yi = np.log(yi)
    ln_yi_xi = np.log(yi) * xi
    b1 = (n * np.sum(ln_yi_xi) - np.sum(ln_yi) * np.sum(xi)) / (n * np.sum(xi ** 2) - np.sum(xi) ** 2)
    b0 = 1 / n * (np.sum(ln_yi) - b1 * np.sum(xi))
    a0 = np.exp(b0)
    a1 = b1
    
    y_mean = np.sum(yi) / n;
    ln_y_pred = b0 + b1 * xi
    numenator = (ln_y_pred - np.log(y_mean)) ** 2
    denominator = (np.log(yi) - np.log(y_mean)) ** 2
    R_squared = np.sum(numenator) / np.sum(denominator)

    return ln_yi, ln_yi_xi, y_mean, ln_y_pred, numenator, denominator, R_squared, a0, a1, b0, b1
# ЭТАП II. Гиперболическая регрессия.
def hyperbolic_regression(xi, yi, n):
    zi = 1 / xi
    zi_squared = zi ** 2
    yi_zi = yi * zi
    a1 = (n * np.sum(yi_zi) - np.sum(yi) * np.sum(zi)) / (n * np.sum(zi_squared) - np.sum(zi) ** 2)
    a0 = 1/n * (np.sum(yi) - a1 * np.sum(zi))
    
    y_mean = np.sum(yi) / n
    y_pred = a0 + a1 * zi
    numenator = (y_pred - y_mean) ** 2
    denominator = (yi - y_mean) ** 2
    R_squared_hyperbolic = np.sum(numenator) / np.sum(denominator)

    return zi, zi_squared, yi_zi, a1, a0, y_mean, y_pred, numenator, denominator, R_squared_hyperbolic
# ЭТАП II. Параболическая регрессия.
def parabolic_regression(xi, yi, n):
    xi_squared = xi ** 2
    xi_cubed = xi ** 3
    xi_quarter = xi ** 4
    yi_xi_squared = yi * xi_squared
    A = [
        [n, np.sum(xi), np.sum(xi_squared)],
        [np.sum(xi), np.sum(xi_squared), np.sum(xi_cubed)],
        [np.sum(xi_squared), np.sum(xi_cubed), np.sum(xi_quarter)]
        ]
    B = [np.sum(yi), np.sum(yi * xi), np.sum(yi_xi_squared)]
    a0, a1, a2 = gauss(A, B)
    
    y_mean = np.sum(yi) / n
    y_pred = a0 + a1 * xi + a2 * xi_squared
    numenator = (y_pred - y_mean) ** 2
    denominator = (yi - y_mean) ** 2
    R_squared = np.sum(numenator) / np.sum(denominator)
    
    return xi_squared, xi_cubed, xi_quarter, yi_xi_squared, a0, a1, a2, y_mean, y_pred, numenator, denominator, R_squared
# ЭТАП II. Полиномиальная регрессия 6-й степени.
def polynom_regression(xi, yi, n):
    A, B = create_normal_equations(xi, yi, 6)
    a0, a1, a2, a3, a4, a5, a6 = gauss(A, B)
    xi_fifth = xi ** 5
    xi_sixth = xi ** 6

    y_mean = np.sum(yi) / n
    y_pred = a0 + a1 * xi + a2 * (xi ** 2) + a3 * (xi ** 3) + a4 * (xi ** 4) + a5 * xi_fifth + a6 * xi_sixth
    numenator = (y_pred - y_mean) ** 2
    denominator = (yi - y_mean) ** 2
    R_squared = np.sum(numenator) / np.sum(denominator)
    
    return xi_fifth, xi_sixth, a0, a1, a2, a3, a4, a5, a6, y_mean, y_pred, numenator, denominator, R_squared
# ЭТАП II. Степенная регрессия.
def power_regression(xi, yi, n):
    ln_xi = np.log(xi)
    ln_yi = np.log(yi)
    ln_yi_ln_xi = ln_yi * ln_xi
    b1 = (n * np.sum(ln_yi_ln_xi) - np.sum(ln_yi) * np.sum(ln_xi)) / (n * np.sum(ln_xi ** 2) - np.sum(ln_xi) ** 2)
    b0 = 1 / n * (np.sum(ln_yi) - b1 * np.sum(ln_xi))
    a0 = np.exp(b0)
    a1 = b1
    
    y_mean = np.sum(yi) / n;
    ln_y_pred = b0 + b1 * ln_xi
    numenator = (ln_y_pred - np.log(y_mean)) ** 2
    denominator = (np.log(yi) - np.log(y_mean)) ** 2
    R_squared = np.sum(numenator) / np.sum(denominator)

    return ln_xi, ln_yi, ln_yi_ln_xi, y_mean, ln_y_pred, numenator, denominator, R_squared, a0, a1, b0, b1
# ЭТАП II. Логарифмическая регрессия.
def logarithmic_regression(xi, yi, n):
    ln_xi = np.log(xi)
    yi_ln_xi = yi * ln_xi
    a1 = (n * np.sum(yi_ln_xi) - np.sum(yi) * np.sum(ln_xi)) / (n * np.sum(ln_xi ** 2) - np.sum(ln_xi) ** 2)
    a0 = 1 / n * (np.sum(yi) - a1 * np.sum(ln_xi))
    
    y_mean = np.sum(yi) / n;
    y_pred = a0 + a1 * ln_xi
    numenator = (y_pred - y_mean) ** 2
    denominator = (yi - y_mean) ** 2
    R_squared = np.sum(numenator) / np.sum(denominator)

    return ln_xi, yi_ln_xi, y_mean, y_pred, numenator, denominator, R_squared, a0, a1

############################################################
#                  ОСНОВНЫЕ ФУНКЦИИ                        #
############################################################
# Необходимые рассчеты на основе начальных данных, вывод результатов в файл и графическое отображение.
def initial_process(xi, yi, output_file):
    try:
        # Расчет необходимых данных на основе начальных.
        n = len(xi)
        sum_xi, sum_yi, sum_xi_squared, sum_yi_squared, sum_xi_yi, xi_squared, yi_squared, xi_yi_product = calculate_sums(xi, yi)
        # Расчет коэффициентов с проверкой на совпадение коэффициента корреляции при расчете по двум формулам.
        result = calculate_coeffs(sum_xi, sum_yi, sum_xi_squared, sum_yi_squared, sum_xi_yi, n)
        if result is None:
            print("Вычисления не завершены из-за ошибки. Завершение программы...")
            return None
        # Получение коэффициентов.
        A, A0, A1, B, B0, B1, a0, a1, b0, b1, r = result
        # Интерпретация коэффициента корреляции
        correlation_type, description = interpret_correlation(r) # Тип и описание
        correlation_strength = evaluate_correlation_strength(r) # Сила связи
        # Расчет несмещенной дисперсии и расчет средненого квадратического отклонения выборочного среднего.
        Sx_squared, Sy_squared, Sx_error, Sy_error= calculate_dispersions_errors(sum_xi, sum_yi, sum_xi_squared, sum_yi_squared, n)
        # Сохранение данных в файл.  
        with open(output_file, 'a') as f:
            # Исходная таблица.
            output_data = np.column_stack((yi, xi, yi_squared, xi_squared, xi_yi_product))
            header = 'yi'.ljust(12) + 'xi'.ljust(12) + 'yi^2'.ljust(12) + 'xi^2'.ljust(14) + 'xi*yi'.ljust(14)
            f.write("Таблица расчетов:\n")
            f.write(header + '\n')
            for row in output_data:
                f.write(f"{row[0]:<12.2f}{row[1]:<12.4f}{row[2]:<12.4f}{row[3]:<14.8f}{row[4]:<14.8f}\n")
            # Вспомогательные величины.
            f.write("\nВычисление вспомогательных величин для расчета коэффициентов регрессии:\n")
            f.write(f"A = {A:.10f}\n")
            f.write(f"A0 = {A0:.10f}\n")
            f.write(f"A1 = {A1:.10f}\n")
            f.write(f"B = {B:.10f}\n")
            f.write(f"B0 = {B0:.10f}\n")
            f.write(f"B1 = {B1:.10f}\n")
            # Коэффициенты корреляции.
            f.write("\nВычисление коэффициентов регрессии:\n")
            f.write(f"a0 = {a0:.10f}\n")
            f.write(f"a1 = {a1:.10f}\n")
            f.write(f"b0 = {b0:.10f}\n")
            f.write(f"b1 = {b1:.10f}\n")
            f.write(f"r = {r:.10f}\n")
            # Интерпретация корреляции.
            f.write("\nПолученный коэффициент коррелляции r позволяет сделать следующие выводы:\n")
            f.write(f"Тип связи: {correlation_type}\n")
            f.write(f"Описание связи: {description}\n")
            f.write(f"Сила связи: {correlation_strength}\n")
            # Несмещенная дисперсия.
            f.write("\nВычисленная несмещенная дисперсия:\n")
            f.write(f"Sx^2 = {Sx_squared}\n")
            f.write(f"Sy^2 = {Sy_squared}\n")
            # Среднее квадратическое отклонение выборочного среднего.
            f.write("\nВычисленное среднее квадратическое отклонения выборочного среднего:\n")
            f.write(f"Sx_cр = {Sx_error}\n")
            f.write(f"Sy_ср = {Sy_error}\n")
            f.write("===================================================================================================\n")
        print(f"Результаты, полученные на основе начальных данных, сохранены в файл '{output_file}'.")
        # Построение графика.
        plt.scatter(xi, yi, color='blue', label='Экспериментальные данные')
        plt.xlabel(f'$x_{{i}}$', fontsize=12)
        plt.ylabel(f'$y_{{i}}$', fontsize=12)
        plt.title("Построение аналитической модели по результатам эксперимента", fontsize=14)
        plt.axhline(0, color='black', linewidth=0.5)
        plt.axvline(0, color='black', linewidth=0.5)
        plt.grid(True, which='both', linestyle='--', linewidth=0.5)
        
        return sum_xi, sum_yi, n, a0, a1, b0, b1
    except Exception as e:
        print(f"Ошибка при вычислениях по исходным данным: {e}")
        return None
# Необходимые рассчеты для прямой линейной регрессии, вывод результатов в файл и графическое отображение.
def direct_linear_regression_process(xi, yi, sum_yi, n, a0, a1, output_file):
    try:
        y_mean, y_pred, numenator, denominator, R_squared_direct_linear = direct_linear_regression(xi, yi, sum_yi, n, a0, a1)
        # Сохранение данных в файл   
        with open(output_file, 'a') as f:
            # Уравнение прямой линейной регрессии
            f.write("---------------------------------------------------------------------------------------------------\n")
            f.write("Прямая линейная регрессия: y = {:.10f} + {:.10f} * x\n".format(a0, a1))
            f.write("Коэффициенты:\na0 = {:.10f},\na1 = {:.10f}\n".format(a0, a1))
            output_data = np.column_stack((yi, xi, y_pred, numenator, denominator))
            header = 'yi'.ljust(12) + 'xi'.ljust(12) + 'yi^p'.ljust(12) + '(yi^p - yср)^2'.ljust(16) + '(yi - yср)^2'.ljust(16)
            f.write("Таблица расчетов:\n")
            f.write(header + '\n')
            for row in output_data:
                f.write(f"{row[0]:<12.2f}{row[1]:<12.4f}{row[2]:<12.4f}{row[3]:<16.10f}{row[4]:<16.10f}\n")
            f.write(f"\ny_ср = {y_mean:.4f}\n")
            f.write(f"R^2 = {R_squared_direct_linear:.4f}\n")
        print(f"Результаты, полученные при вычислении для прямой линейной регрессии, сохранены в файл '{output_file}'.")
        # Построение графика
        sorted_indices = np.argsort(xi)
        x_sorted = xi[sorted_indices]
        y_pred_sorted = y_pred[sorted_indices]
        plt.plot(x_sorted, y_pred_sorted, color='green', label='Прямая линейная регрессия')
        return R_squared_direct_linear
    except Exception as e:
        print(f"Ошибка при вычислениях для прямой линейной регрессии: {e}")
        return None
# Необходиые рассчеты для обратной линейной регрессии, вывод результатов в файл и графическое отображение.
def reverse_linear_regression_process(xi, yi, sum_xi, n, b0, b1, output_file):
    try:
        x_mean, x_pred, numenator, denominator, R_squared_reverse_linear = reverse_linear_regression(xi, yi, sum_xi, n, b0, b1)
        # Сохранение данных в файл
        with open(output_file, 'a') as f:
            f.write("---------------------------------------------------------------------------------------------------\n")
            f.write("Обратная линейная регрессия: x = {:.10f} + {:.10f} * y\n".format(b0, b1))
            f.write("Коэффициенты:\nb0 = {:.10f},\nb1 = {:.10f}\n".format(b0, b1))
            output_data = np.column_stack((xi, yi, x_pred, numenator, denominator))
            header = 'xi'.ljust(12) + 'yi'.ljust(12) + 'xi^p'.ljust(12) + '(xi^p - xср)^2'.ljust(16) + '(xi - xср)^2'.ljust(16)
            f.write("Таблица расчетов:\n")
            f.write(header + '\n')
            for row in output_data:
                f.write(f"{row[0]:<12.4f}{row[1]:<12.2f}{row[2]:<12.4f}{row[3]:<16.10f}{row[4]:<16.10f}\n")
            f.write(f"\nx_ср = {x_mean:.4f}\n")
            f.write(f"R^2 = {R_squared_reverse_linear:.4f}\n")
        print(f"Результаты, полученные при вычислении для обратной линейной регрессии, сохранены в файл '{output_file}'.")
        # Построение графика обратной регрессии
        sorted_indices = np.argsort(xi)
        x_pred_sorted = x_pred[sorted_indices]
        yi_sorted = yi[sorted_indices]
        plt.plot(x_pred_sorted, yi_sorted, color='red', label='Обратная линейная регрессия')
        return R_squared_reverse_linear
    except Exception as e:
        print(f"Ошибка при вычислениях для обратной линейной регрессии: {e}")
        return None
# Необходимые рассчеты для экспоненциальной регрессии, вывод результатов в файл и графическое отображение.
def exponential_regression_process(xi, yi, n, output_file):
    try:
        ln_yi, ln_yi_xi, y_mean, ln_y_pred, numenator, denominator, R_squared_exponential, a0, a1, b0, b1 = exponential_regression(xi, yi, n)
        # Сохранение данных в файл   
        with open(output_file, 'a') as f:
            # Уравнение степенной регрессии
            f.write("---------------------------------------------------------------------------------------------------\n")
            f.write("Экспоненциальная регрессия: ln(y) = {:.10f} + {:.10f} * x или y = {:.10f} * exp^({:.10f} * x)\n".format(b0, b1, a0, a1))
            f.write("Коэффициенты:\nb0 = {:.10f},\nb1 = {:.10f},\na0 = {:.10f},\na1 = {:.10f}\n".format(b0, b1, a0, a1))
            output_data = np.column_stack((yi, xi, ln_yi, ln_yi_xi, ln_y_pred, numenator, denominator))
            header = 'yi'.ljust(12) + 'xi'.ljust(12) + 'ln_yi'.ljust(12) + 'ln_yi_xi'.ljust(12) + 'ln_yi^p'.ljust(12) + '(ln_yi^p - ln_y_ср)^2'.ljust(23) + '(ln_yi - ln_y_ср)^2'.ljust(23)
            f.write("Таблица расчетов:\n")
            f.write(header + '\n')
            for row in output_data:
                f.write(f"{row[0]:<12.2f}{row[1]:<12.4f}{row[2]:<12.6f}{row[3]:<12.8f}{row[4]:<12.6f}{row[5]:<23.10f}{row[6]:<23.10f}\n")
            f.write(f"\nln_y_ср = {y_mean:.4f}\n")
            f.write(f"R^2 = {R_squared_exponential:.4f}\n")
        print(f"Результаты, полученные при вычислении для эксконенциальной регрессии, сохранены в файл '{output_file}'.")
        # Построение графика
        sorted_indices = np.argsort(xi)
        xi_sorted = xi[sorted_indices]
        ln_y_pred_sorted = ln_y_pred[sorted_indices]
        plt.plot(xi_sorted, np.exp(ln_y_pred_sorted), color='m', label='Экспоненциальная регрессия')
        return R_squared_exponential
    except Exception as e:
        print(f"Ошибка при вычислениях для экспоненциальной регрессии: {e}")
        return None 
# Необходимые рассчеты для гиперболической регрессии, вывод результатов в файл и графическое отображение.
def hyperbolic_regression_process(xi, yi, n, output_file):
    try:
        zi, zi_squared, yi_zi, a1, a0, y_mean, y_pred, numenator, denominator, R_squared_hyperbolic = hyperbolic_regression(xi, yi, n)
        # Сохранение данных в файл   
        with open(output_file, 'a') as f:
            # Уравнение гиперболической регрессии
            f.write("---------------------------------------------------------------------------------------------------\n")
            f.write("Гиперболическая регрессия: y = {:.10f} + {:.10f} / x или y = {:.10f} + {:.10f} * z\n".format(a0, a1, a0, a1))
            f.write("Коэффициенты:\na0 = {:.10f},\na1 = {:.10f}\n".format(a0, a1))
            output_data = np.column_stack((yi, xi, zi, zi_squared, yi_zi, y_pred, numenator, denominator))
            header = 'yi'.ljust(12) + 'xi'.ljust(12) + 'zi'.ljust(12) + 'zi^2'.ljust(14) + 'yi*zi'.ljust(14) + 'yi^p'.ljust(10) + '(yi^p - y_ср)^2'.ljust(18) + '(yi - y_ср)^2'.ljust(18)
            f.write("Таблица расчетов:\n")
            f.write(header + '\n')
            for row in output_data:
                f.write(f"{row[0]:<12.2f}{row[1]:<12.4f}{row[2]:<12.4f}{row[3]:<14.4f}{row[4]:<14.6f}{row[5]:<10.2f}{row[6]:<18.8f}{row[7]:<18.8f}\n")
            f.write(f"\ny_ср = {y_mean:.4f}\n")
            f.write(f"R^2 = {R_squared_hyperbolic:.4f}\n")
        print(f"Результаты, полученные при вычислении для гиперболической регрессии, сохранены в файл '{output_file}'.")
        # Построение графика
        sorted_indices = np.argsort(xi)
        xi_sorted = xi[sorted_indices]
        y_pred_sorted = y_pred[sorted_indices]
        plt.plot(xi_sorted, y_pred_sorted, color='yellow', label='Гиперболическая регрессия')
        return R_squared_hyperbolic
    except Exception as e:
        print(f"Ошибка при вычислениях для гиперболической регрессии: {e}")
        return None 
# Необходимые рассчеты для параболической регрессии, вывод результатов в файл и графическое отображение.
def parabolic_regression_process(xi, yi, n, output_file):
    try:
        xi_squared, xi_cubed, xi_quarter, yi_xi_squared, a0, a1, a2, y_mean, y_pred, numenator, denominator, R_squared_parabolic = parabolic_regression(xi, yi, n)
        # Сохранение данных в файл   
        with open(output_file, 'a') as f:
            # Уравнение параболической регрессии
            f.write("---------------------------------------------------------------------------------------------------\n")
            f.write("Параболическая регрессия: y = {:.10f} + {:.10f} * x + {:.10f} * x^2\n".format(a0, a1, a2))
            f.write("Коэффициенты:\na0 = {:.10f},\na1 = {:.10f},\na2 = {:.10f}\n".format(a0, a1, a2))
            output_data = np.column_stack((yi, xi, xi_squared, xi_cubed, xi_quarter, yi_xi_squared, y_pred, numenator, denominator))
            header = 'yi'.ljust(12) + 'xi'.ljust(12) + 'xi^2'.ljust(16) + 'xi^3'.ljust(16) + 'xi^4'.ljust(16) + 'yi*xi^2'.ljust(16) + 'yi^p'.ljust(16) + '(yi^p - y_ср)^2'.ljust(18) + '(yi - y_ср)^2'.ljust(18)
            f.write("Таблица расчетов:\n")
            f.write(header + '\n')
            for row in output_data:
                f.write(f"{row[0]:<12.2f}{row[1]:<12.4f}{row[2]:<16.8f}{row[3]:<16.8E}{row[4]:<16.8E}{row[5]:<16.8E}{row[6]:<16.6E}{row[7]:<18.8E}{row[8]:<18.8E}\n")
            f.write(f"\ny_ср = {y_mean:.4f}\n")
            f.write(f"R^2 = {R_squared_parabolic:.4f}\n")
        print(f"Результаты, полученные при вычислении для параболической регрессии, сохранены в файл '{output_file}'.")
        # Построение графика
        sorted_indices = np.argsort(xi)
        xi_sorted = xi[sorted_indices]
        y_pred_sorted = y_pred[sorted_indices]
        plt.plot(xi_sorted, y_pred_sorted, color='lime', label='Параболическая регрессия')
        return R_squared_parabolic
    except Exception as e:
        print(f"Ошибка при вычислениях для параболической регрессии: {e}")
        return None 
# Необходимые рассчеты для полиномиальной регресии, вывод результатов в файл и графическое отображение.
def polynom_regression_process(xi, yi, n, output_file):
    try:
        xi_fifth, xi_sixth, a0, a1, a2, a3, a4, a5, a6, y_mean, y_pred, numenator, denominator, R_squared_polynom = polynom_regression(xi, yi, n)
        # Сохранение данных в файл   
        with open(output_file, 'a') as f:
            # Уравнение полиномиальной регрессии 6-го порядка.
            f.write("---------------------------------------------------------------------------------------------------\n")
            f.write("Полиномиальная регрессия: y = {:.10f} + {:.10f} * x + {:.10f} * x^2 + {:.10f} * x^3 + {:.10f} * x^4 + {:.10f} * x^5 + {:.10f} * x^6\n".format(a0, a1, a2, a3, a4, a5, a6))
            f.write("Коэффициенты:\na0 = {:.10f},\na1 = {:.10f},\na2 = {:.10f},\na3 = {:.10f},\na4 = {:.10f},\na5 = {:.10f},\na6 = {:.10f}\n".format(a0, a1, a2, a3, a4, a5, a6))
            output_data = np.column_stack((yi, xi, xi_fifth, xi_sixth, y_pred, numenator, denominator))
            header = 'yi'.ljust(12) + 'xi'.ljust(12) + 'xi^5'.ljust(16) + 'xi^6'.ljust(16) + 'yi^p'.ljust(16) + '(yi^p - y_ср)^2'.ljust(18) + '(yi - y_ср)^2'.ljust(18)
            f.write("Таблица расчетов:\n")
            f.write(header + '\n')
            for row in output_data:
                f.write(f"{row[0]:<12.2f}{row[1]:<12.4f}{row[2]:<16.8E}{row[3]:<16.8E}{row[4]:<16.8E}{row[5]:<18.8E}{row[6]:<18.8E}\n")
            f.write(f"\ny_ср = {y_mean:.4f}\n")
            f.write(f"R^2 = {R_squared_polynom:.4f}\n")
        print(f"Результаты, полученные при вычислении для полиномиальной регрессии, сохранены в файл '{output_file}'.")
        # Построение графика
        sorted_indices = np.argsort(xi)
        xi_sorted = xi[sorted_indices]
        y_pred_sorted = y_pred[sorted_indices]
        plt.plot(xi_sorted, y_pred_sorted, color='cyan', label='Полиномиальная регрессия 6-й степени')
        return R_squared_polynom
    except Exception as e:
        print(f"Ошибка при вычислениях для полиномиальной регрессии: {e}")
        return None   
# Необходимые рассчеты для степенной регресии, вывод результатов в файл и графическое отображение.
def power_regression_process(xi, yi, n, output_file):
    try:
        ln_xi, ln_yi, ln_yi_ln_xi, y_mean, ln_y_pred, numenator, denominator, R_squared_power, a0, a1, b0, b1 = power_regression(xi, yi, n)
        # Сохранение данных в файл   
        with open(output_file, 'a') as f:
            # Уравнение степенной регрессии
            f.write("---------------------------------------------------------------------------------------------------\n")
            f.write("Степенная регрессия: ln(y) = {:.10f} + {:.10f} * ln(x) или y = {:.10f} * x^{:.10f})\n".format(b0, b1, a0, a1))
            f.write("Коэффициенты:\nb0 = {:.10f},\nb1 = {:.10f},\na0 = {:.10f},\na1 = {:.10f}\n".format(b0, b1, a0, a1))
            output_data = np.column_stack((yi, xi, ln_yi, ln_xi, ln_yi_ln_xi, ln_y_pred, numenator, denominator))
            header = 'yi'.ljust(12) + 'xi'.ljust(12) + 'ln_yi'.ljust(12) + 'ln_xi'.ljust(12) + 'ln_yi_ln_xi'.ljust(12) + 'ln_yi^p'.ljust(12) + '(ln_yi^p - ln_y_ср)^2'.ljust(23) + '(ln_yi - ln_y_ср)^2'.ljust(23)
            f.write("Таблица расчетов:\n")
            f.write(header + '\n')
            for row in output_data:
                f.write(f"{row[0]:<12.2f}{row[1]:<12.4f}{row[2]:<12.6f}{row[3]:<12.6f}{row[4]:<12.8f}{row[5]:<12.6f}{row[6]:<23.10f}{row[7]:<23.10f}\n")
            f.write(f"\nln_y_ср = {y_mean:.4f}\n")
            f.write(f"R^2 = {R_squared_power:.4f}\n")
        print(f"Результаты, полученные при вычислении для степенной регрессии, сохранены в файл '{output_file}'.")
        # Построение графика
        sorted_indices = np.argsort(xi)
        xi_sorted = xi[sorted_indices]
        ln_y_pred_sorted = ln_y_pred[sorted_indices]
        plt.plot(xi_sorted, np.exp(ln_y_pred_sorted), color='brown', label='Степенная регрессия')
        return R_squared_power
    except Exception as e:
        print(f"Ошибка при вычислениях для степенной регрессии: {e}")
        return None 
# Необходимые рассчеты для логарифмической регресии, вывод результатов в файл и графическое отображение.
def logarithmic_regression_process(xi, yi, n, output_file):
    try:
        ln_xi, yi_ln_xi, y_mean, y_pred, numenator, denominator, R_squared_logarithmic, a0, a1 = logarithmic_regression(xi, yi, n)
        # Сохранение данных в файл   
        with open(output_file, 'a') as f:
            # Уравнение логарифмической регрессии
            f.write("---------------------------------------------------------------------------------------------------\n")
            f.write("Логарифмическая регрессия: y = {:.10f} + {:.10f} * ln(x)\n".format(a0, a1))
            f.write("Коэффициенты:\na0 = {:.10f},\na1 = {:.10f}\n".format(a0, a1))
            output_data = np.column_stack((yi, xi, ln_xi, yi_ln_xi, y_pred, numenator, denominator))
            header = 'yi'.ljust(12) + 'xi'.ljust(12) + 'ln_xi'.ljust(12) + 'yi_ln_xi'.ljust(12) + 'yi^p'.ljust(12) + '(yi^p - y_ср)^2'.ljust(23) + '(yi - y_ср)^2'.ljust(23)
            f.write("Таблица расчетов:\n")
            f.write(header + '\n')
            for row in output_data:
                f.write(f"{row[0]:<12.2f}{row[1]:<12.4f}{row[2]:<12.6f}{row[3]:<12.8f}{row[4]:<12.6f}{row[5]:<23.10f}{row[6]:<23.10f}\n")
            f.write(f"\ny_ср = {y_mean:.4f}\n")
            f.write(f"R^2 = {R_squared_logarithmic:.4f}\n")
        print(f"Результаты, полученные при вычислении для логарифмической регрессии, сохранены в файл '{output_file}'.")
        # Построение графика
        sorted_indices = np.argsort(xi)
        xi_sorted = xi[sorted_indices]
        y_pred_sorted = y_pred[sorted_indices]
        plt.plot(xi_sorted, y_pred_sorted, color='black', label='Логарифмическая регрессия')
        return R_squared_logarithmic
    except Exception as e:
        print(f"Ошибка при вычислениях для степенной регрессии: {e}")
        return None 
    

# Функция для проверки и загрузки данных из файла.
def load_and_validate_data(input_file):
    try:
        with open(input_file, 'r') as file:
            lines = file.readlines()[1:]

        cleaned_lines = []
        for line in lines:
            cleaned_line = "\t".join(line.strip().split())
            if cleaned_line:
                cleaned_lines.append(cleaned_line)

        data = np.array([line.split('\t') for line in cleaned_lines], dtype=float)

        yi = data[:, 0]
        xi = data[:, 1]

        if yi.shape[0] != xi.shape[0]:
            raise ValueError("Размерности массивов yi и xi должны быть равными.")

        return xi, yi
    except Exception as e:
        print(f"Ошибка при чтении или проверке данных: {e}")
        return None, None
# Основная функция для обработки данных и построения графика.
def main():
    # Организация работы с файлами и проверка полученных данных из файла.
    input_file = input("Введите путь к входному файлу (по умолчанию 'input_data.txt'): ") or "input_data.txt"
    output_file = input("Введите путь к выходному файлу для сохранения результата (по умолчанию 'output_data.txt'): ") or "output_data.txt"
    xi, yi = load_and_validate_data(input_file)
    if xi is None or yi is None:
        print("Загрузка данных не удалась.")
        return
    
    # Словарь для хранения коэффициентов детерминации (R^2) для разных типов регрессий.
    regression_r_squared = {
        "linear_direct": None,   
        "linear_reverse": None,
        "exponential": None,
        "hyperbolic": None,        
        "parabolic": None,          
        "polynomial": None,
        "power": None,
        "logarithmic": None
    }

    # Построение графика.
    plt.figure(figsize=(10, 6))
    
    ### ЭТАП I ###
    with open(output_file, 'w') as f:
        f.write("ЭТАП I.Вычисление общих данных для поставленной задачи.\n\n")
    result = initial_process(xi, yi, output_file)
    if result is None:
        return
    ### ЭТАП II ###
    with open(output_file, 'a') as f:
        f.write("ЭТАП II. Вычисление на основе полученных данных уравнений прямой и обратной линейной, гиперболической, экспоненциальной, параболической, полиномиальной регрессий\n")
    sum_xi, sum_yi, n, a0, a1, b0, b1 = result
    
    # Прямая линейная регрессия.
    result = direct_linear_regression_process(xi, yi, sum_yi, n, a0, a1, output_file)
    if result is None:
        return
    regression_r_squared['linear_direct'] = result
    
    # Обратная линейная регрессия.
    result = reverse_linear_regression_process(xi, yi, sum_xi, n, b0, b1, output_file)
    if result is None:
        return
    regression_r_squared['linear_reverse'] = result
    
    # Экспоненциальная регрессия.
    result = exponential_regression_process(xi, yi, n, output_file)
    if result is None:
        return
    regression_r_squared['exponential'] = result
    
    # Гиперболическая регрессия.
    result = hyperbolic_regression_process(xi, yi, n, output_file)
    if result is None:
        return
    regression_r_squared['hyperbolic'] = result
    
    # Параболическая регрессия.
    result = parabolic_regression_process(xi, yi, n, output_file)
    if result is None:
        return
    regression_r_squared['parabolic'] = result
    
    # Полиномиальная регрессия.
    result = polynom_regression_process(xi, yi, n, output_file)
    if result is None:
        return
    regression_r_squared['polynomial'] = result

    # Степенная регрессия.
    result = power_regression_process(xi, yi, n, output_file)
    if result is None:
        return
    regression_r_squared['power'] = result

    # Логарифмическая регрессия.
    result = logarithmic_regression_process(xi, yi, n, output_file)
    if result is None:
        return
    regression_r_squared['logarithmic'] = result

    plt.legend()
    plt.show()
    
    # Отфильтровываем только те модели, у которых есть значение R^2 (не None).
    filtered_regression_r_squared = {key: value for key, value in regression_r_squared.items() if value is not None}
    # Находим модель с максимальным значением R^2 среди отфильтрованных.
    best_model = max(filtered_regression_r_squared, key=filtered_regression_r_squared.get)
    # Записываем результат в файл.
    with open(output_file, 'a') as f:
        f.write("=====================================================================================================\n")
        f.write("Лучшая модель по величине значения коэффициента детерминации R^2 = {:.10f}: {}\n".format(filtered_regression_r_squared[best_model], best_model))
    return

# Старт программы
if __name__ == "__main__":
    main()