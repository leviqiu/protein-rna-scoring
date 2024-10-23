#include <iostream>
#include <qdock.hpp>
#include <particleList.hpp>
#include <pdb.hpp>
#include <param.hpp>
#include <score.hpp>

int 
main(int argc,char *argv[])
{
	Dock_env env;
	Mol rec = readPDBFile(argv[1], &env),
	    lig = readPDBFile(argv[2], &env);
	std::cout << getScore(rec, lig) << std::endl;

	return 0;
}
