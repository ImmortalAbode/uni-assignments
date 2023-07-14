%Первая лабораторная работа.
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
goal1 :-
    peculiarities("Arya Stark", _, _, tree-seer, _), writeln("Arya Strak is tree-seer.");
    not(peculiarities("Arya Stark", _, _, tree-seer, _)), writeln("Arya Stark isn't tree-seer.").
%Цель№2: "Является ли Eddard Stark отцом Sansa Stark?"
goal2 :-
    parent("Eddard Stark", "Sansa Stark"), writeln("Arya Stark's father is Eddard Stark.");
    not(parent("Eddard Stark", "Sansa Stark")), writeln("Arya Starks's father isn't Eddard Stark.").
%Цель№3: "Является ли Lianna Stark тетей Sansa Stark?"
goal3 :-
    aunt("Lianna Stark", "Sansa Stark"), writeln("Sansa Stark's aunt is Lianna Stark."),!;
    not(aunt("Lianna Stark", "Sansa Stark")), writeln("Sansa Stark's aunt isn't Lianna Stark.").
%Цель№4: "Является ли Arya Stark правшой?"
goal4 :-
    peculiarities("Arya Stark", _, _, right-handed, _), writeln("Arya Stark is right-handed.");
    not(peculiarities("Arya Stark", _, _, right-handed, _)), writeln("Arya Stark is left-handed.").

%Цель№5: "Кто является ключевой личностью серии?"
goal5(X) :- pov(X), write(X), writeln(" is POV of series.").
%Цель№6: "Какие у Eddard'а Stark'а есть наследницы престола?"
goal6(X) :-
    parent("Eddard Stark", X), female(X), writeln(X).
%Цель№7: "Кто является внуком Willam'a Stark'a?"
goal7(X) :- grandfather("Willam Stark", X), male(X), write(X), writeln(" is Willam Stark's grandchild.").

%Цель№8: "Кто является девушкой, варгом, но родился после 285 года от З.В.?"
goal8(X):- female(X), peculiarities(X, _, warg, _, _), born(X, Y), (not(Y<285)), writeln(X).

%Цель№9: "Кто имеет лютоволка Призрака?"
goal9 :-  peculiarities(X, _, _, _, "Ghost direwolf"),write(X), writeln(" has direwolf named Ghost.").
%Цель№10: "Willam Stark имеет праправнуков или праправнучек и каких?"
goal10 :- grandfather("Willam Stark", X), parent(X, Y), (male(Y);female(Y)), write("Willam Stark's grandgrandchild is "), write(Y), writeln(".").
%Цель№11: "Является ли Lianna Stark тетей для Robb Stark?"
goal11 :- aunt("Lianna Stark", "Robb Stark"), writeln("Lianna Stark is aunt for Robb Stark."),!.
%Цель№12: "Является ли Benjen Stark дядей или дедушкой для Ricon Stark?"
goal12 :- (uncle("Benjen Stark", "Ricon Stark"), write("Benjen Stark is uncle for Ricon Stark."); grandfather("Benjen Stark", "Ricon Stark"),
           write("Benjen Stark is grandfather for Ricon Stark.")), nl,!.

%Вторая лабораторная работа.
%g = 4212, n = 3
% v = (2*(n-1)+(g(mod 5))+1)(mod 33)
% v = (2*(3-1)+(4212(mod 5))+1)(mod 33)
% v = (2*2+2+1)(mod 33)
% v = 7(mod 33)
% v = 7

my_pow(_,0,1):-!.
my_pow(X, Pow, Result):-
    Pow > 0,
    NewPow is Pow - 1,
    my_pow(X, NewPow, PrevResult),
    Result is X*PrevResult.

arctg(Value, X):-
    X is atan(Value).

approximate(0,X,Summary):-Summary is X,!.
approximate(I,X,NewSummary):-
    I > 0,
    I_Prev is I - 1,
    my_pow(-1,I,Value_1),
    my_pow(X,2*I+1,Value_2),
    approximate(I_Prev,X,PrevSummary),
    NewSummary is PrevSummary+((Value_1*Value_2)/(2*I+1)).

my_compare(Value,I,Compare):-
    arctg(Value,X),
    approximate(I,Value,Result),
    Compare is abs(X-Result).

