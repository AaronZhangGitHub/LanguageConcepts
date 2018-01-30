fibonacci(0,0).
fibonacci(1,1).
fibonacci(FibNumber, Result) :-
  FibNumber>1,
  FibNumber1 is FibNumber-1,
  FibNumber2 is FibNumber-2,
  fibonacci(FibNumber1,Result1),
  fibonacci(FibNumber2,Result2),
  Result is Result1+Result2.

fib(NthFibNumber,N) :-
  fibonacci(NthFibNumber,X),
  X = N.
