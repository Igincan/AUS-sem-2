#pragma once

#include "KriteriumUzemnejJednotky.h"
#include "Obec.h"

class KUzemnaJednotkaPodielPlatnychHlasov : public KriteriumUzemnejJednotky<double>
{
public:

	virtual double operator()(UzemnaJednotka* objekt) override;

private:

	/// <param name="pocetZapisanych"> Vystupny parameter </param>
	/// <param name="pocetZucastnenych"> Vystupny parameter </param>
	void zrataj(UzemnaJednotka* UJ, int& pocetZucastnenych, int& pocetPlatnychSpolu);

};

