#ifndef _SCORE_H
#define _SCORE_H

#include <qdock.hpp>
#include <pdb.hpp>
#include <cube.hpp>

qd_real
cal_score(const myBox &, const myBox &);

void
getBoxSize(const Mol&,
	   const Mol&,
	   qd_real&,
	   qd_real&,
	   qd_real&,
	   qd_real&,
	   qd_real&,
	   qd_real&);

myBox
fillMyBox(const Mol&,
	  qd_real,
	  qd_real,
	  qd_real,
	  qd_real,
	  qd_real,
	  qd_real);

qd_real
getScore(const Mol&, const Mol&);

#endif /*_SCORE_H*/
