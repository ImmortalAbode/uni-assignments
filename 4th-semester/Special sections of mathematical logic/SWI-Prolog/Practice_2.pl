% g = 4212, n = 3
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

arctg(Value,_):-
    not(abs(Value)<1),
    writeln("X should lie in the interval (-1,1).").
arctg(Value, X):-
    X is atan(Value).

approximate(I,_,_):-
    I<0,
    writeln("Row member index (I) should be nonnegative (I>=0).").
approximate(I,_,_):-
    not(integer(I)),
    writeln("Row member index (I) should be integer.").
approximate(_,X,_):-
    not(abs(X)<1),
    writeln("X should lie in the interval (-1,1).").
approximate(0,X,Summary):-Summary is X,!.
approximate(I,X,NewSummary):-
    I > 0,
    I_Prev is I - 1,
    my_pow(-1,I,Value_1),
    my_pow(X,2*I+1,Value_2),
    approximate(I_Prev,X,PrevSummary),
    NewSummary is PrevSummary+((Value_1*Value_2)/(2*I+1)).

my_compare(X, Result,Compare):-
    Compare is abs(X-Result).

print_results(I,_):-
    I<0,
    writeln("Row member index (I) should be nonnegative (I>=0).").
print_results(I,_):-
    not(integer(I)),
    writeln("Row member index (I) should be integer.").
print_results(_,X):-
    not(abs(X)<1),
    writeln("X should lie in the interval (-1,1).").
print_results(Index,Value):-
    arctg(Value,X),
    approximate(Index,Value,Summary),
    my_compare(X, Summary, Compare),
    format('Index = ~6f',[Index]), nl,
    format('Value = ~6f',[Value]), nl,
    writef("arctg(%d) = ",[Value]),
    format('~9f',[X]), nl,
    writef("Approximate value of arctg(%d) with count of row member index %d is ",[Value,Index]),
    format('~9f',[Summary]), nl,
    writef("The absolutely error of arctg(%d) values is ",[Value]),
    format('~9f',[Compare]), nl.
















