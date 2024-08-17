; Program name: Laba_4.lsp
; Author: Andrew
; Creation date: 02.12.2023
; Description:

(trace UFunc)
;Пользовательская функция реализующая индивидуальное задание
(defun UFunc (UTree)
    (print UTree my_output_stream)
    (cond ((null UTree) T)
        (T (let ((root       (car UTree))
                 (left_tree  (cadr UTree))
                 (right_tree (caddr UTree)))
             (cond ((and left_tree right_tree)
                    (and (> root (car left_tree))
                         (< root (car right_tree))
                         (UFunc left_tree)
                         (UFunc right_tree)))
                   (left_tree (and (> root (car left_tree)) (UFunc left_tree)))
                   (right_tree (and (< root (car right_tree)) (UFunc right_tree)))
                   (T T))))))

(defun submain ()
    (format T "~%~%")
    ;Получение исходного дерева из файла inpdata.txt
    (setq my_input_stream (open "inpdata.txt" :direction :input))
    (setq UTree (read my_input_stream))
    (close my_input_stream)
     ;Сохранение полученного результата в файл outdata.txt
    (setq my_output_stream (open "outdata.txt" :direction :output))
    (setq UFunc_res (Ufunc UTree))
    (if (equal UFunc_res T)
        (print 'YES my_output_stream)
        (print 'NO my_output_stream))
    (terpri my_output_stream)
    (close my_output_stream)
    (format T "Результат вывода упорядоченного бинарного дерева записан в outdata.txt~%"))

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



