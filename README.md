pseudo-malloc che per:
     - richieste di  piccole dimensioni (minori di 1/4 di pagina) usa il buddy allocator dove per semplicità si utilizza un singolo buddy allocator implementato con la bit map
     - richieste di grandi dimensioni (maggiori o uguali a 1/4 di pagina) usa la mmap
