% Power function
power(_, 0, 1).
power(Base, Exponent, Result) :-
    Exponent > 0,
    NewExponent is Exponent - 1,
    power(Base, NewExponent, SubResult),
    Result is Base * SubResult.

% Square of a number
square(Number, Result) :-
    Result is Number * Number.

% Modulus of two numbers
modulus(Dividend, Divisor, Result) :-
    Result is Dividend mod Divisor.

% Minimum of three numbers
min_of_three(X, Y, Z, Min) :-
    Min is min(X, min(Y, Z)).

% Maximum of three numbers
max_of_three(X, Y, Z, Max) :-
    Max is max(X, max(Y, Z)).

% Minimum of two numbers
min_of_two(X, Y, Min) :-
    Min is min(X, Y).

% Maximum of two numbers
max_of_two(X, Y, Max) :-
    Max is max(X, Y).

% Sum of two numbers
sum(X, Y) :-
    S is X + Y,
    write(S).

% Subtraction of two numbers
sub(X, Y) :-
    S is X - Y,
    write(S).

% Multiplication of two numbers
multi(X, Y) :-
    S is X * Y,
    write(S).
