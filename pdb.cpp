#include <fstream>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <string>
#include <qdock.hpp>
#include <param.hpp>
#include <pdb.hpp>
#include <particleList.hpp>
#include <genericerror.hpp>
using namespace std;

const string standardName_G   = " G ";
const string standardName_A   = " A ";
const string standardName_C   = " C ";
const string standardName_U   = " U ";
const string standardName_DA  = " DA";
const string standardName_DC  = " DC";
const string standardName_DG  = " DG";
const string standardName_DT  = " DT";
const string standardName_GLY = "GLY";
const string standardName_ARG = "ARG";
const string standardName_ASN = "ASN";
const string standardName_ASP = "ASP";
const string standardName_GLN = "GLN";
const string standardName_GLU = "GLU";
const string standardName_CYS = "CYS";
const string standardName_HIS = "HIS";
const string standardName_ALA = "ALA";
const string standardName_LEU = "LEU";
const string standardName_ILE = "ILE";
const string standardName_MET = "MET";
const string standardName_THR = "THR";
const string standardName_SER = "SER";
const string standardName_PHE = "PHE";
const string standardName_PRO = "PRO";
const string standardName_TRP = "TRP";
const string standardName_TYR = "TYR";
const string standardName_VAL = "VAL";
const string standardName_LYS = "LYS";

bool
isRNA(string & resName)
{
	size_t b, e;
	if ((b = resName.find_first_not_of(' ')) != string::npos)
		resName.erase(0, b);
	if ((e = resName.find_first_of(' ')) != string::npos)
		resName.resize(e);

	if (resName == "GUA") {
		resName = standardName_G;
		return true;
	} else if (resName == "G") {
		resName = standardName_G;
		return true;
	} else if (resName == "G3") {
		resName = standardName_G;
		return true;
	} else if (resName == "G5") {
		resName = standardName_G;
		return true;
	} else if (resName == "ADE") {
		resName = standardName_A;
		return true;
	} else if (resName == "A") {
		resName = standardName_A;
		return true;
	} else if (resName == "A3") {
		resName = standardName_A;
		return true;
	} else if (resName == "A5") {
		resName = standardName_A;
		return true;
	} else if (resName == "URA") {
		resName = standardName_U;
		return true;
	} else if (resName == "U") {
		resName = standardName_U;
		return true;
	} else if (resName == "U3") {
		resName = standardName_U;
		return true;
	} else if (resName == "U5") {
		resName = standardName_U;
		return true;
	} else if (resName == "CYT") {
		resName = standardName_C;
		return true;
	} else if (resName == "C") {
		resName = standardName_C;
		return true;
	} else if (resName == "C3") {
		resName = standardName_C;
		return true;
	} else if (resName == "C5") {
		resName = standardName_C;
		return true;
	} else
		return false;
}

bool
isDNA(string & resName)
{
	size_t b, e;
	if ((b = resName.find_first_not_of(' ')) != string::npos)
		resName.erase(0, b);
	if ((e = resName.find_first_of(' ')) != string::npos)
		resName.resize(e);

	if (resName == "DG") {
		resName = standardName_DG;
		return true;
	} else if (resName == "DG5") {
		resName = standardName_DG;
		return true;
	} else if (resName == "DG3") {
		resName = standardName_DG;
		return true;
	} else if (resName == "DA") {
		resName = standardName_DA;
		return true;
	} else if (resName == "DA5") {
		resName = standardName_DA;
		return true;
	} else if (resName == "DA3") {
		resName = standardName_DA;
		return true;
	} else if (resName == "DC") {
		resName = standardName_DC;
		return true;
	} else if (resName == "DC5") {
		resName = standardName_DC;
		return true;
	} else if (resName == "DC3") {
		resName = standardName_DC;
		return true;
	} else if (resName == "DT") {
		resName = standardName_DT;
		return true;
	} else if (resName == "DT5") {
		resName = standardName_DT;
		return true;
	} else if (resName == "DT3") {
		resName = standardName_DT;
		return true;
	} else
		return false;
}

