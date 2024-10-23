#ifndef _PDB_H
#define _PDB_H

#include <string>
#include <param.hpp>
#include <particleList.hpp>

bool
isRNA(std::string&);

bool
isDNA(std::string&);

bool
isProtein(std::string&);

unsigned
getNumAtoms(const Mol&);

Mol
readPDBFile(const std::string&, const Dock_env* = 0);

void
writePDBFile(const std::string&, const Mol&, const int = 0);

#define	FOR_EACH_ATOM_CONST_BEGIN(M, A)					\
	for (unsigned i##M = 0; i##M < M.size(); i##M++) {		\
		const Atoms & a##M = M[i##M];				\
		for (unsigned j##M = 0; j##M < a##M.size(); j##M++) {	\
			const atom A = a##M[j##M];

#define FOR_EACH_ATOM_CONST_END						\
		}							\
	}

#define FOR_EACH_ATOM_BEGIN(M, A)					\
	for (unsigned i##M = 0; i##M < M.size(); i##M++) {		\
		Atoms & a##M = M[i##M];					\
		for (unsigned j##M = 0; j##M < a##M.size(); j##M++) {	\
			atom & A = a##M[j##M];

#define FOR_EACH_ATOM_END						\
		}							\
	}

void
setChainId(Mol&, const char id);

void
addAtomsToMol(Mol&, const atom&);

void
joinMols(Mol&, const Mol&);

template<typename T>
Mol 
extractSelectedAtoms(const Mol & mol, T & t)
{
	Mol	m;
	FOR_EACH_ATOM_CONST_BEGIN(mol, a) {
		if (t.predicate(a))
			addAtomsToMol(m, a);
	} FOR_EACH_ATOM_CONST_END
	return m;
}

#endif /*_PDB_H*/
