#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <qdock.hpp>
#include <particleList.hpp>
#include <genericerror.hpp>

coor & coor::operator+(const coor & c)
{
	x += c.x;
	y += c.y;
	z += c.z;
	return *this;
}

atom::atom(const coor Pos,
	   const qd_real Vdwr,
	   const qd_real Charge,
	   const qd_real Ace,
	   const qd_int  Type,
	   const qd_int  Resseq,
	   const qd_int  Idx,
	   const char	 Icode,
	   const char	*AtomName,
	   const char	*ResName,
	   const char	*ChainId,
	   const char	*Altloc)
{
	pos = Pos;
	vdwr = Vdwr;
	charge = Charge;
	ace = Ace;
	type = Type;
	resseq = Resseq;
	idx = Idx;
	icode = Icode;
	strcpy(atomname, AtomName);
	strcpy(resname, ResName);
	strcpy(chainid, ChainId);
	strcpy(altloc, Altloc);	
}

atom::atom(const atom & a)
{
	pos = a.pos;
	vdwr = a.vdwr;
	charge = a.charge;
	ace = a.ace;
	type = a.type;
	resseq = a.resseq;
	idx = a.idx;
	icode = a.icode;
	strcpy(atomname, a.atomname);
	strcpy(resname, a.resname);
	strcpy(chainid, a.chainid);
	strcpy(altloc, a.altloc);
}

atom & atom::operator=(const atom & a)
{
	if (this == &a)
		return *this;
	pos = a.pos;
	vdwr = a.vdwr;
	charge = a.charge;
	ace = a.ace;
	type = a.type;
	resseq = a.resseq;
	idx = a.idx;
	icode = a.icode;
	strcpy(atomname, a.atomname);
	strcpy(resname, a.resname);
	strcpy(chainid, a.chainid);
	strcpy(altloc, a.altloc);
	return *this;
}

std::ostream & operator<<(std::ostream & os, const atom & a)
{
	os << std::setw(6) << std::left << "ATOM  ";
	os << std::setw(5) << std::right << a.idx;
	os << std::setw(1) << " ";
	os << std::setw(4) << std::left << a.atomname;
	os << std::setw(1) << a.altloc;
	os << std::setw(3) << a.resname;
	os << std::setw(1) << " ";
	os << std::setw(1) << a.chainid; 
	os << std::setw(4) << std::right << a.resseq;
	os << std::setw(1) << a.icode;
	os << std::setw(3) << "   ";
	os << std::setw(8) << std::setprecision(3) << std::fixed << a.pos.x;
	os << std::setw(8) << std::setprecision(3) << std::fixed << a.pos.y;
	os << std::setw(8) << std::setprecision(3) << std::fixed << a.pos.z;
	os << std::setw(6) << std::setprecision(2) << std::fixed << 1.0f;
	os << std::setw(6) << std::setprecision(2) << std::fixed << 0.0f;
	os << std::setw(6) << "      ";
	os << std::setw(4) << " ";
	os << std::setw(2) << " "; 
	os << std::setw(2) << "  " << std::endl;
	return os;	
}

std::ofstream & operator<<(std::ofstream & ofs, const atom & a)
{
	if (ofs.is_open()) {
		ofs << std::setw(6) << std::left << "ATOM  ";
		ofs << std::setw(5) << std::right << a.idx;
		ofs << std::setw(1) << " ";
		ofs << std::setw(4) << std::left << a.atomname;
		ofs << std::setw(1) << a.altloc;
		ofs << std::setw(3) << a.resname;
		ofs << std::setw(1) << " ";
		ofs << std::setw(1) << a.chainid;
		ofs << std::setw(4) << std::right << a.resseq;
		ofs << std::setw(1) << a.icode;
		ofs << std::setw(3) << "   ";
		ofs << std::setw(8) << std::setprecision(3) << std::fixed << a.pos.x;
		ofs << std::setw(8) << std::setprecision(3) << std::fixed << a.pos.y;
		ofs << std::setw(8) << std::setprecision(3) << std::fixed << a.pos.z;
		ofs << std::setw(6) << std::setprecision(2) << std::fixed << 1.0f;
		ofs << std::setw(6) << std::setprecision(2) << std::fixed << 0.0f;
		ofs << std::setw(6) << "      ";
		ofs << std::setw(4) << " ";
		ofs << std::setw(2) << " ";
		ofs << std::setw(2) << "  " << std::endl;
	} else
		gen_error(FATAL, __FILE__, __LINE__, "output stream is not open.");
	return ofs;
}
