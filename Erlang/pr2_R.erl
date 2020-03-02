%author Diem Vu
% 6/7/2019
% project assignment 2 TCSS 380

-module(pr2_R).
-export([dominoes/1,flip/1, isRing/1,listAsString/1,solution/1,driver/3,pick/3,solutionHelper/1,len/1,giveRandom/1,findMax/2]).


% create  a list of tuples containing all the tiles in the set of double-N dominoes
dominoes(N) ->
    % create two  sequences of all the number from 0 to N
    L1 = lists:seq(0,N),
    L2 = lists:seq(0,N),
    dominoes(L1,L2).

%create a list of tupples by grabbing one element from both sequences and ignore duplicate  
dominoes([],_)->[];
dominoes(_,[]) ->[];
dominoes([H1|T1], [H2|T2]) -> [{H1,H2}] ++ dominoes([H1],T2) ++ dominoes (T1,T2).

% given a list of tuples, returns randomly assembled list of tuples where the
%algorithm picks a random tuple to begin the list and then picks randomly another tuple that matches the preceding one
giveRandom (L) ->
    % randomly pick the first tupple from a list
    N = rand:uniform(len(L)),
    First = lists:nth(N,L),
    Num = rand:uniform(1),
    % randomly create a list based on the first tupple , the second tupple need to match the first or the second element of the first tupple and so on
    X = pr2_R:pick(element(Num +1,First), L, []),
    X.

% a helper method of giveRandom to pick the next tupple from the a list of tupple based on the previous tupple 
pick(_,[], HoldList) -> HoldList; 
pick(X, DominoesList, HoldList) ->
    % create a list of tuple have the first element or the second element equals to the value X
    OptionList = [Y || Y <- DominoesList, (element(1,Y) == X) or (element(2,Y) == X)],
    % find the length of the List have all the potential tupple can be put into the solution list
    Len = pr2_R:len(OptionList),
    if 
        Len > 0 ->  pickHelper(X, OptionList, DominoesList, HoldList);
        % keep grabbing the one tupple until the list is out of tupple
        true -> HoldList
    end.

% helper function for pick function 
pickHelper(X, OptionList, DominoesList, HoldList) ->

    Len = pr2_R: len(OptionList),
    % pick a random tupple from the OptionList
    M = lists:nth(rand:uniform(Len),OptionList),
    A = element(1, M),
    B = element(2, M),
    case X of
        % if the second element of the tupple is the same as the value that we need to compare, the next value will 
        %will be pased in will be the second element of the tupple and vice versa
        A -> pick( element(2,M),lists:delete(M, DominoesList) , [M] ++ HoldList);
        B -> pick(element(1,M), lists:delete(M, DominoesList), [M] ++ HoldList);
        _Other -> done
    end.
      
% find length of a list
len([]) -> 0;
len([_|T]) -> 1 + len(T).


% find the maximum number in a list
findMax(X,[]) -> X;
findMax(X,[H|T]) when (X >= element(1,H)) and (X >= element(2,H)) -> findMax(X, T);
findMax(X,[H|T]) when (X < element(1,H)) and (element(2,H) =< element(1,H))-> findMax(element(1,H), T);
findMax(X,[H|T]) when (X < element(2,H)) and (element(2,H) >= element(1,H)) -> findMax(element(2,H), T).


% check if a list can form a Ring by flipping tupples
isRing(L) -> 
    % find the maximum of the list first
    Max = findMax(0, L),
    Len = pr2_R:len(L),
    % length of the list have to be equal to the size of the tupple dominoes(Max) can generate.
    M = (Max +1)*(Max +2) / 2,
    if M == Len ->
        isRingHelp(L);
        true -> false
    end.

% helper method to check if a List is a ring
isRingHelp(L) ->
    X = len(L),
    case X of
        0 -> false;
        1 -> isRingOne(L);
        2 -> isRingTwo(L);
        _Other -> isRingHelperHeadTail(L)           
    end.

%check when a list have only 2 tupple
isRingTwo([{N,M},{A,B}]) ->
    X = ((N == A) and (M == B)) or (( N == B) and (A == M)),
    case X of
        true -> true;
        false -> false
    end. 
% check when a list have 1 tupple
isRingOne([{N,M}])  when N=/=M -> false;
isRingOne([{N,M}]) when N== M -> true.

%check if the the last and the first tupple of the list match
isRingHelperHeadTail(L) ->
    X = starter(L),
    A = element(1,X),
    B = element(2,X),
    case X of 
        -1 -> false;
        _Other -> isRingHelper(A, tl(L)) == B
    end.

%check if the whole list match 
isRingHelper(X,[])  -> X;
isRingHelper(Num,[H|_])  when (Num =/= element(2, H)) and (Num =/= element(1, H)) -> false;
isRingHelper(Num,[H|T])  when ( Num == element(1, H)) -> X = element(2, H),
    isRingHelper(X, T );
isRingHelper(Num,[H|T])  when (Num == element(2, H)) -> X = element(1, H),
    isRingHelper(X, T ).

%find the first number to compare to the whole list 
starter(L) ->
    Len = pr2_R:len(L),
    A = lists:nth(1,L),
    B = lists:nth(Len,L),
    getStarter(A,B).

% find the first number to be the first number to compare the second tupple with
getStarter({N,M},{A, B}) when (N == A) or (N == B) -> {M,N};
getStarter({N,M},{A, B}) when (M == A) or (M == B) -> {N,M};
getStarter({_,M},{A, B}) when (M =/= A) and (M =/= B)-> {-1,-1}.

% if a list can form a ring, flip tiles to make a ring
flip(L) ->
    Boolean = pr2_R:isRing(L),
    case Boolean of
       true -> flipHelper(L);
       false -> []
    end.

% compare each tupple to the tupple after it and flip the next one
flipHelper([]) -> [];
flipHelper([{N,M}]) -> [{N,M}];
flipHelper([{N,M}|[{A,B}|T]]) when (M =/= A)  and (M =/= B)-> [{M,N}] ++ flipHelper([{B,A}|T]);
flipHelper([{N,M}|[{A,B}|T]]) when (M =/= A)  and (M == B)-> [{N,M}] ++ flipHelper([{B,A}|T]);
flipHelper([{N,M}|[{A,B}|T]]) when M == A -> [{N,M}] ++ flipHelper([{A,B}|T]).

%generate solution by combining all the previous function, return empty list if the number passed in is odd
solution(N) when (N rem 2) == (1) -> [];
solution(N) when (N rem 2) == (0) ->
    L = dominoes(N), 
    solutionHelper(L).

%generate solution based off the list created by dominoes
solutionHelper(L) ->
    M = giveRandom(L),
    IsR = pr2_R:isRing(M),
    Len = pr2_R:len(M),
    Length = pr2_R:len(L),
    if 
        (IsR == true) and (Len == Length) -> pr2_R:flip(M);
        true -> solutionHelper(L)
    end.

% convert the solution into a string
listAsString([]) -> "[]";
listAsString(L) ->"[" ++ listAsStringHelp(L) ++"]".

% convert all the tupple into string with specific format
listAsStringHelp([H|[]]) -> listAsStringHelper(H);
listAsStringHelp([H|T]) ->
   listAsStringHelper(H) ++ ", " ++ listAsStringHelp(T).
%convert each tuple into string with specific format
listAsStringHelper({N, M}) ->
    "{"++lists:flatten(io_lib:format("~w, ", [N])) ++ lists:flatten(io_lib:format("~w", [M])) ++ "}".

% convert solution into a string by combining all the method
driver(F1, F2, N) ->
    F1(F2(N)).