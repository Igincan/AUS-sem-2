#pragma once

#include "KriteriumUzemnejJednotky.h"
#include "Obec.h"

class KUzemnaJednotkaZucastneniVolici : public KriteriumUzemnejJednotky<int>
{
public:

	int operator()(UzemnaJednotka* objekt) override;

private:

	/// <param name="pocetZucastnenych"> Vystupny parameter </param>
	void zrataj(UzemnaJednotka* UJ, int& pocetZucastnenych);

};

