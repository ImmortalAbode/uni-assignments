; Program name: Laba_2.lsp
; Author: Andrew
; Creation date: 20.11.2023
; Description:

(trace UFunc)
(defun UFunc (n double_n sum)
    (cond ((<= n 0) (format T "Значение n должно быть >0. Повторите ввод.~%~%"))
          ((> n 0) (cond ((< double_n n) sum)
                          ((>= double_n n) (setq sum (+ sum double_n)) (UFunc n (- double_n 2) sum))))))

;Вспомогательная функция для main
(defun submain ()
      ;Приглашение для ввода параметра для рекурсивной функции UFunc
     (format T " Введите целое число n для вычисления суммы ряда целых~%четных чисел от n до 2n: ")
     ;Запись в символ n введенных данных
     (setq n (read))
     (format T "~%~%")
     ;Вызов вычислительной функции с записью результатов в символ UFunc_res
     (setq UFunc_res (UFunc n (* 2 n) 0))
     (format T "~%~%")
     ;Сохранение полученного результата в файл
     (cond ((not UFunc_res)) (
     (setq my_output_stream (open "outdata.txt" :direction :output))
     (print n my_output_stream)
     (print UFunc_res my_output_stream)
     (terpri my_output_stream)
     (close my_output_stream)
     ; Возвращение функцией submain в качестве своего результата результат вызова вычисления,
     ;а также вывод информирующих сообщений.
     (format T "Результат выполнения функции: ~A.~%" UFunc_res)
     (format T "Результат выполнения рекурсивной функции UFunc записан в файл outdata.txt~%"))))

;Главная функция программы - точка входа
(defun main ()
    ;Организация пригодности функции для многократного вызова из командной строки XLisp
    (loop
        (format T "Вы хотите начать программу(1) или выйти из нее(0)? ")
        (let ((choice (read)))
            (cond
                ((= choice 1) (submain))
                ((= choice 0) (RETURN))))))
;Вызов главной функции программы
(main)
