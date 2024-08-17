; Program name: laba_1.lsp
; Author: Andrew
; Creation date: 20.11.2023
; Description:

; Определение вспомогательной функции log(a,x) через log по формуле log(a,x)=log(a)/log(x)
(defun log_a_x (a x)
    (/ (log x) (log a)))

;Определение пользовательской функции UF1
(defun UF1 (x)
   (+ (+ (log_a_x 2.0 x) (log_a_x 6.0 x)) (log_a_x 10.0 x)))

;Определение пользовательской функции UF2
(defun UF2 (x)
    (* (* 2.0 (sin (/ (* 2.0 x) 3.0))) (cos (/ (* 2.0 x) 3.0))))

(defun main ()
    ;Ввод пользователем произвольных значений аргументов функций UF1 и UF2
    (format T "Введите значение переменной x для UF1: ")
    (setq x_UF1 (read))
    (format T "Введите значение переменной x для UF2: ")
    (setq x_UF2 (read))
    ;Запись результатов выполнения функции соответственно в result_UF1 и result_UF2
    (setq result_UF1 (UF1 x_UF1))
    (setq result_UF2 (UF2 x_UF2))
    ;Запись в символ UFR списка из полученных результатов
    (setq UFR (list result_UF1 result_UF2))
    ;Запись в символ X1 списка, обратного списку UFR
    (setq X1 (reverse UFR))
    ;Запись в символ X2 длины списка UFR
    (setq X2 (length UFR))
    ;Запись в символ X3 суммы элементов списка UFR
    (setq X3 (apply #'+ UFR))

    ;Вывод полученных результатов
    (format T "UF1: ~a~%" result_UF1)
    (format T "UF2: ~a~%" result_UF2)
    (format T "UFR: ~a~%" UFR)
    (format T "X1: ~a~%" X1)
    (format T "X2: ~a~%" X2)
    (format T "X3: ~a~%" X3))

(main)
