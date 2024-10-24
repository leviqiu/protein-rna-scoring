# protein-rna-scoring
a scoring function for assessing protein-rna complex structures

To compile:

g++ -Wall -m64 -std=c++11 -I. -c *.cpp
g++ -Wall -m64 -std=c++11 -I. -o calcScore *.o -lm

To run the program:

./calcScore test_protein.pdb test_rna.pdb

test_protein.pdb is the file for the protein structure, and test_rna.pdb is for the RNA structure. These two files are provided in the testcases folder.

Note: you must copy the vdwr.dat file to the folder where you execute the program.
