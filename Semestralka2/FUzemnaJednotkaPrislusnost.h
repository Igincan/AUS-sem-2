#pragma once

#include "FilterMaleFi.h"
#include "UzemnaJednotka.h"
#include "KUzemnaJednotkaPrislusnost.h"

template<typename K>
class FUzemnaJednotkaPrislusnost : public FilterMaleFi<bool, UzemnaJednotka, K>
{
public:

	FUzemnaJednotkaPrislusnost(bool alpha, UzemnaJednotka* vyssiCelok);
	~FUzemnaJednotkaPrislusnost();

};

template<typename K>
FUzemnaJednotkaPrislusnost<K>::FUzemnaJednotkaPrislusnost(bool alpha, UzemnaJednotka* vyssiCelok) :
FilterMaleFi<bool, UzemnaJednotka, K>(new KUzemnaJednotkaPrislusnost(vyssiCelok), alpha)
{
}

template<typename K>
FUzemnaJednotkaPrislusnost<K>::~FUzemnaJednotkaPrislusnost()
{
	delete this->kriterium_;
}

