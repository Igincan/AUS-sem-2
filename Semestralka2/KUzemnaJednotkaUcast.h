#pragma once

#include "KriteriumUzemnejJednotky.h"
#include "Obec.h"

class KUzemnaJednotkaUcast : public KriteriumUzemnejJednotky<double>
{
public:

	double operator()(UzemnaJednotka* objekt) override;

private:

	/// <param name="pocetZapisanych"> Vystupny parameter </param>
	/// <param name="pocetZucastnenych"> Vystupny parameter </param>
	void zrataj(UzemnaJednotka* UJ, int& pocetZapisanych, int& pocetZucastnenych);

};

