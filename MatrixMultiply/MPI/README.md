**This code is to achieve MPI-based matrix multiplication.**

**Problem:**
    Matrixes _A_ and _B_ are both _n * n_ matrixes, matrix _C_ = _A * B_, and _C_ is calculated.

**Idea:**
    Firstly, Dividing matrix _A_ into _numprocs_ equal parts. If divisible, then each process handles matrix multiplication of size _n/numproces * n_. If not, set a variable to contain the remain of matrix _A_.Each process calculates the matrix multiplication of its own part, assigns one to calculate the rest and pass the first address of the calculated result to process 0, and process 0 prints it after receiving it.
