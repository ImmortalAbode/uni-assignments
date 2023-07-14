%Факты о семье Старков из "Игры престолов".
%Задание простого двуместного предиката (фактов) "родитель".
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
%Задание простого одноместного предиката (фактов) "мужчина".
male("Eddard Stark").
male("Jhon Snow").
male("Robb Stark").
male("Ricon Stark").
male("Bran Stark").
male("Ricard Stark").
male("Benjen Stark").
male("Edwil Stark").
male("Willam Stark").
%Задание простого одноместного предиката (фактов) "женщина".
female("Unknown female").
female("Katelin Talli").
female("Sansa Stark").
female("Arya Stark").
female("Liarra Stark").
female("Lianna Stark").
female("Marna Stark").
female("Melanta Blackwood").
female("Jocelyn Stark").

%Ключевые личности серии "Игра престолов", POV(point of view) персонажи.
%Задание простого одноместного предиката (фактов) "главный".
pov("Sansa Stark").
pov("Arya Stark").
pov("John Snow").
pov("Bran Stark").
pov("Eddard Stark").
pov("Katelin Talli").


%Отличительные качества детей Старков.
%Задание простого пятиместного предиката (фактов) "особенности".
peculiarities("Arya Stark", princess, warg, left-handed, "Nymeria direwolf").
peculiarities("Sansa Stark", princess, warg, lady, "Lady direwolf").
peculiarities("Bran Stark", prince, warg, tree-seer, "Summer direwolf").
peculiarities("Ricon Stark", prince, warg, child, "Shaggy Dog direwolf").
peculiarities("John Snow", bastard, warg, "Lord Commander of the Night's Watch", "Ghost direwolf").
peculiarities("Robb Stark", prince, warg, commander, "Gray Wind direwolf").

%Летоисчисление от завоевания Вестеросса.
%Задание простого двуместного предиката " дата рождения".
born("John Snow", 283).
born("Arya Stark", 289).
born("Sansa Stark", 286).
born("Ricon Stark", 295).
born("Bran Stark", 290).
born("Robb Stark", 283).

%Правила.
%Задание сложного предиката (правила) "мать".
mother(X,Y) :- parent(X,Y),female(X).
%Задание сложного предиката (правила) "отец".
father(X,Y) :- parent(X,Y),male(X).
%Задание сложного предиката (правила) "ребенок".
child(X,Y) :- parent(Y,X).
%Задание сложного предиката (правила) "бабушка".
grandmother(X,Y) :- mother(X,Z),parent(Z,Y).
%Задание сложного предиката (правила) "дедушка".
grandfather(X,Y) :- father(X,Z),parent(Z,Y).
%Задание сложного предиката (правила) "сестра".
sister(X,Y) :- parent(Z,X), parent(Z,Y), female(X).
%Задание сложного предиката (правила) "брат".
brother(X,Y) :- parent(Z,X), parent(Z,Y), male(X).
%Задание сложного предиката (правила) "тетя".
aunt(X,Y) :- sister(X,Z), parent(Z,Y).
%Задание сложного предиката (правила) "дядя".
uncle(X,Y) :- brother(X,Z), parent(Z,Y).

%goals - цели

%Цель№1: "Является ли Arya Stark древовидцем (tree-seer)?"
goal1 :- peculiarities("Arya Stark", _, _, tree-seer, _).
%Цель№2: "Является ли Eddard Stark отцом Sansa Stark?"
goal2 :- parent("Eddard Stark", "Sansa Stark").
%Цель№3: "Является ли Lianna Stark тетей Sansa Stark?"
goal3 :-  aunt("Lianna Stark", "Sansa Stark").
%Цель№4: "Является ли Arya Stark правшой?"
goal4 :-  peculiarities("Arya Stark", _, _, right-handed, _).

%Цель№5: "Кто является ключевой личностью серии?"
goal5(X) :- pov(X).
%Цель№6: "Какие у Eddard'а Stark'а есть наследницы престола?"
goal6(X) :- parent("Eddard Stark", X), female(X).
%Цель№7: "Кто является внуком Willam'a Stark'a?"
goal7(X) :- grandfather("Willam Stark", X), male(X).

%Цель№8: "Кто является девушкой, варгом, но родился после 285 года от З.В.?"
goal8(X):- female(X), peculiarities(X, _, warg, _, _), born(X, Y), (not(Y<285)).

%Цель№9: "Кто имеет лютоволка Призрака?"
goal9 :-  peculiarities(X, _, _, _, "Ghost direwolf"), writef("%t has direwolf named Ghost.\n", [X]),fail.
%Цель№10: "Willam Stark имеет праправнуков или праправнучек и каких?"
goal10 :- grandfather("Willam Stark", X), parent(X, Y), (male(Y);female(Y)), writef("%t's grandgrandchild Willam's Stark.\n", [Y]),fail.
%Цель№11: "Является ли Lianna Stark тетей для Robb Stark?"
goal11 :- aunt("Lianna Stark", "Robb Stark"), writeln("Lianna Stark is aunt for Robb Stark.").
%Цель№12: "Является ли Benjen Stark дядей или дедушкой для Ricon Stark?"
goal12 :- (uncle("Benjen Stark", "Ricon Stark"), write("Benjen Stark is uncle for Ricon Stark."); grandfather("Benjen Stark", "Ricon Stark"),
           write("Benjen Stark is grandfather for Ricon Stark.")), nl.
