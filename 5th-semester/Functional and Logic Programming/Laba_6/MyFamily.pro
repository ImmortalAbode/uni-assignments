/*****************************************************************************

		Copyright (c) My Company

 Project:  MYFAMILY
 FileName: MYFAMILY.PRO
 Purpose: No description
 Written by: Visual Prolog
 Comments:
******************************************************************************/

include "myfamily.inc"

%������� 3. A3, A13, �9, �19, �23, �10

predicates

  %������� ���������, ���������� � ���� ������.
  nondeterm parent(STRING, STRING)
  nondeterm man(STRING)
  nondeterm woman(STRING)
  nondeterm married_couple(STRING, STRING)
  
  %��������������� ���������.
  nondeterm sibling(STRING, STRING)
  nondeterm check_any_cousin_brother(STRING, STRING, INTEGER)
  
  %����������� ���������, ������������ � ������� ������� ���������.
  %�) ������� ������� ������������.
  %3. ��� (son);
  nondeterm son(STRING, STRING)
  %13. ��������� (nephew) - ��� ������� ����� ��� ������.
  nondeterm nephew(STRING, STRING)
  %�) ��������� ������� ������������.
  %9. N-������� ���� (������ ������) (any_cousin_brother);
  nondeterm any_cousin_brother(STRING, STRING, INTEGER)
  %19. ���������� ��������� (second_cousin_nephew) - ��� ����������� ����� ��� ������;
  nondeterm second_cousin_nephew(STRING, STRING)
  %23. ������� (shoot) - ������� ������-���� ������.
  nondeterm shoot(STRING, STRING, INTEGER)
  %�) ������������ �� ������.
  %10) ���� (daughters_husband) - ��� ������.
  nondeterm daughters_husband(STRING, STRING)
  
  nondeterm run()

