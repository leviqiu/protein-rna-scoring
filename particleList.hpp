#ifndef _PARTICLE_LIST_H
#define _PARTICLE_LIST_H

#include <fstream>
#include <vector>
#include <qdock.hpp>

struct coor {
	qd_real	x;
	qd_real	y;
	qd_real	z;
	coor(const qd_real X = 0.0f, 
	     const qd_real Y = 0.0f, 
	     const qd_real Z = 0.0f) : x(X), y(Y), z(Z) {};
	coor & operator+(const coor & c);
};

struct atom {
	coor	pos;
	qd_real	vdwr;
	qd_real	charge;
	qd_real	ace;
	qd_int	type;
	qd_int	resseq;
	qd_int	idx;
	char	icode;
	char	atomname[5];
	char	resname[4];
	char	chainid[2];
	char	altloc[2];
	char	padding[14];
	atom(const coor Pos = {0.0f, 0.0f, 0.0f},
	     const qd_real Vdwr = 0.0f,
	     const qd_real Charge = 0.0f,
	     const qd_real Ace = 0.0f,
	     const qd_int  Type = -1,
	     const qd_int  Resseq = 0,
	     const qd_int  Idx = 0,
	     const char    Icode = ' ',
	     const char   *AtomName = "    ",
	     const char   *ResName = "   ",
	     const char   *ChainId = "  ",
	     const char   *Altloc = "  ");
	atom(const atom & a);
	atom & operator=(const atom & a);
	virtual ~atom() {};
	friend std::ostream & operator<<(std::ostream & os, const atom & a);
	friend std::ofstream & operator<<(std::ofstream & ofs, const atom & a);
};

template<typename T>
class QDList {
	std::vector<T>	l;
public:
	QDList()  {};
	QDList(const QDList & q) {
		l = q.l;
	};
	~QDList() {};
	QDList & operator=(const QDList & q) {
		if (this == &q)
			return *this;
		l = q.l;
		return *this;
	};
	QDList & append(T t) {
		l.push_back(t);
		return *this;
	};
	QDList & remove(unsigned position) {
		l.erase(l.begin() + position);
		return *this;		
	};
	QDList & insert(unsigned position, T & t) {
		l.insert(l.begin() + position, t);
		return *this;
	};
	T & operator[](unsigned position) {
		return l[position];
	};
	const T & operator[](unsigned position) const {
		return l[position];
	};
	size_t size() const {return l.size();};
	bool isEmpty() const {return l.size() == 0;};
	QDList & clear() {
		l.clear();
		return *this;
	};
};

template class QDList<atom>;
typedef class QDList<atom> Atoms;

template class QDList<Atoms>;
typedef class QDList<Atoms> Mol;

#endif /*_PARTICLE_LIST_H*/