bool
isProtein(string & resName)
{
	if (resName == "GLY") {
		return true;
	} else if (resName == "ARG") {
		return true;
	} else if (resName == "ASN") {
		return true;
	} else if (resName == "ASP") {
		return true;
	} else if (resName == "ASH") {
		resName = standardName_ASP;
		return true;
	} else if (resName == "GLN") {
		return true;
	} else if (resName == "GLU") {
		return true;
	} else if (resName == "GLH") {
		resName = standardName_GLU;
		return true;
	} else if (resName == "CYS") {
		return true;
	} else if (resName == "CYX") {
		resName = standardName_CYS;
		return true;
	} else if (resName == "CYM") {
		resName = standardName_CYS;
		return true;
	} else if (resName == "HIS") {
		return true;
	} else if (resName == "HSD") {
		resName = standardName_HIS;
		return true;
	} else if (resName == "HSE") {
		resName = standardName_HIS;
		return true;
	} else if (resName == "HSP") {
		resName = standardName_HIS;
		return true;
	} else if (resName == "HIP") {
		resName = standardName_HIS;
		return true;
	} else if (resName == "HID") {
		resName = standardName_HIS;
		return true;
	} else if (resName == "HIE") {
		resName = standardName_HIS;
		return true;
	} else if (resName == "ALA") {
		return true;
	} else if (resName == "LEU") {
		return true;
	} else if (resName == "ILE") {
		return true;
	} else if (resName == "MET") {
		return true;
	} else if (resName == "THR") {
		return true;
	} else if (resName == "SER") {
		return true;
	} else if (resName == "PHE") {
		return true;
	} else if (resName == "PRO") {
		return true;
	} else if (resName == "TRP") {
		return true;
	} else if (resName == "TYR") {
		return true;
	} else if (resName == "VAL") {
		return true;
	} else if (resName == "LYS") {
		return true;
	} else if (resName == "LYN") {
		resName = standardName_LYS;
		return true;
	} else
		return false;
}

#define LEN 1024

static void
rectifyAtomName(string & atomName)
{
	string name = atomName;
	size_t b, e;
	b = name.find_first_not_of(' ');
	if (b != string::npos)
		name.erase(0, b);
	else
		return;
	e = name.find_first_of(' ');
	if (e != string::npos)
		name.resize(e);
	if (name == "O1P")
		name = "OP1";
	if (name == "O2P")
		name = "OP2";
	size_t s = name.length();
	if (s == 1)
		atomName = "  " + name + " ";
	else if (s == 2)
		atomName = " " + name + " ";
	else if (s == 3)
		atomName = " " + name;
}

void
parsePDBLine(const string & line, 
	     coor & pos,
	     string & recName,
	     string & resName,
	     string & atomName,
	     string & altloc,
	     string & chainId,
	     string & icode,
	     string & segid,
	     string & element,
	     qd_int & idx,
	     qd_int & resseq,
	     qd_real & occupancy,
	     qd_real & tempfactor) throw(std::invalid_argument)
{
	recName = line.substr(0, 6);
	if (recName == "ATOM  " || recName == "HETATM") {
		std::string::size_type sz;
		idx = std::stoi(line.substr(6, 5), &sz);
		if (sz != 5) {
			const string & msg = string("invalid index:\n")
					   + string(line);
			throw std::invalid_argument(msg);
		}
		atomName = line.substr(12, 4);
		rectifyAtomName(atomName);
		altloc = line.substr(16, 1);
		resName = line.substr(17, 3);
		chainId = line.substr(21, 1);
		resseq = std::stoi(line.substr(22, 4), &sz);
		if (sz != 4) {
			const string & msg = string("invalid residue number:\n")
					   + string(line);
			throw std::invalid_argument(msg);
		}
		icode = line.substr(26, 1);
		pos.x = std::stof(line.substr(30, 8), &sz);
		if (sz != 8) {
			const string & msg = string("invalid x coordinate:\n")
					   + string(line);			
			throw std::invalid_argument(msg);
		}
		pos.y = std::stof(line.substr(38, 8), &sz);
		if (sz != 8) {
			const string & msg = string("invalid y coordinate:\n")
					   + string(line);
			throw std::invalid_argument(msg);
		}
		pos.z = std::stof(line.substr(46, 8), &sz);
		if (sz != 8) {
			const string & msg = string("invalid z coordinate:\n")
					   + string(line);
			throw std::invalid_argument(msg);
		}
		occupancy = std::stof(line.substr(54, 6), &sz);
		tempfactor = std::stof(line.substr(60, 6), &sz);
	//	segid = line.substr(72, 4);
	//	element = line.substr(76, 2);
		segid = " ";
		element = " ";
	}
}

