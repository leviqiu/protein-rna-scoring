#ifndef _CUBE_H
#define _CUBE_H
#include <cstdlib>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <particleList.hpp>
#include <pdb.hpp>

class point {
	float	_x;
	float	_y;
	float	_z;
	int	_t;   // atom type;
	int	_prd; // 0 for protein; 1 for RNA; 2 for DNA;
public:
	point(float x = 0.0f, float y = 0.0f, float z = 0.0f, int t = -1, int prd = -1) :
		_x(x), _y(y), _z(z), _t(t), _prd(prd) {};
	int getAtomType() const {return _t;};
	int getResType() const {return _prd;};
	void setType(int type) {_t = type;};
	void setX(float x) {_x = x;};
	void setY(float y) {_y = y;};
	void setZ(float z) {_z = z;};
	float getX() const {return _x;};
	float getY() const {return _y;};
	float getZ() const {return _z;};
	friend float getDistance(const point & p1, const point & p2);
};

template<typename U, template<typename, typename> class T = std::vector>
class cube {
	T<point,U> pts;
	unsigned n;
public:
	cube() : pts(), n(0) {};
	~cube() {};
	int size() const {return n;};
	cube & addPoint(const point & pt) {
		pts.push_back(pt);
		n++;
		return *this;
	};
	const point & operator[](unsigned i) const {
		return pts[i];
	};
};

template<typename U, typename W, template<typename, typename> class T = std::vector>
class box {
	float		_xl;
	float		_xu;
	float		_yl;
	float		_yu;
	float		_zl;
	float		_zu;
	float		_len;
	unsigned 	dimx;
	unsigned	dimy;
	unsigned	dimz;
	T<U,W> 	cubes;
public:
	box(float xl, float xu, float yl, float yu, float zl, float zu, float d) :
		_xl(xl), _xu(xu), _yl(yl), _yu(yu), _zl(zl), _zu(zu), _len(d) {
		if ((_xl >= _xu) || (_yl >= _yu) || (_zl >= _zu))
			throw std::invalid_argument("lower bound value must be"
						    "less than the upper bound value.");
		if (_len <= 0.0f)
			throw std::invalid_argument("size of a cube must be positive.");
		dimx = (unsigned)ceil((_xu - _xl) / _len) + 1;
		dimy = (unsigned)ceil((_yu - _yl) / _len) + 1;
		dimz = (unsigned)ceil((_zu - _zl) / _len) + 1;
		cubes = T<U,W>(dimx * dimy * dimz);
	}

	~box() {};

	unsigned getDimX() const {return dimx;};
	unsigned getDimY() const {return dimy;};
	unsigned getDimZ() const {return dimz;};

	unsigned size() const {
		return cubes.size();
	};

	unsigned getCubeIndex(float x, float y, float z) const {
		if ((x < _xl || x > _xu) ||
		    (y < _yl || y > _yu) ||
		    (z < _zl || z > _zu))
			throw std::invalid_argument("coordinates exceed limits of box.");
		unsigned xi = (unsigned)floor((x - _xl) / _len),
		    	 yi = (unsigned)floor((y - _yl) / _len),
		    	 zi = (unsigned)floor((z - _zl) / _len);
		return xi * dimy * dimz + yi * dimz + zi;
	};

	T<unsigned, std::allocator<unsigned> > neighbors(unsigned i) const {
		if (i >= cubes.size())
			throw std::out_of_range("The value of i for box.neighors(i) exceeds" 
						"the number of cubes the box contains");
		double	intpart;
		modf((double)i / (double)(dimy * dimz), &intpart);
		int xi = (int)intpart;
		i -= xi * dimy * dimz;
		modf((double)i / (double)dimz, &intpart);
		int yi = (int)intpart;
		i -= yi * dimz;
		int zi = i;
		T<unsigned, std::allocator<unsigned> > nghbs;
		for (int k = xi - 1; k <= xi + 1; k++) {
			if (k < 0 || k >= (int)dimx)
				continue;
			for (int l = yi - 1; l <= yi + 1; l++) {
				if (l < 0 || l >= (int)dimy)
					continue;
				for (int m = zi - 1; m <= zi + 1; m++) {
					if (m < 0 || m >= (int)dimz)
						continue;
					nghbs.push_back((unsigned)k * dimy * dimz + 
							(unsigned)l * dimz + 
							(unsigned)m);
				}
			}
		}
		return nghbs;
	};

	const U & operator[](unsigned i) const {
		return cubes[i];
	};

	U & operator[](unsigned i) {
		return cubes[i];
	};
};

template<typename U, typename W, template<typename, typename> class L>
void createList(const Mol & m, L<U,W> & l)
{
	FOR_EACH_ATOM_CONST_BEGIN(m, a) {
		l.push_back(U(a.pos.x, a.pos.y, a.pos.z, a.type));
	} FOR_EACH_ATOM_CONST_END
}

template<typename U, typename W, template<typename, typename> class L>
void minMax(L<U,W> & l,
	    float & xmin, float & xmax,
	    float & ymin, float & ymax,
	    float & zmin, float & zmax)
{
	for (unsigned i = 0; i < l.size(); i++) {
		if (i == 0) {
			xmin = l[i].getX();
			xmax = xmin;
			ymin = l[i].getY();
			ymax = ymin;
			zmin = l[i].getZ();
			zmax = zmin;
		} else {
			if (xmin > l[i].getX())
				xmin = l[i].getX();
			else if (xmax < l[i].getX())
				xmax = l[i].getX();
			if (ymin > l[i].getY())
				ymin = l[i].getY();
			else if (ymax < l[i].getY())
				ymax = l[i].getY();
			if (zmin > l[i].getZ())
				zmin = l[i].getZ();
			else if (zmax < l[i].getZ())
				zmax = l[i].getZ();
		}
	}
}

template class cube<std::allocator<point>, std::vector>;
typedef cube<std::allocator<point>, std::vector> myCube;
template class box<myCube, std::allocator<myCube>, std::vector>;
typedef box<myCube, std::allocator<myCube>, std::vector> myBox;
#endif /*_CUBE_H*/
