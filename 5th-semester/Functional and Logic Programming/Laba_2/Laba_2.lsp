; Program name: Laba_2.lsp
; Author: Andrew
; Creation date: 20.11.2023
; Description:

(trace UFunc)
(defun UFunc (n double_n sum)
    (cond ((<= n 0) (format T "�������� n ������ ���� >0. ��������� ����.~%~%"))
          ((> n 0) (cond ((< double_n n) sum)
                          ((>= double_n n) (setq sum (+ sum double_n)) (UFunc n (- double_n 2) sum))))))

;��������������� ������� ��� main
(defun submain ()
      ;����������� ��� ����� ��������� ��� ����������� ������� UFunc
     (format T " ������� ����� ����� n ��� ���������� ����� ���� �����~%������ ����� �� n �� 2n: ")
     ;������ � ������ n ��������� ������
     (setq n (read))
     (format T "~%~%")
     ;����� �������������� ������� � ������� ����������� � ������ UFunc_res
     (setq UFunc_res (UFunc n (* 2 n) 0))
     (format T "~%~%")
     ;���������� ����������� ���������� � ����
     (cond ((not UFunc_res)) (
     (setq my_output_stream (open "outdata.txt" :direction :output))
     (print n my_output_stream)
     (print UFunc_res my_output_stream)
     (terpri my_output_stream)
     (close my_output_stream)
     ; ����������� �������� submain � �������� ������ ���������� ��������� ������ ����������,
     ;� ����� ����� ������������� ���������.
     (format T "��������� ���������� �������: ~A.~%" UFunc_res)
     (format T "��������� ���������� ����������� ������� UFunc ������� � ���� outdata.txt~%"))))

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
