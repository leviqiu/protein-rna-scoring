#ifndef _PARAM_H
#define	_PARAM_H

#include <string>
#include <qdock.hpp>
using namespace std;

struct AtomAttributes
{
        qd_real vdwr;
        qd_real ace;
        qd_real charge;
        qd_int 	type;
	AtomAttributes(const qd_real Vdwr = 0.0f,
		       const qd_real Ace = 0.0f,
		       const qd_real Charge = 0.0f,
		       const qd_int  Type = -1);
	AtomAttributes(const AtomAttributes & a);
	AtomAttributes & operator=(const AtomAttributes & a);
};

class Param
{
private:
	string	paraFileName;
	void	*vdwrset;
	void createSet();
	bool areNamesTheSame(string name1, string name2) const;
	qd_int getAtomData(const string & resName, const string & atomName, qd_real *vdwr, qd_real *ace, qd_real *charge, qd_int *type) const;
public:
	Param();
	Param(const string & fileName);
	Param(const Param & param);
	Param & operator=(const Param & param);
	virtual ~Param();
	friend AtomAttributes getAtomAttributes(const Param & env, const string & resName, const string & atomName);
};

typedef	Param	Dock_env;

AtomAttributes
getAtomAttributes(const Dock_env & env, const string & resName, const string & atomName);

bool
areAtomAttributesValid(const AtomAttributes & attr);

#endif /*_PARAM_H*/
