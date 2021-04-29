#pragma once

#include "FilterMaleFi.h"
#include "UzemnaJednotka.h"
#include "KUzemnaJednotkaNazov.h"

template<typename K>
class FUzemnaJednotkaNazov : public FilterMaleFi<std::string, UzemnaJednotka, K>
{
public:

	FUzemnaJednotkaNazov(std::string nazov);
	~FUzemnaJednotkaNazov();

};

template<typename K>
FUzemnaJednotkaNazov<K>::FUzemnaJednotkaNazov(std::string nazov) :
FilterMaleFi<std::string, UzemnaJednotka, K>(new KUzemnaJednotkaNazov(), nazov)
{
}

template<typename K>
FUzemnaJednotkaNazov<K>::~FUzemnaJednotkaNazov()
{
	delete this->kriterium_;
}

