aresame(pair(X,X)).
istree(nil).
istree(t(_,L,R)) :- istree(L), istree(R),!.

maxtree(nil, -99999).
%maxtree(t(V,nil,nil), V).
maxtree(t(V,L,R),Max) :- maxtree(L, Lmax), maxtree(R, Rmax), V > Lmax, V > Rmax, Max = V.
maxtree(t(V,L,R),Max) :- maxtree(L, Lmax), maxtree(R, Rmax), Rmax > V, Rmax > Lmax, Max = Rmax.
maxtree(t(V,L,R),Max) :- maxtree(L, Lmax), maxtree(R, Rmax), Lmax > V, Lmax > Rmax, Max = Lmax.

mintree(nil, 99999).
%maxtree(t(V,nil,nil), V).
mintree(t(V,L,R),Max) :- mintree(L, Lmax), mintree(R, Rmax), V < Lmax, V < Rmax, Max = V.
mintree(t(V,L,R),Max) :- mintree(L, Lmax), mintree(R, Rmax), Rmax < V, Rmax < Lmax, Max = Rmax.
mintree(t(V,L,R),Max) :- mintree(L, Lmax), mintree(R, Rmax), Lmax < V, Lmax < Rmax, Max = Lmax.




isbst(nil).
isbst(t(V,L,R)) :- maxtree(L, Lmax), mintree(R, Rmin), Lmax < V, V < Rmin,
	isbst(L),isbst(R).

bst_contains(nil, _) :- fail.
bst_contains(t(V,_,_), V) .
bst_contains(t(V,L,_), X) :- X < V, bst_contains(L, X).
bst_contains(t(V,_,R), X) :- X > V, bst_contains(R, X).

bst_count(nil, 0).
bst_count(t(_,L,R), C) :- CC is 1,
	bst_count(L, CL), bst_count(R, CR),
	C is CC + CL + CR.

bst_sum(nil, 0).
bst_sum(t(V,L,R), S) :- bst_sum(L, SL), bst_sum(R, SR), S is V + SL + SR.

preorder(nil).
preorder(t(V,L,R)) :- write(V),write(' '), preorder(L), preorder(R).

inorder(nil).
inorder(t(V,L,R)) :- inorder(L), write(V), write(' '), inorder(R).

postorder(nil).
postorder(t(V,L,R)) :- postorder(L), postorder(R), write(V), write(' ').

bst_max(t(M,nil,nil), M).
bst_max(t(_,_,R), M) :- bst_max(R, M).

bst_leaf_count(nil, 0).
bst_leaf_count(t(_,nil,nil), C) :- C is 1.
bst_leaf_count(t(_,L,R), C) :- bst_leaf_count(L, CL),
	bst_leaf_count(R, CR), C is CR + CL, !.

%testing tree [0-6]
%%t(3,t(1,t(0,nil,nil),t(2,nil,nil)),t(5,t(4,nil,nil),t(6,nil,nil)))
