#include "KUzemnaJednotkaPrislusnost.h"

KUzemnaJednotkaPrislusnost::KUzemnaJednotkaPrislusnost(UzemnaJednotka* vyssiCelok) :
vyssiCelok_(vyssiCelok)
{
}

bool KUzemnaJednotkaPrislusnost::operator()(UzemnaJednotka* objekt)
{
	while ((objekt = objekt->getPatriDo()) != nullptr)
	{
		if (objekt == vyssiCelok_)
		{
			return true;
		}
	}
	return false;
}

