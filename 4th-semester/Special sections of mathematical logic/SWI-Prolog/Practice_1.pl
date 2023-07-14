%����� � ����� ������� �� "���� ���������".
%������� �������� ����������� ��������� (������) "��������".
parent("Eddard Stark", "Jhon Snow").
parent("Unknow female", "John Snow").
parent("Eddard Stark", "Robb Stark").
parent("Katelin Talli", "Robb Stark").
parent("Eddard Stark", "Sansa Stark").
parent("Katelin Stark", "Sansa Stark").
parent("Eddard Stark", "Arya Stark").
parent("Katelin Stark", "Arya Stark").
parent("Eddard Stark", "Ricon Stark").
parent("Katelin Stark", "Ricon Stark").
parent("Eddard Stark", "Bran Stark").
parent("Katelin Stark", "Bran Stark").
parent("Ricard Stark", "Eddard Stark").
parent("Liarra Stark", "Eddard Stark").
parent("Ricard Stark", "Lianna Stark").
parent("Liarra Stark", "Lianna Stark").
parent("Ricard Stark", "Benjen Stark").
parent("Liarra Stark", "Benjen Stark").
parent("Edwil Stark", "Ricard Stark").
parent("Marna Locke", "Ricard Stark").
parent("Willam Stark", "Edwil Stark").
parent("Melanta Blackwood", "Edwil Stark").
parent("Willam Stark", "Jocelyn Stark").
parent("Melanta Blackwood", "Jocelyn Stark").
%������� �������� ������������ ��������� (������) "�������".
male("Eddard Stark").
male("Jhon Snow").
male("Robb Stark").
male("Ricon Stark").
male("Bran Stark").
male("Ricard Stark").
male("Benjen Stark").
male("Edwil Stark").
male("Willam Stark").
%������� �������� ������������ ��������� (������) "�������".
female("Unknown female").
female("Katelin Talli").
female("Sansa Stark").
female("Arya Stark").
female("Liarra Stark").
female("Lianna Stark").
female("Marna Stark").
female("Melanta Blackwood").
female("Jocelyn Stark").

%�������� �������� ����� "���� ���������", POV(point of view) ���������.
%������� �������� ������������ ��������� (������) "�������".
pov("Sansa Stark").
pov("Arya Stark").
pov("John Snow").
pov("Bran Stark").
pov("Eddard Stark").
pov("Katelin Talli").


%������������� �������� ����� �������.
%������� �������� ������������ ��������� (������) "�����������".
peculiarities("Arya Stark", princess, warg, left-handed, "Nymeria direwolf").
peculiarities("Sansa Stark", princess, warg, lady, "Lady direwolf").
peculiarities("Bran Stark", prince, warg, tree-seer, "Summer direwolf").
peculiarities("Ricon Stark", prince, warg, child, "Shaggy Dog direwolf").
peculiarities("John Snow", bastard, warg, "Lord Commander of the Night's Watch", "Ghost direwolf").
peculiarities("Robb Stark", prince, warg, commander, "Gray Wind direwolf").

%�������������� �� ���������� ����������.
%������� �������� ����������� ��������� " ���� ��������".
born("John Snow", 283).
born("Arya Stark", 289).
born("Sansa Stark", 286).
born("Ricon Stark", 295).
born("Bran Stark", 290).
born("Robb Stark", 283).

%�������.
%������� �������� ��������� (�������) "����".
mother(X,Y) :- parent(X,Y),female(X).
%������� �������� ��������� (�������) "����".
father(X,Y) :- parent(X,Y),male(X).
%������� �������� ��������� (�������) "�������".
child(X,Y) :- parent(Y,X).
%������� �������� ��������� (�������) "�������".
grandmother(X,Y) :- mother(X,Z),parent(Z,Y).
%������� �������� ��������� (�������) "�������".
grandfather(X,Y) :- father(X,Z),parent(Z,Y).
%������� �������� ��������� (�������) "������".
sister(X,Y) :- parent(Z,X), parent(Z,Y), female(X).
%������� �������� ��������� (�������) "����".
brother(X,Y) :- parent(Z,X), parent(Z,Y), male(X).
%������� �������� ��������� (�������) "����".
aunt(X,Y) :- sister(X,Z), parent(Z,Y).
%������� �������� ��������� (�������) "����".
uncle(X,Y) :- brother(X,Z), parent(Z,Y).

%goals - ����

%�����1: "�������� �� Arya Stark ����������� (tree-seer)?"
goal1 :- peculiarities("Arya Stark", _, _, tree-seer, _).
%�����2: "�������� �� Eddard Stark ����� Sansa Stark?"
goal2 :- parent("Eddard Stark", "Sansa Stark").
%�����3: "�������� �� Lianna Stark ����� Sansa Stark?"
goal3 :-  aunt("Lianna Stark", "Sansa Stark").
%�����4: "�������� �� Arya Stark �������?"
goal4 :-  peculiarities("Arya Stark", _, _, right-handed, _).

%�����5: "��� �������� �������� ��������� �����?"
goal5(X) :- pov(X).
%�����6: "����� � Eddard'� Stark'� ���� ���������� ��������?"
goal6(X) :- parent("Eddard Stark", X), female(X).
%�����7: "��� �������� ������ Willam'a Stark'a?"
goal7(X) :- grandfather("Willam Stark", X), male(X).

%�����8: "��� �������� ��������, ������, �� ������� ����� 285 ���� �� �.�.?"
goal8(X):- female(X), peculiarities(X, _, warg, _, _), born(X, Y), (not(Y<285)).

%�����9: "��� ����� ��������� ��������?"
goal9 :-  peculiarities(X, _, _, _, "Ghost direwolf"), writef("%t has direwolf named Ghost.\n", [X]),fail.
%�����10: "Willam Stark ����� ������������ ��� ������������ � �����?"
goal10 :- grandfather("Willam Stark", X), parent(X, Y), (male(Y);female(Y)), writef("%t's grandgrandchild Willam's Stark.\n", [Y]),fail.
%�����11: "�������� �� Lianna Stark ����� ��� Robb Stark?"
goal11 :- aunt("Lianna Stark", "Robb Stark"), writeln("Lianna Stark is aunt for Robb Stark.").
%�����12: "�������� �� Benjen Stark ����� ��� �������� ��� Ricon Stark?"
goal12 :- (uncle("Benjen Stark", "Ricon Stark"), write("Benjen Stark is uncle for Ricon Stark."); grandfather("Benjen Stark", "Ricon Stark"),
           write("Benjen Stark is grandfather for Ricon Stark.")), nl.
