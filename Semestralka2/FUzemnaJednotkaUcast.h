#pragma once

#include "FilterVelkeFi.h"
#include "UzemnaJednotka.h"
#include "KUzemnaJednotkaUcast.h"

template<typename K>
class FUzemnaJednotkaUcast : public FilterVelkeFi<double, UzemnaJednotka, K>
{
public:

	FUzemnaJednotkaUcast(double alpha, double beta);
	~FUzemnaJednotkaUcast();

};

template<typename K>
FUzemnaJednotkaUcast<K>::FUzemnaJednotkaUcast(double alpha, double beta) :
FilterVelkeFi<double, UzemnaJednotka, K>(new KUzemnaJednotkaUcast(), alpha, beta)
{
}

template<typename K>
FUzemnaJednotkaUcast<K>::~FUzemnaJednotkaUcast()
{
	delete this->kriterium_;
}

