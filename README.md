# CR(3,7)

This is a computer-assisted proof that CR(3, 7) = 20, where CR(r, n) denotes the covering radius of Reed-Muller codes RM(r, n).

## How to test

### verification.cpp 
It is used to verify that the nl3 of fn10||fn6(A^{-1}x+A^-1b)+g(A^-1x) cannot achieve 21.

-g++ -o verification.out verification.cpp boolean_fun.cpp affine_trans.cpp

-./verification.out

### verification_1.cpp 
It is used to determine the third-order nonlinearity of fn2||fn9+g3 cannot achieve 21.

-g++ -o verification1.out verification_1.cpp boolean_fun.cpp affine_trans.cpp

-./verification1.out

### verification_2.cpp 
It is used to determine the third-order nonlinearity of fn10||fn3+g3 cannot achieve 21.

-g++ -o verification2.out verification_2.cpp boolean_fun.cpp affine_trans.cpp

-./verification2.out

### ffn_distribution.cpp 
Compute F_f(r) = {homo g : nl_2(f+g) = r}, and wrtie the results into a file.

The file is ~120MB, and it takes about two hours to finish.

You can use it to generate "Ffn2.txt","Ffn3.txt","Ffn9.txt","Ffn10.txt",

-g++ -o ffn.out ffn_distribution.cpp boolean_fun.cpp homogenous_bf_generator.cpp affine_trans.cpp

-./ffn.out

### bfs_orbit.cpp

Use BFS to find the full orbit of a given Boolean function under affine transformation.

- g++ -o bfs.out bfs_orbit.cpp boolean_fun.cpp affine_trans.cpp

- ./bfs.out


### about .txt

1. Ffn2_8.txt: storing the ANF of all homogeneous Boolean functions of degree 3 in F_fn2(8);
2. Ffn3_14.txt: storing the ANF of all homogeneous Boolean functions of degree 3 in F_fn3(14);
3. Ffn6_6.txt: storing the ANF of all homogeneous Boolean functions of degree 3 in F_fn6(6);
4. Ffn9_15.txt: storing the ANF of all homogeneous Boolean functions of degree 3 in F_fn9(15);
5. Ffn10_7.txt: storing the ANF of all homogeneous Boolean functions of degree 3 in F_fn10(7);
6. Ffn10_9.txt: storing the ANF of all homogeneous Boolean functions of degree 3 in F_fn10(9);
7. Ffn10_15.txt: storing the ANF of all homogeneous Boolean functions of degree 3 in F_fn10(15);
8. f10_af.txt: storing the set of (Ai,bi) in the form of, e,g, "[100000 010000 001000 000100 000010 000001]000000", where A={A_1,...,A_l} for l= 888832, T=Aix+bi such that (Ai,bi)f=f(Aix+bi) enumerates the orbit the fn10.
The size of (Ai,bi) is 65112.





