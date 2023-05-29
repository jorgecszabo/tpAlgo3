for bin in arbol.o  dense.o  lista.o path-compression.o  rank-y-compression.o  union-by-rank.o
do
    ./binarios/$bin < ./inputs/random.in
done
