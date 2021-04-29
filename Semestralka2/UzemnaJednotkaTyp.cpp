#include "KUzemnaJednotkaTyp.h"

TypUzemnejJednotky KUzemnaJednotkaTyp::operator()(UzemnaJednotka* objekt)
{
	return objekt->getTypUzemnejJednotky();
}