print_results(Index,Value):-
    arctg(Value,X),
    approximate(Index,Value,Summary),
    my_compare(Value,Index,Compare),
    format('Index = ~6f',[Index]), nl,
    format('Value = ~6f',[Value]), nl,
    writef("arctg(%d) = ",[Value]),
    format('~9f',[X]), nl,
    writef("Approximate value of arctg(%d) with count of row member index %d is ",[Value,Index]),
    format('~9f',[Summary]), nl,
    writef("The absolutely error of arctg(%d) values is ",[Value]),
    format('~9f',[Compare]), nl.

%Третья лабораторная работа.
start:-
    repeat,
    nl,
    menu,
    readln(Ans),
    check(Ans).
menu:-
    writeln("Choose a command - enter:"),
    writeln("   goal1 - Является ли Arya Stark древовидцем (tree-seer)?"),
    writeln("   goal2 - Является ли Eddard Stark отцом Sansa Stark?"),
    writeln("   goal3 - Является ли Lianna Stark тетей Sansa Stark?"),
    writeln("   goal4 - Является ли Arya Stark правшой?"),
    writeln("   goal5 - Кто является ключевой личностью серии?"),
    writeln("   goal6 - Какие у Eddard'а Stark'а есть наследницы престола?"),
    writeln("   goal7 - Кто является внуком Willam'a Stark'a?"),
    writeln("   goal8 - Кто является девушкой, варгом, но родился после 285 года от З.В.?"),
    writeln("   goal9 - Кто имеет лютоволка Призрака?"),
    writeln("   goal10 - Willam Stark имеет праправнуков или праправнучек и каких?"),
    writeln("   goal11 - Является ли Lianna Stark тетей для Robb Stark?"),
    writeln("   goal12 - Является ли Benjen Stark дядей или дедушкой для Ricon Stark?"),
    writeln("   results - get all calculates of arctg values (approximate and real value, their comparison);"),
    writeln("   exit - terminate the program.").
check([goal1]):-
    goal1,
    fail.
check([goal2]):-
    goal2,
    fail.
check([goal3]):-
    goal3,
    fail.
check([goal4]):-
    goal4,
    fail.
check([goal5]):-
    goal5(_X),
    fail.
check([goal6]):-
    writeln("Heirs to the throne from Eddard Stark:"),
    goal6(_X),
    fail.
check([goal7]):-
    goal7(_X),
    fail.
check([goal8]):-
    goal8(_X),
    fail.
check([goal9]):-
    goal9,
    fail.
check([goal10]):-
    goal10,
    fail.
check([goal11]):-
    goal11,
    fail.
check([goal12]):-
    goal12,
    fail.
check([results]):-
    write("Enter number for value of X and count of row member index: "),
    readln(List),
    checkListLab2(List,Value,I, Flag),
    Flag = 1,
    print_results(I,Value),
    fail.
check([exit]):-
    writeln("Program exucution terminated.").

listLength([],0):-!.
listLength([_|Tail],Length_List):-
    listLength(Tail, Length_T),
    Length_List is Length_T+1.

checkListLab2([Head|Tail],_,_, Flag):-
    listLength([Head|Tail], Length_List),
    (   Length_List < 2; Length_List >3),
    writeln("Error data length. You shoud input two numeric arguments: negative or nonnegative number for X and nonnegative number for index."),
    Flag is 0, !.
checkListLab2([Head|Tail],_,_, Flag):-
    listLength([Head|Tail],Length),
    ( Length = 2, [A,B]=[Head|Tail], (not(integer(A);float(A));not(abs(A)<1); not(integer(B));
   not(B>=0));
   Length = 3, [A,B,C]=[Head|Tail], (not(A = '-'; A = '+');
    not(integer(B);float(B));not(abs(B)<1); not(integer(C)); not(C >= 0))),
   writeln("You shoud input two numeric arguments: X should lie in the interval (-1;1) and Row member index (I) should be integer and nonnegative (I>=0) "),
   Flag is 0, !.

checkListLab2([Head|Tail], Number_1, Number_2, Flag):-
    listLength([Head|Tail], Length),
    (   Length = 2, [A, B] = [Head|Tail];
    Length = 3, [A, B, C] = [Head|Tail]),
    (   Length = 2, Number_1 is A, Number_2 is B;
    Length = 3, A = '-', Number_1 is B*(-1), Number_2 is C;
    Length = 3, A = '+', Number_1 is B, Number_2 is C), Flag is 1.

