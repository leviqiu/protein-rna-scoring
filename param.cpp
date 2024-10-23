#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <genericerror.hpp>
#include <param.hpp>

class AtomParaNode {
	friend class ResidueParaNode;
	friend class Param;
	string	atomName;
	qd_real	vdwr;
	qd_real	ace;
	qd_real	charge;
	qd_int	type;
	AtomParaNode();
};

AtomParaNode::AtomParaNode()
{
	atomName = string("void");
	vdwr = 0.0f;
	ace = 0.0f;
	charge = 0.0f;
	type = -1;
}

class ResidueParaNode {
	friend class Param;
	string			residueName;
	vector<AtomParaNode>	atomNodes;
	ResidueParaNode();
};

ResidueParaNode::ResidueParaNode()
{
	residueName = string("void");
	atomNodes = vector<AtomParaNode>();
}

AtomAttributes::AtomAttributes(const qd_real Vdwr,
			       const qd_real Ace,
			       const qd_real Charge,
			       const qd_int  Type)
{
	vdwr = Vdwr;
	ace = Ace;
	charge = Charge;
	type = Type;
}

AtomAttributes::AtomAttributes(const AtomAttributes & a)
{
	vdwr = a.vdwr;
	ace = a.ace;
	charge = a.charge;
	type = a.type;
}

AtomAttributes & AtomAttributes::operator=(const AtomAttributes & a)
{
	vdwr = a.vdwr;
	ace = a.ace;
	charge = a.charge;
	type = a.type;
	return *this;
}

void
Param::createSet()
{
	qd_uint			firstNode = 1;			
	string			line, sub, cur_residue("");
	ifstream		fin(paraFileName.c_str(), ifstream::in);
	ResidueParaNode		rnode;
	vector<ResidueParaNode>	*rp = new vector<ResidueParaNode>;

	if (!fin.is_open()) {
		std::cout << "Can't open file " << paraFileName;
		std::cout << ", failed to create the param object." << endl;
		std::cout << "The program is terminated." << endl;
		exit(-1);
	}

	while (getline(fin, line)) {
		if (line[0] == '#' && line[1] == '#') // the first line is comment line;
			continue;
		size_t b, e;
		e = line.find_first_of('\t', 0);
		sub = line.substr(0, e);
		if (sub.compare(cur_residue)) {	// if it is a new residue;
			cur_residue = sub;
			if (firstNode) {
				firstNode = 0;
			} else {
				rp->push_back(rnode);
			}
			rnode.residueName = sub;
			rnode.atomNodes.clear();
		}
		AtomParaNode	anode;
		b = e + 1;
		e = line.find_first_of('\t', b);
		anode.atomName = line.substr(b, e - b);
		b = e + 1;
		e = line.find_first_of('\t', b);				
		anode.vdwr = atof(line.substr(b, e - b).c_str());
		b = e + 1;
		e = line.find_first_of('\t', b);
		anode.type = atoi(line.substr(b, e - b).c_str());
		b = e + 1;
		e = line.find_first_of('\t', b);
		anode.ace = atof(line.substr(b, e - b).c_str());
		b = e + 1;
//		e = line.find_first_of("\t\n", b);
//		anode.charge = atof(line.substr(b, e - b).c_str());
		anode.charge = atof(line.substr(b, string::npos).c_str());
		rnode.atomNodes.push_back(anode);
	}
	
	fin.close();
	vdwrset = reinterpret_cast<void*>(rp);
}

Param::Param(const string & fileName)
{
	paraFileName = fileName;
	createSet();
}

Param::Param()
{
	paraFileName = string("./vdwr.dat");
	createSet();
}

Param::Param(const Param & param)
{
	paraFileName = param.paraFileName;
	vector<ResidueParaNode> *rp = reinterpret_cast<vector<ResidueParaNode>* >(param.vdwrset);
	vector<ResidueParaNode> *newrp = new vector<ResidueParaNode>;
	for (size_t i = 0; i < rp->size(); i++)
		newrp->push_back((*rp)[i]); 
	vdwrset = reinterpret_cast<void*>(newrp);
}

Param & Param::operator=(const Param & param)
{
	paraFileName = param.paraFileName;
	vector<ResidueParaNode> *rp = reinterpret_cast<vector<ResidueParaNode>* >(vdwrset);
	rp->~vector<ResidueParaNode>();
	rp = reinterpret_cast<vector<ResidueParaNode>* >(param.vdwrset); 
	vector<ResidueParaNode> *newrp = new vector<ResidueParaNode>; 
	for (size_t i = 0; i < rp->size(); i++)
		newrp->push_back((*rp)[i]);
	vdwrset = reinterpret_cast<void*>(newrp);
	return *this;
}

Param::~Param()
{
	vector<ResidueParaNode> *rp = reinterpret_cast<vector<ResidueParaNode>* >(vdwrset);
	rp->~vector<ResidueParaNode>();	
}

bool
Param::areNamesTheSame(string name1, string name2) const
{
	size_t	b, e;

	b = name1.find_first_not_of(' ');
	if (b != string::npos)
		name1.erase(0, b);
	e = name1.find_first_of(' ');
	if (e != string::npos)
		name1.resize(e);		

	b = name2.find_first_not_of(' ');
	if (b != string::npos)
		name2.erase(0, b);
	e = name2.find_first_of(' ');
	if (e != string::npos)
		name2.resize(e);

	return (name1.compare(name2) == 0);
}

int
Param::getAtomData(const string & resname, const string & atomname, qd_real *vdwr, qd_real *ace, qd_real *charge, qd_int *type) const
{
	vector<ResidueParaNode>	*rp = reinterpret_cast< vector<ResidueParaNode>* >(vdwrset);
	if (rp->size() == 0)
		gen_error(FATAL, __FILE__, __LINE__,
			  "No parameter is loaded.");

	for (vector<ResidueParaNode>::iterator it = rp->begin(); it != rp->end(); ++it) {
		if (areNamesTheSame(resname, (*it).residueName)) {
			for (vector<AtomParaNode>::iterator ait = (*it).atomNodes.begin(); ait != (*it).atomNodes.end(); ++ait) {
				if (areNamesTheSame(atomname, (*ait).atomName)) {
					if (vdwr)
						*vdwr = (*ait).vdwr;
					if (ace)
						*ace = (*ait).ace;
					if (charge)
						*charge = (*ait).charge;
					if (type)
						*type = (*ait).type;
					return 1;
				}
			}
		}
	}
	return 0;
}

AtomAttributes
getAtomAttributes(const Dock_env & env, const string & resName, const string & atomName)
{
	qd_int	type;
	qd_real	vdwr, ace, charge;
	if (env.getAtomData(resName, atomName, &vdwr, &ace, &charge, &type)) {
		AtomAttributes attr = AtomAttributes(vdwr, ace, charge, type);
		return attr;
	} else { 
		AtomAttributes attr = AtomAttributes(0.0f, 0.0f, 0.0f, -1);
		return attr;
	}
}

bool
areAtomAttributesValid(const AtomAttributes & attr)
{
	if (attr.vdwr > 0.0f && attr.type >= 0)
		return true;
	else
		return false;
}
