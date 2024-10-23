#include <iostream>
#include <cmath>
#include <qdock.hpp>
#include <pdb.hpp>
#include <cube.hpp>
#include <ITScorePP.hpp>
#include <ITScorePR.hpp>
#include <genericerror.hpp>

qd_real
getDistance(const point & p1, const point & p2)
{
	return sqrt((p1._x - p2._x) * (p1._x - p2._x)
		  + (p1._y - p2._y) * (p1._y - p2._y)
		  + (p1._z - p2._z) * (p1._z - p2._z));
}

static qd_real
cal_score_pair(const point & p1, const point & p2)
{
        const qd_real pmf_d = 0.2f;
        qd_int     t1 = p1.getAtomType() - 1, t2 = p2.getAtomType() - 1;
        qd_int     r1 = p1.getResType(), r2 = p2.getResType();
        if (t1 < 0 || t2 < 0)
                return 0.0f;
        qd_uint idx = (qd_uint)floor(getDistance(p1, p2) / pmf_d);
	if (r1 == 0 && r2 == 0) { // protein -- protein
		if (idx > 75)
			return 0.0f;
		else
			return vvr_pmf[t1 * 22 + t2][idx];
	} else if (r1 == 0 && r2 == 1) { // protein -- RNA
                if (idx > 75)
                        return 0.0f;
                else
                        return pr_vvr_pmf[t1 * 12 + t2][idx];
        } else if (r1 == 1 && r2 == 0) { // RNA -- protein
                if (idx > 75)
                        return 0.0f;
                else
                        return pr_vvr_pmf[t2 * 12 + t1][idx];
        } else
                return 0.0f;
}

qd_real
cal_score(const myBox & recBox, const myBox & ligBox)
{
        qd_real score = 0.0f;
        for (qd_uint i = 0; i < ligBox.size(); i++) {
                qd_uint lsize = ligBox[i].size();
                if (lsize > 0) {
                        std::vector<qd_uint> nghbs = ligBox.neighbors(i);
                        for (qd_uint j = 0; j < nghbs.size(); j++) {
                                qd_uint k = nghbs[j];
                                qd_uint rsize = recBox[k].size();
                                if (rsize > 0) {
                                        qd_real subscore = 0.0f;
                                        for (qd_uint m = 0; m < lsize; m++)
                                                for (qd_uint n = 0; n < rsize; n++)
                                                        subscore += cal_score_pair(recBox[k][n],
                                                                                   ligBox[i][m]);
                                        score += subscore;
                                }
                        }
                }
        }
        return score;
}

void
getBoxSize(const Mol & m1, const Mol & m2,
	   qd_real & xmin, qd_real & xmax,
	   qd_real & ymin, qd_real & ymax,
	   qd_real & zmin, qd_real & zmax)
{
	qd_real m1_xmin = 0.0f, m1_xmax = 0.0f, 
		m1_ymin = 0.0f, m1_ymax = 0.0f, 
		m1_zmin = 0.0f, m1_zmax = 0.0f;
	qd_real m2_xmin = 0.0f, m2_xmax = 0.0f, 
		m2_ymin = 0.0f, m2_ymax = 0.0f, 
		m2_zmin = 0.0f, m2_zmax = 0.0f;
	std::vector<point> m1Atoms, m2Atoms;

	createList(m1, m1Atoms);
	createList(m2, m2Atoms);
	minMax(m1Atoms, m1_xmin, m1_xmax, m1_ymin, m1_ymax, m1_zmin, m1_zmax);
	minMax(m2Atoms, m2_xmin, m2_xmax, m2_ymin, m2_ymax, m2_zmin, m2_zmax);

	xmin = m1_xmin > m2_xmin ? m2_xmin : m1_xmin;
	xmax = m1_xmax > m2_xmax ? m1_xmax : m2_xmax;
	ymin = m1_ymin > m2_ymin ? m2_ymin : m1_ymin;
	ymax = m1_ymax > m2_ymax ? m1_ymax : m2_ymax;
	zmin = m1_zmin > m2_zmin ? m2_zmin : m1_zmin;
	zmax = m1_zmax > m2_zmax ? m1_zmax : m2_zmax;
}

myBox
fillMyBox(const Mol & m,
	  qd_real xmin, qd_real xmax,
	  qd_real ymin, qd_real ymax,
	  qd_real zmin, qd_real zmax)
{
	myBox b(xmin, xmax, ymin, ymax, zmin, zmax, 15.2f);
	FOR_EACH_ATOM_CONST_BEGIN(m, a) {
		qd_real	x = a.pos.x,
			y = a.pos.y,
			z = a.pos.z;
		qd_int	t = a.type, r;
		string resname = a.resname;
		if (isProtein(resname))
			r = 0;
		else if (isRNA(resname))
			r = 1;
		else if (isDNA(resname))
			r = 2;
		else
			r = -1;
		point p(x, y, z, t, r);
		qd_uint k = b.getCubeIndex(x, y, z);
		b[k].addPoint(p);
	} FOR_EACH_ATOM_CONST_END
	return b;
}

qd_real
getScore(const Mol & m1, const Mol & m2)
{
	qd_real	xmin, xmax, ymin, ymax, zmin, zmax;
	getBoxSize(m1, m2, xmin, xmax, ymin, ymax, zmin, zmax);
	return cal_score(fillMyBox(m1, xmin, xmax, ymin, ymax, zmin, zmax),
			 fillMyBox(m2, xmin, xmax, ymin, ymax, zmin, zmax));
}
