# -*- coding: Windows-1251 -*-
import numpy as np
import matplotlib.pyplot as plt

# Заданные параметры системы ДУ (постоянные).
b_alpha = 0.632
C_alpha = 2.63
C_beta = 3.39
i_alpha = 6.12
i_omega_z1 = 4.32
i_v = 6.82
i_delta_h = 0.359
V = 265

# Начальные приближения
alpha_0 = 2
v_0 = 1.5
omega_z1_0 = 3
delta_h_0 = 10

# Параметры интеграции
T = 10
dt = 0.01

# Функции для:
# alpha_dot = f1(t, alpha, v, omega_z1, delta_h), v_dot = f2(t, alpha, v, omega_z1, delta_h)
# omega_z1_dot = f3(t, alpha, v, omega_z1, delta_h), delta_h_dot = f4(t, alpha, v, omega_z1, delta_h)
def f1(t, alpha, v, omega_z1, delta_h):
    return -b_alpha * alpha + omega_z1


def f2(t, alpha, v, omega_z1, delta_h):
    return omega_z1


def f3(t, alpha, v, omega_z1, delta_h):
    return -C_alpha * alpha - C_beta * (-i_alpha * alpha + i_omega_z1 * omega_z1 + i_v * v + i_delta_h * delta_h)


def f4(t, alpha, v, omega_z1, delta_h):
    return V * (v - alpha) / 57.3


# Метод Рунге-Кутта 4-го порядка точности.
def RungeKutt_4_order_method(alpha_0, v_0, omega_z1_0, delta_h_0, T, dt):
    # Количество итераций.
    n = int(T / dt)
    # Инициализация массивов для хранения значений.
    time = np.arange(0, T + dt, dt)
    alpha_values = np.zeros(n + 1)
    v_values = np.zeros(n + 1)
    omega_z1_values = np.zeros(n + 1)
    delta_h_values = np.zeros(n + 1)
    # Начальные значение alpha, v, omega_z1 и delta_h из начальных условий
    alpha_values[0] = alpha_0
    v_values[0] = v_0
    omega_z1_values[0] = omega_z1_0
    delta_h_values[0] = delta_h_0

    # Реализация метода Рунге-Кутта 4-го порядка точности.
    for i in range(n):
        # Значения t, alpha, v, omega_z1 и delta_h предыдущего шага.
        t_i = time[i]
        alpha_i = alpha_values[i]
        v_i = v_values[i]
        omega_z1_i = omega_z1_values[i]
        delta_h_i = delta_h_values[i]

        # Вычисление следующего значения.
        K1 = dt * f1(t_i, alpha_i, v_i, omega_z1_i, delta_h_i)
        M1 = dt * f2(t_i, alpha_i, v_i, omega_z1_i, delta_h_i)
        L1 = dt * f3(t_i, alpha_i, v_i, omega_z1_i, delta_h_i)
        N1 = dt * f4(t_i, alpha_i, v_i, omega_z1_i, delta_h_i)

        K2 = dt * f1(t_i + dt / 2, alpha_i + K1 / 2, v_i + M1 / 2, omega_z1_i + L1 / 2, delta_h_i + N1 / 2)
        M2 = dt * f2(t_i + dt / 2, alpha_i + K1 / 2, v_i + M1 / 2, omega_z1_i + L1 / 2, delta_h_i + N1 / 2)
        L2 = dt * f3(t_i + dt / 2, alpha_i + K1 / 2, v_i + M1 / 2, omega_z1_i + L1 / 2, delta_h_i + N1 / 2)
        N2 = dt * f4(t_i + dt / 2, alpha_i + K1 / 2, v_i + M1 / 2, omega_z1_i + L1 / 2, delta_h_i + N1 / 2)

        K3 = dt * f1(t_i + dt / 2, alpha_i + K2 / 2, v_i + M2 / 2, omega_z1_i + L2 / 2, delta_h_i + N2 / 2)
        M3 = dt * f2(t_i + dt / 2, alpha_i + K2 / 2, v_i + M2 / 2, omega_z1_i + L2 / 2, delta_h_i + N2 / 2)
        L3 = dt * f3(t_i + dt / 2, alpha_i + K2 / 2, v_i + M2 / 2, omega_z1_i + L2 / 2, delta_h_i + N2 / 2)
        N3 = dt * f4(t_i + dt / 2, alpha_i + K2 / 2, v_i + M2 / 2, omega_z1_i + L2 / 2, delta_h_i + N2 / 2)

        K4 = dt * f1(t_i + dt, alpha_i + K3, v_i + M3, omega_z1_i + L3, delta_h_i + N3)
        M4 = dt * f2(t_i + dt, alpha_i + K3, v_i + M3, omega_z1_i + L3, delta_h_i + N3)
        L4 = dt * f3(t_i + dt, alpha_i + K3, v_i + M3, omega_z1_i + L3, delta_h_i + N3)
        N4 = dt * f4(t_i + dt, alpha_i + K3, v_i + M3, omega_z1_i + L3, delta_h_i + N3)

        alpha_values[i + 1] = alpha_i + (1 / 6) * (K1 + 2 * K2 + 2 * K3 + K4)
        v_values[i + 1] = v_i + (1 / 6) * (M1 + 2 * M2 + 2 * M3 + M4)
        omega_z1_values[i + 1] = omega_z1_i + (1 / 6) * (L1 + 2 * L2 + 2 * L3 + L4)
        delta_h_values[i + 1] = delta_h_i + (1 / 6) * (N1 + 2 * N2 + 2 * N3 + N4)

    return time, alpha_values, v_values, omega_z1_values, delta_h_values


# Получение значений для графиков по методу РК 4-ого порядка точности.
time, alpha_values, v_values, omega_z1_values, delta_h_values = RungeKutt_4_order_method(alpha_0, v_0, omega_z1_0, delta_h_0, T, dt)

### Отрисовка полученных графиков ###
# График возмущения угла атаки.
plt.plot(time, alpha_values, label=r'$\alpha(t)$', color='b')
# График возмущения угла тангажа.
plt.plot(time, v_values, label=r'$v(t)$', color='g')
# График скорости изменения угла тангажа.
plt.plot(time, omega_z1_values, label=r'$\omega_{z1}(t)$', color='r')
# График возмущения высоты относительно заданной.
plt.plot(time, delta_h_values, label=r'$\Delta h(t)$', color='y')

# Настройка заголовка и подписей
plt.title('Возмущение угла атаки, угла тангажа, высоты относительно заданной и скорость изменения угла тангажа')
plt.xlabel('Время (с)')
plt.ylabel('Значение')
plt.legend()
plt.grid()
# Отображение графика
plt.tight_layout()
plt.show()

# Запись результатов в файл results.txt
with open('results.txt', 'w') as txtfile:
    # Заголовок каждого из столбцов результатов.
    txtfile.write(f'{"Время (t)":<15} {"Возмущение угла атаки (alpha)":<20} {"Возмущение угла тангажа (v)":<20} {"Скорость изменения угла тангажа (w_z1)":<40} {"Изменение высоты (delta_h)":<20}\n')
    # Полученные значения.
    for i in range(len(time)):
        file_time = f'{time[i]:.3f}'
        file_alpha = f'{alpha_values[i]:.5f}'
        file_v = f'{v_values[i]:.5f}'
        file_omega_z1 = f'{omega_z1_values[i]:.5f}'
        file_delta_h = f'{delta_h_values[i]:.5f}'
        txtfile.write(f'{file_time:<15} {file_alpha:<20} {file_v:<20} {file_omega_z1:<40} {file_delta_h:<20}\n')