clauses
  %�����.
  parent("�������", "����").
  parent("���������", "����� ������").
  parent("�����", "�����").
  parent("�������", "�����").
  parent("����", "����������").
  parent("���", "����������").
  parent("����������", "������").
  parent("�����", "������").
  parent("������", "����").
  parent("���", "����").
  parent("������", "������").
  parent("���", "������").
  parent("������", "�����").
  parent("��������", "�����").
  parent("������", "������").
  parent("��������", "������").
  parent("������", "�������").
  parent("��������", "�������").
  parent("������", "��������").
  parent("������", "��������").
  parent("������", "�����").
  parent("�����", "�����").
  parent("������", "�����").
  parent("�����", "�����").
  parent("�����", "��������").
  parent("��������", "��������").
  parent("�����", "��������").
  parent("��������", "���������").
  parent("�����", "���������").
  parent("�����", "������").
  parent("�����", "������").
  parent("������", "�����").
  parent("�����", "����� ��������").
  parent("�����", "����").
  parent("����", "�������").
  parent("�����", "�������").
  parent("�������", "�����").
  parent("�����", "������").
  parent("������", "������ ��������").
  parent("�����", "������ ��������").
  
  man("�������").
  man("���������").
  man("�����").
  man("�������").
  man("����").
  man("����������").
  man("������").
  man("����").
  man("������").
  man("������").
  man("������").
  man("������").
  man("�����").
  man("������").
  man("�����").
  man("�����").
  man("����").
  man("�����").
  man("������ ��������").
  
  woman("����").
  woman("����� ������").
  woman("���").
  woman("���").
  woman("�����").
  woman("�����").
  woman("�����").
  woman("������").
  woman("��������").
  woman("��������").
  woman("��������").
  woman("���������").
  woman("�����").
  woman("����� ��������").
  woman("�����").
  woman("�������").
  woman("������").
  
  married_couple("�������", "����� ������").
  married_couple("������", "��������").
  married_couple("������", "���").
  married_couple("����", "���").
  married_couple("����������", "�����").
  married_couple("������", "������").
  married_couple("������", "�����").
  married_couple("�����", "��������").
  married_couple("�����", "�����").
  married_couple("����", "�����").
  married_couple("�����", "������").
  
  %��������������� ���������.
  %��������, ��� ���� �������� ��������/��������.
  sibling(X, Y):-
  	parent(Parent, X), parent(Parent, Y), not(X = Y), !. 
  %��������, ��� N-������� ���� �������� ����. �������� ������ ��������� � �������� �� ���� ��������.
  check_any_cousin_brother(N_Brother, Child, N):-
  	man(N_Brother),
  	any_cousin_brother(N_Brother, Child, N).
  
  %������� (�� �������). �������� ������������ ��� (���, ��� ����) ��� (���, ��� ����, ������ �������)
  %���
  son(ParentChild, Parent):- 
  	parent(Parent, ParentChild), man(ParentChild).
  %���������
  nephew(Nephew, Uncle):- 
  	man(Nephew), 
  	parent(Parent, Nephew),
  	sibling(Uncle, Parent).
  %N-������� ����.
  any_cousin_brother(X, Y, 1):-
  	sibling(X, Y).
  any_cousin_brother(N_Brother, Child, N):-
  	N > 1,
  	parent(Parent_N_Brother, N_Brother),
  	parent(Parent_Child, Child),
  	M = N - 1,
  	any_cousin_brother(Parent_N_Brother, Parent_Child, M).
  %���������� ���������
  second_cousin_nephew(Second_cousin_nephew, Second_cousin_uncle):-
 	man(Second_cousin_nephew),
  	parent(Parent_1, Second_cousin_nephew), 
  	parent(Parent_2, Parent_1),
  	parent(Parent_3, Parent_2),
  	parent(Child_2, Second_cousin_uncle),
  	parent(Child_3, Child_2),
  	sibling(Parent_3, Child_3).
  %�������
  shoot(N_Child, N_Parent, 0):-
  	N_Child = N_Parent.
  shoot(N_Child, N_Parent, N):-
  	N > 0,
  	parent(N_Parent, Child),
  	M = N - 1,
  	shoot(N_Child, Child, M).
  %����
  daughters_husband(Daughters_Husband, Daughters_Parent):- 
  	man(Daughters_Husband), 
  	married_couple(Daughters_Husband,Daughter), 
  	woman(Daughter), 
  	parent(Daughters_Parent, Daughter).	 
  %�������� ������� ���������.
  run():-
  	%�������� ��������, ���������� ����������� ��������� ��������� �����:
	%1)��������� �� ������� a � ��������� R � ��������� b?[���: R(a, b)]
	%������ 1. �������� �� ����� ����� �������?
	write("�������� �� ����� ����� �������?"), nl,
	son("�����", "�������"),
	write("����� ��� ��� �������."),
	nl, nl,
	fail;
	
	%������ 2. �������� �� ����� ����������� �������?
	write("�������� �� ����� ����������� �������?"), nl,
	nephew("�����", "������"),
	write("����� ��������� ��� �������."),
	nl, nl,
	fail;
	
	
	%������ 3. �������� �� ������ ���������� ������ ���������?
	write("�������� �� ������ ���������� ������ ���������?"), nl,
	check_any_cousin_brother("������", "���������", 3),
	write("������ ���������� ���� ��� ���������."),
	nl, nl,
	fail;
	
	%������ 4. �������� �� ������� ���������� ����������� ��������?
	write("�������� �� ������� ���������� ����������� ��������?"), nl,
	second_cousin_nephew("�������", "��������"),
	write("������� ���������� ��������� ��������."),
	nl, nl,
	fail;
	
	%������ 5. �������� �� ����� ��������� �����?
	write("�������� �� ����� ��������� �����?"), nl,
	shoot("�����", "�����", 5),
	write("����� ������� �����."),
	nl, nl,
	fail;
	
	%������ 6. �������� �� ���������� ����� �������?
	write("�������� �� ���������� ����� �������?"), nl,
	daughters_husband("����������", "������"),
	write("���������� ���� �������."),
	nl, nl,
	fail;
	
	%2)��� ��������� � ��������� R � ��������� a?[���: R(a, Y), R(X, b)]
	%������ 1. ��� �������� ���������� �������?
	write("��� �������� ���������� �������?"), nl,
	parent(Parent, "�������"),
	write(Parent), 
	nl,
	fail;
	
	%������ 2. ��� �������� ����� ������?
	nl,
	write("��� �������� ����� ������?"), nl,
	daughters_husband("�����", Daughters_parent),
	write(Daughters_parent),
	nl,
	fail;
	
	%������ 3. ��� �������� ����� �������?
	nl,
	write("��� �������� ����� �������?"), nl,
	son(Son, "������"),
	write(Son),
	nl,
	fail;
	
	%3)����� ��� ���� ���������, ����������� � ��������� R. [���: R(X,Y)]".
	%������ 1.
	nl,
	write ("������ ���� ���������� �����������:"), nl,
	second_cousin_nephew(Second_cousin_nephew, Second_cousin_uncle),
	write(Second_cousin_nephew, " ��� ",Second_cousin_uncle),
	nl,
	fail;
	%������ 2.
	nl,
	write ("������ ���� �����������:"), nl,
	nephew(Nephew, Uncle),
	write(Nephew, " ��� ",Uncle),
	nl,
	fail;
	%������ 3.
	nl,
	write("������ ���� ������� ���:"), nl,
	married_couple(Man, Woman),
	write(Man, " � ",Woman),
	nl,
	fail.
	
goal
	run().
	