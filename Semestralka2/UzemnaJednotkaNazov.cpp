#include "KUzemnaJednotkaNazov.h"

std::string KUzemnaJednotkaNazov::operator()(UzemnaJednotka* objekt)
{
	return objekt->getNazov();
}
