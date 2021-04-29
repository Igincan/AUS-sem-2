#include "KUzemnaJednotkaPodielPlatnychHlasov.h"

double KUzemnaJednotkaPodielPlatnychHlasov::operator()(UzemnaJednotka* objekt)
{
	int pocetZucastnenych = 0;
	int pocetPlatnychSpolu = 0;

	zrataj(objekt, pocetZucastnenych, pocetPlatnychSpolu);

	if (pocetZucastnenych > 0)
	{
		return (static_cast<double>(pocetPlatnychSpolu) / pocetZucastnenych) * 100;
	}
	else
	{
		return -1;
	}
}

void KUzemnaJednotkaPodielPlatnychHlasov::zrataj(UzemnaJednotka* UJ, int& pocetZucastnenych, int& pocetPlatnychSpolu)
{
	if (UJ->getTypUzemnejJednotky() == TypUzemnejJednotky::OBEC)
	{
		Obec* obec = dynamic_cast<Obec*>(UJ);
		for (int i = 1; i <= obec->getPocetOkrskov(); i++)
		{
			pocetZucastnenych += obec->getVolebnaUcastOkrsku(i)->pocetZucastnenych_;
			pocetPlatnychSpolu += obec->getVolebnaUcastOkrsku(i)->pocetPlatnychSpolu_;
		}
	}
	else
	{
		for (auto item : *UJ->getPatriaDonho())
		{
			zrataj(item->accessData(), pocetZucastnenych, pocetPlatnychSpolu);
		}
	}
}