Mol
readPDBFile(const string & fileName, const Dock_env *env)
{
	char	buffer[LEN];
	ifstream ifs;

	ifs.open(fileName);
	if (!ifs.is_open())
		gen_error(FATAL, __FILE__, __LINE__, "Can't open file %s.", fileName.c_str());

	char	prevChainId = '#';
	Atoms	chain;
	Mol	m;
	while (ifs.getline(buffer, LEN), !ifs.eof()) {
		if (ifs.bad()) {
			gen_error(FATAL, __FILE__, __LINE__, "Error in reading file %s.",
				  fileName.c_str());
		} else {
			coor	pos;
			qd_int	idx, resseq;
			qd_real	occupancy, tempfactor;
			string 	recName, resName, atomName, altloc, chainId, icode, segid, element;
			try {
				parsePDBLine(buffer, pos, recName, 
					     resName, atomName, altloc, 
					     chainId, icode, segid, 
					     element, idx, resseq, 
					     occupancy, tempfactor);
			} catch (const std::invalid_argument & ia) {
				std::cerr << ia.what() << std::endl;
				continue;
			}
			if (recName == "ATOM  " || recName == "HETATM") {
				if (!(isProtein(resName) || isRNA(resName) || isDNA(resName)))  
					continue;
				if (altloc != " ") {
					if (altloc == "A")
						altloc = " ";
					else
						continue;
				}
				if (chainId[0] != prevChainId) {
					if (!chain.isEmpty()) {
						m.append(chain);
						chain.clear();
					}
					prevChainId = chainId[0];
				}
				AtomAttributes attr;
				if (env)  attr = getAtomAttributes(*env, resName, atomName);
				atom a = atom(pos, attr.vdwr, attr.charge, attr.ace, attr.type,
					      resseq, idx, icode[0], atomName.c_str(),
					      resName.c_str(), chainId.c_str(), altloc.c_str());
				if (occupancy == 0.0f)
					a.ace = 20.0f;
				chain.append(a);
			} else if (recName.find("TER") != std::string::npos) {
				if (!chain.isEmpty()) {
					m.append(chain);
					chain.clear();		
				}
			} else
				continue;
		}
	}

	if (!chain.isEmpty())
		m.append(chain);
	
	ifs.close();
	
	return m;	
}

void
writePDBFile(const string & fileName, const Mol & m, const qd_int mode)
{
	fstream fs;
	if (mode == 0)
		fs.open(fileName, std::fstream::in | std::fstream::out | std::fstream::trunc);
	else {
		fs.open(fileName, std::fstream::in | std::fstream::out | std::ofstream::ate);	
		fs.seekp(-7, std::ios_base::cur);
	}
	for (qd_uint i = 0; i < m.size(); i++) {
		Atoms a = m[i];
		for (qd_uint j = 0; j < a.size(); j++)
			fs << a[j];
		fs << "TER" << std::endl;
	}
	fs << "ENDMDL" << std::endl;
	fs.close();		
}

qd_uint
getNumAtoms(const Mol & m)
{
	qd_uint n = 0;
	for (qd_uint i = 0; i < m.size(); i++) {
		n += m[i].size();
	}
	return n;
}

void
setChainId(Mol & m, const char id)
{
	FOR_EACH_ATOM_BEGIN(m, a) {
		a.chainid[0] = id;
	} FOR_EACH_ATOM_END
}

void
addAtomsToMol(Mol & m, const atom & a)
{
	for (qd_uint i = 0; i < m.size(); i++) {
		Atoms & as = m[i];
		if (as[0].chainid[0] == a.chainid[0]) {
			as.append(a);
			return;
		}
	}
	Atoms nas;
	nas.append(a);
	m.append(nas);
}

void
joinMols(Mol & m, const Mol & n)
{
	for (qd_uint i = 0; i < n.size(); i++)
		m.append(n[i]);
}
