#pragma once

#include "KriteriumUzemnejJednotky.h"
#include "Obec.h"
#include "SposobOdovzdania.h"

class KUzemnaJednotkaOdovzdaneObalky : public KriteriumUzemnejJednotky<int>
{
public:

	KUzemnaJednotkaOdovzdaneObalky(SposobOdovzdania sposobOdovzdania);

	int operator()(UzemnaJednotka* objekt) override;

private:

	/// <param name="pocetOdovzdanychObalok"> Vystupny parameter </param>
	void zrataj(UzemnaJednotka* UJ, int& pocetOdovzdanychObalok);

	SposobOdovzdania sposobOdovzdania_;

};

