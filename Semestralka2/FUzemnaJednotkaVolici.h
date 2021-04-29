#pragma once

#include "FilterVelkeFi.h"
#include "UzemnaJednotka.h"
#include "KUzemnaJednotkaVolici.h"

template<typename K>
class FUzemnaJednotkaVolici : public FilterVelkeFi<int, UzemnaJednotka, K>
{
public:

	FUzemnaJednotkaVolici(int alpha, int beta);
	~FUzemnaJednotkaVolici();

};

template<typename K>
inline FUzemnaJednotkaVolici<K>::FUzemnaJednotkaVolici(int alpha, int beta) :
FilterVelkeFi<int, UzemnaJednotka, K>(new KUzemnaJednotkaVolici(), alpha, beta)
{
}

template<typename K>
inline FUzemnaJednotkaVolici<K>::~FUzemnaJednotkaVolici()
{
	delete this->kriterium_;
}
