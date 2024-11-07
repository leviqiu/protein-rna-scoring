# protein-rna-scoring
A scoring function for assessing protein-rna complex structures

To compile:
```
g++ -Wall -m64 -std=c++11 -I. -c *.cpp
g++ -Wall -m64 -std=c++11 -I. -o calcScore *.o -lm
```
To run the program:
```
./calcScore 1VFG_protein.pdb 1VFG_rna.pdb
```
1VFG_protein.pdb is the file for the protein structure, and 1VFG_rna.pdb is for the RNA structure. These two files are provided in the testcases folder.
The output score for the test case is -269.7, though minor difference is possible due to different systems used to testing.

Note: you must copy the vdwr.dat file to the folder where you execute the program.
