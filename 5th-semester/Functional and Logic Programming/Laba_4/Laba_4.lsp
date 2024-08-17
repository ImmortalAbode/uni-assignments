; Program name: Laba_4.lsp
; Author: Andrew
; Creation date: 02.12.2023
; Description:

(trace UFunc)
;���������������� ������� ����������� �������������� �������
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
    ;��������� ��������� ������ �� ����� inpdata.txt
    (setq my_input_stream (open "inpdata.txt" :direction :input))
    (setq UTree (read my_input_stream))
    (close my_input_stream)
     ;���������� ����������� ���������� � ���� outdata.txt
    (setq my_output_stream (open "outdata.txt" :direction :output))
    (setq UFunc_res (Ufunc UTree))
    (if (equal UFunc_res T)
        (print 'YES my_output_stream)
        (print 'NO my_output_stream))
    (terpri my_output_stream)
    (close my_output_stream)
    (format T "��������� ������ �������������� ��������� ������ ������� � outdata.txt~%"))

;������� ������� ��������� - ����� �����
(defun main ()
    ;����������� ����������� ������� ��� ������������� ������ �� ��������� ������ XLisp
    (loop
        (format T "�� ������ ������ ���������(1) ��� ����� �� ���(0)? ")
        (let ((choice (read)))
            (cond
                ((= choice 1) (submain))
                ((= choice 0) (RETURN))))))
;����� ������� ������� ���������
(main)



