#pragma once

#include "FilterMaleFi.h"
#include "TypUzemnejJednotky.h"
#include "UzemnaJednotka.h"
#include "KUzemnaJednotkaTyp.h"

template<typename K>
class FUzemnaJednotkaTyp : public FilterMaleFi<TypUzemnejJednotky, UzemnaJednotka, K>
{
public:

	FUzemnaJednotkaTyp(TypUzemnejJednotky typ);
	~FUzemnaJednotkaTyp();

};

template<typename K>
FUzemnaJednotkaTyp<K>::FUzemnaJednotkaTyp(TypUzemnejJednotky typ) :
FilterMaleFi<TypUzemnejJednotky, UzemnaJednotka, K>(new KUzemnaJednotkaTyp(), typ)
{
}

template<typename K>
FUzemnaJednotkaTyp<K>::~FUzemnaJednotkaTyp()
{
	delete this->kriterium_;
}

