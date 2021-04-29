#pragma once

#include "KriteriumUzemnejJednotky.h"
#include "Obec.h"

class KUzemnaJednotkaVolici : public KriteriumUzemnejJednotky<int>
{
public:

	int operator()(UzemnaJednotka* objekt) override;

private:

	/// <param name="pocetZapisanych"> Vystupny parameter </param>
	void zrataj(UzemnaJednotka* UJ, int& pocetZapisanych);

};

